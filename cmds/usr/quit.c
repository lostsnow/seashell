#include <ansi.h>

inherit IH_CLEAN_UP;

int main(object me, string arg)
{
    object login_ob, env;

    login_ob = me->get_login_ob();

    me->set("last_online", time());
    me->set("last_saved_at", time());

    if (objectp(login_ob)) {
        me->set("last_login_ip", login_ob->get_ip_number());
        login_ob->clean_token();
        destruct(login_ob);
    }

    write("欢迎下次再来！\n");

    env = environment(me);

    if (env) {
        tell_room(env, HIW + me->short() + NOR + "离开游戏。\n", ({me}));
    }

    me->save();
    destruct(me);
    return 1;
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式 : quit

当你想暂时离开时, 可利用此命令。
HELP;
// *INDENT-ON*
}
