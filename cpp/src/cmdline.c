#include "cpp.h"

#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef _MAX_PATH
#ifdef PATH_MAX
#define _MAX_PATH PATH_MAX
#else
#define _MAX_PATH 255
#endif
#endif

#define mapcase(c) tolower(c)

#define MAXARGS 512
#define MAXLEN _MAX_PATH
#define QUOTE -128
#define CHUNK 256
#define isterminator(c) ((c) == 0)
#define look() (*str)

int _argc_;

static char *name, *str, *bp;

static size_t bpSize;
static char interactive;
static void error(char *s, ...);
static char nxtch(void);
#define iswild(c) ((c) == '*' || (c) == '?')
#define isseparator(c) ((c) == ' ' || (c) == '\t' || (c) == '\n')

static bool match(char *regexp, char *text);
static bool matchstar(char *regexp, char *text);

char **_getargs(char *_str, char *_name) {
    char **argv;
    char *ap;
    char *cp;
    short argc;
    char c, quote;
    char *argbuf[MAXARGS + 1];
    char buf[MAXLEN];
    bool hasWild;

    bp = NULL;
    quote = 0;
    name = _name;
    str = _str;
    if ((interactive = (str == NULL)))
        str = "\\";
    else {
        while (*str == ' ' || *str == '\t')
            str++;
        cp = str + strlen(str);
        while (--cp >= str && isseparator(*cp));
        cp[1] = '\0';
    }
    argbuf[0] = name;
    argc = 1;

    while (look()) {
        if (argc == MAXARGS)
            error("too many arguments");
        while (isseparator(c = nxtch()));
        if (c == '\0')
            break;
        ap = buf;

        if (c == '\'' || c == '"')
            quote = c;
        else
            *ap++ = c;

        hasWild = iswild(c);

        while ((c = nxtch()) && (quote || !isseparator(c))) {
            if (ap == &buf[MAXLEN -1])
                error("argument too long");
            if (c == quote)
                quote = 0;
            else if (!quote && (c == '\'' || c == '"'))
                quote = c;
            else {
                if (!quote && iswild(c))
                    hasWild = true;
                *ap++ = c;
            }
        }
        *ap = 0;

        if (hasWild) {
            char pattern[_MAX_PATH];
            char path_part[_MAX_PATH];
            
            char *last_sep = strrchr(buf, '/');
            if (last_sep) {
                strncpy(path_part, buf, last_sep - buf + 1);
                path_part[last_sep - buf + 1] = '\0';
                strcpy(pattern, last_sep + 1);
            } else {
                strcpy(path_part, ".");
                strcpy(pattern, buf);
            }

            DIR *dir = opendir(path_part);
            if (dir) {
                struct dirent *entry;
                while ((entry = readdir(dir))) {
                    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                        if (match(pattern, entry->d_name)) {
                            if (argc >= MAXARGS) error("too many arguments after globbing");
                            size_t path_len = (strcmp(path_part, ".") == 0) ? 0 : strlen(path_part);
                            argbuf[argc] = malloc(path_len + strlen(entry->d_name) + 2);
                            if (path_len > 0) {
                                strcpy(argbuf[argc], path_part);
                                /* Don't add a separator if path_part is just "./" */
                                if(strcmp(path_part, "./") != 0) strcat(argbuf[argc], "/");
                            } else {
                                *argbuf[argc] = '\0';
                            }
                            strcat(argbuf[argc++], entry->d_name);
                        }
                    }
                }
                closedir(dir);
            } else {
                 /* No match, treat as literal */
                 argbuf[argc] = malloc(strlen(buf) + 1);
                 strcpy(argbuf[argc++], buf);
            }
        } else {
            argbuf[argc] = malloc(strlen(buf) + 1);
            strcpy(argbuf[argc++], buf);
        }
    }

    _argc_ = argc;
    argbuf[argc] = NULL; /* Null terminate the array */

    argv = malloc((argc + 1) * sizeof(*argv));
    if(!argv) error("malloc failed for argv");
    memcpy(argv, argbuf, (argc + 1) * sizeof(*argv));

    return argv;
}

static char nxtch(void) {
    if (interactive && *str == '\\' && str[1] == 0) {
        if (isatty(fileno(stdin)))
            fprintf(stderr, "%s> ", name);
        size_t cnt = 0;
        int c;
        bpSize = CHUNK;
        bp = malloc(bpSize);
        if(!bp) error("malloc failed for input buffer");

        while ((c = getchar()) != '\n' && c != EOF) {
            if (cnt + 1 >= bpSize) {
                bpSize += CHUNK;
                char* new_bp = realloc(bp, bpSize);
                if(!new_bp) { free(bp); error("realloc failed for input buffer"); }
                bp = new_bp;
            }
            bp[cnt++] = c;
        }
        bp[cnt] = 0;
        str = bp;
    }
    if (*str)
        return *str++;
    return 0;
}

static void error(char *s, ...) {
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    va_end(args);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

static bool match(char *regexp, char *text) {
    if (*regexp == '\0') return *text == '\0';
    if (*regexp == '*') return matchstar(regexp + 1, text);
    if (*text != '\0' && (mapcase(*regexp) == mapcase(*text) || *regexp == '?'))
        return match(regexp + 1, text + 1);
    return false;
}

static bool matchstar(char *regexp, char *text) {
    do {
        if (match(regexp, text))
            return true;
    } while (*text++ != '\0');
    return false;
}