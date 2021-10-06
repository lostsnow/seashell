// K_IH_GMCP

#include <config.h>

varargs mixed gmcp_payload(string pl, int verify);
int is_gmcp();
string get_ip_number();
void login_success(string login_token);
void login_fail(string err, string msg);

protected nosave int inited;
protected nosave string ip_number;
protected string token;
protected int token_create_at;
protected nosave int is_gmcp_login;

varargs void send_gmcp(string key, mixed value)
{
    if (has_gmcp()) {
        efun::send_gmcp(key + " " + json_encode(value));
    }
}

void init_gmcp()
{
    if (inited) {
        return;
    }

    if (!has_gmcp()) {
        call_out("init_gmcp", 1);
        return;
    }

    send_gmcp("Char.Login", ([]));
    send_gmcp("Char.Info", ([]));
    inited = 1;
}

varargs mixed gmcp_payload(string pl, int verify)
{
    mapping payload;
    mixed err;

    err = catch (payload = json_decode(pl));

    if (err || !mapp(payload)) {
        return 0;
    }

    if (verify) {
        if (stringp(payload["secret"]) && CFG_GMCP_SECRET() == payload["secret"]) {
            payload["verified"] = 1;
        } else {
            payload["verified"] = 0;
        }
    }

    return payload;
}

void gmcp(string arg)
{
    if (arg == "Core.Ping") {
        efun::send_gmcp(arg);
    }
}

void login_gmcp(string arg)
{
    string pl;
    mapping payload;
    object me = this_object();

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

void send_char_info()
{
    object me = this_object();
    me->send_gmcp("Char.Info", (["id": me->get_id(), "short": me->short()]));
}

void login_success(string login_token)
{
    object me = this_object();
    me->send_gmcp("Char.Login", (["code": 0, "id": me->get_id(), "token": login_token]));
}

void login_fail(string err, string msg)
{
    string key = "Char.Login";
    object me = this_object();

    if (err == "ERR_REGISTER") {
        key = "Char.Register";
    }

    me->send_gmcp(key, (["code": -1, "error": err, "message": msg]));
}
