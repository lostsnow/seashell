inherit IH_CLEAN_UP;

string help(object me);

int main(object me, string arg)
{
    object eval_ob;
    string filename, file, path, id;

    id = me->get_id();
    if (id == "") {
        tell_object(me, "用户无效");
    }
    path = "/u/" + id;
    filename = path + "/eval.c";

    if (file_size(path) != -2) {
        mkdir(path);
    }

    if (file_exists(filename)) {
        rm(filename);
    }

    if (eval_ob = find_object(filename)) {
        destruct(eval_ob);
    }

    file = "mixed eval(object me) {\n\t" + arg + ";\n}\n";
    write_file(filename, file, 1);
    tell_object(me, sprintf("Result = %O\n", filename->eval(me)));
    rm(filename);

    if (eval_ob = find_object(file)) {
        destruct(eval_ob);
    }

    return 1;
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式: eval <lpc code>

测试专用，直接执行 LPC 代码片断，如：eval return me
HELP;
// *INDENT-ON*
}