// K_IH_ROOM

inherit IH_CLEAN_UP;
inherit IH_PROPERTY;
inherit IH_NAME;

mapping exits = ([]);

void setup()
{
    if (query("chat_room")) {
        set("no_fight", 1);
    }

    seteuid(getuid());
    this_object()->reset();
}

mapping get_exits() {
    return exits;
}

void set_exits(mapping ex) {
    exits = ex;
}
