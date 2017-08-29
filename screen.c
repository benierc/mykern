#include "types.h"

#define RAMSCREEN 0xB8000       /* debut de la memoire video */
#define SIZESCREEN 0xFA0        /* 4000, nombres d'octets d'une page texte */
#define SCREENLIM 0xB8FA0

void print(char *string )
{
    uchar colour = 0xE;
    unsigned char *video = 0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}
