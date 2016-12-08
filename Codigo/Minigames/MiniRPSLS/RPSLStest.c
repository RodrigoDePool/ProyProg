#include "../../interface.h"
#include "miniRPSLS.h"

int main()
{
    Interface *i;
    _term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    i_drawAll(i);
    miniRPSLS(i);
    i_free(i);
    _term_close();
    return 1;
}
