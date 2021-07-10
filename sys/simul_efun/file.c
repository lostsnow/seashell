void assure_file(string file)
{
    string path, *dir;
    int i;

    if (file_size(file) != -1) {
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
    log_file(file, sprintf("[%s] %s", datetime(time()), message));
}

void log_error(string message)
{
    log_file("error.log", sprintf("[%s] %s", datetime(time()), message));
}

void cat(string file)
{
    write(read_file(file));
}

void color_cat(string file)
{
    write(color_filter(read_file(file)));
}
