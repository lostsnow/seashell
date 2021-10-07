// K_IH_ROOM

#include <inherit/room.h>

inherit IH_CLEAN_UP;
inherit IH_PROPERTY;
inherit IH_NAME;

protected mapping exits = ([]);
protected mapping doors;

void setup()
{
    if (query("chat_room")) {
        set("no_fight", 1);
    }

    seteuid(getuid());
    this_object()->reset();
}

mapping query_exits()
{
    return exits;
}

void set_exits(mapping ex)
{
    exits = ex;
}

string look_door(string dir)
{
    if (!mapp(doors) || undefinedp(doors[dir])) {
        return "你要看什么？\n";
    }

    if (doors[dir]["status"] & DOOR_CLOSED) {
        return "这个" + doors[dir]["name"] + "是关着的。\n";
    } else {
        return "这个" + doors[dir]["name"] + "是开着的。\n";
    }
}

varargs int open_door(string dir, int from_other_side)
{
    mapping exits;
    object ob;

    if (!mapp(doors) || undefinedp(doors[dir])) {
        return notify_fail("这个方向没有门。\n");
    }

    if (!(doors[dir]["status"] & DOOR_CLOSED)) {
        return notify_fail(doors[dir]["name"] + "已经是开着的了。\n");
    }

    exits = query_exits();

    if (!mapp(exits) || undefinedp(exits[dir])) {
        return notify_fail("这个方向没有出路。\n");
    }

    if (from_other_side) {
        message("vision", "有人从另一边将" + doors[dir]["name"] + "打开了。\n", this_object());
    } else if (objectp(ob = find_object(exits[dir]))) {
        if (!ob->open_door(doors[dir]["other_side_dir"], 1)) {
            return 0;
        }
    }

    doors[dir]["status"] &= (!DOOR_CLOSED);
    return 1;
}

varargs int close_door(string dir, int from_other_side)
{
    mapping exits;
    object ob;

    if (!mapp(doors) || undefinedp(doors[dir])) {
        return notify_fail("这个方向没有门。\n");
    }

    if ((doors[dir]["status"] & DOOR_CLOSED)) {
        return notify_fail(doors[dir]["name"] + "已经是关着的了。\n");
    }

    exits = query_exits();

    if (!mapp(exits) || undefinedp(exits[dir])) {
        return notify_fail("这个方向没有出路。\n");
    }

    if (from_other_side) {
        message("vision", "有人从另一边将" + doors[dir]["name"] + "关上了。\n", this_object());
    } else if (objectp(ob = find_object(exits[dir]))) {
        if (!ob->close_door(doors[dir]["other_side_dir"], 1)) {
            return 0;
        }
    }

    doors[dir]["status"] |= DOOR_CLOSED;
    return 1;
}

int check_door(string dir, mapping door)
{
    // If we have no responding door, assume it is correct.
    if (!mapp(doors) || undefinedp(doors[dir])) {
        return 1;
    }

    door["status"] = doors[dir]["status"];
    return 1;
}

varargs void create_door(string dir, mixed data, string other_side_dir, int status)
{
    mapping d, exits;
    object ob;

    exits = query_exits();

    if (!mapp(exits) || undefinedp(exits[dir])) {
        return notify_fail("这个方向没有出路。\n");
    }

    // Compact mode.
    if (stringp(data)) {
        d = allocate_mapping(4);
        d["name"] = data;
        d["id"] = ({ dir, data, "door" });
        d["other_side_dir"] = other_side_dir;
        d["status"] = status;
    } else if (mapp(data)) {
        d = data;
    } else {
        error("create_door: Invalid door data, string or mapping expected.\n");
    }

    if (objectp(ob = find_object(exits[dir]))) {
        if (!ob->check_door(other_side_dir, d)) {
            return;
        }
    }

    if (!mapp(doors)) {
        doors = ([ dir: d ]);
    } else {
        doors[dir] = d;
    }
}

mapping query_doors()
{
    return doors;
}

mixed query_door(string dir, string prop)
{
    if (!mapp(doors) || undefinedp(doors[dir])) {
        return 0;
    } else {
        return doors[dir][prop];
    }
}

int valid_leave(object me, string dir)
{
    if (mapp(doors) && !undefinedp(doors[dir])) {
        if (doors[dir]["status"] & DOOR_CLOSED) {
            return notify_fail("你必须先把" + doors[dir]["name"] + "打开！\n");
        }
    }

    return 1;
}
