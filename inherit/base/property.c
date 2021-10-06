// K_IH_PROPERTY

#include <inherit/property.h>

mapping properties = ([]);
nosave mapping temp_properties = ([]);

nomask mixed set(mixed key, mixed value)
{
    return properties[key] = value;
}

nomask mixed add(mixed key, mixed value)
{
    mixed old;

    old = query(key, 1);
    if (typeof(value) == typeof(old) && !functionp(value)) {
        if (!old) {
            return set(key, value);
        }
        return set(key, old + value);
    }
}

varargs nomask mixed query(mixed key, int raw)
{
    mixed value;
    value = properties[key];

    if (raw) {
        return value;
    }

    return evaluate(value, this_object());
}

nomask int delete (mixed key)
{
    return map_delete(properties, key);
}

nomask mapping query_properties()
{
    return properties;
}

nomask mixed set_temp(mixed key, mixed value)
{
    return temp_properties[key] = value;
}

nomask mixed add_temp(mixed key, mixed value)
{
    mixed old;

    old = query_temp(key, 1);
    if (typeof(value) == typeof(old) && !functionp(value)) {
        if (!old) {
            return set_temp(key, value);
        }
        return set_temp(key, old + value);
    }
}

varargs nomask mixed query_temp(mixed key, int raw)
{
    mixed value;
    value = temp_properties[key];

    if (raw) {
        return value;
    }

    return evaluate(value, this_object());
}

nomask int delete_temp(mixed key)
{
    return map_delete(temp_properties, key);
}

nomask mapping query_temp_properties()
{
    return temp_properties;
}
