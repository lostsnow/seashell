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

    if (objectp(find_object(file))) {
        return;
    }

    if (err = catch (call_other(file, "??"))) {
        write(sprintf("preloading %s failed: %s\n", file, err));
    }
}
