// K_IH_MESSAGE

#include <inherit/property.h>

void receive_message(string type, string msg)
{
    if (type == "telnet") {
        receive(msg);
        return;
    }

    if (query_temp("block_msg/all") || query_temp("block_msg/" + type)) {
        return;
    }

    receive(msg);
}

varargs void block_message(string type)
{
    if (!type) {
        type = "all";
    }

    set_temp("block_msg/" + type, 1);
}

varargs void unblock_message(string type)
{
    if (!type) {
        type = "all";
    }

    delete_temp("block_msg/" + type);
}
