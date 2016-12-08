#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    int  shared1;
    char *shared2;
} share;


pthread_t tid[2];

void* doSomeThing(void *arg)
{
    share *s = (shared *) arg;

    while (1)
        ;
    unsigned long i  = 0;
    pthread_t     id = pthread_self();

    if (pthread_equal(id, tid[0]))
    {
        printf("\n First thread processing\n");
    }
    else
    {
        printf("\n Second thread processing\n");
    }

    for (i = 0; i < (0xFFFFFFFF); i++)
        ;

    return NULL;
}

int main(void)
{
    int   i = 0;
    int   err;

    share *s = (shared *) malloc(sizeof(shared));

    while (i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, (void *) s);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }

    sleep(5);
    return 0;
}
