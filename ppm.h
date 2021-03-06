// ppm.h
// Řešení IJC-DU1, příklad a), 3.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Hlavičkový soubor pro pmm se strukturou a limitem velikosti vstupniho obrazku

#ifndef IJCPROJ1_PPM_H
#define IJCPROJ1_PPM_H

#define MAX_LIMIT 8000*8000*3

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);

#endif //IJCPROJ1_PPM_H
