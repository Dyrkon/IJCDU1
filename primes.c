// primes.c
// Řešení IJC-DU1, příklad a), 3.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Hledání prvočísel pomocí Eratosthenova síta

#include <stdio.h>
#include "bitset.h"
#include "error.h"
#include <math.h>

#ifdef USE_INLINE
    extern inline void bitset_setbit(bitset_t arr_name, bitset_index_t index, unsigned value);
    extern inline bitset_index_t bitset_getbit(bitset_t arr_name, bitset_index_t index);
    extern inline void bitset_free(bitset_t arr_name);
    extern inline bitset_index_t bitset_size(bitset_t arr_name);
#endif

void eratosthenes(bitset_t array)
{
    array[1]=1; array[2]=1;

    unsigned long size = array[0];

    for (bitset_index_t i = 2; i <= sqrt(size); i++)
    {
        if (bitset_getbit(array, i))
            continue;
        for (bitset_index_t j = 2*i; j < size; j += i)
            bitset_setbit(array,j,1);
    }
}

void eratho_print(void) {
    bitset_alloc(p, N);

    eratosthenes(p);

    bitset_index_t results[10];

    unsigned counter = 0;
    for (bitset_index_t i = bitset_size(p)-1; counter < 10 && i > 1; --i) {
        if(bitset_getbit(p,i) == 0)
        {
            results[counter] = i;
            counter++;
        }
    }

    for (int i = 9; i >= 0; --i)
    {
        printf("%lu\n", results[i]);
    }

    bitset_free(p);
}