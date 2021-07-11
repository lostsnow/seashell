// sefun: time
#include <localtime.h>

string datetime(int t)
{
    mixed *loc;
    loc = localtime(t);
    return sprintf("%d-%02d-%02d %02d:%02d:%02d", loc[LT_YEAR], loc[LT_MON] + 1, loc[LT_MDAY],
            loc[LT_HOUR], loc[LT_MIN], loc[LT_SEC]);
}

string now()
{
    return datetime(time());
}
