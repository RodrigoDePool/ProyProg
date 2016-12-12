#include <stdlib.h>
#include "interface.h"
typedef struct _Snake Snake;

Snake *snake_ini(int* coordinates);
void snake_free(Snake* s);
void snake_move(Interface* i, int dir);


