inherit IH_CLEAN_UP;

int main(object me, string arg)
{
    int last_time;

    seteuid(getuid());

    if (!objectp(me->get_login_ob())) {
        return notify_fail("你不是经由正常链接进入，不能保存。\n");
    }

    last_time = time() - (int)me->query("last_save_at");

    if (last_time >= 0 && last_time < 30 && !wizardp(me)) {
        return notify_fail("为了降低系统负载，请不要频繁保存进度。\n");
    }

    if (me->save()) {
        write("存档保存完毕。\n");
        return 1;
    }

    write("保存失败。\n");
    return 0;
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式：save

把你辛苦奋斗的结果存起来。
HELP;
// *INDENT-ON*
}
