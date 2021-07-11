// master: valid applies

// valid_seteuid: determines whether an object ob can become euid str
int valid_seteuid(object ob, string str)
{
    return 1;
}

int valid_bind(object binder, object old_owner, object new_owner)
{
    return 1;
}

// valid_socket: controls access to socket efunctions
int valid_socket(object caller, string func, mixed *info)
{
    return 1;
}
