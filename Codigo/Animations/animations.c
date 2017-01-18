#include "animations.h"
#include "../interface.h"
#include <unistd.h>
#define READ_TIME_FAST 3500000
#define READ_TIME_SLOW 7000000

void One2Two_animation(Interface *i)
{
	int  mysrow=22, myscol=42, plrow = i_wherePlayerBeRow(i), plcol = i_wherePlayerBeCol(i), j;
	char buff[50];
	i_readFile(i, "../DATA/Dialogue/OneToTwo/1.txt", 0, 0, 3);
	while (_read_key() != ' ');
	i_cleanCommand(i);

	i_writeCharMap(i, '?', mysrow, myscol, 1);
	
	while(mysrow != plrow){
		mysrow--;
		i_writeCharMap(i, '?', mysrow, myscol, 1);
		i_writeCharMap(i, ' ', mysrow+1, myscol, 1);
		usleep(150000);
	}

	while(myscol != plcol+1){
		myscol--;
		i_writeCharMap(i, '?', mysrow, myscol, 1);
		i_writeCharMap(i, ' ', mysrow, myscol+1, 1);
		usleep(100000);
	}

	i_writeCharMap(i, '!', plrow-1, plcol, 1);
	usleep(150000);
	i_writeCharMap(i, ' ', plrow-1, plcol, 1);
	i_writeCharMap(i, ' ', plrow, plcol, 1);
	i_writeCharMap(i, 'X', plrow, plcol-2, 1);

	for(j=2; j<=7; j++){
		sprintf(buff, "../DATA/Dialogue/OneToTwo/%d.txt", j);		
		i_readFile(i, buff, 0, 0, 3);
		while (_read_key() != ' ');
		i_cleanCommand(i);
		if (j == 5) i_cleanMap(i);
		if (j == 6){
			i_readFile(i, "../Maps/BedRoom1.map", 0, 0, 1);
			i_drawAll(i);
		}
	}

}


void Two2Three_animation(Interface *i)
{
	int j;
	char buff[50];	

	for (j=1; j<=16; j++){
		sprintf (buff, "Frames/TwoToThree/BedRoom1-%d.map", j);
		usleep(10000);
		i_cleanMap(i);
		i_readFile(i, buff, 0, 0, 1);
		i_drawAll(i);
	}
	
	usleep(2000);
	i_readFile(i, "Frames/TwoToThree/BedRoom1-1.map", 0, 0, 1);
	
	for (j=1; j<=9; j++){
		sprintf (buff, "../DATA/Dialogue/TwoToThree/%d.txt", j);
		i_readFile(i, buff, 0, 0, 3);
		while (_read_key() != ' ');
		i_cleanCommand(i);
		if (j == 2) i_cleanMap(i);
		if (j == 4){
			i_readFile(i, "../Maps/BedRoom2.map", 0, 0, 1);
			i_drawAll(i);
		}
	}
}
	
void Three_animation_LucyFight(Interface *i)
{
	int  lucyrow=1, lucycol=21, plrow = i_wherePlayerBeRow(i), plcol = i_wherePlayerBeCol(i), j, index, eq;
	
	i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
	
	while(lucycol != 65){
		lucycol++;
		i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
		i_writeCharMap(i, ' ', lucyrow, lucycol-1, 1);
		usleep(10000);
	}

	while(lucyrow != plrow){
		lucyrow++;
		i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
		i_writeCharMap(i, ' ', lucyrow-1, lucycol, 1);
		usleep(20000);
	}

	if (lucycol > plcol) eq = -1;
	else eq = 1; 

	while(lucycol != plcol-eq){		
		lucycol += eq;
		i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
		i_writeCharMap(i, ' ', lucyrow, lucycol-eq, 1);
		usleep(10000);
	}
	
	for (index=0; index < 34; index ++){
		for (j=0; j<114; j+=2)
			i_writeCharMap(i, '#', index, j, 1);
		for (j=1; j<115; j+=2)
			i_writeCharMap(i, '#', 33-index, j, 1);
		usleep(30000);
	}
	usleep(500000);
	i_cleanMap(i);
}

void Three2Four_animation (Interface *i)
{
	
	int index, j;
	char buff[50];
	
	for (j=1; j<=3; j++){
		sprintf (buff, "../DATA/Dialogue/ThreeToFour/%d.txt", j);
		i_readFile(i, buff, 0, 0, 3);
		while (_read_key() != ' ');
		i_cleanCommand(i);
		if (j == 2){
			i_readFile(i, "../Maps/BedRoom3.map", 0, 0, 1);
			i_drawAll(i);
			usleep(1000);
			for (index=0; index<=3; index++) {
				i_writeCharMap(i, '!', 26, 20, 1);
				i_writeCharMap(i, '!', 26, 21, 1);
				i_writeCharMap(i, '!', 26, 22, 1);
				i_writeCharMap(i, '!', 27, 20, 1);
				i_writeCharMap(i, '!', 27, 21, 1);
				i_writeCharMap(i, '!', 27, 22, 1);
				usleep(200000);
				i_writeCharMap(i, ' ', 26, 20, 1);
				i_writeCharMap(i, ' ', 26, 21, 1);
				i_writeCharMap(i, ' ', 26, 22, 1);
				i_writeCharMap(i, '_', 27, 20, 1);
				i_writeCharMap(i, '_', 27, 21, 1);
				i_writeCharMap(i, '_', 27, 22, 1);
			}
		}
	}
}

