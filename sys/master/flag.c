// master: flag apply

#include <ansi.h>

nosave int DEBUG = 0;

void flag(string arg)
{
    string file, func, level;

    if (previous_object()) {
        return;
    }

    if (sscanf(arg, "call:%s %s", file, func)) {
        write("Got " + call_other(file, func) + " back.\n");
    } else if (sscanf(arg, "debug:%s", level)) {
        switch (lower_case(level)) {
            case "error":
                DEBUG = DEBUG_LEVEL_ERROR;
                break;

            case "warn":
                DEBUG = DEBUG_LEVEL_ERROR | DEBUG_LEVEL_WARN;
                break;

            case "info":
                DEBUG = DEBUG_LEVEL_ERROR | DEBUG_LEVEL_WARN | DEBUG_LEVEL_INFO;
                break;

            case "debug":
                DEBUG = DEBUG_LEVEL_ERROR | DEBUG_LEVEL_WARN | DEBUG_LEVEL_INFO | DEBUG_LEVEL_DEBUG;
                break;

            case "trace":
                DEBUG = DEBUG_LEVEL_ERROR | DEBUG_LEVEL_WARN | DEBUG_LEVEL_INFO | DEBUG_LEVEL_DEBUG | DEBUG_LEVEL_TRACE;
                break;

            default:
                DEBUG = DEBUG_LEVEL_ERROR;
                break;
        }
    } else {
        efun::debug_message(HIR + "Flag '" + arg + "' is not supproted." + NOR);
    }

    return;
}

int debug_level()
{
    return DEBUG;
}
