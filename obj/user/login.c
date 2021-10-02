// LOGIN_OB

#include <login.h>

inherit IH_SAVE;
inherit IH_NAME;
inherit IH_GMCP;

private nosave string ip_number;
private nosave object user_ob;
private string password;
private nosave string temp_password;
nosave int password_tries = 0;
private string token;
private int token_create_at;
private nosave int is_gmcp_login;

void logon()
{
    object me = this_object();
    ip_number = query_ip_number(me);
    remove_call_out("logon_timeout");
    call_out("logon_timeout", LOGIN_TIMEOUT);

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
        ansi_write("%^HIY%^您花在登录的时间太久了，下次先想好再来吧。\n%^NOR%^");
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

string get_ip_number()
{
    return ip_number;
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

void login_fail(string err, string msg)
{
    object me = this_object();
    me->send_gmcp("login.info", (["code": -1, "error": err, "message": msg]));
}

void gmcp(string arg)
{
    string login_token, user_id, user_passwd, user_name;

    if (sscanf(arg, "/register %s %s %s", user_id, user_passwd, user_name) == 3) {
        is_gmcp_login = 1;
        LOGIN_D->gmcp_register(this_object(), user_id, user_passwd, user_name);
        return;
    }

    if (sscanf(arg, "/login %s %s", user_id, user_passwd) == 2) {
        is_gmcp_login = 1;
        LOGIN_D->gmcp_logon(this_object(), user_id, user_passwd);
        return;
    }

    if (sscanf(arg, "/login %s", login_token) == 1) {
        is_gmcp_login = 1;
        LOGIN_D->gmcp_logon_token(this_object(), login_token);
        return;
    }
}

string get_token()
{
    return token;
}

// @TODO: delete token when cmd quit
string generate_token(int renew)
{
    object me = this_object();

    if (renew || !token) {
        token = me->get_id() + ":" + random_string(128);
        token_create_at = time();
    }

    return token;
}

int is_gmcp()
{
    return is_gmcp_login;
}
