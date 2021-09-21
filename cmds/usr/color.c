#include <ansi.h>

inherit IH_CLEAN_UP;

int main(object me, string arg)
{
    tell_object(me, MAG + "#" + HIY + "颜色列表" + NOR + MAG + "#\n" + NOR);
    tell_object(me,
        "  黑色- BLK" + BLK + "■■■" + NOR + " HIK" + HIK + "■■■" + NOR +
        "  HBBLK" + HBBLK + "■■■" + NOR + " BBLK" + BBLK + "■■■" + NOR + "\n" +
        "  红色- RED" + RED + "■■■" + NOR + " HIR" + HIR + "■■■" + NOR +
        "  HBRED" + HBRED + "■■■" + NOR + " BRED" + BRED + "■■■" + NOR + "\n" +
        "  绿色- GRN" + GRN + "■■■" + NOR + " HIG" + HIG + "■■■" + NOR +
        "  HBGRN" + HBGRN + "■■■" + NOR + " BGRN" + BGRN + "■■■" + NOR + "\n" +
        "  黄色- YEL" + YEL + "■■■" + NOR + " HIY" + HIY + "■■■" + NOR +
        "  HBYEL" + HBYEL + "■■■" + NOR + " BYEL" + BYEL + "■■■" + NOR + "\n" +
        "  蓝色- BLU" + BLU + "■■■" + NOR + " HIB" + HIB + "■■■" + NOR +
        "  HBBLU" + HBBLU + "■■■" + NOR + " BBLU" + BBLU + "■■■" + NOR + "\n" +
        "  粉色- MAG" + MAG + "■■■" + NOR + " HIM" + HIM + "■■■" + NOR +
        "  HBMAG" + HBMAG + "■■■" + NOR + " BMAG" + BMAG + "■■■" + NOR + "\n" +
        "  青色- CYN" + CYN + "■■■" + NOR + " HIC" + HIC + "■■■" + NOR +
        "  HBCYN" + HBCYN + "■■■" + NOR + " BCYN" + BCYN + "■■■" + NOR + "\n" +
        "  白色- WHT" + WHT + "■■■" + NOR + " HIW" + HIW + "■■■" + NOR
        "  HBWHT" + HBWHT + "■■■" + NOR + " BWHT" + BWHT + "■■■" + NOR + "\n");
    return 1;
}

string help(object me)
{
// *INDENT-OFF*
    return @HELP
命令格式：color

这个命令可以让你知道游戏中各种颜色的 ANSI 控制字符及颜色效果，
从而方便您选择中意的颜色。
HELP;
// *INDENT-ON*
}
