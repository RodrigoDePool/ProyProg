
#define NDEBUG
#include <assert.h>
#include "game.h"

#define RIDDLEPATH     "./Codigo/DATA/game/riddles.txt"
#define STRPATH        "./Codigo/DATA/game/string.txt"
#define CLUEPATH       "./Codigo/DATA/game/clue.txt"
#define DISPLAYPATH    "./Codigo/DATA/game/display.txt"
#define INIROW         1
#define INICOL         1
#define POPUPROW       12
#define POPUPCOL       40

/**********************************************/
/******   LOCAL FUNCTIONS DECLARATION   *******/
/**********************************************/
/*Gives a clue to the space riddle if the player has all the space objects
   Else, tells the player that he cannot be helped
   Returns -1 if anything went wrong*/

int game_help(World *w, String *s);

/*Saves the game and shows message
   Returns -1 if something went wrong, else 0*/
int game_save(World *w, String* s);

/*Lets the player solve the riddle if he has enough objects
   Returns 1 if correct answer, 0 if wrong answer, or -1 if anything went wrong*/
int game_solve(World *w, String *s);


/**********************************************/
/*****   LOCAL FUNCTIONS IMPLEMENTATION   *****/
/**********************************************/

int game_help(World *w, String *s)
{
    assert(w && s);
    FILE      *f = NULL;
    int       i, nlev = world_getPllevel(w);
    char      *clue, c = 0;
    Interface *in = world_getInterface(w);
    if (!in)
        return -1;
    if (nlev < 0)
        return -1;

    if ((world_getNumObjects(w) % 3 != 0) || (world_getNumObjects(w) == 0))
    {
        /*Not enough objects for the clue*/
        string_drawLines(in, string_getString(s, 0), INIROW, INICOL, 3, '\n', '*');
        c = _read_key();
        i_cleanCommand(in);
    }
    else
    {
        f = fopen(CLUEPATH, "r");
        if (f == NULL)
        {
            return -1;
        }
        else
        {
            /*AQUI ASUMO QUE LA PRIMERA CLUE ES LA DEL LEVEL 0, NO 1*/
            for (i = 0; i < nlev; i++)
                fscanf(f, "%*[^|]|\n");
            fscanf(f, "%m[^|]|\n", &clue);
            if (clue == NULL)
            {
                fclose(f);
                return -1;
            }
            else
            {
                i_drawStrMap(in, clue, INIROW, INICOL, 3);
                free(clue);
            }
        }
        fclose(f);
    }

    return 0;
}


int game_save(World *w, String* s)
{
    assert(w && s);
    Interface *i = world_getInterface(w);
    char      c;
    if (!i)
        return -1;

    if (world_saveToFile(w, NULL) == -1)
    {
        /*Fail to save string*/
        string_drawLines(i, string_getString(s, 1), INIROW, INICOL, 3, '\n', '*');
        c = _read_key();
        return -1;
    }
    else
    {
        /*Successfully saved*/
        string_drawLines(i, string_getString(s, 2), INIROW, INICOL, 3, '\n', '*');
        c = _read_key();
        return 0;
    }
}




int game_solve(World *w, String *s)
{
    assert(w && s);
    Interface *i = world_getInterface(w);
    if (!i)
        return -1;
    char  pl_sol[20], *lev_sol;
    char  c;
    int   nlev;
    Level *l;

    /*Check if the player has enough objects*/
    nlev = world_getPllevel(w);
    if (nlev < -1)
        return -1;
    if (world_getNumObjects(w) < (3 + (3 * nlev)))
    {
        string_drawLines(i, string_getString(s, 6), POPUPROW, POPUPCOL, 1, '\n', '*');
        c = _read_key();
        i_drawAll(i);
        return 0;
    }

    /*"Enter the solution" string*/
    string_drawLines(i, string_getString(s, 3), INIROW, INICOL, 3, '\n', '*');

    /*Read the solution and writes it in row = 1, col = 1*/
    _term_close();
    printf("%c[%d;%dH", 27, 39, 3); /*Moving the pointer*/
    fscanf(stdin, "%s", pl_sol);
    _term_init();

    /*Non se si la interfaz se borra, pongo idrawall por si acasp*/
    i_drawAll(i);

    /*Get the pointer associated to that level number*/
    l = world_getLevel(w, nlev);
    if (l == NULL)
        return -1;

    if (strcmp(pl_sol, l->solution) == 0)
    {
        /*You passed level string*/
        string_drawLines(i, string_getString(s, 4), POPUPROW, POPUPCOL, 1, '\n', '*');
        c = _read_key();
        c = _read_key();
        i_drawAll(i);
        return 1;
    }
    else
    {
        /*Youre wrong string*/
        string_drawLines(i, string_getString(s, 5), POPUPROW, POPUPCOL, 1, '\n', '*');
        c = _read_key();
        c = _read_key();
        i_drawAll(i);
        return 0;
    }
}




/**********************************************/
/****   PUBLIC FUNCTIONS IMPLEMENTATION   *****/
/**********************************************/

int game_f(World *w, int n)
{
    assert(w && n > -1 && n < 3);
    String *s  = string_ini(STRPATH);
    int    ret = 0;

    /*Clean evrything before calling the proper function*/
    i_cleanCommand(world_getInterface(w));

    if (s == NULL)
        return -1;

    if (n == 0)
    {
        return game_help(w, s);
    }
    else if (n == 1)
    {
        ret = game_save(w, s);
        i_cleanCommand(world_getInterface(w));
        return ret;
    }
    else if (n == 2)
    {
        ret = game_solve(w, s);
        i_cleanCommand(world_getInterface(w));
        return ret;
    }
}

int game_objInLevel(World *w)
{
    assert(w);
    int nlev = world_getPllevel(w);
    int nobj = world_getNumObjects(w);
    if ((nlev > -1 && nobj == (nlev + 1) * 3) || nobj == 12)
        return 3;
    if (nobj >= 0)
        return nobj % 3;
    return -1;
}

int game_drawDisplay(World *w)
{
    assert(w);
    String    *s;
    int       sid, nlev, nobj, st, i;
    char      *sdesc, *ldesc;
    Interface *in = world_getInterface(w);
    if (!in)
        return -1;

    i_cleanDisplay(in);
    i_readFile(in, DISPLAYPATH, 0, 0, 2);

    s = string_ini(RIDDLEPATH);
    if (s == NULL || string_getNumber(s) != 12)
    {
        return -1;
    }

    /*With the level, what riddle to use,
       with the number ob objects, the number of parts to show*/


    /* Riddle starts at row 3, 6, 9
       Description at row 14*/
    nlev = world_getPllevel(w);
    nobj = game_objInLevel(w);
    if (nlev < -1 || nobj < 0)
    {
        string_free(s);
        return -1;
    }

    /*Print riddle*/
    for (i = 0; i < nobj; i++)
    {
        st = (3 * nlev) + i;
        string_drawLines(in, string_getString(s, st), 3 * i + 4, 1, 2, '\n', '*');
    }

    /*Print descriptions*/
    sid   = world_getPlSpaceID(w);
    sdesc = space_getSDesc(world_getSpace(w, sid));
    if (sdesc == NULL)
    {
        string_free(s);
        return -1;
    }

    i_drawStr(in, sdesc, 16, 1, 2);
    free(sdesc);
    ldesc = space_getLDesc(world_getSpace(w, sid));
    if (ldesc == NULL)
    {
        string_free(s);
        return -1;
    }
    i_drawStr(in, ldesc, 17, 1, 2);
    free(ldesc);

    string_free(s);
    return 0;
}

