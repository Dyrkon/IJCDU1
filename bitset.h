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

void eratho_print(void);

#define N 200000000

#define CHAR_BITS 8

#define SIZE_OF(member) (sizeof(*member)*CHAR_BITS)

#define sizeofset(size) ((size/(sizeof(bitset_index_t)*CHAR_BITS)) + (size%(sizeof(bitset_index_t)*CHAR_BITS) == 0 ? 0 : 1) + 1)

#define bitset_alloc(arr_name,size) \
    bitset_t arr_name;              \
    if ((arr_name = calloc(sizeofset(size), sizeof(bitset_index_t))) == NULL)  \
    { error_exit("bitset_alloc: Chyba alokace pameti"); } \
    else { arr_name[0] = size; };

#define INDEX_CHECK(arr_name, index) ((unsigned long)index <= arr_name[0] /*&& index >= 0*/)

#define INDEX_ERROR(arr_name, index) (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(bitset_index_t)index, (bitset_index_t)arr_name[0]),0)

#define SET_BIT(arr_name, index, value) (value == 0) ? ((arr_name[index/SIZE_OF(arr_name)+1]) &= (~(1UL << index%SIZE_OF(arr_name)))) : ((arr_name[index/SIZE_OF(arr_name)+1]) |= (1UL << index%SIZE_OF(arr_name)))

#define GET_BIT(arr_name, index) (((arr_name[index/SIZE_OF(arr_name)+1]) & (1UL << index%SIZE_OF(arr_name))) != 0)

#ifndef USE_INLINE

#define bitset_create(arr_name, size) \
    bitset_index_t arr_name[sizeofset(size)] = { size, 0 }; \
    static_assert(size > 0, "Neuspesna inicializace pole");


#define bitset_free(arr_name) free(arr_name);

#define bitset_size(arr_name) arr_name[0]

#define bitset_getbit(arr_name, index) (INDEX_CHECK(arr_name, index) ? GET_BIT(arr_name, index) : INDEX_ERROR(arr_name, index))

#define bitset_setbit(arr_name, index, value) ((INDEX_CHECK(arr_name, index)) ? SET_BIT(arr_name, index, value) : INDEX_ERROR(arr_name, index))

#endif

#ifdef USE_INLINE

    static inline void bitset_setbit(bitset_t arr_name, bitset_index_t index, unsigned value)
    {
        if (value == 0)
        {
            arr_name[index/SIZE_OF(arr_name)+1] &= (~(1UL << index%SIZE_OF(arr_name)));
        }
        else
            arr_name[index/SIZE_OF(arr_name)+1] |= (1UL << index%SIZE_OF(arr_name));
    }


    static inline bitset_index_t bitset_getbit(bitset_t arr_name, unsigned index)
    {
        return (((arr_name[index/SIZE_OF(arr_name)+1]) & (1UL << index%SIZE_OF(arr_name))) != 0);
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
