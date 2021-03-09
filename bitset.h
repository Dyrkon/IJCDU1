// bitset.h
// Řešení IJC-DU1, příklad a), 3.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Hlavička bitsetu s inline funkcemi a makry

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "error.h"


#ifndef IJCPROJ1_BITSET_H
#define IJCPROJ1_BITSET_H


typedef unsigned long *bitset_t;

typedef unsigned long bitset_index_t;

void eratosthenes(bitset_t array);

#define N 200000000

#define CHAR_BITS 8

#define sizeofset(size) ((size/sizeof(bitset_index_t)) + (size%sizeof(bitset_index_t) == 0 ? 0 : 1) + 1)

#define bitset_alloc(arr_name,size) \
    bitset_t arr_name;              \
    if ((arr_name = calloc(sizeofset(size), sizeof(bitset_index_t))) == NULL)  \
    { error_exit("bitset_alloc: Chyba alokace pameti"); } \
    else { arr_name[0] = size; };

#ifndef USE_INLINE

#define INDEX_CHECK(arr_name, index) (index <= arr_name[0] && index > 0)

#define INDEX_ERROR(arr_name, index) (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(bitset_index_t)index, (bitset_index_t)arr_name[0]),0)

#define SET_BIT(arr_name, index, value) (value == 0) ? ((arr_name[index/sizeof(bitset_index_t)+1]) &= (~(1UL << index%sizeof(bitset_index_t)))) : ((arr_name[index/sizeof(bitset_index_t)+1]) |= (1UL << index%sizeof(bitset_index_t)))

#define GET_BIT(arr_name, index) (((arr_name[index/sizeof(bitset_index_t)+1]) & (1UL << index%sizeof(bitset_index_t))) != 0)


#define bitset_create(arr_name, size) \
    bitset_index_t arr_name[sizeofset(size)] = { size, 0 }; \
    _Static_assert(size > 0, "Neuspesna inicializace pole");


#define bitset_free(arr_name) free(arr_name);

#define bitset_size(arr_name) arr_name[0]

#define bitset_getbit(arr_name, index) (INDEX_CHECK(arr_name, index) ? GET_BIT(arr_name, index) : INDEX_ERROR(arr_name, index))

#define bitset_setbit(arr_name, index, value) ((INDEX_CHECK(arr_name, index)) ? SET_BIT(arr_name, index, value) : INDEX_ERROR(arr_name, index))

#endif

#ifdef USE_INLINE

    inline void bitset_setbit(bitset_t arr_name, bitset_index_t index, unsigned value)
    {
        if ((index) <= arr_name[0] && index > 0)
        {
            (value == 0) ? ((arr_name[index/sizeof(bitset_index_t)+1]) &= (~(1UL << index%sizeof(bitset_index_t)))) : ((arr_name[index/sizeof(bitset_index_t)+1]) |= (1UL << index%sizeof(bitset_index_t)));
        }
        else {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(bitset_index_t)index, (bitset_index_t)arr_name[0]);
        }
    }

    inline bitset_index_t bitset_getbit(bitset_t arr_name, bitset_index_t index)
    {
        if ((index) <= arr_name[0] && index > 0)
        {
            return (((arr_name[index/sizeof(bitset_index_t)+1]) & (1UL << index%sizeof(bitset_index_t))) != 0);
        }
        else {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(bitset_index_t)index, (bitset_index_t)arr_name[0]);
        }
        return 0;
    }

    /*static inline bitset_t bitset_alloc(bitset_t arr_name, bitset_index_t size) {
        if ((arr_name = calloc(sizeofset(size), sizeof(bitset_index_t))) == NULL)
        {
            error_exit("bitset_alloc: Chyba alokace pameti");
        }
        else {
            arr_name[0] = size;
        };
        return arr_name;
    }*/
    inline void bitset_free(bitset_t arr_name)
    {
        free(arr_name);
    }

    inline bitset_index_t bitset_size(bitset_t arr_name)
    {
        return arr_name[0];
    }

#endif /* USE_INLINE */

#endif /* IJCPROJ1_BITSET_H */
