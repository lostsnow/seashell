// K_IH_CHAR

#include <ansi.h>

inherit IH_PROPERTY;
inherit IH_NAME;
inherit IH_COMMAND;
inherit IH_MESSAGE;
inherit IH_MORE;
inherit IH_MOVE;

void create()
{
    // LOGIN_D can export uid to us
    seteuid(0);
}

int is_character()
{
    return 1;
}

void setup()
{
    seteuid(getuid());
    set_heart_beat(1);
    enable_player_commands();
}

varargs string short(int raw)
{
    string str;
    object me;

    str = ::short(raw);
    me = this_object();

    if (raw) {
        return str;
    }

    if (me->is_net_dead()) {
        str += HIG + " <断线中>" + NOR;
    }

    if (interactive(me) && query_idle(me) > 120) {
        str += HIM + " <发呆中>" + NOR;
    }

    return str;
}
