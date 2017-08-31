#include "types.h"

#define RAMSCREEN 0xB8000       /* debut de la memoire video */
#define SIZESCREEN 0xFA0        /* 4000, nombres d'octets d'une page texte */
#define SCREENLIM 0xB8FA0
#define LINES 24
#define COLUMNS 80

uchar cursor_x = 0;
uchar cursor_y = 0;

void scrollup(uchar n)
{
    uchar *video, *tmp;
    for(video = (uchar *)RAMSCREEN; video < SCREENLIM; video+=2)
    {
        tmp = (uchar *)(video + 2*(LINES - n) * COLUMNS * 2);
        if(tmp < (uchar *)SCREENLIM)
        {
            *video = *tmp;
            *(video + 1) = *(tmp + 1);
        }
        else
        {
            *video = 0;
            *(video + 1)= 0x7;
        }
    }
}

void newline(void)
{
    cursor_x = 0;
    if(++cursor_y % LINES == 0)
    {
        scrollup(1);
        cursor_y = 0;
    }
}

void print_char(uchar c, uchar colour)
{
    if( c == '\n')
    {
        newline();
    }
    else
    {
        uchar *video = (uchar *)RAMSCREEN;
        /*2 bytes for a character*/
        video += cursor_x*2 + COLUMNS*cursor_y*2;
        *(video) = c;
        *(video + 1) = colour;
        if(++cursor_x % COLUMNS == 0)
            newline();
    }
}

void print(char *string )
{
    uchar colour = 0xE;
    while(*string != '\0')
    {
        print_char(*string, colour);
        string++;
    }
}
