// __PROPERTY_H__

#ifndef __PROPERTY_H__
#define __PROPERTY_H__

nomask mixed set(mixed key, mixed value);
nomask mixed add(mixed key, mixed value);
varargs nomask mixed query(mixed key, int raw);
nomask int delete (mixed key);
nomask mapping query_properties();
nomask mixed set_temp(mixed key, mixed value);
nomask mixed add_temp(mixed key, mixed value);
varargs nomask mixed query_temp(mixed key, int raw);
nomask int delete_temp(mixed key);
nomask mapping query_temp_properties();

#endif //__PROPERTY_H__
