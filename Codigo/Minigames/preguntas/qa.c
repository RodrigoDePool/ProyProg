#include "qa.h"
#define NDEBUG
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "../../Animations/animations.h"
#define PATHLUCIA         "./Codigo/DATA/miniInst/lucia/preguntas.txt"
#define PATHPREGUNTAS     "Codigo/DATA/miniInst/preguntas/preguntas.txt"
#define INSTPATH          "Codigo/DATA/miniInst/preguntas/instructions.txt"
#define PREGUNTAS_INFO    "./Codigo/DATA/miniInst/preguntas/info.txt"
#define LUCIA_INFO        "./Codigo/DATA/miniInst/lucia/info.txt"
#define LUCIA_ASCII       "./Codigo/DATA/miniInst/lucia/lucia_ascii"

struct _Game
{
    char     *intro;
    char     *correct;
    char     *incorrect;
    char     *dunno;
    char     *won;
    int      nquestions;
    Question **q;
};

struct _Question
{
    char   *person;
    char   *qu;
    int    numans;
    Answer **ans;
};

struct _Answer
{
    char code;
    int  truth;
    char *answer;
};


/*************************************************/
/********* LOCAL FUNCTIONS DECLARATION ***********/
/*************************************************/


/*Copied from the cop*/
char *unpack_answer(char *ans, char *object, char separator);

/*Given a game struct, builds and writes the intro of a certain question
   "Imagine arroz asked you, "habicbuela?" what whoukd you answer?"
   Returns -1 if anything went wrong
 */
int build_intro(Interface *in, Game* g, int i, int row, int col, int level);

/*Checks if the choice made for the question q is ok or not.
   Writes a message on the board saying it, in (row, col) NOT MAP COORDS
   Returns 1/0 depending on the choice being correct or not
   if no matching code, returns -1*/
int answer_check(Interface *in, Game *g, Question *q, int row, int col, char choice);

/* This function will be called as a thread from last_answer, to check if a
   character has been pressed in the last answer. If so, the game would be lost*/
void * last_answer_check(void *c);

/*This executes (writes and checks) the last question (i-esima)
   Returns -1 in case of error, 1 if the player didnt answer for 15 secs, else 0*/
int last_answer(Interface *in, Game *g, int i, int *row, int col, int level);

/*Executes the Lucia game if level = 2; else the normal one
   If level is not going to be 2, the .txt containing n questions must have "n+1"
   in the second line (nquestions line) */
int qa(Interface *in, int level);


/*************************************************/
/******* GLOBAL FUNCTIONS IMPLEMENTATION *********/
/*************************************************/


Game *game_ini(FILE *f)
{
    assert(f);
    int  i, j;
    Game *g;
    g = (Game *) malloc(sizeof(Game));
    if (g == NULL)
        return NULL;
    fscanf(f, "%m[^\n]\n", &(g->intro));
    if (g->intro == NULL)
    {
        free(g);
        return NULL;
    }
    fscanf(f, "%m[^\n]\n", &(g->correct));
    if (g->intro == NULL)
    {
        free(g);
        return NULL;
    }
    fscanf(f, "%m[^\n]\n", &(g->incorrect));
    if (g->intro == NULL)
    {
        free(g);
        return NULL;
    }
    fscanf(f, "%m[^\n]\n", &(g->dunno));
    if (g->intro == NULL)
    {
        free(g);
        return NULL;
    }
    fscanf(f, "%m[^\n]\n", &(g->won));
    if (g->intro == NULL)
    {
        free(g);
        return NULL;
    }

    fscanf(f, "%d\n", &(g->nquestions));

    /*Scan all the questions*/
    g->q = (Question * *) malloc(g->nquestions * sizeof(Question *));
    for (i = 0; i < g->nquestions; i++)
    {
        if ((g->q[i] = question_ini(f)) == NULL)
        {
            for (j = 0; j < i; j++)
            {
                question_free(g->q[j]);
            }
            free(g->q);
            free(g);
            return NULL;
        }
    }

    return g;
}

