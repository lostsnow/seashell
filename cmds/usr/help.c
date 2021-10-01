inherit IH_CLEAN_UP;

#include <ansi.h>

string *help_search = HELP_DIRS;

string help(object me);

private varargs string help_style(string title, string arg, string content, string last_modify)
{
    return sprintf(
            HIC + " %-52s%26s \n" + NOR +
            HIC + repeat_string("─", 40) + "\n" + NOR +
            "%s\n" +
            HIC + repeat_string("─", 40) + "\n" + NOR +
            (!undefinedp(last_modify) ? YEL + "%79s\n" + NOR : ""),
            title, "[" + HIY + arg + NOR + HIC + "]",
            ansi_filter(content), "最后更新 " + last_modify);
}

int main(object me, string arg)
{
    int i;
    string file, content, title = "帮助";

    if (!arg) {
        arg = "topics";

        if (!file_exists(HELP_DIR + "/topics.txt")) {
            return notify_fail(help_style(title, arg, sprintf("%|80s", ansi("HIR", "没能找到帮助主题。"))));
        }
    } else if (strwidth(arg) > 24) {
        return notify_fail(help_style(title, sprintf("%.19s...", arg), sprintf("%|80s", ansi("HIR", "帮助主题无效。"))));
    }

    // Search the individual search path first.
    if (pointerp(help_search)) {
        i = sizeof(help_search);

        while (i--) {
            file = help_search[i] + arg + ".txt";

            if (file_exists(file)) {
                me->start_more(help_style(title, arg, read_file(file), datetime(stat(file)[1])));
                return 1;
            }
        }
    }

    // 命令帮助
    if (file = me->find_command(arg)) {
        title = "命令" + title;
        content = file->help(me);

        if (content == 0) {
            return notify_fail(help_style(title, arg, sprintf("%|80s", ansi("HIR", "有这个指令存在，但是并没有详细的说明。"))));
        }

        write(help_style(title, arg, file->help(me), datetime(stat(file)[1])));
        return 1;
    }

    return notify_fail(help_style(title, arg, sprintf("%|80s", ansi("HIR", "没有针对这项主题的说明文件。"))));
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式：help <主题>              例如： > help cmds

这个命令提供你针对某一主题的详细说明文件，若是不指定主题，
则提供你有关主题的文件。
HELP;
// *INDENT-ON*
}
