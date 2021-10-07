// VOID_OB

inherit IH_ROOM;

void create()
{
    set_short_name("虚空之上");
// *INDENT-OFF*
    set_long_name(@LONG
无尽虚空的上面还是虚空，四周依然是白茫茫的一片，什么也没有。
LONG);
// *INDENT-ON*

// *INDENT-OFF*
    set_exits(
        ([
            "down": __DIR__ + "void",
        ])
    );
// *INDENT-ON*

    set("no_fight", 1);
    set("no_sleep_room", 1);

    setup();
}
