#include "cop.h"
#define NDEBUG
#include <assert.h>

#define MAX_STR    500


/*Stores an internal string which we associate to a function*/
typedef struct   _Assoc
{
    char *int_name;
    pfun f;
};

/*Stores a command which we associate to an internal string, and to the possible
   answers it may return*/
typedef struct   _Ext
{
    char *ext_name;
    char *int_name;
    int  n_ans;
    char **ans;
};

/*Stores an array of assocs, as well as an array of exts an the number of
   elements in each array*/
typedef struct   _CoP
{
    int   numexts;
    Ext   **exts;
    int   numassocs;
    int   maxassocs;
    Assoc **assocs;
};

/*char *strdup(char *);*/

/*EXAMPLE OF THE FILE THIS MODULE WILL READ*/
/*First command will be the error one	   */
/*
    2 ##Num of commands to read
    draw ##typed command, could change
    internal_draw ##wont change
    1 ##num of possible answers
    I'll draw * when I find my pencils
    paint *
    internal_paint
    2
    I wont paint *
    Ive already painted *
 */




/******* LOCAL FUNCTIONS DECLARATION*******/

/*Function: creates ext from an open file      */
/*Parameter: file                              */
/*Returns:  pointer to the Ext/NULL when error */
/*Revision: 5/11/2016                          */
Ext *ext_ini(FILE *f);

/*Function: frees given Ext and all its members*/
/*Parameter: pointer to Ext                    */
/*Returns:                             */
/*Revision: 5/11/16                    */
void ext_free(Ext *e);

/*Function: creates assoc setting members to COPY of int_name and to f*/
/*Parameter: string with the internal name, function pointer          */
/*Returns:  pointer to the Assoc/NULL when error                  */
/*Revision: 5/11/2016                                     */
Assoc *assoc_ini(char *int_name, pfun f);

/*Function: frees given Assoc and all its members        */
/*Parameter: pointer to Assoc                        */
/*Returns: TRUE if int_name was in CoP assocs, else FALSE*/
/*Revision: 5/11/16                          */
void assoc_free(Assoc *a);

/*Function: checks if int_name is añready associated in c       */
/*Parameter: pointer to CoP(NOT COPY), string with int_name         */
/*Returns: pointer to the func associated, NULL if func not found   */
/*Revision: 10/11/16                                    */
pfun assoc_search(char *int_name, CoP *c);

/*Function: checks if verb is in an Ext in c          */
/*Parameter: pointer to CoP, string with verb (ext_name)  */
/*Returns:pointer to the _Ext(NOT COPY); NULL if not found*/
/*Revision: 10/11/16                          */
Ext *ext_search(char *verb, CoP *c);


/******* PUBLIC  FUNCTIONS ********/

CoP *cop_ini(FILE *f)
{
    assert(f);

    int   n_exts, i, j;
    Ext   **e = NULL;
    Assoc **a = NULL;
    CoP   *c  = NULL;
    c = (CoP *) malloc(sizeof(CoP));
    if (c == NULL)
        return NULL;

    /*Start reading file*/

    /*FIRST: array of Exts*/
    fscanf(f, "%d\n", &n_exts);
    e = (Ext * *) malloc(n_exts * sizeof(Ext *));
    if (e == NULL)
    {
        free(c);
        return NULL;
    }
    for (i = 0; i < n_exts; i++)
    {
        e[i] = ext_ini(f);
        if (e[i] == NULL)
        {
            for (j = 0; j < i; j++)
                ext_free(e[j]);
            free(e);
            free(c);
            return NULL;
        }
    }

    /*SECOND: array of Assocs*/

    /*Initial array size: the minimum we'll use (the number of ext cmds)*/
    a = (Assoc * *) malloc(n_exts * sizeof(Assoc *));
    if (a == NULL)
    {
        for (i = 0; i < n_exts; i++)
            ext_free(e[i]);
        free(e);
        free(c);
    }

    /*THIRD: set info to the alloc'd CoP*/
    c->numexts   = n_exts;
    c->exts      = e;
    c->numassocs = 0;
    c->maxassocs = n_exts;
    c->assocs    = a;
    return c;
}

void cop_free(CoP *c)
{
    int i;
    if (c)
    {
        if (c->exts)
        {
            for (i = 0; i < c->numexts; i++)
            {
                if (c->exts[i])
                    ext_free(c->exts[i]);
            }
            free(c->exts);
        }
        if (c->assocs)
        {
            for (i = 0; i < c->maxassocs; i++)
            {
                if (c->assocs[i])
                    assoc_free(c->assocs[i]);
            }
            free(c->assocs);
        }
        free(c);
    }
}

