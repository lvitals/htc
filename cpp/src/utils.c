#include "cpp.h"

#include <string.h>

/*
 * Retorna um ponteiro para o nome do arquivo dentro de um caminho.
 * Ex: "/path/to/file.c" -> "file.c"
 */
char *fname(char *name) {
    char *t;
    while ((t = strpbrk(name, DIRSEP)))
        name = t + 1;
    return name;
}