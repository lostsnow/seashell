// sefun: message

void writeln(mixed message)
{
    write(message + "\n");
}

void ansi_write(string content)
{
    write(ansi_filter(content));
}

varargs void ansi_printf(string msg, mixed* args...)
{
    msg = sprintf(msg, args...);
    ansi_write(msg);
}
