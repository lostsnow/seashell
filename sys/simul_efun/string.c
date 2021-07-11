// efun: string

int atoi(string str)
{
    int v;

    if (!stringp(str) || !sscanf(str, "%d", v)) {
        return 0;
    }

    return v;
}

public string itoa(int arg)
{
    return sprintf("%d", arg);;
}

string itoc(int c)
{
    return sprintf("%c", c);
}

string to_string(mixed arg)
{
    return stringp(arg) ? arg : save_variable(arg);
}

// is the string1 be a substring of string2
int is_sub(string s_str, string m_str)
{
    if (! m_str || ! s_str) {
        return 0;
    }

    return strsrch("," + m_str + ",", "," + s_str + ",") != -1;
}

// add a s_str
string add_sub(string s_str, string m_str)
{
    string *slist;
    int i;

    if (! s_str || is_sub(s_str, m_str)) {
        return m_str;
    }

    slist = explode(s_str, ",");
    slist -= ({ "" });

    for (i = 0; i < sizeof(slist); i++) {
        if (! is_sub(slist[i], m_str)) {
            if (m_str == 0 || m_str == "") {
                m_str = slist[i];
            } else {
                m_str += "," + slist[i];
            }
        }
    }

    return m_str;
}

// remove a s_str
string remove_sub(string s_str, string m_str)
{
    string *slist;
    string *trilist;

    if (! m_str || m_str == s_str) {
        return 0;
    }

    slist = explode(m_str, ",") - ({ "" });
    trilist = explode(s_str, ",");
    slist -= trilist;

    if (! sizeof(slist)) {
        return 0;
    }

    m_str = implode(slist, ",");
    return m_str;
}
