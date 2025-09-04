#ifndef _PORTAB_H
#define _PORTAB_H

/*
 * =============================================================================
 * portab.h -- Cabeçalho de Portabilidade
 * =============================================================================
 * Usa macros pré-definidas padrão para detectar o sistema operacional alvo
 * durante a compilação. A estrutura if/elif/else garante que apenas um
 * conjunto de definições seja ativado.
 * =============================================================================
 */

/* --- Detecção de Sistemas tipo Unix (Linux, macOS, FreeBSD, etc.) --- */
/* __unix__ é o mais comum, mas checamos os outros para garantir. */
#if defined(__unix__) || defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#define NULDEV "/dev/null"
#define DIRSEP "/"
#define ISDIRSEP(ch) ((ch) == '/')
#define HOST_OS "Unix"


/* --- Detecção de Sistemas Windows e MS-DOS --- */
#elif defined(_WIN32) || defined(MSDOS)
    #undef NULDEV
    #undef DIRSEP
    #undef ISDIRSEP
    #undef HOST_OS
    #define NULDEV "NUL"
    #define DIRSEP "\\"
    #define ISDIRSEP(ch) ((ch) == '\\' || (ch) == '/') /* Aceita ambos */
    #define HOST_OS "Windows/DOS"


/* --- Detecção de CP/M (requer flag manual -DCPM) --- */
#elif CPM
    #undef NULDEV
    #undef DIRSEP
    #undef ISDIRSEP
    #undef HOST_OS
    /* CP/M não tem um NULDEV padrão ou separadores de diretório.
     * A flag -M talvez precise de uma implementação diferente. */
    #define NULDEV "NUL" /* Provisório, pode não funcionar */
    #define DIRSEP ":"   /* O separador de drive é o mais próximo */
    #define ISDIRSEP(ch) ((ch) == ':')
    #define HOST_OS "CP/M"
/* --- Caso Padrão: Plataforma Desconhecida --- */
/* Se nenhum dos sistemas acima for detectado, a compilação irá falhar
 * com uma mensagem clara, o que é mais seguro do que usar definições erradas. */
#else
    #error "Plataforma de compilação não suportada ou não detectada. Por favor, edite include/portab.h"
#endif

#endif /* _PORTAB_H */