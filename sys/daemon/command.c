// COMMAND_D

#include <ansi.h>
#include <inherit/command.h>

inherit IH_NAME;

void create()
{
    seteuid(ROOT_UID);
    set_name(HIW + "指令精灵" + NOR);
    set_id("COMMAND_D");
}

// *INDENT-OFF*
private nosave mapping default_aliases = ([
    "s": "go south",
    "n": "go north",
    "w": "go west",
    "e": "go east",
    "sd": "go southdown",
    "nd": "go northdown",
    "wd": "go westdown",
    "ed": "go eastdown",
    "su": "go southup",
    "nu": "go northup",
    "wu": "go westup",
    "eu": "go eastup",
    "sw": "go southwest",
    "se": "go southeast",
    "nw": "go northwest",
    "ne": "go northeast",
    "d": "go down",
    "u": "go up",
    "i": "inventory",
    "l": "look",
    "sc": "score",
    "exit": "quit",
]);
// *INDENT-ON*

string process_aliases(string verb)
{
    string *word;
    verb = trim(verb);

    // @TODO: reject command

    switch (verb[0]) {
        case '\'':
            return "say " + verb[1..strlen(verb) - 1];

        case '.':
            return "skip " + verb[1..strlen(verb) - 1];
    }

    word = explode(verb, " ");

    if (sizeof(word) && !undefinedp(default_aliases[word[0]])) {
        word[0] = default_aliases[word[0]];
        return implode(word, " ");
    }

    return verb;
}

mapping search = ([ ]);

void rehash(string dir)
{
    int i;
    string path;
    string *cmds;
    mapping cmdlist;

    if (!sscanf(dir, K_CMD_DIR + "%s", path) && !sscanf(dir, CMD_DIR + "%s", path)) {
        printf("%s 不是有效命令目录, 操作失败。\n", dir);
        return;
    }

    if (dir[sizeof(dir) - 1] != '/') {
        dir += "/";
    }

    cmds = get_dir(dir);
    i = sizeof(cmds);
    cmdlist = allocate_mapping(i);

    // 取所有命令
    while (i--) {
        if (sscanf(cmds[i], "%s.c", cmds[i])) {
            cmdlist[cmds[i]] = dir + cmds[i] + ".c";
        }
    }

    if (sizeof(cmds)) {
        search[dir] = cmdlist;
    }
}

string find_command(string verb, string *path)
{
    int i;
    string file;
    mapping current;

    if (!arrayp(path)) {
        return 0;
    }

    for (i = 0; i < sizeof(path); i++) {
        if (undefinedp(current = search[path[i]])) {
            rehash(path[i]);

            if (undefinedp(current = search[path[i]])) {
                continue;
            }
        }

        if (stringp(file = current[verb])) {
            return file;
        }
    }

    return 0;
}
