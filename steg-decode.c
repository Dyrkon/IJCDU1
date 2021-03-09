// steg-decode.c
// Řešení IJC-DU1, příklad a), 3.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// ...popis příkladu - poznámky, omezení, atd

#include "error.h"
#include "ppm.h"
#include "bitset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(int argc, char **argv)
{
    if (argc == 2)
    {

    } else
        eratho_print();

    struct ppm *msg;

    if ((msg = ppm_read(argv[1])) == NULL)
        return 0;

    bitset_alloc(p, msg->xsize*msg->ysize*3);

    eratosthenes(p);

    char decoded_char[2] = {8, 0};
    unsigned char_index = 0;

    // CHYBA
    for (int i = 0;msg->data[i]; i++)
    {
        if (bitset_getbit(p, i) == 0)
        {
            bitset_setbit(decoded_char, char_index,(msg->data[i] & 1));
        }
        char_index++;

        if (char_index == CHAR_BITS)
        {
            putchar(decoded_char[1]);

            if (decoded_char[1] == '\0')
            {
                break;
            }
            char_index = 0;
        }
    }

    ppm_free(msg);
    bitset_free(p);

    return 0;
}