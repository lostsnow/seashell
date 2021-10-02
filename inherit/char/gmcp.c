// K_IH_GMCP

void send_gmcp(string key, mixed value)
{
    if (has_gmcp()) {
        efun::send_gmcp(key + " " + json_encode(value));
    }
}
