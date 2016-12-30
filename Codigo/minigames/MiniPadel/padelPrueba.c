#include "miniPadel.h"

int main()
{
    int       sol;
    char      c;
    char      s[90] = "Presiona 'h' para modo dificil o 'e' para modo facil:\n";
    Interface *i;
    _term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    i_drawAll(i);


    i_drawStr(i, (char *) s, 6, 6, 1);
    do
    {
        c = _read_key();
    } while (c != 'h' && c != 'e' && c != 'E' && c != 'H');
    if (c == 'e' || c == 'E')
        sol = miniPadel(i, 0);
    else
        sol = miniPadel(i, 1);

    i_free(i);
    _term_close();
    return 1;
}