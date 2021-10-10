#include <ansi.h>

inherit IH_CLEAN_UP;

int main(object me, string arg)
{
    int i;
    string colors_256 = "";

    tell_object(me, MAG + "#" + HIY + "颜色列表" + NOR + MAG + "#\n" + NOR);
    tell_object(me,
        "  BLK " + BLK + "黑色" + NOR + " HIK " + HIK + "黑色" + NOR +
        "  HBBLK " + HBBLK + "黑色" + NOR + " BBLK " + BBLK + "黑色" + NOR + "\n" +
        "  RED " + RED + "红色" + NOR + " HIR " + HIR + "红色" + NOR +
        "  HBRED " + HBRED + "红色" + NOR + " BRED " + BRED + "红色" + NOR + "\n" +
        "  GRN " + GRN + "绿色" + NOR + " HIG " + HIG + "绿色" + NOR +
        "  HBGRN " + HBGRN + "绿色" + NOR + " BGRN " + BGRN + "绿色" + NOR + "\n" +
        "  YEL " + YEL + "黄色" + NOR + " HIY " + HIY + "黄色" + NOR +
        "  HBYEL " + HBYEL + "黄色" + NOR + " BYEL " + BYEL + "黄色" + NOR + "\n" +
        "  BLU " + BLU + "蓝色" + NOR + " HIB " + HIB + "蓝色" + NOR +
        "  HBBLU " + HBBLU + "蓝色" + NOR + " BBLU " + BBLU + "蓝色" + NOR + "\n" +
        "  MAG " + MAG + "品红" + NOR + " HIM " + HIM + "品红" + NOR +
        "  HBMAG " + HBMAG + "品红" + NOR + " BMAG " + BMAG + "品红" + NOR + "\n" +
        "  CYN " + CYN + "青色" + NOR + " HIC " + HIC + "青色" + NOR +
        "  HBCYN " + HBCYN + "青色" + NOR + " BCYN " + BCYN + "青色" + NOR + "\n" +
        "  WHT " + WHT + "白色" + NOR + " HIW " + HIW + "白色" + NOR
        "  HBWHT " + HBWHT + "白色" + NOR + " BWHT " + BWHT + "白色" + NOR + "\n\n");

    for (i = 0; i < 256; i++) {
        colors_256 += ansi("256B-" + i, sprintf("%|5s", "" + i));
        if (i == 7 || i == 15) {
            colors_256 += "\n";
        }

        if (i > 15 && (i-15) % 12 == 0) {
            colors_256 += "\n";
        }
    }

    tell_object(me, colors_256);
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
