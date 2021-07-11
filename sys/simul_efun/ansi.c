// sefun: ansi

#include <ansi.h>

string color_filter(string content)
{
    if (!content) {
        return "";
    }

    // Foreground color
    content = replace_string(content, "$BLK$", BLK);
    content = replace_string(content, "$RED$", RED);
    content = replace_string(content, "$GRN$", GRN);
    content = replace_string(content, "$YEL$", YEL);
    content = replace_string(content, "$BLU$", BLU);
    content = replace_string(content, "$MAG$", MAG);
    content = replace_string(content, "$CYN$", CYN);
    content = replace_string(content, "$WHT$", WHT);
    // Hi Intensity Foreground Colors
    content = replace_string(content, "$HIK$", HIK);
    content = replace_string(content, "$HIR$", HIR);
    content = replace_string(content, "$HIG$", HIG);
    content = replace_string(content, "$HIY$", HIY);
    content = replace_string(content, "$HIB$", HIB);
    content = replace_string(content, "$HIM$", HIM);
    content = replace_string(content, "$HIC$", HIC);
    content = replace_string(content, "$HIW$", HIW);
    // Background color
    content = replace_string(content, "$BBLK$", BBLK);
    content = replace_string(content, "$BRED$", BRED);
    content = replace_string(content, "$BGRN$", BGRN);
    content = replace_string(content, "$BYEL$", BYEL);
    content = replace_string(content, "$BBLU$", BBLU);
    content = replace_string(content, "$BMAG$", BMAG);
    content = replace_string(content, "$BCYN$", BCYN);
    content = replace_string(content, "$BWHT$", BWHT);
    // High Intensity Background Colors
    content = replace_string(content, "$HBBLK$", HBBLK);
    content = replace_string(content, "$HBRED$", HBRED);
    content = replace_string(content, "$HBGRN$", HBGRN);
    content = replace_string(content, "$HBYEL$", HBYEL);
    content = replace_string(content, "$HBBLU$", HBBLU);
    content = replace_string(content, "$HBMAG$", HBMAG);
    content = replace_string(content, "$HBCYN$", HBCYN);
    content = replace_string(content, "$HBWHT$", HBWHT);
    // Reset
    content = replace_string(content, "$NOR$", NOR);
    // Additional
    content = replace_string(content, "$U$", U);
    content = replace_string(content, "$BLINK$", BLINK);
    content = replace_string(content, "$REV$", REV);
    content = replace_string(content, "$HIREV$", HIREV);
    content = replace_string(content, "$BOLD$", BOLD);
    return content;
}

string remove_ansi(string content)
{
    if (!content) {
        return "";
    }

    // Foreground color
    content = replace_string(content, BLK, "");
    content = replace_string(content, RED, "");
    content = replace_string(content, GRN, "");
    content = replace_string(content, YEL, "");
    content = replace_string(content, BLU, "");
    content = replace_string(content, MAG, "");
    content = replace_string(content, CYN, "");
    content = replace_string(content, WHT, "");
    // Hi Intensity Foreground Colors
    content = replace_string(content, HIK, "");
    content = replace_string(content, HIR, "");
    content = replace_string(content, HIG, "");
    content = replace_string(content, HIY, "");
    content = replace_string(content, HIB, "");
    content = replace_string(content, HIM, "");
    content = replace_string(content, HIC, "");
    content = replace_string(content, HIW, "");
    // Background color
    content = replace_string(content, BBLK, "");
    content = replace_string(content, BRED, "");
    content = replace_string(content, BGRN, "");
    content = replace_string(content, BYEL, "");
    content = replace_string(content, BBLU, "");
    content = replace_string(content, BMAG, "");
    content = replace_string(content, BCYN, "");
    content = replace_string(content, BWHT, "");
    // High Intensity Background Colors
    content = replace_string(content, HBBLK, "");
    content = replace_string(content, HBRED, "");
    content = replace_string(content, HBGRN, "");
    content = replace_string(content, HBYEL, "");
    content = replace_string(content, HBBLU, "");
    content = replace_string(content, HBMAG, "");
    content = replace_string(content, HBCYN, "");
    content = replace_string(content, HBWHT, "");
    // Reset
    content = replace_string(content, NOR, "");
    // Additional
    content = replace_string(content, U, "");
    content = replace_string(content, BLINK, "");
    content = replace_string(content, REV, "");
    content = replace_string(content, HIREV, "");
    content = replace_string(content, BOLD, "");

    return content;
}
