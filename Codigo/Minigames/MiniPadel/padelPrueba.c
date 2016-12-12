#include "miniPadel.h"

int main()
{
    int       sol;
    char      c;
    Interface *i;
    _term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    i_drawAll(i);

    sol = miniPadel(i, 0);

    i_free(i);
    _term_close();
    return 1;
}