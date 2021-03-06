// LOGIN_OB

#include <ansi.h>
#include <config.h>
#include <login.h>

inherit IH_NAME;

private void get_uid(string arg, object ob);
private void get_passwd(string pass, object ob);
private void check_logon(object ob);
private void confirm_relogin(string yn, object ob, object user);
varargs void reconnect(object ob, object user, int silent);

private void confirm_id(string yn, object ob);
private void new_password(string pass, object ob);
private void confirm_password(string pass, object ob);
private void get_name(string arg, object ob);

private object init_user(object ob);
varargs void enter_world(object ob, object user, int silent);
int check_legal_id(string id);
int check_legal_name(string name);

#define min_length_id 3
#define max_length_id 16
#define min_length_name 2
#define max_length_name 4

void create()
{
    set_name(HIW + "连线精灵" + NOR);
    set_id("LOGIN_D");
}

void logon(object ob)
{
    ansi_cat(WELCOME);

    ansi_printf("您的$HIY$英文名字$NOR$（$HIY$%d $NOR$到$HIY$ %d $NOR$个英文字母，新玩家可以选择一喜欢的名字）：",
        min_length_id, max_length_id);
    input_to("get_uid", ob);
}

private void get_uid(string arg, object ob)
{
    arg = lower_case(arg);

    if (!check_legal_id(arg)) {
        ansi_write("您的$HIY$英文名字$NOR$：");
        input_to("get_uid", ob);
        return;
    }

    ob->set_id(arg);

    if (file_exists(ob->query_save_file() + __SAVE_EXTENSION__)) {
        if (ob->restore()) {
            write("请输入密码：");
            input_to("get_passwd", 1, ob);
            return;
        }

        write("您的账号存档出了一些问题，请通知巫师处理。\n");
        destruct(ob);
        return;
    }

    ansi_printf("使用[$HIC$%s$NOR$]这个 ID 将会创造一个新的角色，您确定吗($HIG$y$NOR$/$HIR$n$NOR$)？", ob->get_id());
    input_to("confirm_id", ob);
}

private void get_passwd(string pass, object ob)
{
    string my_pass;
    my_pass = ob->get_password();

    if (!stringp(my_pass) || crypt(pass, my_pass) != my_pass) {
        ob->add_password_tries();
        if (ob->get_password_tries() < 3) {
            write("密码错误！请重新输入：");
            input_to("get_passwd", 1, ob);
            return;
        }
        write("密码错误！\n");
        destruct(ob);
        return;
    }

    check_logon(ob);
}

private void check_logon(object ob)
{
    object user;
    // Check if we are already playing.
    user = find_player(ob->get_id());

    if (user) {
        if (user->is_net_dead()) {
            reconnect(ob, user);
            return;
        }

        ansi_write("$WHT$您要将另一个连线中的相同角色赶出去，取而代之吗？（$HIY$y/n$NOR$$WHT$）$NOR$");
        input_to("confirm_relogin", ob, user);
        return;
    }

    user = init_user(ob);

    if (!objectp(user)) {
        ansi_write("$HIR$无法初始化角色，你可以尝试重新登录或是和巫师联系。$NOR$\n");
        return;
    }

    if (!user->restore()) {
        destruct(user);
        ansi_write("$HIR$无法读取你的数据档案，您需要和巫师联系。$NOR$\n");
        destruct(ob);
    }

    log_time("login.log", sprintf("%s(%s) login from %s\n",
            user->name(), user->get_id(), query_ip_number(ob)));

    enter_world(ob, user);
}

private void confirm_relogin(string yn, object ob, object user)
{
    object old_link;

    if (!yn || yn == "") {
        ansi_write("$WHT$您要将另一个连线中的相同角色赶出去，取而代之吗？（$NOR$$HIY$y/n$NOR$$WHT$$NOR$）");
        input_to("confirm_relogin", ob, user);
        return;
    }

    if (yn[0] != 'y' && yn[0] != 'Y') {
        write("好吧，欢迎下次再来。\n");
        destruct(ob);
        return;
    }

    if (!user) {
        write("在线玩家断开了连接，你需要重新登陆。\n");
        destruct(ob);
        return;
    }

    tell_object(user, "有人从别处（" + query_ip_number(ob) + "）连线取代你所控制的角色。\n");
    log_time("login.log", sprintf("%s(%s) relogin from %s\n",
            user->name(), user->get_id(), query_ip_number(ob)));
    // Kick out tho old player.
    old_link = user->get_login_ob();

    if (old_link) {
        exec(old_link, user);
        destruct(old_link);
    }

    reconnect(ob, user);
}

