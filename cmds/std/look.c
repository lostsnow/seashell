#include <ansi.h>

#define RETURN_RESULT 1

inherit IH_CLEAN_UP;

int look_room(object me, object env, int brief);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string look_all_inventory_of_room(object me, object env, int ret_str);

void create()
{
    seteuid(getuid());
}

int main(object me, string arg)
{
    int result;
    string objid, where;
    object obj, env;

    if (!arg) {
        result = look_room(me, environment(me), 0);
    } else {
        if (sscanf(arg, "%s of %s", objid, where) == 2) {
            if (where == "here") {
                obj = present(objid, environment(me));
            } else if (where == "me") {
                obj = present(objid, me);
            } else {
                env = present(where, environment(me));

                if (!objectp(env)) {
                    return notify_fail("你要看哪里的东西？\n");
                }

                obj = present(objid, env);
            }

            if (!obj) {
                return notify_fail("那里没有这样东西。\n");
            }
        }

        if (obj || (obj = present(arg, environment(me))) || (obj = present(arg, me))) {
            if (obj->is_character()) {
                result = look_living(me, obj);
            } else {
                result = look_item(me, obj);
            }
        } else {
            result = look_room_item(me, arg);
        }
    }

    return result;
}

void realtime_map(object me, object env)
{
    object room_obj;
    mapping exits;
    int i, pending;
    string map_room, map_room2, arrow;
    string *dirs;
    string placeholder = repeat_string(" ", 12);

    // *INDENT-OFF*
    mapping alldirs = ([
        "northwest" : placeholder,
        "north"     : placeholder,
        "northup"   : placeholder,
        "northeast" : placeholder,
        "west"      : placeholder,
        "east"      : placeholder,
        "southeast" : placeholder,
        "south"     : placeholder,
        "southwest" : placeholder,
        "southdown" : placeholder,
        "eastup"    : placeholder,
        "southup"   : placeholder,
        "northdown" : placeholder,
        "eastdown"  : placeholder,
        "westup"    : placeholder,
        "westdown"  : placeholder,
        "enter"     : placeholder,
        "out"       : placeholder,
        "up"        : placeholder,
        "down"      : placeholder,
        "left"      : placeholder,
        "right"     : placeholder,
    ]);
    // *INDENT-ON*

    if (mapp(exits = env->get_exits())) {
        dirs = keys(exits);

        for (i = 0; i < sizeof(dirs); i++) {
            if (!room_obj = find_object(exits[dirs[i]])) {
                room_obj = load_object(exits[dirs[i]]);
            }

            if (room_obj) {
                if (room_obj->short()) {
                    alldirs[dirs[i]] = room_obj->short();
                };
            }
        }

        arrow = "  ";
        map_room2 = alldirs["enter"];

        if (alldirs["enter"] != placeholder) {
            map_room2 = alldirs["enter"];
            arrow = HIR + "∧" + NOR;
        }

        if (alldirs["up"] != placeholder) {
            map_room2 = alldirs["up"];
            arrow = HIC + "〓" + NOR;
        }

        if (alldirs["northdown"] != placeholder) {
            map_room2 = alldirs["northdown"];
            arrow = "↓";
        }

        if (alldirs["northup"] != placeholder) {
            map_room2 = alldirs["northup"];
            arrow = "↑";
        }

        if (alldirs["north"] != placeholder) {
            map_room2 = alldirs["north"];
            arrow = "｜";
        }

        map_room = map_room2;

        printf("%22s  %|12s  %-12s\n",
            alldirs["northwest"], map_room, alldirs["northeast"]);

        printf("%24s%|12s%s\n",
            alldirs["northwest"] == placeholder ? "  " : "＼",
            arrow,
            alldirs["northeast"] == placeholder ? "  " : "／");

        arrow = "  ";
        map_room2 = alldirs["westdown"];

        if (map_room2 != placeholder) {
            arrow = "→";
        }

        if (alldirs["left"] != placeholder) {
            map_room2 = alldirs["left"];
            arrow = "〈";
        }

        if (alldirs["westup"] != placeholder) {
            map_room2 = alldirs["westup"];
            arrow = "←";
        }

        if (alldirs["west"] != placeholder) {
            map_room2 = alldirs["west"];
            arrow = "--";
        }

        printf("%22s%s", map_room2, arrow);
        map_room2 = env->short();
        map_room = HIG + map_room2 + NOR;

        pending = (12 - strwidth(map_room)) / 2;

        if (pending > 0) {
            if (arrow == "--") {
                printf(repeat_string("-", pending));
            } else {
                printf(repeat_string(arrow, pending/2));
                if (pending%2 == 1) {
                    printf(" ");
                }
            }
        }

        printf("%s", map_room);

        arrow = "  ";
        map_room2 = alldirs["eastup"];

        if (map_room2 != placeholder) {
            arrow = "→";
        }

        if (alldirs["right"] != placeholder) {
            map_room2 = alldirs["right"];
            arrow = "〉";
        }

        if (alldirs["eastdown"] != placeholder) {
            map_room2 = alldirs["eastdown"];
            arrow = "←";
        }

        if (alldirs["east"] != placeholder) {
            map_room2 = alldirs["east"];
            arrow = "--";
        }

        if (pending > 0) {
            if (arrow == "--") {
                printf(repeat_string("-", pending));
            } else {
                if (pending%2 == 1) {
                    printf(" ");
                }
                printf(repeat_string(arrow, pending/2));
            }
        }

        printf("%s%-12s\n", arrow, map_room2);

        arrow = "  ";
        map_room2 = alldirs["out"];

        if (alldirs["out"] != placeholder) {
            map_room2 = alldirs["out"];
            arrow = HIR + "∨" + NOR;
        }

        if (alldirs["down"] != placeholder) {
            map_room2 = alldirs["down"];
            arrow = HIC + "〓" + NOR;
        }

        if (alldirs["southdown"] != placeholder) {
            map_room2 = alldirs["southdown"];
            arrow = "↑";
        }

        if (alldirs["southup"] != placeholder) {
            map_room2 = alldirs["southup"];
            arrow = "↓";
        }

        if (alldirs["south"] != placeholder) {
            map_room2 = alldirs["south"];
            arrow = "｜";
        }

        map_room = map_room2;

        printf("%24s%|12s%-12s\n",
            alldirs["southwest"] == placeholder ? "  " : "／",
            arrow,
            alldirs["southeast"] == placeholder ? "  " : "＼");
        printf("%22s  %|12s  %-12s\n",
            alldirs["southwest"], map_room, alldirs["southeast"]);
    } else {
        map_room = HIG + env->short() + NOR;

        printf("%34s", map_room);
    }

    return;
}

