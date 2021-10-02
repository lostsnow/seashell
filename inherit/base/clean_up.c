// K_IH_CLEAN_UP

#define NEVER_AGAIN         0
#define TRY_AGAIN_LATER     1

#define NO_CLEAN_UP_PROP    "apply/clean_up/no"

int get_no_clean(object ob)
{
    return (int) ob->query(NO_CLEAN_UP_PROP);
}

void set_no_clean(int var)
{
    this_object()->set(NO_CLEAN_UP_PROP, var);
}

void add_no_clean(int var)
{
    this_object()->add(NO_CLEAN_UP_PROP, var);
}

int clean_up(int inherited)
{
    object *inv;

    if (!this_object()) {
        return NEVER_AGAIN;
    }

    // non-clone & clean_up property objects
    if (!clonep() && get_no_clean(this_object())) {
        return 1;
    }

    // online users
    if (interactive(this_object())) {
        return TRY_AGAIN_LATER;
    }

    // If we are contained in something, let environment do the clean
    // up instead of making recursive call. This will prevent clean-up
    // time lag.
    if (environment()) {
        return TRY_AGAIN_LATER;
    }

    // If environment containes something interactive or disable clean-up,
    // This will prevent clean-up time lag.
    inv = deep_inventory();

    if (inv && sizeof(inv)) {
        if (sizeof(filter(inv, (: interactive($1) || get_no_clean($1) :)))) {
            return TRY_AGAIN_LATER;
        }
    }

    destruct(this_object());
    return NEVER_AGAIN;
}
