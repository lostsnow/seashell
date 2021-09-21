#include <runtime_config.h>
#include <config.h>

inherit IH_CLEAN_UP;

string help(object me);

int main(object me, string arg)
{
    object obj;
    string err;

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
