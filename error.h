//
// Created by dyrkon on 06.03.21.
//

#ifndef IJCPROJ1_ERROR_H
#define IJCPROJ1_ERROR_H

/*
    Napište modul "error.c" s rozhraním v "error.h", který definuje
   funkci void warning_msg(const char *fmt, ...) a
   funkci void error_exit(const char *fmt, ...). Tyto funkce mají
   stejné parametry jako printf(); tisknou text "CHYBA: " a potom
   chybové hlášení podle formátu fmt. Vše se tiskne do stderr
   (funkcí vfprintf) a potom pouze error_exit ukončí program voláním
   funkce exit(1).  Použijte definice ze stdarg.h.
 */

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif //IJCPROJ1_ERROR_H
