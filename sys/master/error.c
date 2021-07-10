// master: error

#include <config.h>

#define TRACE_DETAIL_LENGTH_LIMIT 800

string print_vars(mixed *vars);
string standard_trace(mapping error, int caught);
string full_trace(mapping error, int caught);

// This is called when there is a driver segmentation fault or a bus error, etc.
void crash(string error, object command_giver, object current_object)
{
    mixed cmds;
    int i;
    string crash_file = "crash.log";
    efun::shout("系统核心发出一声惨叫：哇—哩—咧—\n");
    efun::shout("系统核心告诉你：要当机了，自己保重吧！\n");
    log_time(crash_file, sprintf("system crashed: %s\n", error));

    if (command_giver) {
        log_file(crash_file, sprintf("  this_player: %O\n", command_giver));
        cmds = command_giver->query_commands();

        for (i = 0; i < sizeof(cmds); i++) {
            if (cmds[i][2] == command_giver) {
                continue;
            }

            log_time(crash_file, sprintf("    %-15s %2d %O\n", cmds[i][0], cmds[i][1], cmds[i][2]));
        }

        if (environment(command_giver)) {
            log_file(crash_file, sprintf("    in where: %s(%s)。\n",
                    environment(command_giver)->query("short"),
                    base_name(environment(command_giver))));
        }

        log_time(crash_file, sprintf("  this_player: %O 。 end command (%s)\n",
                command_giver, command_giver->query_last_input()));
    }

    if (current_object) {
        log_file(crash_file, sprintf("  this_object: %O\n", current_object));
    }
}

void log_error(string file, string message)
{
    if (this_player(1)) {
        if (wizardp(this_player(1))) {
            tell_object(this_player(1), message);
        }
    }

    log_time("error.log", message);
}


string error_handler(mapping error, int caught)
{
    string trace;
    trace = standard_trace(error, caught);

    if (this_player(1)) {
        if (wizardp(this_player(1))) {
            tell_object(this_player(1), trace);
        } else {
            tell_object(this_player(1), color_filter(DEFAULT_ERROR_MESSAGE()) + "\n");
        }
    }

    // 写入完整的出错信息
    log_file("debug-full.log", full_trace(error, caught));
    return trace;
}

string standard_trace(mapping error, int caught)
{
    int i, s;
    string res;
    object *obj, env;
    int size;
    string err, var;
    /* keep track of number of errors per object...if you're into that */
    res = (caught) ? "错误讯息被拦截：\n" : "";
    err = error["error"];
    res += sprintf("\n[%s] ", datetime(time()));

    if (strlen(err) >= 18 && err[0..17] == "*Too long command.") {
        res += "执行时段错误：" + err;
    } else {
        res += sprintf("执行时段错误：%s\n程序：%s 第 %i 行\n物件：%s\n",
                error["error"],
                (undefinedp(error["program"]) ? "(none)" : error["program"]),
                error["line"],
                ((undefinedp(error["object"]) || !error["object"]) ? "(none)" : file_name(error["object"])));

        if (sizeof(error["trace"]) > 0) {
            for (i = 0, s = sizeof(error["trace"]); i < s; i++) {
                res += sprintf("呼叫来自：%s 的 %s() 第 %i 行，物件： %O\n",
                        error["trace"][i]["program"],
                        error["trace"][i]["function"],
                        error["trace"][i]["line"],
                        error["trace"][i]["object"]);
                res += "调用参数：" + error["trace"][i]["function"] + "(" +
                    print_vars(error["trace"][i]["arguments"]) + ")\n";
                var = print_vars(error["trace"][i]["locals"]);

                if (sizeof(var) > 200) {
                    var = var[0..199] + "\n...";
                }

                res += "局部变量：" + var + "\n";
            }
        }
    }

    if (env = this_player()) {
        res += sprintf("this_player: %O\n", this_player());

        while (env = environment(env)) {
            res += sprintf("          <- %O\n", env);
        }
    }

    // this_object() is always master.c, so no need to print.
    obj = previous_object(-1);
    size = sizeof(obj);

    if (size > 0) {
        for (i = 0; i < size; i++) {
            res += sprintf("previous_object(%d): %O\n", i, obj[i]);
        }
    }

    res += "+----------------------------------------------------------------------+\n\n";
    return res;
}

// 完整出错信息
string full_trace(mapping error, int caught)
{
    int count;
    string err_msg;
    mapping trace;
// *INDENT-OFF*
    err_msg = "\n" + sprintf(@ERR
——————————————<Bugs Report>——————————————
[ 错误时间 ]: % s
[ 错误内容 ]: % s
[ 错误档案 ]: % s
[ 错误行数 ]: % d
[ 资料回溯 ]:
ERR,
// *INDENT-ON*
            datetime(time()),
            replace_string(error["error"], "\n", " "),
            error["file"],
            error["line"]);

    foreach (trace in error["trace"]) {
        count++;
// *INDENT-OFF*
        err_msg += sprintf(@ERR
    -- 第 % d 层调用 --
    [ 触动物件 ]: % O
    [ 程式档案 ]: % s
    [ 函式名称 ]: % s( % s)
    [ 呼叫行数 ]: % s
ERR,
// *INDENT-ON*
                count,
                trace["object"],
                trace["program"] || "",
                trace["function"] || "",
                trace["arguments"] ? implode(map(trace["arguments"], (: typeof($1) :)), ", ") : "",
                (trace["line"] || "未知") + "");

        if (trace["arguments"]) {
            err_msg += "        [ 传入参数 ]:\n";
            err_msg += implode(map(trace["arguments"], (: "            ** (" + typeof($1) + ") " +
                            implode(explode(sprintf("%." + TRACE_DETAIL_LENGTH_LIMIT + "O\n", $1) +
                                    (strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... 讯息过长省略\n" : ""), "\n"),
                                "\n") :)), "\n") + "\n";
        }

        if (trace["locals"]) {
            err_msg += "        [ 程式变数 ]:\n";
            err_msg += implode(map(trace["locals"], (: "            ** (" + typeof($1) + ") " +
                            implode(explode(sprintf("%." + TRACE_DETAIL_LENGTH_LIMIT + "O\n", $1) +
                                    (strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... 讯息过长省略\n" : ""), "\n"),
                                "\n") :)), "\n") + "\n";
        }
    }

    err_msg += "——————————————<Bugs Report>——————————————\n\n";
    return err_msg;
}

string print_vars(mixed *vars)
{
    string *result = allocate(sizeof(vars));
    int i;

    for (i = 0; i < sizeof(vars); i++) {
        if (mapp(vars[i])) {
            result[i] = "([ ... ])";
        } else if (functionp(vars[i])) {
            result[i] = "(: ... :)";
        } else if (intp(vars[i])) {
            if (vars[i]) {
                result[i] = vars[i] + "";
            } else if (nullp(vars[i])) {
                result[i] = "NULL";
            } else if (undefinedp(vars[i])) {
                result[i] = "UNDEFINED";
            } else {
                result[i] = "0";
            }
        } else if (stringp(vars[i])) {
            result[i] = "\"" + vars[i] + "\"";
        } else if (pointerp(vars[i])) {
            result[i] = "({ ... })";
        } else if (floatp(vars[i])) {
            result[i] = vars[i] + "";
        } else if (bufferp(vars[i])) {
            result[i] = "<BUFFER>";
        }
    }

    return implode(result, ", ");
}