varargs void reconnect(object ob, object user, int silent)
{
    user->set_login_ob(ob);
    ob->set_user_ob(user);
    exec(user, ob);
    user->reconnect();

    if (!silent) {
        tell_room(environment(user), HIW + user->name() + NOR + "重新连线回到这个世界。\n", ({user}));
    }
}

private void confirm_id(string yn, object ob)
{
    if (yn == "") {
        ansi_write("使用这个 ID 将会创造一个新的角色，您确定吗($HIG$y$NOR$/$HIR$n$NOR$)？");
        input_to("confirm_id", ob);
        return;
    }

    if (lower_case(yn[0..0]) != "y") {
        write("好吧，那么请重新输入您的 ID：");
        input_to("get_id", ob);
        return;
    }

    write("请设定您的密码：");
    input_to("new_password", 1, ob);
}

private void new_password(string pass, object ob)
{
    if (strlen(pass) < 5) {
        ansi_write("密码的长度至少要$HIY$五$NOR$个字符，请重设您的$HIW$密码$NOR$：");
        input_to("new_password", 1, ob);
        return;
    }

    ob->set_temp_password(crypt(pass, 0));
    ansi_write("请再输入一次您的$HIW$密码$NOR$，以确认您没记错：");
    input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
    string old_pass;
    old_pass = ob->get_temp_password();

    if (crypt(pass, old_pass) != old_pass) {
        ansi_write("您两次输入的密码不同，请重新设定一次$HIW$密码$NOR$：");
        input_to("new_password", 1, ob);
        return;
    }

    ob->set_password(old_pass);

    ansi_printf("您的$HIY$中文名字$NOR$（$HIY$ %d $NOR$到$HIY$ %d $NOR$个汉字）：",
        min_length_name, max_length_name);
    input_to("get_name", ob);
}

private void get_name(string arg, object ob)
{
    object user;

    if (!check_legal_name(arg)) {
        ansi_write("您的$HIY$中文名字$NOR$：");
        input_to("get_name", ob);
        return;
    }

    user = init_user(ob);
    user->set_name(arg);

    log_time("register.log", sprintf("%s was created from %s\n",
            user->get_id(), query_ip_number(ob)));

    enter_world(ob, user);
}

private object init_user(object ob)
{
    object user;

    user = new (USER_OB);
    seteuid(ob->get_id());
    export_uid(user);
    seteuid(getuid());
    user->set_id(ob->get_id());
    return user;
}

varargs void enter_world(object ob, object user, int silent)
{
    if (interactive(ob)) {
        exec(user, ob);
    }

    user->set_temp("login_at", time());
    user->set("last_login_at", time());
    user->add("login_times", 1);
    user->set("last_saved_at", time());

    user->setup();
    user->save();
    ob->save();

    write("你连线进入" + LOCAL_MUD_NAME() + "。\n\n");

    user->send_char_info();
    // @TODO
}

int check_legal_id(string id)
{
    int i, len;
    i = strlen(id);
    len = i;

    while (i--) {
        if (id[i] < 'a' || id[i] > 'z') {
            ansi_write("对不起，你的英文名字只能用$HIY$英文字母$NOR$。\n");
            return 0;
        }
    }

    if (len < min_length_id || len > max_length_id) {
        ansi_printf("对不起，你的英文名字必须是$HIY$ %d $NOR$到$HIY$ %d $NOR$个英文字母。\n",
            min_length_id, max_length_id);
        return 0;
    }

    return 1;
}

int check_legal_name(string name)
{
    int len;

    if (!is_chinese(name)) {
        ansi_write("对不起，请您用$HIY$「中文」$NOR$取名字。\n");
        return 0;
    }

    len = strlen(name);

    if (len < min_length_name || len > max_length_name) {
        ansi_printf("对不起，你的中文名字必须是$HIY$ %d $NOR$到$HIY$ %d $NOR$个汉字。\n",
            min_length_name, max_length_name);
        return 0;
    }

    return 1;
}
