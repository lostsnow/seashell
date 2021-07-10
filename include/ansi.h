// The standard set of ANSI codes for mudlib use

#ifndef __ANSI_H__
#define __ANSI_H__

#define ESC         "\x1b"
#define CSI         ESC "["

/* Foreground Colors */
#define BLK         CSI "30m"            /* Black    */
#define RED         CSI "31m"            /* Red      */
#define GRN         CSI "32m"            /* Green    */
#define YEL         CSI "33m"            /* Yellow   */
#define BLU         CSI "34m"            /* Blue     */
#define MAG         CSI "35m"            /* Magenta  */
#define CYN         CSI "36m"            /* Cyan     */
#define WHT         CSI "37m"            /* White    */

/* Hi Intensity Foreground Colors */
#define HIK         CSI "1;30m"          /* Black    */
#define HIR         CSI "1;31m"          /* Red      */
#define HIG         CSI "1;32m"          /* Green    */
#define HIY         CSI "1;33m"          /* Yellow   */
#define HIB         CSI "1;34m"          /* Blue     */
#define HIM         CSI "1;35m"          /* Magenta  */
#define HIC         CSI "1;36m"          /* Cyan     */
#define HIW         CSI "1;37m"          /* White    */

/* Background Colors */
#define BBLK        CSI "40m"            /* Black    */
#define BRED        CSI "41m"            /* Red      */
#define BGRN        CSI "42m"            /* Green    */
#define BYEL        CSI "43m"            /* Yellow   */
#define BBLU        CSI "44m"            /* Blue     */
#define BMAG        CSI "45m"            /* Magenta  */
#define BCYN        CSI "46m"            /* Cyan     */
#define BWHT        CSI "47m"            /* White    */

/* High Intensity Background Colors */
#define HBBLK       CSI "40;1m"          /* Black    */
#define HBRED       CSI "41;1m"          /* Red      */
#define HBGRN       CSI "42;1m"          /* Green    */
#define HBYEL       CSI "43;1m"          /* Yellow   */
#define HBBLU       CSI "44;1m"          /* Blue     */
#define HBMAG       CSI "45;1m"          /* Magenta  */
#define HBCYN       CSI "46;1m"          /* Cyan     */
#define HBWHT       CSI "47;1m"          /* White    */

#define REDGRN      CSI "1;31;42m"
#define REDYEL      CSI "1;31;43m"
#define REDBLU      CSI "1;31;44m"
#define REDMAG      CSI "1;31;45m"
#define REDCYN      CSI "1;31;46m"
#define REDWHI      CSI "1;31;47m"
#define GRNRED      CSI "1;32;41m"
#define GRNYEL      CSI "1;32;43m"
#define GRNBLU      CSI "1;32;44m"
#define GRNMAG      CSI "1;32;45m"
#define GRNCYN      CSI "1;32;46m"
#define GRNWHI      CSI "1;32;47m"
#define YELRED      CSI "1;33;41m"
#define YELGRN      CSI "1;33;42m"
#define YELBLU      CSI "1;33;43m"
#define YELMAG      CSI "1;33;45m"
#define YELCYN      CSI "1;33;46m"
#define YELWHI      CSI "1;33;47m"
#define BLURED      CSI "1;34;41m"
#define BLUGRN      CSI "1;34;42m"
#define BLUYEL      CSI "1;34;43m"
#define BLUMAG      CSI "1;34;45m"
#define BLUCYN      CSI "1;34;46m"
#define BLUWHI      CSI "1;34;47m"
#define MAGRED      CSI "1;35;41m"
#define MAGGRN      CSI "1;35;42m"
#define MAGYEL      CSI "1;35;43m"
#define MAGBLU      CSI "1;35;44m"
#define MAGCYN      CSI "1;35;46m"
#define MAGWHI      CSI "1;35;47m"
#define CYNRED      CSI "1;36;41m"
#define CYNGRN      CSI "1;36;42m"
#define CYNYEL      CSI "1;36;43m"
#define CYNBLU      CSI "1;36;44m"
#define CYNMAG      CSI "1;36;45m"
#define CYNWHI      CSI "1;36;47m"
#define WHIRED      CSI "1;37;41m"
#define WHIGRN      CSI "1;37;42m"
#define WHIYEL      CSI "1;37;43m"
#define WHIBLU      CSI "1;37;44m"
#define WHIMAG      CSI "1;37;45m"
#define WHICYN      CSI "1;37;46m"

#define NOR         CSI "2;37;0m"        /* Puts everything back to normal */

/* Additional ansi Esc codes added to ansi.h by Gothic april 23,1993 */
/* Note, these are Esc codes for VT100 terminals, and emulators      */
/*       and they may not all work within the mud                    */
#define BOLD        CSI "1m"             /* Turn on bold mode                        */
#define CLR         CSI "2J"             /* Clear the screen                         */
#define HOME        CSI "H"              /* Send cursor to home position             */
#define REF         CLR HOME             /* Clear screen and home cursor             */
#define BIGTOP      ESC "#3"             /* Dbl height characters, top half          */
#define BIGBOT      ESC "#4"             /* Dbl height characters, bottom half       */
#define SAVEC       CSI "s"              /* Save cursor position                     */
#define REST        CSI "u"              /* Restore cursor to saved position         */
#define REVINDEX    ESC "M"              /* Scroll screen in opposite direction      */
#define SINGW       ESC "#5"             /* Normal, single-width characters          */
#define DBL         ESC "#6"             /* Creates double-width characters          */
#define FRTOP       CSI "2;25r"          /* Freeze top line                          */
#define FRBOT       CSI "1;24r"          /* Freeze bottom line                       */
#define UNFR        CSI "r"              /* Unfreeze top and bottom lines            */
#define BLINK       CSI "5m"             /* Initialize blink mode                    */
#define U           CSI "4m"             /* Initialize underscore mode               */
#define REV         CSI "7m"             /* Turns reverse video mode on              */
#define HIREV       CSI "1,7m"           /* Hi intensity reverse video               */

#define BEEP        "\x07\x07\x07"

#endif // __ANSI_H__
