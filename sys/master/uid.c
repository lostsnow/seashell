// master: uid applies

// master apply::get_root_uid
string get_root_uid()
{
    return ROOT_UID;
}

// master apply::get_bb_uid
string get_bb_uid()
{
    return BACKBONE_UID;
}

// master apply::author_file
string author_file(string str)
{
    return (string) call_other(SIMUL_EFUN_OB, "author_file", str);
}

// master apply::creator_file
string creator_file(string str)
{
    return (string) call_other(SIMUL_EFUN_OB, "creator_file", str);
}

// master apply::domain_file
string domain_file(string str)
{
    return (string) call_other(SIMUL_EFUN_OB, "domain_file", str);
}
