// master: preload applies

// master apply::epilog
// return file list to preload
string *epilog(int load_empty)
{
    return separate_file(CONFIG_DIR + PRELOAD_CFG);
}

// master apply::preload
// preload file when a mudlib is starting
void preload(string file)
{
    string err;

    file += ".c";

    if (objectp(find_object(file))) {
        return;
    }

    err = catch (call_other(file, "??"));

    if (err) {
        write(sprintf("preloading %s failed: %s\n", file, err));
    }
}
