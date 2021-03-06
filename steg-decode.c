// steg-decode.c
// Řešení IJC-DU1, příklad a), 3.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Soubor pro spouštění dekodování a Eratosthenova síta

#include "error.h"
#include "ppm.h"
#include "bitset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
    // decider between primes and decode
    if (argc == 2)
    {
        struct ppm *msg;

        if ((msg = ppm_read(argv[1])) == NULL)
            return 0;

        bitset_alloc(p, msg->xsize*msg->ysize*3);

        eratosthenes(p);

        char decoded_char[2] = {8,0};
        unsigned char_index = 0;

        for (int i = 21;msg->data[i]; i++)
        {
            if (bitset_getbit(p, i) == 0)
                bitset_setbit(decoded_char, char_index,(msg->data[i] & 1));
            else
                continue;
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
    } else
    {
        clock_t start_t = clock();
        eratho_print();
        fprintf(stderr, "Time=%.3g\n", (double)(clock()-start_t)/CLOCKS_PER_SEC);
    }
    return 0;
}
