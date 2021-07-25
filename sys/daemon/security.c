// SECURITY_D

#define WIZLIST_FILE CONFIG_DIR + WIZLIST_CFG

private nosave mapping wiz_level_map = ([]);

protected nosave string *wiz_levels = ({
    USER_LEVEL_NAME_PLAYER,
    USER_LEVEL_NAME_WIZARD,
    USER_LEVEL_NAME_ADMIN,
});

int restore();
string get_level(mixed ob);

void create()
{
    seteuid(getuid());
    restore();
}

void restore()
{
    string *wizlist, wiz_name, wiz_level;
    int i;

    // restore wizlist
    wizlist = separate_file(WIZLIST_FILE);
    wiz_level_map = allocate_mapping(sizeof(wizlist));

    for (i = 0; i < sizeof(wizlist); i++) {
        if (wizlist[i][0] == '#' || sscanf(wizlist[i], "%s %s", wiz_name, wiz_level) != 2) {
            continue;
        }

        wiz_level_map[wiz_name] = wiz_level;
    }
}

string *query_wizlist()
{
    return keys(wiz_level_map);
}

int get_wiz_level(mixed ob)
{
    return member_array(get_level(ob), wiz_levels);
}

// This function returns the level of an uid.
string get_level(mixed ob)
{
    string euid;

    if (objectp(ob)) {
        euid = geteuid(ob);

        if (!euid) {
            euid = getuid(ob);
        }
    } else if (stringp(ob)) {
        euid = ob;
    }

    if (!undefinedp(wiz_level_map[euid])) {
        return wiz_level_map[euid];
    } else if (member_array(euid, wiz_levels) != -1) {
        return euid;
    } else {
        return USER_LEVEL_NAME_PLAYER;
    }
}

int set_level(mixed ob, string level)
{
    string uid, *wiz, wizlist;
    int i;

    if (geteuid(previous_object()) != ROOT_UID) {
        return 0;
    }

    if (userp(ob))          {
        uid = getuid(ob);
    } else if (stringp(ob))    {
        uid = ob;
    } else {
        return 0;
    }

    if (level == "(player)") {
        map_delete(wiz_level_map, uid);
    } else {
        wiz_level_map[uid] = level;
    }

    wiz = keys(wiz_level_map);

    for (wizlist = "", i = 0; i < sizeof(wiz); i++) {
        wizlist += wiz[i] + " " + wiz_level_map[wiz[i]] + "\n";
    }

    rm(WIZLIST_FILE);
    write_file(WIZLIST_FILE, wizlist);
    log_time("security.log", capitalize(uid) + " become a " + level + "\n");
    return 1;
}
