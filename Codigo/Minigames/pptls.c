#include <stdio.h>
#include <string.h>
#include <time.h>

int main (){
    char play[30];
    char *opplay[5] = {"Stone", "Paper", "Scissors", "Lizard", "Spock"}; 
    srand(time(NULL));
    int ran;
    while (1){
    printf("Set play: ");
    scanf("%s", play);
    ran = rand() % 5;
    printf ("%d\n", ran);
    printf ("Opponent play: %s\n", opplay[ran]);
    if (!strcmp(play, "Stone") || !strcmp(play, "stone")) {
            if (ran == 0){
                printf ("Tie!\n");
                return 0;
            }
            else if (ran == 1 || ran == 4){
                printf ("You lost!\n");
                return -1;
            }
            else {
                printf ("You won!\n");
                return 1;
            }
    }
    if (!strcmp(play, "Paper") || !strcmp(play, "paper")) {
            if (ran == 1){
                printf ("Tie!\n");
                return 0;
            }
            else if (ran == 2 || ran == 3){
                printf ("You lost!\n");
                return -1;
            }
            else {
                printf ("You won!\n");
                return 1;
            }
    }    
    if (!strcmp(play, "Scissors") || !strcmp(play, "scissors")) {
            if (ran == 2){
                printf ("Tie!\n");
                return 0;
            }
            else if (ran == 0 || ran == 4){
                printf ("You lost!\n");
                return -1;
            }
            else {
                printf ("You won!\n");
                return 1;
            }
    }     
    if (!strcmp(play, "Lizard") || !strcmp(play, "lizard")) {
            if (ran == 3){
                printf ("Tie!\n");
                return 0;
            }
            else if (ran == 0 || ran == 2){
                printf ("You lost!\n");
                return -1;
            }
            else {
                printf ("You won!\n");
                return 1;
            }
    }        
    if (!strcmp(play, "Spock") || !strcmp(play, "spock")) {
            if (ran == 4){
                printf ("Tie!\n");
                return 0;
            }
            else if (ran == 3 || ran == 1){
                printf ("You lost!\n");
                return -1;
            }
            else {
                printf ("You won!\n");
                return 1;
            }
    }
    printf ("Invalid Play!");
    }
}
