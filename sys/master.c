// K_MASTER_OB

#include "master/file.c"

void connect_init(int port)
{
}

object connect(int port)
{
    object login_ob;
    mixed err;
    connect_init(port);
    err = catch (login_ob = new (LOGIN_OB));

    if (err) {
        write("系统核心出现了故障，请待会再来。\n");
        error(err);
        destruct(this_object());
        return 0;
    }

    return login_ob;
}

string get_root_uid()
{
    return ROOT_UID;
}

string get_bb_uid()
{
    return BACKBONE_UID;
}
