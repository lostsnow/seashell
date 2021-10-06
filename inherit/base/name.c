// K_IH_NAME

#include <ansi.h>
#include <inherit/name.h>

nosave string *my_ids;

string oid;
string oname;
string short_name;
string long_name;
nosave string apply_name;
nosave string apply_short_name;
nosave string apply_long_name;

// apply id
int id(string id)
{
    if (!id) {
        return 0;
    }

    if (my_ids && member_array(id, my_ids) != -1) {
        return 1;
    }

    return 0;
}

string get_id()
{
    return oid;
}

string set_id(string id)
{
    if (!my_ids) {
        my_ids = ({id});
    } else if (member_array(id, my_ids) == -1) {
        my_ids += ({id});
    }

    return oid = id;
}

varargs string set_name(string name, string *ids)
{
    oname = name;

    if (pointerp(ids) && sizeof(ids) > 0) {
        set_id(lower_case(ids[0]));
        my_ids = ids;
    }

    return oname;
}

string set_temp_name(string name)
{
    return apply_name = name;
}

varargs string name(int raw)
{
    if (!raw && stringp(apply_name) && apply_name != "") {
        return apply_name;
    }

    if (!stringp(oname) || oname == "") {
        oname = file_name(this_object());
    }

    return oname;
}

string set_short_name(string name)
{
    return short_name = name;
}

string set_temp_short_name(string name)
{
    return apply_short_name = name;
}

varargs string short(int raw)
{
    if (!raw && stringp(apply_short_name) && apply_short_name != "") {
        return apply_short_name;
    }

    if (!stringp(short_name) || short_name == "") {
        return name(raw) + "(" + capitalize(get_id()) + ")";
    }

    return short_name;
}

string set_long_name(string name)
{
    return long_name = name;
}

string set_temp_long_name(string name)
{
    return apply_long_name = name;
}

varargs string long(int raw)
{
    string str, extra;

    if (!raw && stringp(apply_long_name) && apply_long_name != "") {
        str = apply_long_name;
    } else if (!stringp(long_name) || long_name == "") {
        str = short(raw);
    } else {
        str = long_name;
    }

    extra = this_object()->extra_long();

    if (stringp(extra) && extra != "") {
        str += "\n" + extra;
    }

    return str;
}

string *id_list()
{
    return my_ids;
}
