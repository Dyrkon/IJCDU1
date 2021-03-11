// error.c
// Řešení IJC-DU1, příklad a), 3.3.2021
// Autor: Matěj Mudra, FIT
// Přeloženo: gcc 10.2.0
// Soubor s metodamy pro hlášení chyb

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include <stdarg.h>

/*
    Napište modul "error.c" s rozhraním v "error.h", který definuje
   funkci void warning_msg(const char *fmt, ...) a
   funkci void error_exit(const char *fmt, ...). Tyto funkce mají
   stejné parametry jako printf(); tisknou text "CHYBA: " a potom
   chybové hlášení podle formátu fmt. Vše se tiskne do stderr
   (funkcí vfprintf) a potom pouze error_exit ukončí program voláním
   funkce exit(1).  Použijte definice ze stdarg.h.
 */

void warning_msg(const char *fmt, ...)
{
    va_list arg;
    va_start (arg, fmt);
    vfprintf (stderr, fmt, arg);
    va_end (arg);
}

void error_exit(const char *fmt, ...)
{
    va_list arg;
    va_start (arg, fmt);
    vfprintf (stderr, fmt, arg);
    va_end (arg);

    exit(1);
}