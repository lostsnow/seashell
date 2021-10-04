// K_IH_GMCP

#include <config.h>

protected nosave int inited;

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

    send_gmcp("Core.Info", MSSP_D->mssp_telopt());
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