Question *question_ini(FILE *f)
{
    assert(f);
    int      i, j;
    Question *q = (Question *) malloc(sizeof(Question));
    if (q == NULL)
        return NULL;
    fscanf(f, "%m[^\n]\n", &(q->person));
    if (q->person == NULL)
    {
        free(q);
        return NULL;
    }
    fscanf(f, "%m[^\n]\n", &(q->qu));
    if (q->qu == NULL)
    {
        free(q->person);
        free(q);
        return NULL;
    }
    fscanf(f, "%d\n", &(q->numans));
    q->ans = (Answer * *) malloc(q->numans * sizeof(Answer *));
    if (q->ans == NULL)
    {
        free(q->qu);
        free(q->person);
        free(q);
        return NULL;
    }

    /*scan all the answers*/
    for (i = 0; i < q->numans; i++)
    {
        if ((q->ans[i] = answer_ini(f)) == NULL)
        {
            for (j = 0; j < i; j++)
            {
                answer_free(q->ans[j]);
            }
            free(q->ans);
            free(q->qu);
            free(q->person);
            free(q);
            return NULL;
        }
    }
    return q;
}
Answer *answer_ini(FILE *f)
{
    assert(f);
    Answer *a = (Answer *) malloc(sizeof(Answer));
    if (a == NULL)
        return NULL;
    fscanf(f, "%c %d ", &(a->code), &(a->truth));
    fscanf(f, "%m[^\n]\n", &(a->answer));
    if (a->answer == NULL)
    {
        free(a);
        return NULL;
    }
    return a;
}

void game_free(Game *g)
{
    int i;
    if (g)
    {
        if (g->intro)
            free(g->intro);
        if (g->correct)
            free(g->correct);
        if (g->incorrect)
            free(g->incorrect);
        if (g->won)
            free(g->won);
        if (g->dunno)
            free(g->dunno);

        if (g->q)
        {
            for (i = 0; i < g->nquestions; i++)
            {
                if (g->q[i])
                    question_free(g->q[i]);
            }
            free(g->q);
        }
        free(g);
    }
}

void question_free(Question *q)
{
    int i;
    if (q)
    {
        if (q->person)
            free(q->person);
        if (q->qu)
            free(q->qu);
        if (q->ans)
        {
            for (i = 0; i < q->numans; i++)
            {
                if (q->ans[i])
                    answer_free(q->ans[i]);
            }
            free(q->ans);
        }
        free(q);
    }
}

void answer_free(Answer *a)
{
    if (a)
    {
        if (a->answer)
            free(a->answer);
        free(a);
    }
}

int lucia(Interface *in)
{
    assert(in);
    return qa(in, 1);
}

int questions(Interface *in)
{
    int n;
    assert(in);
    n = qa(in, 0);
    if (n == 1)
    {
        Four_animation_call3(in);
    }
    return n;
}





/*************************************************/
/****** LOCAL FUNCTIONS IMPLEMENTATION ***********/
/*************************************************/

char *unpack_answer(char *ans, char *object, char separator)
{
    assert(ans && object);
    char *answer = NULL, *pc1, *pc2;
    int  obj_len = strlen(object);
    int  n_stars = 0;

    /*Initializes answ with enough space*/
    for (pc1 = ans; *pc1 != '\0'; pc1++)
    {
        if (*pc1 == separator)
            n_stars++;
    }
    answer = (char *) malloc(strlen(ans) + ((n_stars * obj_len) + 1) * sizeof(char));
    if (!answer)
        return NULL;

    /*Copy ans in answer replacing * with object*/
    for (pc1 = ans, pc2 = answer; *pc1 != '\0'; pc1++)
    {
        if (*pc1 != separator)
        {
            *pc2 = *pc1;
            pc2++;
        }
        else
        {
            for (int i = 0; i < obj_len; i++)
                *pc2++ = object[i];
            /*			pc2 += obj_len; */
        }
    }
    *pc2 = '\0';
    return answer;
}


int build_intro(Interface *in, Game* g, int i, int row, int col, int level)
{
    char *intro, *buff, size;
    /*Build intro using a cop function*/
    /*First we replace the person name,then the question between " "*/
    intro = unpack_answer(g->intro, g->q[i]->person, '*');
    buff  = unpack_answer(intro, g->q[i]->qu, ')');
    free(intro);
    /*We have to add a \n at the end of the question*/
    size  = 1 + strlen(buff);
    intro = (char *) malloc((size + 1) * sizeof(char));
    if (intro == NULL)
    {
        free(buff);
        return -1;
    }

    strcpy(intro, buff);
    intro[strlen(buff) + 1] = '\n';
    intro[strlen(buff) + 2] = '\0';
    /*Clean board to erase previous question*/
    i_cleanMap(in);
    if (level == 1)
    {
        i_readFile(in, LUCIA_ASCII, 17, 1, 1);
    }
    /*Ask question and check the answer*/
    i_drawStr(in, intro, row, col, 1);
    free(intro);
    free(buff);
    return 0;
}

