string author_file(string str)
{
    return (string) call_other(SIMUL_EFUN_OB, "author_file", str);
}

string creator_file(string str)
{
    return (string) call_other(SIMUL_EFUN_OB, "creator_file", str);
}

string domain_file(string str)
{
    return (string) call_other(SIMUL_EFUN_OB, "domain_file", str);
}
