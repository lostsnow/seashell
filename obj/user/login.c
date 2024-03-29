// LOGIN_OB

#include <login.h>

inherit IH_SAVE;
inherit IH_NAME;
inherit IH_GMCP;

private nosave object user_ob;
private string password;
private nosave string temp_password;
nosave int password_tries = 0;

void logon()
{
    object me = this_object();
    ip_number = query_ip_number(me);
    remove_call_out("logon_timeout");
    call_out("logon_timeout", LOGIN_TIMEOUT);
    init_gmcp();

    LOGIN_D->logon(me);
}

void logon_timeout()
{
    object me = this_object();

    if (objectp(user_ob)) {
        if (!environment(user_ob)) {
            destruct(user_ob);
        }

        return;
    }

    if (interactive(me)) {
        ansi_write("\n%^HIY%^您花在登录的时间太久了，下次先想好再来吧。\n%^NOR%^");
    }

    destruct(me);
}

// Don't destruct(this_object()) in the net_dead() interactive apply or
// there'll be error message: Double call to remove_interactive()
void net_dead()
{
    remove_call_out("logon_timeout");
    call_out("logon_timeout", 1);
}

string query_save_file()
{
    object me = this_object();
    string id;
    id = me->get_id();

    if (!stringp(id) || id == "") {
        return 0;
    }

    return sprintf(DATA_DIR + "login/%s/%s", id[0..0], id);
}

void receive_message(string type, string str)
{
    if (type != "write") {
        return;
    }

    receive(str);
}

object get_user_ob()
{
    return user_ob;
}

object set_user_ob(object ob)
{
    return user_ob = ob;
}

string get_password()
{
    return password;
}

string set_password(string pass)
{
    return password = pass;
}

string get_temp_password()
{
    return temp_password;
}

string set_temp_password(string pass)
{
    return temp_password = pass;
}

int get_password_tries()
{
    return password_tries;
}

void add_password_tries()
{
    password_tries++;
}

void gmcp(string arg)
{
    ::gmcp(arg);
    login_gmcp(arg);
}
