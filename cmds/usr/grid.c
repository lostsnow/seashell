#include <ansi.h>

inherit IH_CLEAN_UP;

int main(object me, string arg)
{
    string grid;
    tell_object(me, MAG + "#" + HIY + "网格" + NOR + MAG + "#\n" + NOR);

// *INDENT-OFF*
    grid = @GRID
╔═╦═╗
║  ║  ║
╠═╬═╣
║  ║  ║
╚═╩═╝
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
    grid = @GRID
╓─╥─╖
║  ║  ║
╟─╫─╢
║  ║  ║
╙─╨─╜
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
    grid = @GRID
╒═╤═╕
│  │  │
╞═╪═╡
│  │  │
╘═╧═╛
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
    grid = @GRID
┌─┬─┐
│  │  │
├─┼─┤
│  │  │
└─┴─┘
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
grid = @GRID
╭─┬─╮
│  │  │
├─┼─┤
│  │  │
╰─┴─╯
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
    grid = @GRID
┍━┯━┑
│  │  │
┝━┿━┥
│  │  │
┕━┷━┙
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
    grid = @GRID
┎─┰─┒
┃  ┃  ┃
┠─╂─┨
┃  ┃  ┃
┖─┸─┚
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
    grid = @GRID
┏━┳━┓
┃  ┃  ┃
┣━╋━┫
┃  ┃  ┃
┗━┻━┛
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
    grid = @GRID
┏━━━━━━━┳━━━━━━━┓
┃              ┃              ┃
┡━━━━━━━╇━━━━━━━┩
│              │              │
├───────┼───────┤
│              │              │
├───────┼───────┤
│              │              │
┢━━━━━━━╈━━━━━━━┪
┃              ┃              ┃
┗━━━━━━━┻━━━━━━━┛
GRID;
// *INDENT-ON*
    tell_object(me, grid);

// *INDENT-OFF*
    grid = @GRID
┏━┱─┬─┬─┬─┬─┲━┓
┃  ┃  │  │  │  │  ┃  ┃
┃  ┃  │  │  │  │  ┃  ┃
┃  ┃  │  │  │  │  ┃  ┃
┃  ┃  │  │  │  │  ┃  ┃
┣━╉─┼─┼─┼─┼─╊━┫
┃  ┃  │  │  │  │  ┃  ┃
┃  ┃  │  │  │  │  ┃  ┃
┃  ┃  │  │  │  │  ┃  ┃
┗━┹─┴─┴─┴─┴─┺━┛
GRID;
// *INDENT-ON*
    tell_object(me, grid);

    return 1;
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式：grid

这个命令可以让你查看各种网格布局模式。
HELP;
// *INDENT-ON*
}
