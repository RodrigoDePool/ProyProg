#include <stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "interface.h"


int a = 0;

pthread_t tid[2];

void *load_gif(void *arg)
{
	Interface *i = (Interface*) arg;
 	i_drawStr(i, "loading.", 17, 51, 1);
	sleep(1);
	while (1){
		i_drawStr(i, ".", 17, 59, 1);
		sleep(1);
		i_drawStr(i, ".", 17, 60, 1);
		sleep(1);
		i_drawStr(i, " ", 17, 59, 1);
		i_drawStr(i, " ", 17, 60, 1);
		sleep(1);
	}
	return;
}

void *countthings(void *foo)
{
	sleep(9);
	a = 1;
	return;
}

int load_game(Interface *i)
{
    int err;


        err = pthread_create(&(tid[0]), NULL, load_gif, (void*) i);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
	  err = pthread_create(&(tid[1]), NULL, countthings, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));



    while (!a);

    return 0;
}

int main (){
	Interface *i;
 	 _term_init();
  	i=i_create(MAXCOLS-30,MAXROWS-6,30,6,'@',40,37,40,37,40,37);
  	i_drawAll(i);
	load_game(i);
	_term_close();
	i_free(i);
	return 0;
}