int answer_check(Interface *in, Game *g, Question *q, int row, int col, char choice)
{
    assert(in && q && row > 0 && col > 0);
    int i;
    for (i = 0; i < q->numans; i++)
    {
        if (q->ans[i]->code == choice)
        {
            if (q->ans[i]->truth == 1)
            {
                i_drawStr(in, g->correct, row + 1, col, 1);
                sleep(1);
                return 1;
            }
            i_drawStr(in, g->incorrect, row + 1, col, 1);
            sleep(1);
            return 0;
        }
    }
    /*If the choice didnt match any answer*/
    i_drawStr(in, g->dunno, 1 + row, col, 1);
    sleep(2);
    i_drawStr(in, "                                                              ", 1 + row, col, 1);
    return -1;
}

void * last_answer_check(void *c)
{
    *((char *) c) = _read_key();
    return NULL;
}

int last_answer(Interface *in, Game *g, int i, int *row, int col, int level)
{
    int       j;
    char      c = 0;
    time_t    ini, now;
    pthread_t pth;
    *row = 5;

    if (build_intro(in, g, i, *row, col, level) == -1)
    {
        return -1;
    }

    (*row)++;
    for (j = 0; j < g->q[i]->numans; j++)
    {
        i_writeChar(in, g->q[i]->ans[j]->code, ++(*row), col, 1);
        i_writeChar(in, ' ', *row, col + 1, 1);
        i_drawStr(in, g->q[i]->ans[j]->answer, *row, col + 2, 1);
    }
    (*row)++;
    /*Create thread for pad movement*/
    pthread_create(&pth, NULL, last_answer_check, (void *) (&c));
    ini = time(NULL);
    do
    {
        sleep(1);
        now = time(NULL) - ini;
    } while (now < 15 && c == 0);

    /*If a key was pressed, the game has been lost. Else, won*/
    if (c != 0)
    {
        i_drawStr(in, g->incorrect, ++(*row), col, 1);
        sleep(1);
        return 0;
    }

    i_drawStr(in, g->correct, ++(*row), col, 1);
    sleep(1);

    pthread_cancel(pth);
    return 1;
}

int qa(Interface *in, int level)
{
    assert(in);
    int  i, j, row, col, result;
    char choice;
    FILE *f;

    /*Print instructions*/
    i_cleanDisplay(in);
    i_cleanMap(in);
    i_cleanCommand(in);
    i_readFile(in, INSTPATH, 1, 1, 2);


    if (level == 1)
    {
        f = fopen(PATHLUCIA, "r");
        i_readFile(in, LUCIA_INFO, 6, 19, 1);
        _read_key();
        i_cleanMap(in);
    }
    else
    {
        f = fopen(PATHPREGUNTAS, "r");
        i_readFile(in, PREGUNTAS_INFO, 9, 18, 1);
        _read_key();
        i_cleanMap(in);
    }

    if (f == NULL)
    {
        return -1;
    }
    Game *g = game_ini(f);
    fclose(f);
    if (g == NULL)
    {
        return -1;
    }
    /*We build and ask each question*/
    for (i = 0; i < g->nquestions - 1; i++)
    {
        row = 5;
        col = 10;

        if (build_intro(in, g, i, row, col, level) == -1)
        {
            game_free(g);
            i_cleanDisplay(in);
            i_cleanMap(in);
            return -1;
        }

        row++;
        for (j = 0; j < g->q[i]->numans; j++)
        {
            i_writeChar(in, g->q[i]->ans[j]->code, ++row, col, 1);
            i_writeChar(in, ' ', row, col + 1, 1);
            i_drawStr(in, g->q[i]->ans[j]->answer, row, col + 2, 1);
        }

        do
        {
            choice = _read_key();
            if (choice == 'q')
            {
                i_cleanDisplay(in);
                i_cleanMap(in);
                game_free(g);
                return 0;
            }
            result = answer_check(in, g, g->q[i], 1 + row, col, choice);
        } while (result == -1);

        if (result == 0)
        {
            sleep(1);
            game_free(g);
            i_cleanDisplay(in);
            i_cleanMap(in);
            return 0;
        }
    }


    /*Aqui podemos poner un if level == 2 para que solo se ejecute si
       es el juego en el que lucia te pega y no el normal de preguntas
       al normal ademas se le pasaria en nquestions una mas de las q realmente
       quiisieras, y añadirias un una pregunta inutil*/
    if (level == 1)
        result = last_answer(in, g, i, &row, col, level);

    if (result != 1)
    {
        game_free(g);
        i_cleanDisplay(in);
        i_cleanMap(in);
        return result;
    }

    /*If the game hasnt returned yet, its because all the answers were correct:
       return 1*/
    i_drawStr(in, g->won, row + 2, col, 1);
    sleep(2);
    i_cleanDisplay(in);
    i_cleanMap(in);
    game_free(g);
    return 1;
}









