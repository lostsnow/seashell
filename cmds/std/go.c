#include <ansi.h>

inherit IH_CLEAN_UP;

// *INDENT-OFF*
nosave mapping default_dirs = ([
    "north":"北方",
    "south":"南方",
    "east":"东方",
    "west":"西方",
    "northup":"北边",
    "southup":"南边",
    "eastup":"东边",
    "westup":"西边",
    "northdown":"北边",
    "southdown":"南边",
    "eastdown":"东边",
    "westdown":"西边",
    "northeast":"东北",
    "northwest":"西北",
    "southeast":"东南",
    "southwest":"西南",
    "up":"上面",
    "down":"下面",
    "enter":"里面",
    "out":"外面",
]);

nosave mapping r_dirs = ([
    "north":"south",
    "south":"north",
    "east":"west",
    "west":"east",
    "northup":"southdown",
    "southup":"northdown",
    "eastup":"westdown",
    "westup":"eastdown",
    "northdown":"southup",
    "southdown":"northup",
    "eastdown":"westup",
    "westdown":"eastup",
    "northeast":"southwest",
    "northwest":"southeast",
    "southeast":"northwest",
    "southwest":"northeast",
    "up":"down",
    "down":"up",
    "enter":"out",
    "out":"enter",
]);
// *INDENT-ON*

nosave mapping empty_mapping = ([]);

int main(object me, string arg)
{
    string dest, dir, msg_in, msg_out, room_id;
    object env, obj;
    mapping exits;

    if (!arg) {
        return notify_fail("你要往哪个方向走？\n");
    }

    if (!objectp(me)) {
        return 1;
    }

    // TODO: 负重
    // TODO: busy

    env = environment(me);

    if (!env) {
        return notify_fail("你哪里也去不了。\n");
    }

    if (!mapp(exits = env->query_exits()) || undefinedp(exits[arg])) {
        if (query_verb() == "go") {
            return notify_fail("这个方向没有出路。\n");
        }

        return 0;
    }

    dest = exits[arg];

    if (!(obj = find_object(dest))) {
        if (!objectp(obj = load_object(dest))) {
            return notify_fail(sprintf("目标区域无法找到，无法向 %s 移动。\n", dest));
        }
    }

    if (!env->valid_leave(me, arg)) {
        return 1;
    }

    if (!undefinedp(default_dirs[arg])) {
        dir = default_dirs[arg];
    } else {
        if (stringp(room_id = env->query_room_id(arg))) {
            dir = room_id;
        } else {
            dir = arg;
        }
    }

    msg_out = me->short(1) + "往" + dir + "离开了。";
    message("vision", msg_out, env, ({me}));

    me->move(dest);

    msg_in = me->short(1) + "走了过来。";
    message("vision", msg_in, env, ({me}));

    return 1;
}

string query_reverse(string dir)
{
    if (undefinedp(r_dirs[dir])) {
        return 0;
    }

    return r_dirs[dir];
}

string query_chinese_dir(string dir)
{
    return default_dirs[dir];
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
    命令格式 : go <方向>

这个命令可以让你向指定的方向移动。
HELP;
// *INDENT-ON*
}
