// ppm.c
// Řešení IJC-DU1, příklad a), 3.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// ...popis příkladu - poznámky, omezení, atd

#include "../headers/error.h"
#include "../headers/ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ppm * ppm_read(const char * filename)
{
    FILE *f;

    f = fopen(filename, "rb");
    if (f == NULL)
    {
        warning_msg("CHYBA: Nepodarilo se otevrit soubor!\n");
        fclose(f);
        return NULL;
    }

    char file_type[3];
    unsigned x_size = 0;
    unsigned y_size = 0;
    int depth = 0;

    if ((fscanf(f,"%s %u %u %d", file_type, &x_size, &y_size, &depth)) != 4)
    {
        warning_msg("CHYBA: Nepodarilo se nacist hlavicku!\n");
        fclose(f);
        return NULL;
    }

    unsigned int limit = x_size*y_size*3;

    if (strcmp(file_type, "P6") != 0)
    {
        warning_msg("CHYBA: Soubor je v nespravnem formatu %s, je pozadovan P6!", file_type);
        fclose(f);
        return NULL;
    }

    if (limit > MAX_LIMIT)
    {
        warning_msg("Obrazek je priliz velky!");
        fclose(f);
        return NULL;
    }

    struct ppm *temp_struct;

    if ((temp_struct = malloc(2*sizeof(unsigned) + limit)) == NULL)
    {
        warning_msg("CHYBA: Alokace pro bytove pole se nezdarila!\n");
        fclose(f);
        return NULL;
    }

    temp_struct->xsize = x_size;
    temp_struct->ysize = y_size;

    if ((fread(temp_struct->data, sizeof(char), limit, f)) != limit)
    {
        warning_msg("CHYBA: Pole se nezdarilo nacist!\n");
        fclose(f);
        return NULL;
    }

    if (fgetc(f) == EOF)
    {
        printf("posledni %i", fgetc(f));
        warning_msg("CHYBA: Soubor nebyl nacten do konce!\n");
        fclose(f);
        return NULL;
    }
    else
    {
        fclose(f);
        return temp_struct;
    }
}

void ppm_free(struct ppm *p)
{
    free(p);
}