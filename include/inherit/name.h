// __NAME_H__

#ifndef __NAME_H__
#define __NAME_H__

string get_id();
string set_id(string id);
varargs string set_name(string name, string *ids);
string set_temp_name(string name);
varargs string name(int raw);
string set_short_name(string name);
string set_temp_short_name(string name);
varargs string short(int raw);
string set_long_name(string name);
string set_temp_long_name(string name);
varargs string long(int raw);
string *id_list();

#endif //__NAME_H__
