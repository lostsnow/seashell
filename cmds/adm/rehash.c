inherit IH_CLEAN_UP;

string help(object me);

int main(object me, string arg)
{
    if (!arg) {
        write(help(me));
        return 1;
    }

    if (arg[0] != '/') {
        arg = "/" + arg;
    }

    if (arg[sizeof(arg) - 1] != '/') {
        arg += "/";
    }

    if (file_size(arg) != -2) {
        return notify_fail("没有这个目录！\n");
    }

    write("更新命令表：" + arg + "\n");
    COMMAND_D->rehash(arg);
    return 1;
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式：rehash <目录名称>

这个命令会更新系统内部的命令表，如果你新增或删除了某个目录下的指令，
必须用这个指令更新该目录才能使用。
HELP;
// *INDENT-OFF*
}
