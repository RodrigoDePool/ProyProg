#include "animations.h"
#include "../interface.h"
#include <unistd.h>
#define READ_TIME_FAST 3500000
#define READ_TIME_SLOW 7000000

void One2Two_animation(Interface *i)
{
	int  mysrow=22, myscol=42, plrow = i_wherePlayerBeRow(i), plcol = i_wherePlayerBeCol(i), index;
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

	for(index=2; index<=7; index++){
		sprintf(buff, "../DATA/Dialogue/OneToTwo/%d.txt", index);		
		i_readFile(i, buff, 0, 0, 3);
		while (_read_key() != ' ');
		i_cleanCommand(i);
		if (index == 5) i_cleanMap(i);
		if (index == 6){
			i_readFile(i, "../Maps/BedRoom1.map", 0, 0, 1);
			i_drawAll(i);
		}
	}

}


void Two2Three_animation(Interface *i)
{
	int index;
	char buff[50];	

	for (index=1; index<=16; index++){
		sprintf (buff, "Frames/TwoToThree/BedRoom1-%d.map", index);
		usleep(10000);
		i_cleanMap(i);
		i_readFile(i, buff, 0, 0, 1);
		i_drawAll(i);
	}
	
	usleep(2000);
	i_readFile(i, "Frames/TwoToThree/BedRoom1-1.map", 0, 0, 1);
	
	for (index=1; index<=9; index++){
		sprintf (buff, "../DATA/Dialogue/TwoToThree/%d.txt", index);
		i_readFile(i, buff, 0, 0, 3);
		while (_read_key() != ' ');
		i_cleanCommand(i);
		if (index == 2) i_cleanMap(i);
		if (index == 4){
			i_readFile(i, "../Maps/BedRoom2.map", 0, 0, 1);
			i_drawAll(i);
		}
	}
}
	
void Three2Four_animation_LucyFight(Interface *i)
{
	int  lucyrow=1, lucycol=21, plrow = i_wherePlayerBeRow(i), plcol = i_wherePlayerBeCol(i), index, j, eq;
	
	i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
	
	while(lucycol != 65){
		lucycol++;
		i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
		i_writeCharMap(i, ' ', lucyrow, lucycol-1, 1);
		usleep(100000);
	}

	while(lucyrow != plrow){
		lucyrow++;
		i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
		i_writeCharMap(i, ' ', lucyrow-1, lucycol, 1);
		usleep(10000);
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
		usleep(25000);
	}
}












