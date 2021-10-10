// sefun: ansi

#include <ansi.h>

// *INDENT-OFF*
mapping terminal_codes = ([
    // Foreground color
    "BLK":    BLK,
    "RED":    RED,
    "GRN":    GRN,
    "YEL":    YEL,
    "BLU":    BLU,
    "MAG":    MAG,
    "CYN":    CYN,
    "WHT":    WHT,
    // Hi Intensity Foreground Colors
    "HIK":    HIK,
    "HIR":    HIR,
    "HIG":    HIG,
    "HIY":    HIY,
    "HIB":    HIB,
    "HIM":    HIM,
    "HIC":    HIC,
    "HIW":    HIW,
    // Background color
    "BBLK":    BBLK,
    "BRED":    BRED,
    "BGRN":    BGRN,
    "BYEL":    BYEL,
    "BBLU":    BBLU,
    "BMAG":    BMAG,
    "BCYN":    BCYN,
    "BWHT":    BWHT,
    // High Intensity Background Colors
    "HBBLK":    HBBLK,
    "HBRED":    HBRED,
    "HBGRN":    HBGRN,
    "HBYEL":    HBYEL,
    "HBBLU":    HBBLU,
    "HBMAG":    HBMAG,
    "HBCYN":    HBCYN,
    "HBWHT":    HBWHT,
    // Reset
    "NOR":     NOR,
    // Additional
    "U":       U,
    "BLINK":   BLINK,
    "REV":     REV,
    "HIREV":   HIREV,
    "BOLD":    BOLD
]);

mapping no_color_codes = ([
    // Foreground color
    "BLK":    "",
    "RED":    "",
    "GRN":    "",
    "YEL":    "",
    "BLU":    "",
    "MAG":    "",
    "CYN":    "",
    "WHT":    "",
    // Hi Intensity Foreground Colors
    "HIK":    "",
    "HIR":    "",
    "HIG":    "",
    "HIY":    "",
    "HIB":    "",
    "HIM":    "",
    "HIC":    "",
    "HIW":    "",
    // Background color
    "BBLK":    "",
    "BRED":    "",
    "BGRN":    "",
    "BYEL":    "",
    "BBLU":    "",
    "BMAG":    "",
    "BCYN":    "",
    "BWHT":    "",
    // High Intensity Background Colors
    "HBBLK":    "",
    "HBRED":    "",
    "HBGRN":    "",
    "HBYEL":    "",
    "HBBLU":    "",
    "HBMAG":    "",
    "HBCYN":    "",
    "HBWHT":    "",
    // Reset
    "NOR":     "",
    // Additional
    "U":       "",
    "BLINK":   "",
    "REV":     "",
    "HIREV":   "",
    "BOLD":    ""
]);
// *INDENT-ON*

void init_ansi()
{
    int i;

    for (i = 0; i < 256; i++) {
        terminal_codes["256F-" + i] = CSI + "38;5;" + i + "m";
        terminal_codes["256B-" + i] = CSI + "48;5;" + i + "m";
        no_color_codes["256F-" + i] = "";
        no_color_codes["256B-" + i] = "";
    }
}

string ansi_filter(string content)
{
    if (!content) {
        return "";
    }

    return terminal_colour(content, terminal_codes);;
}

string remove_ansi(string content)
{
    if (!content) {
        return "";
    }

    return terminal_colour(content, no_color_codes);;
}

string ansi(string color, string content)
{
    if (color == "") {
        return ansi_filter(content);
    }

    return ansi_filter(sprintf("%s%s%s", "%^" + upper_case(color) + "%^", content, "%^NOR%^"));
}
