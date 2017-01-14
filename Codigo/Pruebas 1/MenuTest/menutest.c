#include "../../menu.h"
#include "../../world.h"

int main()
{
    World     *w = menu();
    Interface *i = world_getInterface(w);
    world_free(w);
    _term_close();
    i_free(i);
    return 1;
}