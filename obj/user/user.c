// USER_OB

#include <ansi.h>

inherit IH_CHAR;
inherit IH_SAVE;
inherit IH_GMCP;

varargs string short(int raw);

private nosave object login_ob;
private nosave int net_dead;                    // 标志：是否断开了连接

void create()
{
    seteuid(0);
}

void setup()
{
    seteuid(getuid(this_object()));
    set_heart_beat(1);
    enable_player_commands();
}

int is_player()
{
    return clonep();
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
    set_heart_beat(1);
    net_dead = 0;
    remove_call_out("net_dead_clean");
    tell_object(this_object(), "重新连线完毕。\n");
}

int is_net_dead()
{
    return net_dead || !interactive(this_object());
}

// net_dead: called by the gamedriver when an interactive player loses
// his network connection to the mud.
void net_dead()
{
    set_heart_beat(0);
    call_out("net_dead_clean", 60);
    say(name() + "断线了。\n");

    net_dead = 1;
}

void net_dead_clean()
{
    object me = this_object();

    if (environment()) {
        tell_room(environment(), short() + "断线超过 1 分钟，自动退出这个世界。\n");
    }

    me->set("last_online", time());
    me->set("last_saved_at", time());

    if (objectp(login_ob)) {
        me->set("last_login_ip", login_ob->get_ip_number());
        destruct(login_ob);
    }

    me->save();
    destruct(me);
}

string query_save_file()
{
    string id;
    id = geteuid();

    if (!id) {
        id = getuid();
    }

    if (!stringp(id) || id == "" || id == ROOT_UID) {
        return 0;
    }

    return sprintf(DATA_DIR + "user/%s/%s", id[0..0], id);
}

object get_login_ob()
{
    return login_ob;
}

object set_login_ob(object ob)
{
    return login_ob = ob;
}

varargs string short(int raw)
{
    string str;
    object me;

    str = ::short(raw);
    me = this_object();

    if (me->is_net_dead()) {
        str += HIG + " <断线中>" + NOR;
    }

    return str;
}
