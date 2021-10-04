// K_IH_GMCP

protected nosave int inited;

void send_gmcp(string key, mixed value)
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
    object me = this_object();
    me->send_gmcp("Char.Login", (["code": -1, "error": err, "message": msg]));
}