int look_room(object me, object env, int brief)
{
    mapping exits;
    string str, *dirs;

    if (!env) {
        tell_object(me, "你的四周灰蒙蒙地一片，什么也没有。\n");
        return 1;
    }

    if (!brief) {
        str = sprintf(HIC + "%s" + NOR + "%s\n    %s" + NOR,
                env->short(), " - " + HIK + file_name(env) + NOR,
                env->long());
    } else {
        str = sprintf(HIC + "%s" + NOR + "%s\n" + NOR,
                env->short(), " - " + HIK + file_name(env) + NOR);
    }

    if (mapp(exits = env->get_exits())) {
        dirs = keys(exits);

        // @TODO: closed door

        if (sizeof(dirs) == 0) {
            str += "    这里没有任何明显的出路。\n";
        } else if (sizeof(dirs) == 1) {
            str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
        } else {
            str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
                    implode(dirs[0..sizeof(dirs) - 2], "、"),
                    dirs[sizeof(dirs) - 1]);
        }
    }

    if (!brief) {
        realtime_map(me, env);
    }

    str += look_all_inventory_of_room(me, env, RETURN_RESULT);
    tell_object(me, str);
    return 1;
}

string desc_of_objects(object *obs)
{
    int i;

    string str;
    mapping count;
    mapping unit;
    string short_name;
    string *dk;

    if (obs && sizeof(obs) > 0) {
        str = "";
        count = ([]);
        unit = ([]);

        for (i = 0; i < sizeof(obs); i++) {
            short_name = obs[i]->short();

            if (undefinedp(count[short_name])) {
                count[short_name] = 1;
                unit[short_name] = obs[i]->query("unit") ? obs[i]->query("unit") : "个";
            } else {
                count[short_name] += 1;
            }
        }

        dk = sort_array(keys(count), 1);

        for (i = 0; i < sizeof(dk); i++) {
            str += "  ";

            if (count[dk[i]] > 1) {
                str += count[dk[i]] + unit[dk[i]];
            }

            str += dk[i] + "\n";
        }

        return str;
    }

    return "";
}

string look_all_inventory_of_room(object me, object env, int ret_str)
{
    object *inv, *obs;
    string str;

    if (!env || !me) {
        return "";
    }

    str = "";

    inv = all_inventory(env);

    if (!sizeof(inv)) {
        return str;
    }

    obs = filter_array(inv, (: $(me) != $1 :));
    str += desc_of_objects(obs);

    if (!ret_str) {
        tell_object(me, str);
    }

    return str;
}

int look_item(object me, object obj)
{
    string str;
    str = obj->short();

    tell_object(me, str);
    return 1;
}

int look_living(object me, object obj)
{
    string str;
    str = obj->short();

    tell_object(me, str);
    return 1;
}

int look_room_item(object me, string arg)
{
    object env;
    mapping item, exits;

    if (!objectp(env = environment(me))) {
        return notify_fail("这里只有灰蒙蒙地一片，什么也没有。\n");
    }

    if (mapp(item = env->query("items")) && !undefinedp(item[arg])) {
        if (stringp(item[arg])) {
            tell_object(me, item[arg]);
        } else if (functionp(item[arg])) {
            tell_object(me, (string)(*item[arg])(me));
        }

        return 1;
    }

    if (mapp(exits = env->get_exits()) && !undefinedp(exits[arg])) {
        if (objectp(env = find_object(exits[arg]))) {
            look_room(me, env, 0);
        } else {
            call_other(exits[arg], "???");
            look_room(me, find_object(exits[arg]), 0);
        }

        return 1;
    }

    return notify_fail("你要看什么？\n");
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式: look [<环境>|<物品>|<生物>|<方向>]

这个命令让你查看你所在的环境、某件物品、生物、或是方向。如果在 look 命令后面
有参数，将先察看身上是否有该物品，如果没有则察看你所在的环境中是否有该物品或
人物。如果你身上的物品和你所在的环境有 ID 相同的物品，你可以指明
look ??? of me/here 以指明你想要察看自己身上的物品还是附近环境中的物品。
同时，如果使用命令 look ??? of <id> 可以看他人的装备或是亮出来的物品。
HELP;
// *INDENT-ON*
}
