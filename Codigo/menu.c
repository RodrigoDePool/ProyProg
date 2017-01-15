#include "menu.h"
#include <string.h>
#include <assert.h>

/*
    Main menu graphical interface
    Return:
        -1 if error
        1 if player wants to go to create new game
        2 for load another game
        3 for exit the game

 */
int mainMenu(Interface *i)
{
    int xpos, ypos, key, linenum = 1;
    /*Y separation between lines*/
    int sep = 2;
    if (i == NULL)
        return -1;
    /*Graphical interface*/
    i_readFile(i, MENU_BASE, 1, 18, 1);
    i_readFile(i, MENU_INST, 9, 2, 2);
    /*Initialize the arrow to first option*/
    xpos = 47;
    ypos = 14;
    i_writeCharMap(i, '-', ypos, xpos, 1);
    i_writeCharMap(i, '>', ypos, xpos + 1, 1);
    do
    {
        key = _read_key();
        if (key == NORTH && linenum > 1)
        {
            linenum--;
            /*we delete the arrow*/
            i_writeCharMap(i, ' ', ypos, xpos, 1);
            i_writeCharMap(i, ' ', ypos, xpos + 1, 1);
            /*change ypos*/
            ypos = ypos - 3;
            /*rewrite the arrow*/
            i_writeCharMap(i, '-', ypos, xpos, 1);
            i_writeCharMap(i, '>', ypos, xpos + 1, 1);
        }
        if (key == SOUTH && linenum < 3)
        {
            linenum++;
            /*we delete the arrow*/
            i_writeCharMap(i, ' ', ypos, xpos, 1);
            i_writeCharMap(i, ' ', ypos, xpos + 1, 1);
            /*change ypos*/
            ypos = ypos + 3;
            /*rewrite the arrow*/
            i_writeCharMap(i, '-', ypos, xpos, 1);
            i_writeCharMap(i, '>', ypos, xpos + 1, 1);
        }
    } while (key != 's' && key != 'S');
    return linenum;
}



/*
    Create menu graphical interface
    It gives the player the option to either go back to main menu or create
    a new game by giving it a name.
    This function will be occupied of copying the default settings for a starting
    game in to a file with the name given by the player, in this new file
    youll be able to save the game without compromising other starting games.
    This path will be added to list Index where you can find all saved games
    Return:
        -1 if error;
        3 if successfully created  a file with given path by player
        0 if exit to main menu

 */
int create_menu(Interface *i, char *path)
{
    int  aux, aux2;
    FILE *f;
    char string[100];

    /*We get the size of the string and the string read, it must have maximium*/
    /*of 50 characters*/
    /*This string indicates to the player to give a name to the campaign*/
    f = fopen(CREATE_COMMAND, "r");
    if (f == NULL)
        return -1;
    fgets(string, 100, f);
    /*Number of chars of string*/
    aux = atoi(string);
    fgets(string, 100, f);
    fclose(f);

    /*We get the interface ready*/
    i_cleanMap(i);
    i_cleanDisplay(i);
    i_cleanCommand(i);
    i_readFile(i, MENU_CREATE, 1, 18, 1);
    i_readFile(i, CREATE_INST, 9, 1, 2);
    i_drawStrMap(i, string, 1, 1, 3);

    /*We make the terminal capable of reading a string again and move the
       pointer to the correct position, this might be format sensible*/
    _term_close();
    aux  = aux + 5;
    aux2 = i_getbr(i);
    aux2 = aux2 + 3;
    printf("%c[%d;%dH", 27, aux2, aux); /*Moving the pointer*/
    fscanf(stdin, "%s", path);
    _term_init();                       /*We leave the terminal as it was*/

    /*If its main we exit to main menu*/
    if (strcmp(path, "main") == 0)
    {
        return 0;
    }

    /*If not, we initialize the file with the given name and add it to the index*/
    /*First we add it to the index*/
    f = fopen(MENU_INDEX, "a");
    if (f == NULL)
        return -1;
    fprintf(f, "%s", path);
    fprintf(f, "\n");
    fclose(f);
    /*We copy default settings to the new file*/
    /*This part is OS sensible*/
    strcpy(string, "cp DATA/LOAD/default DATA/LOAD/");
    strcat(string, path);
    system(string);

    return 3;
}



