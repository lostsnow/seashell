// sefun: message

#include <ansi.h>

void writeln(mixed message)
{
    write(message + "\n");
}

void ansi_write(string content)
{
    write(ansi_filter(content));
}

varargs string ansi_sprintf(string msg, mixed* args...)
{
    return sprintf(ansi_filter(msg), args...);
}

varargs void ansi_printf(string msg, mixed* args...)
{
    write(ansi_sprintf(msg, args...));
}

varargs void debug_message(string msg, int lvl)
{
    string level, color;
    int run_lvl = DEBUG_LEVEL();

    if (!lvl) {
        lvl = DEBUG_LEVEL_INFO;
    }

    if (!(run_lvl & lvl)) {
        return;
    }

    switch (lvl) {
        case DEBUG_LEVEL_TRACE:
            level = "TRACE";
            color = HIK;
            break;

        case DEBUG_LEVEL_DEBUG:
            level = "DEBUG";
            color = HIK;
            break;

        case DEBUG_LEVEL_INFO:
            level = "INFO";
            color = HIB;
            break;

        case DEBUG_LEVEL_WARN:
            level = "WARN";
            color = HIY;
            break;

        case DEBUG_LEVEL_ERROR:
            level = "ERROR";
            color = HIR;
            break;
    }

    efun::debug_message(sprintf("[%s] %s[%s]%s %s", now(), color, level, NOR, msg));
}
