// VOID_OB

inherit IH_ROOM;

void create()
{
    set_short_name("无尽虚空");
// *INDENT-OFF*
    set_long_name(@LONG
这里就是传说中的无尽虚空，你看到四周白茫茫的一片，什么也没有。
只是脚下有一点亮光，似乎传来熟悉的声音。
LONG);
// *INDENT-ON*

// *INDENT-OFF*
    set_exits(
        ([])
    );
// *INDENT-ON*F

    set("no_fight", 1);
    set("no_sleep_room", 1);

    setup();
}
