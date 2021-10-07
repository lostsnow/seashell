inherit IH_CLEAN_UP;

protected string normalize_map(mapping map);

int main(object me, string arg)
{
    mapping list, tlist, p_vars, t_vars;
    mixed *vars;
    mixed val;
    string *vv;
    object ob, ob1;
    string text, id, spec;

    if (arg) {
        sscanf(arg, "%s %s", spec, arg);

        if (arg == "-t" || arg == "-d") {
            spec = arg;
            arg = 0;
        }

        if (spec && spec != "-d" && spec != "-t") {
            arg = spec + " " + arg;
            spec = 0;
        }
    }

    if (!arg || arg == "") {
        ob = me;
    } else if (sscanf(arg, "%s in %s", arg, id) == 2) {
        ob1 = present(id, environment(me));

        if (!ob1) {
            ob1 = present(id, me);
        }

        if (!ob1) {
            return notify_fail("本地无此生物: " + id + "\n");
        }

        if (!ob = present(arg, ob1)) {
            return notify_fail("该生物身上无此物件: " + arg + "\n");
        }
    } else if (arg == "here") {
        ob = environment(me);
    } else {
        arg = lower_case(arg);

        ob = present(arg, environment(me));

        if (!ob) {
            ob = find_player(arg);
        }

        if (!ob) {
            ob = find_living(arg);
        }

        if (!ob) {
            ob = present(arg, me);
        }

        if (!ob) {
            return notify_fail("Data: 无法找到此对象: " + arg + "。\n");
        }
    }

    vars = variables(ob, 1);
    list = ob->query_properties();
    tlist = ob->query_temp_properties();

    p_vars = ([]);
    t_vars = ([]);

    foreach (vv in vars) {
        if (!stringp(vv[0]) || vv[0] == "properties" || vv[0] == "temp_properties") {
            continue;
        }

        if (strsrch(vv[1], "private") != -1) {
            continue;
        }

        val = fetch_variable(vv[0], ob);

        if (!val) {
            continue;
        }

        if (strsrch(vv[1], "nosave") == -1) {
            p_vars[vv[0]] = val;
        } else {
            t_vars[vv[0]] = val;
        }
    }

    if (!mapp(p_vars) && !mapp(t_vars) && !mapp(list) && !mapp(tlist)) {
        return  notify_fail("Data: 此对象并没有储存任何的资料。\n");
    }

    text = "Object: " + base_name(ob) + ".c\n\n";

    text += "%^HIY%^VARIABLE:%^NOR%^\n";
    text += normalize_map(p_vars);
    text += "\n%^HIY%^总共有 " + sizeof(p_vars) + " 个储存的变量。%^NOR%^\n\n";

    text += "%^HIY%^TEMP VARIABLE:%^NOR%^\n";
    text += normalize_map(t_vars);
    text += "\n%^HIY%^总共有 " + sizeof(t_vars) + " 个暂存的变量。%^NOR%^\n\n";

    text += "%^HIY%^PROPERTY:%^NOR%^\n";
    text += normalize_map(list);
    text += "\n%^HIY%^总共有 " + sizeof(list) + " 个储存的属性。%^NOR%^\n\n";

    text += "%^HIY%^TEMP PROPERTY:%^NOR%^\n";
    text += normalize_map(tlist);
    text += "\n%^HIY%^总共有 " + sizeof(tlist) + " 个暂存的属性。%^NOR%^\n\n";

    me->start_more(ansi_sprintf(text));
    return 1;
}

protected string normalize_map(mapping map)
{
    string *map_keys, *map_vals;
    int i;

    if (!mapp(map) || !sizeof(map)) {
        return "";
    }

    map_keys = keys(map);
    map_keys = sort_array(map_keys, "strcmp", this_object());

    map_vals = ({});

    for (i = 0; i < sizeof(map_keys); i++) {
        map_vals += ({ sprintf("%-16s:%O", map_keys[i], map[map_keys[i]]) });
    }

    return implode(map_vals, "\n");
}

string help(object  me)
{
// *INDENT-OFF*
    return @LONG
指令格式: data <-t|-d> <玩家|物件|here> <in 玩家或生物>

指令范例:
    data                  <--  看自己的所有  data  base
    data -t               <--  看自己的暂存资料
    data -d               <--  看自己的永久资料
    data -t here          <--  看所在房间的暂时资料
    data wade             <--  看 wade 这个玩家(或物件)的所有资料
    data board            <--  看版子的资料
    data cloth in wade    <--  看 wade 身上的 cloth 的资料

指令说明:
    此命令让你可以观看所指定物件的资料，且将会以 more 的
方式输出，如果没有指定数，则自动以使用者为参数。其中的 -t 选
项可以显示暂时变数, -d 选项可以只显示永久变数， 所要看的对象
可以是玩家或任何物件。
LONG;
// *INDENT-ON*
}
