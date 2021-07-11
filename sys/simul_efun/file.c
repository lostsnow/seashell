// sefun: file

void log_error(string message);

int file_exists(string str) {
    return (file_size(str) > -1);
}

mixed *separate_file(string file)
{
    string *list;
    string str;
    int i;

    if (!file_exists(file))
    {
        log_error("file " + file + " not found\n");
        return ({});
    }

    str = read_file(file);

    if (!str) {
        return ({});
    }

    str = replace_string(str, "\r", "");
    list = explode(str, "\n");

    for (i = 0; i < sizeof(list); i++) {
        if (list[i] == "" || list[i][0] == '#') {
            list[i] = 0;
        }
    }

    list -= ({ 0 });
    return list;
}

void assure_file(string file)
{
    string path, *dir;
    int i;

    if (file_exists(file)) {
        return;
    }

    dir = explode(file, "/");

    if (file[strlen(file) - 1] != '/') {
        // the file is refer to a file, not directory
        dir = dir[0..sizeof(dir) - 2];
    }

    path = "";

    for (i = 0; i < sizeof(dir); i++) {
        path += "/" + dir[i];
        mkdir(path);
    }

    return;
}

void log_file(string file, string arg)
{
    assure_file(LOG_DIR + file);
    write_file(LOG_DIR + file, arg);
}

void log_time(string file, string message)
{
    log_file(file, sprintf("[%s] %s", now(), message));
}

void log_error(string message)
{
    log_time("error.log", message);
}

void cat(string file)
{
    write(read_file(file));
}

void ansi_cat(string file)
{
    write(ansi_filter(read_file(file)));
}
