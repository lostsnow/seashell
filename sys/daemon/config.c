// CONFIG_D

#include <ansi.h>

inherit IH_PROPERTY;
inherit IH_NAME;

#define LIB_CONFIG_FILE CONFIG_DIR + LIB_CFG

// 配置文件中参数的格式是: arg: value
// 如果以 # 打头表示注释，& 打头表示是系统注释的。

void load_config();
string query_config_file_name();

void create()
{
    set_name(HIW + "配置精灵" + NOR);
    set_id("CONFIG_D");
    load_config();
}

// 返回配置文件的名字
string query_config_file_name()
{
    return LIB_CONFIG_FILE;
}

void load_config()
{
    string *tmp, file;
    string line;
    string arg, value;
    string last_remember;
    string affix;
    int len;
    int sys_del;
    file = read_file(query_config_file_name());

    if (!stringp(file) || file == "") {
        return;
    }

    // 去掉 "\r" 保证文件格式兼容
    file = replace_string(file, "\r", "");
    sys_del = 0;
    tmp = explode(file, "\n");

    foreach (line in tmp) {
        // 上一个参数是被系统注释掉的
        if (sys_del) {
            last_remember = 0;
            sys_del = 0;
        }

        // 去掉行首的空格
        while (strlen(line) && line[0] == ' ') {
            line = line[1.. < 1];
        }

        // 注释
        if (line[0] == '#') {
            last_remember = line;
            continue;
        }

        // 被系统注释的
        if (line[0] == '&') {
            line = line[1.. < 1];

            while (strlen(line) && line[0] == ' ') {
                line = line[1.. < 1];
            }

            sys_del = 1;
        }

        // 去掉 # 以后所有的字符
        len = strsrch(line, '#');

        if (len != -1) {
            // 记录尾注
            affix = line[len.. < 1];
            line = line[0..len - 1];
        } else {
            affix = 0;
        }

        if (!strlen(line)) {
            continue;
        }

        // 检查该行
        if (sscanf(line, "%s:%s", arg, value) != 2) {
            log_error(sprintf("syntax error: <%s>\n", line));
            continue;
        }

        // 去掉arg末尾的空格
        while ((len = strlen(arg)) > 0 && arg[len - 1] == ' ') {
            arg = arg[0.. < 2];
        }

        if (!strlen(arg)) {
            log_error(sprintf("syntax error: <%s>\n", line));
            last_remember = 0;
            continue;
        }

        // 去掉value打头的空格
        while (strlen(value) && value[0] == ' ') {
            value = value[1.. < 1];
        }

        // 去掉value末尾的空格
        while ((len = strlen(value)) > 0 && value[len - 1] == ' ') {
            value = value[0.. < 2];
        }

        // 系统没有注释这个参数
        if (!sys_del) {
            set(arg, value);
            sys_del = 0;
        }

        // 如果有注释，则加上
        if (stringp(last_remember)) {
            set_temp("remember/" +arg, last_remember);
            last_remember = 0;
        }

        // 如果有尾注，则加上
        if (stringp(affix)) {
            set_temp("affix/" + arg, affix);
            affix = 0;
        }
    }
}

// 返回整数参数
int query_int(string index)
{
    int result;

    // 不是 INT 类型的值
    if (!intp(result = query(index))) {
        // 是字符串吗？如果是则取值
        if (stringp(result)) {
            sscanf(result, "%d", result);
        } else {
            result = 0;
        }

        set(index, result);
    }

    return result;
}

// 返回字符串参数
string query_string(string index)
{
    string result;

    if (!stringp(result = query(index))) {
        result = "";
    }
    return result;
}

// 返回参数的注释
string query_remember(string index)
{
    return query_temp("remember/" + index);
}

// 返回参数的尾注
string query_affix(string index)
{
    return query_temp("affix/" + index);
}
