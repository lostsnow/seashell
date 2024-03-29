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

// valid_override: controls which simul_efuns may be overridden with
//   efun:: prefix and which may not.  This function is only called at
//   object compile-time
int valid_override(string file, string efun_name, string main_file)
{
    // simul_efun can override any simul_efun by Annihilator
    if (file == SIMUL_EFUN_OB || file == MASTER_OB || file == K_SIMUL_EFUN_OB || file == K_MASTER_OB) {
        return 1;
    }

    if (efun_name == "destruct" || efun_name == "shutdown" ||
        efun_name == "snoop" || efun_name == "exec") {
        return 0;
    }

    //  may also wish to protect shutdown, snoop, and exec.
    return 1;
}

// valid_write: write privileges; called with the file name, the object
//   initiating the call, and the function by which they called it.
int valid_write(string file, mixed user, string func)
{
    // debug_message(sprintf("[%O]->valid_write(): %s(%s)", user, file, func), DEBUG_LEVEL_TRACE);
    return 1;
}

// valid_read: read privileges; called exactly the same as valid_write()
int valid_read(string file, mixed user, string func)
{
    // debug_message(sprintf("[%O]->valid_read(): %s(%s)", user, file, func), DEBUG_LEVEL_TRACE);
    return 1;
}
