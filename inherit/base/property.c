// IH_BASE

mapping properties = ([]);
nosave mapping temp_properties = ([]);

nomask void set(mixed key, mixed value)
{
    properties[key] = value;
}

nomask void add(mixed key, mixed value)
{
    if (typeof(value) == typeof(properties[key])) {
        if (!functionp(value)) {
            properties[key] += value;
        }
    }
}

varargs nomask mixed query(mixed key, int raw)
{
    mixed value;
    value = properties[value];

    if (raw) {
        return value;
    }

    return evaluate(value, this_object());
}

void delete (mixed key)
{
    map_delete(properties, key);
}

nomask mapping query_properties()
{
    return properties;
}

nomask void set_temp(mixed key, mixed value)
{
    temp_properties[key] = value;
}

nomask void add_temp(mixed key, mixed value)
{
    if (typeof(value) == typeof(temp_properties[key])) {
        if (!functionp(value)) {
            temp_properties[key] += value;
        }
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

void delete_temp(mixed key)
{
    map_delete(temp_properties, key);
}

nomask mapping query_temp_properties()
{
    return temp_properties;
}