/*
    LOAD GAME:
        If there are no loaded games in the index this function will
        return 0 indicating you are going back to main menu.
        If there are loaded games in the index the interface will be
        printing them in groups of 4, given the player the option
        to either select one of those loaded games, exit the game to main menu
        or seeing the next 4 saved games on the list (if there are).
    return:
        -1 if Error
        0 if going back to main menu
        3 if the path to the file is successfully copyed
 */
int load_menu(Interface *i, char *path)
{
    char string[4][50]; /*array of 4 strings*/
    char aux[100], key;
    int  j = 0, num;
    FILE *f;
    if (i == NULL)
        return -1;

    /*We open the index*/
    f = fopen(MENU_INDEX, "r");
    if (f == NULL)
        return -1;

    /*if index file is empty return to main menu*/
    if (fgets(string[0], 50, f) == NULL)
        return 0;

    /*if not*/
    /*We leave the pointer back at the top of the file*/
    fseek(f, 0, SEEK_SET);
    while (1)
    {
        /*Initialize the interface*/
        i_cleanMap(i);
        i_cleanDisplay(i);
        i_cleanCommand(i);
        /*we can reuse same menu logo from create*/
        i_readFile(i, MENU_CREATE, 1, 18, 1);
        i_readFile(i, LOAD_INST, 9, 1, 2);

        /*We print the first 4 options in the index*/
        for (j = 0; j < 4 && fgets(string[j], 50, f) != NULL; j++)
        {
            sprintf(aux, "(%d) %s", j + 1, string[j]);
            i_drawStrMap(i, aux, 15 + j * 3, 20, 1);
        }

        /*we read the player option*/
        do
        {
            key = _read_key();
            /*EXIT to main menu*/
            if (key == 'e' || key == 'E')
            {
                fclose(f);
                return 0;
            }
            if (key == '1' || key == '2' || key == '3' || key == '4')
            {
                num = key - '0';
                /*if its a possible option*/
                if (num <= j)
                {
                    fclose(f);
                    strcpy(path, string[num - 1]);
                    /*The string probably was read with the last character as \n*/
                    /*Except if we are talking about the last name in the index*/
                    /*we have to eliminate it*/
                    if (path[strlen(path) - 1] == '\n')
                    {
                        path[strlen(path) - 1] = 0;
                    }
                    return 3;
                }
            }
            /*if the player did not press next or there are no more options
               keep doing the loop*/
        } while ((key != 'n' && key != 'N') || j < 4);
    }
}



/*
    Main function menu, to know how it works look at the .h
 */
World *menu()
{
    Interface *i;
    int       option = 0;
    char      path[50], aux[100];
    World     *w;

    /*Initialize the interface*/
    _term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    if (i == NULL)
        return NULL;
    i_drawAll(i);
    /*We loop in diferent menus*/
    do
    {
        /*we clean displays in case of second loop*/
        i_cleanMap(i);
        i_cleanDisplay(i);
        i_cleanCommand(i);
        i_drawAll(i);
        /*Main menu */
        option = mainMenu(i);

        /*exit*/
        if (option == 3)
        {
            i_free(i);
            _term_close();
            return NULL;
        }

        /*CREATE*/
        else if (option == 1)
        {
            option = create_menu(i, (char *) path);
            if (option == -1)
            {
                _term_close();
                i_free(i);
                printf("ERROR opening file in create menu\n");
                return NULL;
            }
        }
        /*LOAD*/
        else if (option == 2)
        {
            option = load_menu(i, (char *) path);
            if (option == -1)
            {
                _term_close();
                i_free(i);
                printf("ERROR opening file in load menu\n");
                return NULL;
            }
        }
    } while (option != 3);

    /*We clean displays to give it back to main function*/
    i_cleanMap(i);
    i_cleanDisplay(i);
    i_cleanCommand(i);
    i_drawAll(i);


    /*Now path has the name of file in DATA/LOAD where the setting for the*/
    /*game are saved, we need to initialize the world in this path*/
    strcpy(aux, "DATA/LOAD/");
    strcat(aux, path);
    w = worldfromfile(aux, i);
    if (w == NULL)
        return NULL;

    return w;
}












