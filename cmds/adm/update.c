#include <runtime_config.h>
#include <config.h>

inherit IH_CLEAN_UP;

string help(object me);

int main(object me, string arg)
{
    object obj;
    object *inv;
    string err;
    int i;

    if (!arg) {
        write(help(me));
        return 1;
    }

    if (arg[0] != '/') {
        arg = "/" + arg;
    }

    if (!sscanf(arg, "%*s.c")) {
        arg += ".c";
    }


    if (!file_exists(arg)) {
        return notify_fail("没有这个文件。\n");
    }

    if (obj = find_object(arg)) {
        if (environment(me) == obj) {
            if (file_name(obj) == VOID_OB) {
                return notify_fail("你不能在 VOID_OB 里重新编译 VOID_OB。\n");
            }

            inv = all_inventory(obj);
            i = sizeof(inv);

            while (i--) {
                if (inv[i]->is_player() || inv[i]->is_chatter()) {
                    // 玩家、聊天魂魄
                    // @TODO: object with owner
                    inv[i]->move(VOID_OB, 1);
                } else    {
                    inv[i] = 0;
                }
            }
        }

        destruct(obj);
    }

    if (obj) {
        return notify_fail("无法清除旧程序。\n");
    }

    write("重新编译 " + arg + "：");
    err = catch (call_other(arg, "???"));

    if (err) {
        write(sprintf("发生错误：\n%s\n", err));
    } else {
        write("成功！\n");

        if ((i = sizeof(inv)) && (obj = find_object(arg))) {
            while (i--) {
                if (inv[i]) {
                    inv[i]->move(obj, 1);
                }
            }
        }
    }

    return 1;
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式：update <文件名>

这个命令可以更新文件，并将新文件的内容载入内存内。
HELP;
// *INDENT-ON*
}