void Four_animation_call1 (Interface *i)
{
	int j;
	i_readFile(i,"../DATA/Dialogue/ThreeToFour/2.txt", 0, 0, 3);
	for (j=0; j<3; j++) {
				i_writeCharMap(i, '!', 26, 20, 1);
				i_writeCharMap(i, '!', 26, 21, 1);
				i_writeCharMap(i, '!', 26, 22, 1);
				i_writeCharMap(i, '!', 27, 20, 1);
				i_writeCharMap(i, '!', 27, 21, 1);
				i_writeCharMap(i, '!', 27, 22, 1);
				usleep(200000);
				i_writeCharMap(i, ' ', 26, 20, 1);
				i_writeCharMap(i, ' ', 26, 21, 1);
				i_writeCharMap(i, ' ', 26, 22, 1);
				i_writeCharMap(i, '_', 27, 20, 1);
				i_writeCharMap(i, '_', 27, 21, 1);
				i_writeCharMap(i, '_', 27, 22, 1);
	}
	while (_read_key() != ' ');
	i_cleanCommand(i);
	i_readFile(i,"../DATA/Dialogue/ThreeToFour/4.txt", 0, 0, 3);
	while (_read_key() != ' ');
	i_cleanCommand(i);
}

void Four_animation_call2 (Interface *i)
{
	int j;
	i_readFile(i,"../DATA/Dialogue/ThreeToFour/2.txt", 0, 0, 3);
	for (j=0; j<3; j++) {
				i_writeCharMap(i, '!', 26, 20, 1);
				i_writeCharMap(i, '!', 26, 21, 1);
				i_writeCharMap(i, '!', 26, 22, 1);
				i_writeCharMap(i, '!', 27, 20, 1);
				i_writeCharMap(i, '!', 27, 21, 1);
				i_writeCharMap(i, '!', 27, 22, 1);
				usleep(200000);
				i_writeCharMap(i, ' ', 26, 20, 1);
				i_writeCharMap(i, ' ', 26, 21, 1);
				i_writeCharMap(i, ' ', 26, 22, 1);
				i_writeCharMap(i, '_', 27, 20, 1);
				i_writeCharMap(i, '_', 27, 21, 1);
				i_writeCharMap(i, '_', 27, 22, 1);
	}
	while (_read_key() != ' ');
	i_cleanCommand(i);
	i_readFile(i,"../DATA/Dialogue/ThreeToFour/5.txt", 0, 0, 3);
	while (_read_key() != ' ');
	i_cleanCommand(i);
}

void Four_animation_call3 (Interface *i)
{
	int j;
	i_readFile(i,"../DATA/Dialogue/ThreeToFour/2.txt", 0, 0, 3);
	for (j=0; j<3; j++) {
				i_writeCharMap(i, '!', 26, 20, 1);
				i_writeCharMap(i, '!', 26, 21, 1);
				i_writeCharMap(i, '!', 26, 22, 1);
				i_writeCharMap(i, '!', 27, 20, 1);
				i_writeCharMap(i, '!', 27, 21, 1);
				i_writeCharMap(i, '!', 27, 22, 1);
				usleep(200000);
				i_writeCharMap(i, ' ', 26, 20, 1);
				i_writeCharMap(i, ' ', 26, 21, 1);
				i_writeCharMap(i, ' ', 26, 22, 1);
				i_writeCharMap(i, '_', 27, 20, 1);
				i_writeCharMap(i, '_', 27, 21, 1);
				i_writeCharMap(i, '_', 27, 22, 1);
	}
	while (_read_key() != ' ');
	i_cleanCommand(i);
	i_readFile(i,"../DATA/Dialogue/ThreeToFour/6.txt", 0, 0, 3);
	while (_read_key() != ' ');
	i_cleanCommand(i);
}
/*
void Four2Five_animation
{
	int j;
	i_readFile(i,"../DATA/Dialogue/ThreeToFour/2.txt", 0, 0, 3);
	for (j=0; j<3; j++) {
				i_writeCharMap(i, '!', 26, 20, 1);
				i_writeCharMap(i, '!', 26, 21, 1);
				i_writeCharMap(i, '!', 26, 22, 1);
				i_writeCharMap(i, '!', 27, 20, 1);
				i_writeCharMap(i, '!', 27, 21, 1);
				i_writeCharMap(i, '!', 27, 22, 1);
				usleep(200000);
				i_writeCharMap(i, ' ', 26, 20, 1);
				i_writeCharMap(i, ' ', 26, 21, 1);
				i_writeCharMap(i, ' ', 26, 22, 1);
				i_writeCharMap(i, '_', 27, 20, 1);
				i_writeCharMap(i, '_', 27, 21, 1);
				i_writeCharMap(i, '_', 27, 22, 1);
	}
	while (_read_key() != ' ');
	i_cleanCommand(i);


	for (j=1; j<=7; j++){
		sprintf (buff, "../DATA/Dialogue/FourToFive/%d.txt", j);
		i_readFile(i, buff, 0, 0, 3);
		while (_read_key() != ' ');
		i_cleanCommand(i);
		if (j == 2) i_cleanMap(i);
		if (j == 3){
			i_readFile(i, "../Maps/BedRoom2.map", 0, 0, 1);
			i_drawAll(i);
		}
	}


*/




















