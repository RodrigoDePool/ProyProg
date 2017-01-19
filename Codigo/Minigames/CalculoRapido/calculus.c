#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../interface.h"
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct resStruct {
    int *flag_result;
    int *resAtt;
} resStruct;

<<<<<<< HEAD
resStruct *resStruct_ini(){
    resStruct *foo = (resStruct*) malloc(sizeof(resStruct));
    return foo;
}

void *calc (void *res)
{
        int i, ret;
        char result[3], buf; 
        resStruct *foo = (resStruct*) res;       
        sprintf(result, "%d", *(foo->resAtt));
        for (i = 0; i<strlen(result); i++){
                buf = _read_key();
                if (buf != result [i]) {
                      *(foo->flag_result) = 0;
                      return NULL;
                }
        }
        *(foo->flag_result) = 1;
        return NULL;
}

int calculus (Interface *i)
{       
	int first, firstTen, second, secondTen, decider, res, j, flag = -1;
    pthread_t cal;
	char operator;
    char buff[50];
    i_cleanMap(i);
    resStruct *foo = resStruct_ini();
    foo->flag_result = &flag;
	srand(time(NULL));
	first = rand()%20 + 1;
	decider = rand()%3;
	switch (decider){
		case 0:
			operator = 'x';
			break;
		case 1:
			operator = '+';
			break;
		case 2: 
			operator = '-';
			break;
		default: return -1;
	}

	if (operator == 'x') {
                second = rand()%10 + 1;
                res = first * second;
        }
	else if (operator == '-') {
                second = rand()%first +1;
                res = first - second;
        }
	else if (operator ==  '+') {
                second = rand()%25 +1;
                res = first + second;
        }
    foo->resAtt = &res;
	firstTen = first/10;
	secondTen = second/10;
	
	i_readFile (i, "Codigo/DATA/miniInst/calculus/map.txt", 0, 0, 1);
	i_drawAll(i);
        sprintf (buff, "Codigo/DATA/miniInst/calculus/%d.txt", firstTen);
        i_readFile(i, buff, 12, 7, 1);
        sprintf (buff, "Codigo/DATA/miniInst/calculus/%d.txt", first - firstTen*10);
        i_readFile(i, buff, 12, 22, 1);
        sprintf (buff, "Codigo/DATA/miniInst/calculus/%c.txt", operator);
        i_readFile(i, buff, 12, 37, 1);
        sprintf (buff, "Codigo/DATA/miniInst/calculus/%d.txt", secondTen);
        i_readFile(i, buff, 12, 52, 1);
        sprintf (buff, "Codigo/DATA/miniInst/calculus/%d.txt", second - secondTen*10);
        i_readFile(i, buff, 12, 67, 1);
        
        pthread_create(&cal, NULL, calc, (void*) foo);
        for (j = 0; j<10; j++){
                if (*(foo->flag_result) == 1) return 1;
                if (*(foo->flag_result) == 0) return 0;
                usleep(300000);
        }
        pthread_cancel(cal);
        return 0;              
}

int calculus_game(Interface *i){
        int j,res;
        for (j=0; j<3; j++){
                res = calculus(i);
                if (res == 0){
                    i_drawStrMap(i, "You lost", 1, 1, 3);
                    sleep(2);
                    i_cleanCommand(i);
                    return 0;
                }
                else i_drawStrMap(i, "Correct!", 1, 1, 3);
                sleep(2);
                i_cleanCommand(i);
        }
        return 1;
=======
void *calc(void *res)
{
    int  i, ret;
    char result[3], buf;
    sprintf(result, "%d", *((int *) res));
    for (i = 0; i < strlen(result); i++)
    {
        buf = _read_key();
        if (buf != result [i])
        {
            flag_result = 0;
            return NULL;
        }
    }
    flag_result = 1;
    return NULL;
}

int calculus(Interface *i)
{
    int       first, firstTen, second, secondTen, decider, res, j;
    pthread_t cal;
    char      operator;
    char      buff[50];
    i_cleanMap(i);
    srand(time(NULL));
    first   = rand() % 20 + 1;
    decider = rand() % 3;
    switch (decider)
    {
    case 0:
        operator = 'x';
        break;
    case 1:
        operator = '+';
        break;
    case 2:
        operator = '-';
        break;
    default: return -1;
    }

    if (operator == 'x')
    {
        second = rand() % 10 + 1;
        res    = first * second;
    }
    else if (operator == '-')
    {
        second = rand() % first + 1;
        res    = first - second;
    }
    else if (operator == '+')
    {
        second = rand() % 25 + 1;
        res    = first + second;
    }

    firstTen  = first / 10;
    secondTen = second / 10;

    i_readFile(i, "Codigo/DATA/miniInst/calculus/map.txt", 0, 0, 1);
    i_drawAll(i);
    sprintf(buff, "Codigo/DATA/miniInst/calculus/%d.txt", firstTen);
    i_readFile(i, buff, 12, 7, 1);
    sprintf(buff, "Codigo/DATA/miniInst/calculus/%d.txt", first - firstTen * 10);
    i_readFile(i, buff, 12, 22, 1);
    sprintf(buff, "Codigo/DATA/miniInst/calculus/%c.txt", operator);
    i_readFile(i, buff, 12, 37, 1);
    sprintf(buff, "Codigo/DATA/miniInst/calculus/%d.txt", secondTen);
    i_readFile(i, buff, 12, 52, 1);
    sprintf(buff, "Codigo/DATA/miniInst/calculus/%d.txt", second - secondTen * 10);
    i_readFile(i, buff, 12, 67, 1);

    pthread_create(&cal, NULL, calc, (void *) &res);
    for (j = 0; j < 10; j++)
    {
        if (flag_result == 1)
            return 1;
        if (flag_result == 0)
            return 0;
        usleep(300000);
    }
    pthread_cancel(cal);
    return 0;
>>>>>>> 2ef93400751d922c6955a7af5fbb67e9fec27cbf
}

int calculus_game(Interface *i)
{
    int j, res;
    for (j = 0; j < 3; j++)
    {
        res = calculus(i);
        if (res == 0)
        {
            i_drawStrMap(i, "You lost", 1, 1, 3);
            sleep(3);
            i_cleanCommand(i);
            return 0;
        }
        else
            i_drawStrMap(i, "Correct!", 1, 1, 3);
        sleep(3);
        i_cleanCommand(i);
    }
    return 1;
}


