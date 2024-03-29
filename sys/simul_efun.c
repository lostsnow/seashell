// K_SIMUL_EFUN_OB

#include "simul_efun/std/json.c"

#include "simul_efun/uid.c"
#include "simul_efun/ansi.c"
#include "simul_efun/table.c"
#include "simul_efun/string.c"
#include "simul_efun/time.c"

#include "simul_efun/chinese.c"
#include "simul_efun/message.c"
#include "simul_efun/file.c"

void create()
{
    init_ansi();
    efun::write("simul_efun: loaded successfully.\n");
}
