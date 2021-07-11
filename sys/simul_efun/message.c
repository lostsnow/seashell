// sefun: message

void writeln(mixed message)
{
    write(message + "\n");
}

void ansi_write(string content)
{
    write(ansi_filter(content));
}

varargs void ansi_printf(string msg, mixed a1, mixed a2, mixed a3, mixed a4,
    mixed a5, mixed a6, mixed a7, mixed a8, mixed a9, mixed a10,
    mixed a11, mixed a12, mixed a13, mixed a14, mixed a15, mixed a16)
{
    msg = sprintf(msg, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
    ansi_write(msg);
}