int assoc_add(CoP *c, char *int_name, pfun f)
{
    assert(c && int_name && f);

    Assoc *a = NULL;
    /*Make sure int_name isnt already associated*/
    if (assoc_search(int_name, c) != NULL)
        return -1;
    /*Make sure there is enough room for the new assoc*/
    if (c->numassocs >= c->maxassocs)
    {
        c->maxassocs += 10;
        c->assocs     = (Assoc * *) realloc(c->assocs, (c->maxassocs) * sizeof(Assoc*));
        if (c->assocs == NULL)
            return -1;
    }
    a = assoc_ini(int_name, f);
    if (a == NULL)
        return -1;
    c->assocs[c->numassocs++] = a;
    return c->numassocs;
}

int cop_execute(CoP *c, char *cmd, void *world)
{
    assert(c && cmd && world);

    char   *verb, *object, *cmd_cpy;
    cmd_cpy = strdup(cmd);
    Ext    * e;
    pfun   f;
    char   **answers;
    Status ret;
    /*Separate action and object from cmd*/
    object  = strchr(cmd_cpy, ' ');
    *object = '\0';
    object++;
    verb = cmd_cpy;

    /*Lets see if the verb is actually a command*/
    e = ext_search(verb, c);
    /*And what func the command is associated to*/
    f = assoc_search(e->int_name, c);
    /*generate the proper strings for verb and object*/
    answers = unpack_answers(e, object);
    if (answers == NULL)
        return -1;

    /*Compruebo si las ans se llegaron a unpackar*/

    /*calls f with proper arguments and return its value*/
    ret = (*f)(world, object, answers, e->n_ans);
    for (int i = 0; i < e->n_ans; i++)
    {
        if (answers[i])
            free(answers[i]);
    }
    free(answers);
    free(cmd_cpy);
    return ret;
}


