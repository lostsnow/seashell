// master: error applies

#include <config.h>

#define TRACE_DETAIL_LENGTH_LIMIT 800

string standard_trace(mapping error, int caught);
string full_trace(mapping error, int caught);

// master apply::crash
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

// master apply::log_error
void log_error(string file, string message)
{
    if (this_player(1)) {
        if (wizardp(this_player(1))) {
            tell_object(this_player(1), message);
        }
    }

    log_time("error.log", message);
}

// master apply::error_handler
string error_handler(mapping error, int caught)
{
    string trace, full_trace;

    if (caught) {
        return "";
    }

    trace = standard_trace(error, caught);

    if (this_player(1)) {
        if (wizardp(this_player(1))) {
            tell_object(this_player(1), trace);
        } else {
            tell_object(this_player(1), ansi_filter(DEFAULT_ERROR_MESSAGE()) + "\n");
        }
    }

    log_time("error.log", trace);
    // 写入完整的出错信息
    full_trace = full_trace(error, caught);
    log_file("debug-full.log", full_trace);
    return trace;
}

string standard_trace(mapping error, int caught)
{
    return error["file"] + ":" + error["line"] + ": " + error["error"];
}

// 完整出错信息
string full_trace(mapping error, int caught)
{
    int count, j;
    string err_msg;
    mapping trace;
// *INDENT-OFF*
    err_msg = "\n" + sprintf(@ERR
——————————————<Bugs Report>——————————————
Time: %s
Message: %s
Program: %s
File: %s
Line: %d
ERR,
// *INDENT-ON*
            now(),
            replace_string(error["error"], "\n", " "),
            error["program"],
            error["file"],
            error["line"]);

    foreach (trace in error["trace"]) {
        count++;
// *INDENT-OFF*
        err_msg += sprintf(@ERR

    -- Trace #%d --
    Object: %O
    File: %s
    Line: %s
    Function: %s(%s)
ERR,
// *INDENT-ON*
                count,
                trace["object"],
                trace["program"] || "",
                (trace["line"] || "unknown") + "",
                trace["function"] || "",
                trace["arguments"] ? implode(map(trace["arguments"], (: typeof($1) :)), ", ") : "");

        if (trace["arguments"]) {
            err_msg += "    Arguments:\n";

            for (j = 0; j < sizeof(trace["arguments"]); j++) {
                string arg = trace["arguments"][j];
                err_msg += "        #" + (j + 1) + ": " + typeof(arg) + " " +
                    sprintf("%." + TRACE_DETAIL_LENGTH_LIMIT + "O", arg);

                if (strlen(sprintf("%O", arg)) > TRACE_DETAIL_LENGTH_LIMIT) {
                    err_msg += "...";
                }

                err_msg += "\n";
            }
        }

        if (trace["locals"]) {
            err_msg += "    Locals:\n";

            for (j = 0; j < sizeof(trace["locals"]); j++) {
                string loc = trace["locals"][j];
                err_msg += "        #" + (j + 1) + ": " + typeof(loc) + " " +
                    sprintf("%." + TRACE_DETAIL_LENGTH_LIMIT + "O", loc);

                if (strlen(sprintf("%O", loc)) > TRACE_DETAIL_LENGTH_LIMIT) {
                    err_msg += "...";
                }

                err_msg += "\n";
            }
        }
    }

    err_msg += "——————————————<Bugs Report>——————————————\n\n";
    return err_msg;
}

