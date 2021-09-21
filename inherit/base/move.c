// K_IH_MOVE

varargs int move(mixed dest, int raw)
{
    object me, ob, env;
    me = this_object();

    // Find the destination ob for moving.
    if (objectp(dest)) {
        ob = dest;
    } else if (stringp(dest)) {
        call_other(dest, "???");
        ob = find_object(dest);
    }

    if (!ob || ob == me) {
        return notify_fail("移动目标无效。\n");
    }

    move_object(ob);

    if (interactive(me) && living(me) && !raw) {
        command("look");
    }

    return 1;
}