/********LOCAL FUNCTIONS IMPLEMENTATION ********/
Ext *ext_ini(FILE *f)
{
    assert(f);
    char *extname, *intname, **answers;
    int  numans, i, j;
    Ext  *e = (Ext *) malloc(sizeof(Ext));
    if (e == NULL)
        return NULL;

    /*Read ext from file (format is after #defines*/
    /*This strange way of reading strings will read EVERYTHING it reads till
       it finds a \n and store it in the CHAR** given afterwards, allocating
       sufficient memory for it. Then, itll read the /n */
    fscanf(f, "%m[^\n]\n", &extname);
    fscanf(f, "%m[^\n]\n", &intname);
    fscanf(f, "%d\n", &numans);
    answers = (char * *) malloc(numans * sizeof(char*));
    if (answers == NULL)
    {
        free(extname);
        free(intname);
        free(e);
        return NULL;
    }
    for (i = 0; i < numans; i++)
    {
        fscanf(f, "%m[^\n]\n", answers + i);
        if (answers[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(answers[j]);
            free(answers);
            free(extname);
            free(intname);
            free(e);
            return NULL;
        }
    }
    /*Set all the info to the Ext alloc'd before*/
    e->ext_name = extname;
    e->int_name = intname;
    e->n_ans    = numans;
    e->ans      = answers;
    return e;
}

void ext_free(Ext *e)
{
    int i;
    if (e == NULL)
        return;
    if (e->ext_name != NULL)
        free(e->ext_name);
    if (e->int_name != NULL)
        free(e->int_name);
    if (e->ans)
    {
        for (i = 0; i < e->n_ans; i++)
        {
            if (e->ans[i] != NULL)
                free(e->ans[i]);
        }
        free(e->ans);
    }
    free(e);
    return;
}


Assoc *assoc_ini(char *int_name, pfun f)
{
    assert(int_name && f);

    Assoc *a = (Assoc *) malloc(sizeof(Assoc));
    if (a == NULL)
        return NULL;
    a->int_name = strdup(int_name);
    a->f        = f;
    return a;
}

void assoc_free(Assoc *a)
{
    if (a == NULL)
        return;
    if (a->int_name != NULL)
        free(a->int_name);
    free(a);
}



pfun assoc_search(char *int_name, CoP *c)
{
    assert(int_name && c);
    int i;
    for (i = 0; i < c->numassocs; i++)
    {
        if (strcmp(c->assocs[i]->int_name, int_name) == 0)
            return c->assocs[i]->f;
    }
    return NULL;
}


Ext *ext_search(char *verb, CoP *c)
{
    assert(verb && c);
    int i;
    /*i=1 bc exts[0] = error function*/
    for (i = 0; i < c->numexts; i++)
    {
        if (strcmp(c->exts[i]->ext_name, verb) == 0)
            return c->exts[i];
    }
    /*verb is not an external command in the CoP, return error*/
    return c->exts[0];
}

char **unpack_answers(Ext *e, char *object)
{
    assert(e != NULL && object != NULL);
    char **answers = (char * *) malloc(e->n_ans * sizeof(char*));
    if (answers == NULL)
        return NULL;
    for (int i = 0; i < e->n_ans; i++)
    {
        answers[i] = unpack_answer(e->ans[i], object, '*');
        if (answers[i] == NULL)
        {
            for (int j = 0; j < i; i++)
            {
                free(answers[j]);
            }
            free(answers);
            return NULL;
        }
    }
    return answers;
}

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









/*


   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@'';,.`.'@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@         `'@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@#         ,`#@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@'        #@.@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@ '        ,#;@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@ '        ##'@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@# +        `@..@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@`@        .@@ @@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@`;        +#@`@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@  .       +`# @@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@. +   `:,`` ;,@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@; @ `    `@,`:@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@# ,+`     .' .@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@ . :,;+'`';`.@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@ @` .;,;    ;@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@`;          '@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@```   .  ,;.'@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@; ':+@.,..  ,@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@; + ``  '`  +@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@+ + ';`,  .'@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ '   `     #@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@         ` :@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@           +@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ .      `  ,@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ ,`     ,+..@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@`:       `+:@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ '       , `@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@#@@ +        ::@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ +`        #@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@`+          ;@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@:@          `@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ '           @@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ ; `         @@@@#.+..' ,@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ ,`          :`` # `'``@` @@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ ,    +#. `.`; `+       ,,;@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ ,   `    ` `#, `,',   `. `@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@ , ';'@` ;@` @`@@@@@#     `@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@+, ,@#@ :  ` `.# `` +'#.   .##    '@@@@@@@@
   @@@@@@@@@@@@@@@@@#+``    +#.#    '.    .@#     :'+#   `@@@@@@@@
   @@@@@@@@@@@@@@@@@@@#+@@` `@`''         `@` `,,`  `@+   @@@@@@@@
   @@@@@@@@@@@@@@@@@``       @:;,        ,`@+.      ` @`  ,@@@@@@@
   @@@@@@@@@@@@@@@@@         @; `        ` @`,      ' #@ . #@@@@@@
   @@@@@@@@@@:.'@@##         @++`          @`;`     ' ,@`#``@#@@@@
   @@@@@@@@@'.  `+@'         ##;           @;       ```@  @ .@@@@@
   @@@@@@@@     `;#: ``      :+ `          @;.`      ` @` `@,#@@@@
   @@@@@@@++``  .`@,```      ,@ `          @,`     ` ``@.  #` @@@@
   @@@@@@@.;,  `;`@:``       `@ `          @ .       .+@.  '`,#@@@
   @@@@@@@+#      +'` . `    `@ ,        ``@. `   #+,'.@. :#  #@@@
   @@@@@@'``'   ;':+'`:       @ '         :@'    `  .  @. `'@ @@@@
   @@@@@@`  @     ;#..        @`'        `.@@   ,'@;`  @, .``;@@@@
   @@@@@@ . #  .++:# :        @`+     `;@ `@+` `.   :, @` `:`#@@@@
   @@@@@@ +##   `''@ +.       #`,     ;:` '@       ' ':@. @ .#@@@@
   @@@@@@ #+'`   ''@ @'``     +#``   . `   #   `   '   @,,`,'@@@@@
   @@@@@@;##:    ` @ ,        +#,''``   ``;#       +`` @' : @@@@@@
   @@@@@@`#;;     ,@` `       ':; `     `` @`      '   .@  `@@@@@@
   @@@@@@`#;+     .@`#        '```        `@#       :   @  @@@@@@@
   @@@@@@#@ ;    `,@:.        #  `         '@       +   ,##@@@@@@@
   @@@@@@   .      +,@`       @              +           #@@@@@@@@
   @@@@@@`         @.         :             `+           .@@@@@@@@
   @@@@@@;         @        `+ `              .           @@@@@@@@
   @@@@@`#       `+                           .           @@@@@@@@
   @@@@@ @                                                @@@@@@@@
   @@@@# `'                                          ,    @@@@@@@@
   @@@@;  #   `                                          `@@@@@@@@
   @@@@@   +                                             ;@@@@@@@@
   @@@@@#      .                                         @@@@@@@@@
   @@@@@@#    +`       ` `   `                 `  :     '@@@@@@@@@
   @@@@@@@# `+; ++     #`#, :                #:`::#` ``,#@@@@@@@@@
   @@@@@@@@+`....:'   @. .`#`   ,.         `  `@#@#:  +@@@@@@@@@@@
   @@@@@@@@@+++'#;#@#``;'#@@, `  `;#,`,'    ` `+ :``.@@@@@@@@@@@@@
   @@@@@@@@@@#@@@@@@@@+@:+``..+'+ ,:  @'   `,@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#;``  # .@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@##+#`@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

 */
