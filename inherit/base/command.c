// K_IH_COMMAND

#include <inherit/property.h>
#include <inherit/name.h>
#include <inherit/command.h>

string *query_path();

nosave int enabled = 0;
mapping aliases;
// Let command path be static, thus we can make sure no one can get command
// path directly from restore_object().
nosave string *path;

// apply process_input
string process_input(string arg)
{
    string *args, cmd, arg_str;
    int i, j;

    if (mapp(aliases)) {
        if (!undefinedp(aliases[arg])) {
            return replace_string(aliases[arg], "$*", "");
        }

        if (sscanf(arg, "%s %s", cmd, arg_str) == 2 && ! undefinedp(aliases[cmd])) {
            cmd = replace_string(aliases[cmd], "$*", arg_str);
            args = explode(arg_str, " ");

            if ((j = sizeof(args))) {
                for (i = 0; i < j; i++) {
                    cmd = replace_string(cmd, "$" + (i + 1), args[i]);
                }
            }

            arg = cmd;
        }
    }

    return COMMAND_D->process_aliases(arg);
}

mapping query_alias()
{
    return aliases;
}

int set_alias(string verb, string replace)
{
    if (!replace) {
        if (mapp(aliases)) {
            map_delete(aliases, verb);
        }
    } else {
        if (!mapp(aliases)) {
            aliases = ([verb:replace]);
        } else if (sizeof(aliases) > MAX_ALIASES) {
            return notify_fail("您设定的别名太多了，请先删掉一些不常用的。\n");
        } else {
            aliases[verb] = replace;
        }
    }

    return 1;
}

string find_command(string verb)
{
    return COMMAND_D->find_command(verb, query_path());
}

nomask int command_hook(string arg)
{
    string verb, file;
    object me;
    me = this_object();
    verb = trim(query_verb());

    if (verb == "") {
        return 0;
    }

    if (!arg && (objectp(environment()) && stringp(environment()->query("exits/" + verb))) &&
        stringp(file = find_command("go")) && call_other(file, "main", me, verb)) {
        ;
    } else if (stringp(file = find_command(query_verb())) && call_other(file, "main", me, arg)) {
        ;
    } else {
        return 0;
    }

    return 1;
}

protected nomask void set_path(string *p)
{
    path = p;
}

string *query_path()
{
    return path;
}

nomask void enable_player_commands()
{
    object me = this_object();
    string *my_path;

    if (stringp(get_id())) {
        set_living_name(get_id());
    } else {
        set_living_name(name());
    }

    if (!enabled) {
        enable_commands();
        enabled = 1;
        add_action("command_hook", "", 1);
    }

    if (!me->is_player() && !interactive(me) && !me->is_chatter()) {
        my_path = CMD_PATH_NPC;
    } else {
        switch (SECURITY_D->get_level(me)) {
            case USER_LEVEL_NAME_ADMIN:
                my_path = CMD_PATH_ADM;
                enable_wizard();
                break;

            case USER_LEVEL_NAME_WIZARD:
                my_path = CMD_PATH_WIZ;
                enable_wizard();
                break;

            default:
                if (this_object()->is_in_prison()) {
                    my_path = CMD_PATH_PRISON;
                } else {
                    my_path = CMD_PATH_PLAYER;
                }
        }
    }

    // remove skill cmds & usr cmds
    if (me->is_chatter()) {
        my_path -= CMD_PATH_EXCLUDE_CHATTER;
    }

    set_path(my_path);
}

nomask void disable_player_commands(string type)
{
    set("disable_type", type);

    if (enabled) {
        disable_commands();
        enabled = 0;
    }
}
