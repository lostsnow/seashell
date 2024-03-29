// K_MASTER_OB

#include "master/flag.c"
#include "master/uid.c"
#include "master/error.c"
#include "master/preload.c"
#include "master/valid.c"

void create()
{
    efun::write("master: loaded successfully.\n");
}

void connect_init(int port)
{
    string charset;
    charset = CFG_PORT_CHARSET(itoa(port));

    if (charset != "") {
        debug_message("[K_MASTER_OB] set encoding " + charset + " for port " + itoa(port), DEBUG_LEVEL_DEBUG);
        set_encoding(charset);
    }
}

object connect(int port)
{
    object login_ob;
    mixed err;
    connect_init(port);
    err = catch (login_ob = new (LOGIN_OB));

    if (err) {
        write("系统核心出现了故障，请待会再来。\n");
        log_time("error.log", err);
        destruct(this_object());
        return 0;
    }

    return login_ob;
}

mapping get_mud_stats()
{
    return MSSP_D->mssp_telopt();
}
