#include "animations.h"
#include "../interface.h"
#include <unistd.h>
#include "../Minigames/preguntas/qa.h"

int One2Two_animation(Interface *i)
{
    int  myscol = 112, mysrow = 19, plrow = i_wherePlayerBeRow(i), plcol = i_wherePlayerBeCol(i), j;
    char buff[50];
    i_readFile(i, "Codigo/DATA/Dialogue/OneToTwo/1.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);

    i_writeCharMap(i, '?', mysrow, myscol, 1);

    while (myscol != 31)
    {
        myscol--;
        i_writeCharMap(i, '?', mysrow, myscol, 1);
        i_writeCharMap(i, ' ', mysrow, myscol + 1, 1);
        usleep(20000);
    }

    while (mysrow != plrow)
    {
        mysrow--;
        i_writeCharMap(i, '?', mysrow, myscol, 1);
        i_writeCharMap(i, ' ', mysrow + 1, myscol, 1);
        usleep(20000);
    }

    while (myscol != plcol + 1)
    {
        myscol--;
        i_writeCharMap(i, '?', mysrow, myscol, 1);
        i_writeCharMap(i, ' ', mysrow, myscol + 1, 1);
        usleep(20000);
    }

    i_writeCharMap(i, '!', plrow - 1, plcol, 1);
    usleep(150000);
    i_writeCharMap(i, ' ', plrow - 1, plcol, 1);
    i_writeCharMap(i, ' ', plrow, plcol, 1);
    i_writeCharMap(i, 'X', plrow, plcol - 2, 1);

    for (j = 2; j <= 8; j++)
    {
        sprintf(buff, "Codigo/DATA/Dialogue/OneToTwo/%d.txt", j);
        i_readFile(i, buff, 0, 0, 3);
        _read_key();
        i_cleanCommand(i);
        if (j == 6){
            i_cleanMap(i);
            usleep(100000);
            i_readFile(i, "Codigo/DATA/IniCredits", 0, 25, 1);
            usleep(1500000);
            i_cleanMap(i);
        }
        if (j == 7)
        {
            i_cleanMap(i);
            i_readFile(i, "Codigo/Animations/Maps/BedRoom1.map", 0, 0, 1);
        }
    }
    return 0;
}


int Two2Three_animation(Interface *i)
{
    int  j;
    char buff[50];
    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/BedRoom1-1.map", 0, 0, 1);
    for (j = 1; j <= 16; j++)
    {
        sprintf(buff, "Codigo/Animations/Frames/TwoToThree/BedRoom1-%d.map", j);
        usleep(20000);
        i_readFile(i, buff, 0, 62, 1);
    }

    usleep(2000);
    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/BedRoom1-1.map", 0, 0, 1);

    for (j = 1; j <= 9; j++)
    {
        sprintf(buff, "Codigo/DATA/Dialogue/TwoToThree/%d.txt", j);
        i_readFile(i, buff, 0, 0, 3);
        _read_key();
        i_cleanCommand(i);
        if (j == 2)
            i_cleanMap(i);
        if (j == 4)
        {
            i_readFile(i, "Codigo/Animations/Maps/BedRoom2.map", 0, 0, 1);
        }
    }
    return 0;
}

int Three2Four_animation(Interface *i)
{
    int  lucyrow = 1, lucycol = 21, plrow = i_wherePlayerBeRow(i), plcol = i_wherePlayerBeCol(i), j, index, eq;
    char buff[50];
    i_writeCharMap(i, 'L', lucyrow, lucycol, 1);

    while (lucycol != 65)
    {
        lucycol++;
        i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
        i_writeCharMap(i, ' ', lucyrow, lucycol - 1, 1);
        usleep(10000);
    }

    while (lucyrow != plrow)
    {
        lucyrow++;
        i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
        i_writeCharMap(i, ' ', lucyrow - 1, lucycol, 1);
        usleep(20000);
    }

    if (lucycol > plcol)
        eq = -1;
    else
        eq = 1;

    while (lucycol != plcol - eq)
    {
        lucycol += eq;
        i_writeCharMap(i, 'L', lucyrow, lucycol, 1);
        i_writeCharMap(i, ' ', lucyrow, lucycol - eq, 1);
        usleep(10000);
    }

    for (index = 0; index < 34; index++)
    {
        for (j = 0; j < 114; j += 2)
            i_writeCharMap(i, '#', index, j, 1);
        for (j = 1; j < 115; j += 2)
            i_writeCharMap(i, '#', 33 - index, j, 1);
        usleep(30000);
    }
    usleep(500000);
    i_cleanMap(i);

     while (lucia (i) != 1){
        i_cleanMap(i);
        i_readFile(i, "Codigo/DATA/popups/hit", 13, 39, 1);
        _read_key();
    }

    for (j = 1; j <= 3; j++)
    {
        sprintf(buff, "Codigo/DATA/Dialogue/ThreeToFour/%d.txt", j);
        i_readFile(i, buff, 0, 0, 3);
        _read_key();
        i_cleanCommand(i);
        if (j == 2)
        {
            i_cleanMap(i);
            i_readFile(i, "Codigo/Animations/Maps/BedRoom3.map", 0, 0, 1);
            usleep(1000);
            for (index = 0; index <= 3; index++)
            {
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
                usleep(200000);
            }
        }
    }
    return 0;
}

int Four_animation_call1(Interface *i)
{
    int j;
    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/BedRoom3.map", 0, 0, 1);
    usleep(1000);
    i_readFile(i, "Codigo/DATA/Dialogue/ThreeToFour/2.txt", 0, 0, 3);
    for (j = 0; j < 3; j++)
    {
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
        usleep(200000);
    }
    _read_key();
    i_cleanCommand(i);
    i_readFile(i, "Codigo/DATA/Dialogue/ThreeToFour/4.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);
    return 0;
}

int Four_animation_call2(Interface *i)
{
    int j;
    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/BedRoom3.map", 0, 0, 1);
    usleep(1000);
    i_readFile(i, "Codigo/DATA/Dialogue/ThreeToFour/2.txt", 0, 0, 3);
    for (j = 0; j < 3; j++)
    {
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
        usleep(200000);
    }
    _read_key();
    i_cleanCommand(i);
    i_readFile(i, "Codigo/DATA/Dialogue/ThreeToFour/5.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);
    return 0;
}

int Four_animation_call3(Interface *i)
{
    int j;
    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/BedRoom3.map", 0, 0, 1);
    usleep(1000);
    i_readFile(i, "Codigo/DATA/Dialogue/ThreeToFour/2.txt", 0, 0, 3);
    for (j = 0; j < 3; j++)
    {
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
        usleep(200000);
    }
    _read_key();
    i_cleanCommand(i);
    i_readFile(i, "Codigo/DATA/Dialogue/ThreeToFour/6.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);
    return 0;
}

int Four2Five_animation(Interface *i)
{
    int  j, index;
    char buff[50];
    i_readFile(i, "Codigo/DATA/Dialogue/ThreeToFour/2.txt", 0, 0, 3);
    for (j = 0; j < 3; j++)
    {
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
        usleep(200000);
    }
    _read_key();
    i_cleanCommand(i);


    for (j = 1; j <= 7; j++)
    {
        sprintf(buff, "Codigo/DATA/Dialogue/FourToFive/%d.txt", j);
        i_readFile(i, buff, 0, 0, 3);
        _read_key();
        i_cleanCommand(i);
        if (j == 2)
            i_cleanMap(i);
        if (j == 3)
        {
            i_cleanMap(i);
            i_readFile(i, "Codigo/Animations/Maps/Entrance.map", 0, 0, 1);
            for (index = 1; index < 13; index++)
            {
                i_writeCharMap(i, '^', index, 51, 1);
                if (index != 1)
                    i_writeCharMap(i, ' ', index - 1, 51, 1);
                usleep(100000);
            }
        }
    }
    return 0;
}

int Five_animation_maze(Interface *i)
{
    int j, index;
    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/BedRoom4.map", 0, 0, 1);
    i_writeCharMap(i, '^', 1, 20, 1);
    for (j = 21; j < 66; j++)
    {
        i_writeCharMap(i, '^', 1, j, 1);
        i_writeCharMap(i, ' ', 1, j - 1, 1);
        usleep(50000);
    }

    for (j = 2; j < 26; j++)
    {
        i_writeCharMap(i, '^', j, 65, 1);
        i_writeCharMap(i, ' ', j - 1, 65, 1);
        usleep(100000);
    }

    for (j = 64; j > 6; j--)
    {
        i_writeCharMap(i, '^', 25, j, 1);
        i_writeCharMap(i, ' ', 25, j + 1, 1);
        usleep(50000);
    }

    for (j = 26; j < 32; j++)
    {
        i_writeCharMap(i, '^', j, 7, 1);
        i_writeCharMap(i, ' ', j - 1, 7, 1);
        usleep(100000);
    }

    i_readFile(i, "Codigo/DATA/Dialogue/FourToFive/7.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);

    for (index = 0; index < 34; index++)
    {
        for (j = 0; j < 114; j += 2)
            i_writeCharMap(i, '#', index, j, 1);
        for (j = 1; j < 115; j += 2)
            i_writeCharMap(i, '#', 33 - index, j, 1);
        usleep(30000);
    }
    return 0;
}

int Five_animation_2048(Interface *i)
{
    int j, index;
    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/Bathroom2.map", 0, 0, 1);
    i_writeCharMap(i, '^', 18, 52, 1);
    for (j = 19; j < 25; j++)
    {
        i_writeCharMap(i, '^', j, 52, 1);
        i_writeCharMap(i, ' ', j - 1, 52, 1);
        usleep(100000);
    }

    for (j = 53; j > 12; j--)
    {
        i_writeCharMap(i, '^', 24, j, 1);
        if (j == 29 || j == 28 || j == 27)
            i_writeCharMap(i, '_', 24, j + 1, 1);
        else
            i_writeCharMap(i, ' ', 24, j + 1, 1);
        usleep(100000);
    }

    for (j = 23; j > 19; j--)
    {
        i_writeCharMap(i, '^', j, 13, 1);
        i_writeCharMap(i, ' ', j + 1, 13, 1);
        usleep(100000);
    }


    for (j = 12; j > 1; j--)
    {
        i_writeCharMap(i, '^', 20, j, 1);
        i_writeCharMap(i, ' ', 20, j + 1, 1);
        usleep(100000);
    }

    i_readFile(i, "Codigo/DATA/Dialogue/FourToFive/8.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);

    for (index = 0; index < 34; index++)
    {
        for (j = 0; j < 114; j += 2)
            i_writeCharMap(i, '#', index, j, 1);
        for (j = 1; j < 115; j += 2)
            i_writeCharMap(i, '#', 33 - index, j, 1);
        usleep(30000);
    }

    return 0;
}

int Five_animation_pong(Interface *i)
{
    int j, index;
    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/Bathroom2-1.map", 0, 0, 1);
    i_writeCharMap(i, '^', 10, 69, 1);

    for (j = 70; j < 97; j++)
    {
        i_writeCharMap(i, '^', 10, j, 1);
        i_writeCharMap(i, ' ', 10, j - 1, 1);
        usleep(100000);
    }

    for (j = 11; j < 19; j++)
    {
        i_writeCharMap(i, '^', j, 96, 1);
        i_writeCharMap(i, ' ', j - 1, 96, 1);
        usleep(100000);
    }

    i_readFile(i, "Codigo/DATA/Dialogue/FourToFive/9.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);

    for (index = 0; index < 34; index++)
    {
        for (j = 0; j < 114; j += 2)
            i_writeCharMap(i, '#', index, j, 1);
        for (j = 1; j < 115; j += 2)
            i_writeCharMap(i, '#', 33 - index, j, 1);
        usleep(30000);
    }

    return 0;
}

int Five2End_animation(Interface *i)
{
    int  j, index, count = 0;
    char buff[50];

    for (index = 0; index < 34; index++)
    {
        for (j = 0; j < 114; j += 2)
            i_writeCharMap(i, '#', index, j, 1);
        for (j = 1; j < 115; j += 2)
            i_writeCharMap(i, '#', 33 - index, j, 1);
        usleep(30000);
    }

    i_cleanMap(i);
    i_readFile(i, "Codigo/Animations/Maps/Hall.map", 0, 0, 1);

    for (j = 1; j <= 4; j++)
    {
        sprintf(buff, "Codigo/DATA/Dialogue/FiveToEnd/%d.txt", j);
        i_readFile(i, buff, 0, 0, 3);
        _read_key();
        i_cleanCommand(i);
    }

    for (j = 19; j < 35; j++)
    {
        i_writeCharMap(i, '^', j, 48, 1);
        if (j == 27)
            i_writeCharMap(i, '!', j - 1, 48, 1);
        else if (j == 29)
            i_writeCharMap(i, 'e', j - 1, 48, 1);
        else if (j == 30)
            i_writeCharMap(i, 'r', j - 1, 48, 1);
        else if (j == 31)
            i_writeCharMap(i, 'a', j - 1, 48, 1);
        else
            i_writeCharMap(i, ' ', j - 1, 48, 1);
        usleep(100000);
    }

    for (index = 0; index < 34; index++)
    {
        for (j = 0; j < 114; j += 2)
            i_writeCharMap(i, '#', index, j, 1);
        for (j = 1; j < 115; j += 2)
            i_writeCharMap(i, '#', 33 - index, j, 1);
        usleep(30000);
    }

    i_cleanMap(i);
    i_readFile(i, "Codigo/DATA/Dialogue/FiveToEnd/5.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);
    i_readFile(i, "Codigo/Animations/Maps/CorridorLeft-1.map", 0, 0, 1);
    i_readFile(i, "Codigo/DATA/Dialogue/FiveToEnd/6.txt", 0, 0, 3);
    _read_key();
    i_cleanCommand(i);
    i_readFile(i, "Codigo/Animations/Maps/simone.map", 15, 23, 1);
    i_readFile(i, "Codigo/DATA/Dialogue/FiveToEnd/7.txt", 0, 0, 3);
    for (j = 22; j >= 12; j--)
    {
        i_readFile(i, "Codigo/Animations/Maps/simone.map", 15, j, 1);
        for (index = 0; index < 9; index++)
        {
            i_writeCharMap(i, '@', 18, 112 - count, 1);
            if (count == 93)
                i_writeCharMap(i, ')', 18, 112 - count + 1, 1);
            else
                i_writeCharMap(i, ' ', 18, 112 - count + 1, 1);
            count++;
            usleep(50000);
        }
    }


    i_writeCharMap(i, '@', 18, 112 - count, 1);
    i_writeCharMap(i, ' ', 18, 112 - count + 1, 1);
    usleep(50000);
    i_writeCharMap(i, '!', 17, 11, 1);
    usleep(150000);
    i_writeCharMap(i, ' ', 17, 11, 1);
    i_writeCharMap(i, ' ', 18, 112 - count, 1);
    i_writeCharMap(i, 'X', 18, 9, 1);


    for (j = 8; j <= 11; j++)
    {
        sprintf(buff, "Codigo/DATA/Dialogue/FiveToEnd/%d.txt", j);
        i_readFile(i, buff, 0, 0, 3);
        _read_key();
        i_cleanCommand(i);
    }

    for (index = 0; index < 34; index++)
    {
        for (j = 0; j < 114; j += 2)
            i_writeCharMap(i, '#', index, j, 1);
        for (j = 1; j < 115; j += 2)
            i_writeCharMap(i, '#', 33 - index, j, 1);
        usleep(100000);
    }


    return 0;
}









