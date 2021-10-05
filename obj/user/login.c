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
    string pl;
    mapping payload;
    object me = this_object();

    ::gmcp(arg);

    if (sscanf(arg, "Core.Hello %s", pl) == 1) {
        payload = gmcp_payload(pl, 1);

        if (payload && payload["verified"] && payload["ip"]) {
            ip_number = payload["ip"];
        }

        return;
    }

    if (sscanf(arg, "Char.Register %s", pl) == 1) {
        payload = gmcp_payload(pl);

        if (!payload) {
            login_fail("ERR_REGISTER", "注册参数无效");
            return;
        }

        if (payload["id"] && payload["password"] && payload["name"]) {
            is_gmcp_login = 1;
            LOGIN_D->gmcp_register(me, to_str(payload["id"]), to_str(payload["password"]), to_str(payload["name"]));
            return;
        }
    }

    if (sscanf(arg, "Char.Login %s", pl) == 1) {
        payload = gmcp_payload(pl);

        if (!payload) {
            login_fail("ERR_LOGIN", "登录参数无效");
            return;
        }

        if (payload["id"] && payload["token"]) {
            is_gmcp_login = 1;
            LOGIN_D->gmcp_logon_token(me, to_str(payload["id"]), to_str(payload["token"]));
            return;
        }

        if (payload["id"] && payload["password"]) {
            is_gmcp_login = 1;
            LOGIN_D->gmcp_logon(me, to_str(payload["id"]), to_str(payload["password"]));
            return;
        }
    }
}

string get_token()
{
    return token;
}

void clean_token()
{
    token = 0;
    token_create_at = 0;
    save();
}

string generate_token(int renew)
{
    if (renew || !token) {
        token = random_string(128);
        token_create_at = time();
    }

    return token;
}

int is_gmcp()
{
    return is_gmcp_login;
}

string get_ip_number()
{
    return ip_number;
}
