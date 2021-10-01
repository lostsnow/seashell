// LOGIN_OB

#include <ansi.h>
#include <config.h>
#include <login.h>

#ifndef START_ROOM
#define START_ROOM VOID_OB
#endif

inherit IH_NAME;

private void get_uid(string arg, object ob);
private void get_passwd(string pass, object ob);
private void check_logon(object ob);
private void confirm_relogin(string yn, object ob, object user);
private varargs void reconnect(object ob, object user, int silent);

private void confirm_id(string yn, object ob);
private void new_password(string pass, object ob);
private void confirm_password(string pass, object ob);
private void get_name(string arg, object ob);

private object init_user(object ob);
private varargs void enter_world(object ob, object user, int silent);

void fail(object ob, string err, string msg);
int check_legal_id(string id, int is_gmcp);
int check_legal_name(string name, int is_gmcp);

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

    ansi_printf("您的%^HIY%^英文名字%^NOR%^（%^HIY%^%d %^NOR%^到%^HIY%^ %d %^NOR%^个英文字母，新玩家可以选择一喜欢的名字）：",
        min_length_id, max_length_id);
    input_to("get_uid", ob);
}

private void get_uid(string arg, object ob)
{
    if (ob->is_gmcp()) {
        return;
    }

    arg = lower_case(arg);

    if (!check_legal_id(arg, 0)) {
        ansi_write("您的%^HIY%^英文名字%^NOR%^：");
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

    ansi_printf("使用[%^HIC%^%s%^NOR%^]这个 ID 将会创造一个新的角色，您确定吗(%^HIG%^y%^NOR%^/%^HIR%^n%^NOR%^)？", ob->get_id());
    input_to("confirm_id", ob);
}

private void get_passwd(string pass, object ob)
{
    string my_pass;
    my_pass = ob->get_password();

    if (!stringp(my_pass) || crypt(pass, my_pass) != my_pass) {
        if (ob->is_gmcp()) {
            fail(ob, "ERR_LOGIN", "登录信息无效，请重试。");
        } else {
            ob->add_password_tries();

            if (ob->get_password_tries() < 3) {
                write("密码错误！请重新输入：");
                input_to("get_passwd", 1, ob);
                return;
            }

            write("密码错误！\n");
            destruct(ob);
        }

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

        if (ob->is_gmcp()) {
            confirm_relogin("y", ob, user);
        } else {
            ansi_write("%^WHT%^您要将另一个连线中的相同角色赶出去，取而代之吗？（%^HIY%^y/n%^NOR%^%^WHT%^）%^NOR%^");
            input_to("confirm_relogin", ob, user);
        }

        return;
    }

    user = init_user(ob);

    if (!objectp(user)) {
        fail(ob, "ERR_LOGIN", "无法初始化角色，你可以尝试重新登录或是和巫师联系。");
        return;
    }

    if (!user->restore()) {
        destruct(user);
        fail(ob, "ERR_LOGIN", "无法读取你的数据档案，您需要和巫师联系。");
        return;
    }

    log_time("login.log", sprintf("%s(%s) login from %s\n",
            user->name(), user->get_id(), query_ip_number(ob)));

    enter_world(ob, user);
}

private void confirm_relogin(string yn, object ob, object user)
{
    object old_link;

    if (!yn || yn == "") {
        ansi_write("%^WHT%^您要将另一个连线中的相同角色赶出去，取而代之吗？（%^NOR%^%^HIY%^y/n%^NOR%^%^WHT%^%^NOR%^）");
        input_to("confirm_relogin", ob, user);
        return;
    }

    if (yn[0] != 'y' && yn[0] != 'Y') {
        write("好吧，欢迎下次再来。\n");
        destruct(ob);
        return;
    }

    if (!user) {
        fail(ob, "ERR_LOGIN", "在线玩家断开了连接，你需要重新登陆。");
        return;
    }

    tell_object(user, "有人从别处（" + query_ip_number(ob) + "）连线取代你所控制的角色。\n");
    log_time("login.log", sprintf("%s(%s) relogin from %s\n",
            user->name(), user->get_id(), query_ip_number(ob)));
    // Kick out tho old player.
    old_link = user->get_login_ob();

    if (old_link) {
        if (interactive(user)) {
            exec(old_link, user);
        }

        destruct(old_link);
    }

    reconnect(ob, user, 1);
}

private varargs void reconnect(object ob, object user, int new_token)
{
    string login_token;

    login_token = ob->generate_token(new_token);

    if (new_token) {
        ob->save();
    }

    user->set_login_ob(ob);
    ob->set_user_ob(user);
    exec(user, ob);
    user->reconnect();

    user->login_success(login_token);

    if (environment(user)) {
        tell_room(environment(user), HIW + user->name() + NOR + "重新连线回到这个世界。\n", ({user}));
    }
}

private void confirm_id(string yn, object ob)
{
    if (yn == "") {
        ansi_write("使用这个 ID 将会创造一个新的角色，您确定吗(%^HIG%^y%^NOR%^/%^HIR%^n%^NOR%^)？");
        input_to("confirm_id", ob);
        return;
    }

    if (lower_case(yn[0..0]) != "y") {
        write("好吧，那么请重新输入您的 ID：");
        input_to("get_uid", ob);
        return;
    }

    write("请设定您的密码：");
    input_to("new_password", 1, ob);
}

private void new_password(string pass, object ob)
{
    if (strlen(pass) < 5) {
        ansi_write("密码的长度至少要%^HIY%^五%^NOR%^个字符，请重设您的%^HIW%^密码%^NOR%^：");
        input_to("new_password", 1, ob);
        return;
    }

    ob->set_temp_password(crypt(pass, 0));
    ansi_write("请再输入一次您的%^HIW%^密码%^NOR%^，以确认您没记错：");
    input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
    string old_pass;
    old_pass = ob->get_temp_password();

    if (crypt(pass, old_pass) != old_pass) {
        ansi_write("您两次输入的密码不同，请重新设定一次%^HIW%^密码%^NOR%^：");
        input_to("new_password", 1, ob);
        return;
    }

    ob->set_password(old_pass);

    ansi_printf("您的%^HIY%^中文名字%^NOR%^（%^HIY%^ %d %^NOR%^到%^HIY%^ %d %^NOR%^个汉字）：",
        min_length_name, max_length_name);
    input_to("get_name", ob);
}

private void get_name(string arg, object ob)
{
    object user;

    if (!check_legal_name(arg, ob->is_gmcp())) {
        if (ob->is_gmcp()) {
            fail(ob, "ERR_REGISTER", sprintf("中文名字必须是 %d 到 %d 个汉字", min_length_name, max_length_name));
        } else {
            ansi_write("您的%^HIY%^中文名字%^NOR%^：");
            input_to("get_name", ob);
        }

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

private varargs void enter_world(object ob, object user, int silent)
{
    string login_token;

    login_token = ob->generate_token();
    user->set_login_ob(ob);
    ob->set_user_ob(user);

    if (interactive(ob)) {
        exec(user, ob);
    }

    user->set_temp("login_at", time());
    user->set("last_login_at", time());
    user->add("login_times", 1);
    user->set("last_saved_at", time());

    user->login_success(login_token);

    user->setup();
    user->save();
    ob->save();

    write("你连线进入" + LOCAL_MUD_NAME() + "。\n\n");

    user->send_char_info();
    user->move(START_ROOM);
}

void gmcp_register(object ob, string user_id, string user_passwd, string user_name)
{
    user_id = lower_case(user_id);

    if (!check_legal_id(user_id, 1)) {
        fail(ob, "ERR_REGISTER", sprintf("英文名字必须是 %d 到 %d 个英文字母", min_length_id, max_length_id));
        return;
    }

    ob->set_id(user_id);

    if (file_exists(ob->query_save_file() + __SAVE_EXTENSION__)) {
        fail(ob, "ERR_REGISTER", "英文名字已经存在，请更换一个重试。");
        return;
    }

    ob->set_password(crypt(user_passwd, 0));

    get_name(user_name, ob);
}

void gmcp_logon(object ob, string user_id, string user_passwd)
{
    user_id = lower_case(user_id);

    if (!check_legal_id(user_id, 1)) {
        fail(ob, "ERR_LOGIN", "登录信息有误，请重试。");
        return;
    }

    ob->set_id(user_id);

    if (!file_exists(ob->query_save_file() + __SAVE_EXTENSION__)) {
        fail(ob, "ERR_LOGIN_USER_NOT_FOUND", "查无此人，请先注册或重新登录。");
        return;
    }

    if (!ob->restore()) {
        fail(ob, "ERR_LOGIN", "您的账号存档出了一些问题，请通知巫师处理。");
        return;
    }

    get_passwd(user_passwd, ob);
}

void gmcp_logon_token(object ob, string login_token)
{
    string user_id, sub_token;

    if (sscanf(login_token, "%s:%s", user_id, sub_token) != 2) {
        fail(ob, "ERR_LOGIN", "登录信息有误，请重试。");
        return;
    }

    ob->set_id(user_id);

    if (!file_exists(ob->query_save_file() + __SAVE_EXTENSION__)) {
        fail(ob, "ERR_LOGIN", "登录信息无效，请重试。");
        return;
    }

    if (!ob->restore()) {
        fail(ob, "ERR_LOGIN", "您的账号存档出了一些问题，请通知巫师处理。");
        return;
    }

    if (login_token != ob->get_token()) {
        fail(ob, "ERR_LOGIN", "登录信息无效，请重试。");
        return;
    }

    check_logon(ob);
}

void fail(object ob, string err, string msg)
{
    if (ob->is_gmcp()) {
        ob->login_fail(err, msg);
        destruct(ob);
        return;
    }

    ansi_printf("%^HIR%^%s%^NOR%^\n", msg);
    destruct(ob);
}

int check_legal_id(string id, int is_gmcp)
{
    int i, len;
    i = strlen(id);
    len = i;

    while (i--) {
        if (id[i] < 'a' || id[i] > 'z') {
            if (!is_gmcp) {
                ansi_write("对不起，你的英文名字只能用%^HIY%^英文字母%^NOR%^。\n");
            }

            return 0;
        }
    }

    if (len < min_length_id || len > max_length_id) {
        if (!is_gmcp) {
            ansi_printf("对不起，你的英文名字必须是%^HIY%^ %d %^NOR%^到%^HIY%^ %d %^NOR%^个英文字母。\n",
                min_length_id, max_length_id);
        }

        return 0;
    }

    return 1;
}

int check_legal_name(string name, int is_gmcp)
{
    int len;

    if (!is_chinese(name)) {
        if (!is_gmcp) {
            ansi_write("对不起，请您用%^HIY%^「中文」%^NOR%^取名字。\n");
        }

        return 0;
    }

    len = strlen(name);

    if (len < min_length_name || len > max_length_name) {
        if (!is_gmcp) {
            ansi_printf("对不起，你的中文名字必须是%^HIY%^ %d %^NOR%^到%^HIY%^ %d %^NOR%^个汉字。\n",
                min_length_name, max_length_name);
        }

        return 0;
    }

    return 1;
}
