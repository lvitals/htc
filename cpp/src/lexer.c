#include "cpp.h"

#include <string.h>
#include <ctype.h>

/*s Redefinições locais do cpp.h para este módulo */
#define OROR 267
#define ANDAND 266
#define RS 265
#define LS 264
#define GE 263
#define LE 262
#define NE 261
#define EQ 260
#define DEFINED 259
#define stop 258
#define number 257

LOCAL int tobinary(char *, int);

int yylex(void) {
    static int ifdef = 0;
    static char *op2[] = { "||", "&&", ">>", "<<", ">=", "<=", "!=", "==" };
    static int val2[] = { OROR, ANDAND, RS, LS, GE, LE, NE, EQ };
    static char *opc = "b\bt\tn\nf\fr\r\\\\";
    register char savc, *s;
    int val;
    register char **p2;
    struct symtab *sp;

    for (;;) {
        newp = skipbl(newp);
        if (*inptr == '\n')
            return (stop);
        savc = *newp;
        *newp = '\0';
        for (p2 = op2 + 8; --p2 >= op2;)
            if (0 == strcmp(*p2, inptr)) {
                val = val2[p2 - op2];
                goto ret;
            }
        s = "+-*/%<>&^|?:!~(),";
        while (*s)
            if (*s++ == *inptr) {
                val = *--s;
                goto ret;
            }
        if (isdigit((unsigned char)*inptr)) {
            if (*inptr == '0')
                yylval = (inptr[1] == 'x' || inptr[1] == 'X') ? tobinary(inptr + 2, 16)
                                                             : tobinary(inptr + 1, 8);
            else
                yylval = tobinary(inptr, 10);
            val = number;
        } else if (isid(*inptr)) {
            if (0 == strcmp(inptr, "defined")) {
                ifdef = 1;
                ++flslvl;
                val = DEFINED;
            } else {
                sp = lookup(inptr, -1);
                if (ifdef != 0) {
                    ifdef = 0;
                    --flslvl;
                }
                yylval = (sp->value == 0) ? 0 : 1;
                val = number;
            }
        } else if (*inptr == '\'') {
            val = number;
            if (inptr[1] == '\\') {
                if (newp[-1] == '\'')
                    newp[-1] = '\0';
                s = opc;
                while (*s)
                    if (*s++ != inptr[2])
                        ++s;
                    else {
                        yylval = *s;
                        goto ret;
                    }
                if (isdigit((unsigned char)inptr[2]))
                    yylval = tobinary(inptr + 2, 8);
                else
                    yylval = inptr[2];
            } else
                yylval = inptr[1];
        } else if (0 == strcmp("\\\n", inptr)) {
            *newp = savc;
            continue;
        } else {
            *newp = savc;
            pperror("Illegal character %c in preprocessor if", *inptr);
            continue;
        }
    ret:
        *newp = savc;
        outptr = inptr = newp;
        return (val);
    }
}

LOCAL int tobinary(char *st, int b) {
    int n, c, t;
    char *s;
    n = 0;
    s = st;
    while ((c = *s++)) {
        if (isdigit(c)) {
            t = c - '0';
        } else if (isxdigit(c)) {
            t = tolower(c) - 'a' + 10;
        } else {
            t = -1;
            if (c == 'l' || c == 'L')
                if (*s == '\0')
                    break;
            pperror("Illegal number %s", st);
        }
        if (t < 0 || t >=b)
            break;
        n = n * b + t;
    }
    return (n);
}