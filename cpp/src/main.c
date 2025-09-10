#include "cpp.h"

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef CPM
#include <unixio.h>
#define O_RDONLY 0
#define USE_GETARGS 1
#endif

#define STATIC static

#ifdef SMALL
#define SYMLEN 31
#else
#define SYMLEN 128
#endif

#define SALT '#'
#ifndef BUFSIZ
#define BUFSIZ 512
#endif

STATIC char *pbeg;
STATIC char *pbuf;
STATIC char *pend;
char *outptr, *inptr;
char *newp;
STATIC char cinit;
bool g_skip_sayline_on_startup = false;

#define ALFSIZ 256 /* alphabet size */
STATIC char macbit[ALFSIZ + 11];
STATIC char toktyp[ALFSIZ];
#define BLANK 1 /* white space (" \t\v\f\r") */
#define IDENT 2 /* valid char for identifier names */
#define NUMBR 3 /* chars is of "0123456789." */

#define scw1 1

#if scw1
#define b0 1
#define b1 2
#define b2 4
#define b3 8
#define b4 16
#define b5 32
#define b6 64
#define b7 128
#endif

#define NB 4
#define CB 8
#define QB 16
#define WB 32
#define SB 2
char fastab[ALFSIZ];
STATIC char slotab[ALFSIZ];
STATIC char *ptrtab;

#define isslo (ptrtab == (slotab + COFF))
#define isspc(a) (ptrtab[(int)a] & SB)
#define isnum(a) ((fastab + COFF)[(int)a] & NB)
#define iscom(a) ((fastab + COFF)[(int)a] & CB)
#define isquo(a) ((fastab + COFF)[(int)a] & QB)
#define iswarn(a) ((fastab + COFF)[(int)a] & WB)

#define eob(a) ((a) >= pend)
#define bob(a) (pbeg >= (a))

#ifdef SMALL
#define BUFFERSIZ 512
#else
#define BUFFERSIZ 8192
#endif
STATIC char buffer[SYMLEN + BUFFERSIZ + BUFFERSIZ + SYMLEN];

#ifdef SMALL
#define SBSIZE 12000
STATIC char sbf[SBSIZE];
#else
#define SBSIZE 65536
STATIC char *sbf;
#endif
#ifdef SMALL
STATIC char *savch = sbf;
#else
STATIC char *savch;
#endif

#define DROP 0xFE
#define WARN DROP
#define SAME 0
#define MAXINC 10
#define MAXIDIRS 10
#define MAXFRE 14
#define MAXFRM 31

#define MAXMULT (INT_MAX / 10)
#define MAXVAL (INT_MAX)

static char warnc = (char)WARN;

STATIC int mactop;
STATIC int fretop;
STATIC char *instack[MAXFRE];
STATIC char *bufstack[MAXFRE];
STATIC char *endbuf[MAXFRE];

STATIC int plvl;
STATIC int maclin;
STATIC char *macfil;
STATIC char *macnam;
STATIC int maclvl;
STATIC char *macforw;
STATIC int macdam;

#if tgp
int tgpscan;
#endif

STATIC int inctop[MAXINC];
STATIC char *fnames[MAXINC];
STATIC char *dirnams[MAXINC];
STATIC FILE *fins[MAXINC];
STATIC int lineno[MAXINC];
#ifndef SMALL
STATIC char *input;
#endif

STATIC char *dirs[MAXIDIRS + 3];
STATIC FILE *fin;
STATIC FILE *fout;
#ifndef SMALL
STATIC FILE *mout;
#endif
STATIC int nd = 1;
STATIC int pflag;
STATIC int passcom;
STATIC int rflag;
#ifndef SMALL
STATIC int hflag;
STATIC int mflag;
#endif
#ifndef CPM
STATIC int noinclude;
#endif
STATIC int nopredef;
STATIC int ifno;
#define NPREDEF 20
STATIC char *prespc[NPREDEF];
STATIC char **predef = prespc;
STATIC char *punspc[NPREDEF];
STATIC char **prund = punspc;
STATIC int exfail;
STATIC struct symtab *lastsym;

LOCAL void sayline(void);
LOCAL void dump(void);
LOCAL char *refill(char *);
LOCAL char *cotoken(char *);
EXPORT char *skipbl(char *);
LOCAL char *unfill(char *);
LOCAL char *doincl(char *);
LOCAL int equfrm(char *, char *, char *);
LOCAL char *dodef(char *);
LOCAL void control(char *);
LOCAL struct symtab *stsym(char *);
LOCAL struct symtab *ppsym(char *);
EXPORT void pperror(char *fmt, ...);
EXPORT void yyerror(char *fmt, ...);
LOCAL void ppwarn(char *fmt, ...);
EXPORT struct symtab *lookup(char *, int);
LOCAL struct symtab *slookup(char *, char *, int);
LOCAL char *subst(char *, struct symtab *);
LOCAL char *trmdir(char *);
LOCAL char *copy(char *);
EXPORT int yywrap(void);
EXPORT int main(int argc, char **argv);
#ifndef SMALL
LOCAL void newsbf(void);
LOCAL struct symtab *newsym(void);

#endif

#define symsiz 500
#define SYMINCR 340
#ifdef SMALL
STATIC struct symtab stab[symsiz];
#else
STATIC struct symtab *stab[symsiz];
#endif

STATIC struct symtab *defloc;
STATIC int defining;
STATIC struct symtab *udfloc;
STATIC struct symtab *incloc;
STATIC struct symtab *ifloc;
STATIC struct symtab *elsloc;
STATIC struct symtab *eifloc;
STATIC struct symtab *elifloc;
STATIC struct symtab *ifdloc;
STATIC struct symtab *ifnloc;
STATIC struct symtab *asmloc;
STATIC struct symtab *lneloc;
STATIC struct symtab *ulnloc;
STATIC struct symtab *easloc;
STATIC struct symtab *uflloc;

STATIC struct symtab *pragmaloc;
STATIC struct symtab *errorloc;
STATIC int trulvl;
int flslvl;
STATIC int elflvl;
STATIC int elslvl;

#if !defined(CPM)
size_t afread(void *ptr, size_t count, FILE *stream) {
    int c = 0;
    size_t cnt = 0;
    while (cnt < count && (c = getc(stream)) != EOF && c != 0x1a)
        if (c != '\r')
            ((char *)ptr)[cnt++] = c;
    if (c == 0x1a)
        ungetc(c, stream);
    return cnt;
}
#define fread(ptr, size, count, stream) afread(ptr, count, stream)
#endif

STATIC void sayline(void) {
    if (g_skip_sayline_on_startup) {
        return;
    }
    if (pflag == 0)
        fprintf(fout, "# %d \"%s\"\n", lineno[ifno], fnames[ifno]);
}

STATIC void dump(void) {
    register char *p1;
    register FILE *f;
    if ((p1 = outptr) == inptr || flslvl != 0)
        return;
    f = fout;
    while (p1 < inptr)
        fputc(*p1++, f);
    outptr = p1;
}

STATIC char *refill(register char *p) {
    register char *np, *op;
    register int ninbuf;
    dump();
    np = pbuf - (p - inptr);
    op = inptr;
    if (bob(np + 1)) {
        pperror("token too long");
        np = pbeg;
        p = inptr + BUFFERSIZ;
    }
    macdam += (int)(np - inptr);
    outptr = inptr = np;
    while (op < p)
        *np++ = *op++;
    p = np;
    for (;;) {
        if (mactop > inctop[ifno]) {
            op = instack[--mactop];
            np = pbuf;
            do {
                while ((*np++ = *op++) != '\0')
                    ;
            } while (op < endbuf[mactop]);
            pend = np - 1;
            if (fretop < MAXFRE)
                bufstack[fretop++] = instack[mactop];
            return (p);
        } else {
            maclvl = 0;
            if (0 < (ninbuf = (int)fread(pbuf, 1, BUFFERSIZ, fin))) {
                pend = pbuf + ninbuf;
                *pend = '\0';
                return (p);
            }
            if (ifno == 0) {
                if (plvl != 0) {
                    int n = plvl, tlin = lineno[ifno];
                    char *tfil = fnames[ifno];
                    lineno[ifno] = maclin;
                    fnames[ifno] = macfil;
                    pperror("%s: unterminated macro call", macnam);
                    lineno[ifno] = tlin;
                    fnames[ifno] = tfil;
                    np = p;
                    *np++ = '\n';
                    while (--n >= 0)
                        *np++ = ')';
                    pend = np;
                    *np = '\0';
                    if (plvl < 0)
                        plvl = 0;
                    return (p);
                }
                inptr = p;
                dump();
                exit(exfail);
            }
            fclose(fin);
            fin = fins[--ifno];
            dirs[0] = dirnams[ifno];
            fputc('\n', fout);
            sayline();
        }
    }
}

#define BEG 0
#define LF 1

STATIC char *cotoken(register char *p) {
    register int c, i;
    char quoc;
    int cppcom = 0;
    static int state = BEG;

    if (state != BEG)
        goto prevlf;
    for (;;) {
    again:
        while (!isspc(*p++));
        switch (*(inptr = p - 1)) {
        case 0:
            if (eob(--p)) {
                p = refill(p);
                goto again;
            } else
                ++p;
            break;
        case '|':
        case '&':
            for (;;) {
                if (*p++ == *inptr)
                    break;
                if (eob(--p))
                    p = refill(p);
                else
                    break;
            }
            break;
        case '=':
        case '!':
            for (;;) {
                if (*p++ == '=')
                    break;
                if (eob(--p))
                    p = refill(p);
                else
                    break;
            }
            break;
        case '<':
        case '>':
            for (;;) {
                if (*p++ == '=' || p[-2] == p[-1])
                    break;
                if (eob(--p))
                    p = refill(p);
                else
                    break;
            }
            break;
        case '\\':
            for (;;) {
                if (*p++ == '\n') {
                    ++lineno[ifno];
                    break;
                }
                if (eob(--p))
                    p = refill(p);
                else {
                    ++p;
                    break;
                }
            }
            break;
        case '/':
            for (;;) {
                if (*p == '*' || *p == '/') {
                    if (*p++ == '/')
                        cppcom++;
                    if (defining || !passcom) {
                        for (inptr = p - 2; (toktyp + COFF)[(int)inptr[-1]] == BLANK && inptr != outptr; inptr--);
                        dump();
                        ++flslvl;
                    }
                    for (;;) {
                        while (!iscom(*p++));
                        if (cppcom && p[-1] == '\n') {
                            p--;
                            goto endcom;
                        }
                        if (p[-1] == '*') {
                            for (;;) {
                                if (*p++ == '/')
                                    goto endcom;
                                if (eob(--p)) {
                                    if (defining || !passcom) {
                                        inptr = p;
                                        p = refill(p);
                                    } else if ((p - inptr) >= BUFFERSIZ) {
                                        inptr = p;
                                        p = refill(p);
                                        fputc('/', fout);
                                        outptr = inptr = p -= 3;
                                        *p++ = '/';
                                        *p++ = '*';
                                        *p++ = '*';
                                    } else
                                        p = refill(p);
                                } else
                                    break;
                            }
                        } else if (p[-1] == '\n') {
                            ++lineno[ifno];
                            if (defining || !passcom)
                                fputc('\n', fout);
                        } else if (eob(--p)) {
                            if (!passcom) {
                                inptr = p;
                                p = refill(p);
                            } else if ((p - inptr) >= BUFFERSIZ) {
                                inptr = p;
                                p = refill(p);
                                fputc('*', fout);
                                fputc('/', fout);
                                outptr = inptr = p -= 2;
                                *p++ = '/';
                                *p++ = '*';
                            } else
                                p = refill(p);
                        } else
                            ++p;
                    }
                endcom:
                    cppcom = 0;
                    if (defining || !passcom) {
                        outptr = inptr = p;
                        --flslvl;
                        goto again;
                    }
                    break;
                } else {
                    p++;
                }
                if (eob(--p))
                    p = refill(p);
                else
                    break;
            }
            break;
        case '"':
        case '\'':
            quoc = p[-1];
            for (;;) {
                while (!isquo(*p++));
                if (p[-1] == quoc)
                    break;
                if (p[-1] == '\n') {
                    --p;
                    break;
                }
                if (p[-1] == '\\')
                    for (;;) {
                        if (*p++ == '\n') {
                            ++lineno[ifno];
                            break;
                        }
                        if (eob(--p))
                            p = refill(p);
                        else {
                            ++p;
                            break;
                        }
                    }
                else if (eob(--p))
                    p = refill(p);
                else
                    ++p;
            }
            break;
        case '\n':
            ++lineno[ifno];
            if (isslo) {
                state = LF;
                return (p);
            }
        prevlf:
            state = BEG;
            for (;;) {
                if (*p++ == '#')
                    return (p);
                if (eob(inptr = --p))
                    p = refill(p);
                else
                    goto again;
            }
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            for (;;) {
                while (isnum(*p++));
                if (eob(--p))
                    p = refill(p);
                else
                    break;
            }
            break;
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
        case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
        case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
        case 'Y': case 'Z': case '_': case 'a': case 'b': case 'c':
        case 'd': case 'e': case 'f': case 'g': case 'h': case 'i':
        case 'j': case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't': case 'u':
        case 'v': case 'w': case 'x': case 'y': case 'z':

#define xmac1(c, bit, op) ((macbit + COFF)[(int)c] op (bit))
#define tmac1(c, bit) if (!xmac1(c, bit, &)) goto nomac

            if (flslvl)
                goto nomac;
            for (;;) {
                c = p[-1];
                tmac1(c, b0);
                i = *p++; if (!isid(i)) goto endid;
                tmac1(i, b1);
                c = *p++; if (!isid(c)) goto endid;
                tmac1(c, b2);
                i = *p++; if (!isid(i)) goto endid;
                tmac1(i, b3);
                c = *p++; if (!isid(c)) goto endid;
                tmac1(c, b4);
                i = *p++; if (!isid(i)) goto endid;
                tmac1(i, b5);
                c = *p++; if (!isid(c)) goto endid;
                tmac1(c, b6);
                i = *p++; if (!isid(i)) goto endid;
                tmac1(i, b7);
                while (isid(*p++));
                if (eob(--p)) {
                    refill(p);
                    p = inptr + 1;
                    continue;
                }
                goto lokid;
            endid:
                if (eob(--p)) {
                    refill(p);
                    p = inptr + 1;
                    continue;
                }
            lokid:
                slookup(inptr, p, 0);
                if (newp) {
                    p = newp;
                    goto again;
                } else
                    break;
            nomac:
                while (isid(*p++));
                if (eob(--p)) {
                    p = refill(p);
                    goto nomac;
                } else
                    break;
            }
            break;
        }
        if (isslo)
            return (p);
    }
}

char *skipbl(register char *p) {
    do {
        outptr = inptr = p;
        p = cotoken(p);
    } while ((toktyp + COFF)[(int)*inptr] == BLANK);
    return (p);
}

STATIC char *unfill(register char *p) {
    register char *np, *op;
    register int d;
    if (mactop >= MAXFRE) {
        pperror("%s: too much pushback", macnam);
        p = inptr = pend;
        dump();
        while (mactop > inctop[ifno]) {
            p = refill(p);
            p = inptr = pend;
            dump();
        }
    }
    if (fretop > 0)
        np = bufstack[--fretop];
    else {
        np = savch;
        savch += BUFFERSIZ;
        if (savch >= sbf + SBSIZE) {
#ifdef SMALL
            pperror("no space");
            exit(exfail);
#else
            newsbf();
            np = savch;
            savch += BUFFERSIZ;
#endif
        }
        *savch++ = '\0';
    }
    instack[mactop] = np;
    op = pend - BUFFERSIZ;
    if (op < p)
        op = p;
    for (;;) {
        while ((*np++ = *op++) != '\0');
        if (eob(op))
            break;
    }
    endbuf[mactop++] = np;
    np = pbuf + BUFFERSIZ;
    op = pend - BUFFERSIZ;
    pend = np;
    if (op < p)
        op = p;
    while (outptr < op)
        *--np = *--op;
    if (bob(np))
        pperror("token too long");
    d = (int)(np - outptr);
    outptr += d;
    inptr += d;
    macdam += d;
    return (p + d);
}

STATIC char *doincl(register char *p) {
    int filok, inctype;
    register char *cp;
    char **dirp, *nfil;
    char isFixedPath;
    char filname[BUFFERSIZ];

    filname[0] = '\0';
    p = skipbl(p);
    cp = filname;
    if (*inptr++ == '<') {
        inctype = 1;
        for (;;) {
            outptr = inptr = p;
            p = cotoken(p);
            if (*inptr == '\n') {
                --p;
                *cp = '\0';
                break;
            }
            if (*inptr == '>') {
                *cp = '\0';
                break;
            }
            while (inptr < p)
                *cp++ = *inptr++;
        }
    } else if (inptr[-1] == '"') {
        inctype = 0;
        while (inptr < p)
            *cp++ = *inptr++;
        if (*--cp == '"')
            *cp = '\0';
    } else {
        pperror("bad include syntax");
        inctype = 2;
    }
    ++flslvl;
    do {
        outptr = inptr = p;
        p = cotoken(p);
    } while (*inptr != '\n');
    --flslvl;
    inptr = p;
    dump();
    if (inctype == 2)
        return (p);
    if (ifno + 1 >= MAXINC) {
        pperror("Unreasonable include nesting");
        return (p);
    }
    if ((nfil = savch) > sbf + SBSIZE - BUFFERSIZ) {
#ifdef SMALL
        pperror("no space");
        exit(exfail);
#else
        newsbf();
        nfil = savch;
#endif
    }
    filok = 0;
#ifdef DEVSEP
    isFixedPath = ISDIRSEP(filname[0]) || strchr(filname, DEVSEP);
#else
    isFixedPath = ISDIRSEP(filname[0]);
#endif
    for (dirp = dirs + inctype; *dirp; ++dirp) {
        if (isFixedPath || **dirp == '\0')
            strcpy(nfil, filname);
        else {
            strcpy(nfil, *dirp);
            if (*fname(nfil))
                strcat(nfil, "/");
            strcat(nfil, filname);
        }

        if ((fins[ifno + 1] = fopen(nfil, "r"))) {
            filok = 1;
            fin = fins[++ifno];
            break;
        }
        if (isFixedPath)
            break;
    }
    if (filok == 0) {
        pperror("Can't find include file %s", filname);
    } else {
        lineno[ifno] = 1;
        fnames[ifno] = cp = nfil;
        while (*cp++);
        savch = cp;
        dirnams[ifno] = dirs[0] = trmdir(copy(nfil));
        sayline();
#ifndef SMALL
        if (hflag)
            fprintf(stderr, "%s\n", nfil);
        if (mflag)
            fprintf(mout, "%s: %s\n", input, fnames[ifno]);
#endif
        while (!eob(p))
            p = unfill(p);
        inctop[ifno] = mactop;
    }
    return (p);
}

STATIC int equfrm(register char *a, register char *p1, register char *p2) {
    register char c;
    int flag;
    c = *p2;
    *p2 = '\0';
    flag = strcmp(a, p1);
    *p2 = c;
    return (flag == SAME);
}

STATIC int xstrcmp(register char *s, char *t) {
    int cmp;
    char *snws;
    char *tnws;
    char slch;
    char tlch;
    char *p;
    while (*s && (*s == ' ' || *s == '\t'))
        s++;
    snws = NULL;
    for (p = s; *p; p++)
        if (*p != ' ' && *p != '\t')
            snws = p;

    if (snws) {
        slch = *++snws;
        *snws = 0;
    }
    while (*t && (*t == ' ' || *t == '\t'))
        t++;
    tnws = NULL;
    for (p = t; *p; p++)
        if (*p != ' ' && *p != '\t')
            tnws = p;

    if (tnws) {
        tlch = *++tnws;
        *tnws = 0;
    }
    cmp = strcmp(s, t);
    if (snws)
        *snws = slch;
    if (tnws)
        *tnws = tlch;
    return cmp;
}

STATIC char *dodef(char *p) {
    register char *pin, *psav, *cf;
    char **pf, **qf;
    int b, c, params;
    struct symtab *np;
    char quoc;
    char *oldval, *oldsavch;
    char *formal[MAXFRM];
    char formtxt[BUFFERSIZ];

    formtxt[0] = '\0';

    if (savch > sbf + SBSIZE - BUFFERSIZ) {
#ifdef SMALL
        pperror("too much defining");
        return p;
#else
        newsbf();
#endif
    }
    oldsavch = savch;
    ++flslvl;
    p = skipbl(p);
    pin = inptr;
    if ((toktyp + COFF)[(int)*pin] != IDENT) {
        ppwarn("illegal macro name");
        while (*inptr != '\n')
            p = skipbl(p);
        return (p);
    }
    np = slookup(pin, p, 1);
    if ((oldval = np->value) != NULL)
        savch = oldsavch;
    b = 1;
    cf = pin;
    while (cf < p) {
        c = *cf++;
        xmac1(c, b, |=);
        b = (b + b) & 0xFF;
    }
    params = 0;
    outptr = inptr = p;
    p = cotoken(p);
    pin = inptr;
    formal[0] = "";
    pf = formal;
    if (*pin == '(') {
        cf = formtxt;
        pf = formal;
        for (;;) {
            p = skipbl(p);
            pin = inptr;
            if (*pin == '\n') {
                --lineno[ifno];
                --p;
                pperror("%s: missing )", np->name);
                break;
            }
            if (*pin == ')')
                break;
            if (*pin == ',')
                continue;
            if ((toktyp + COFF)[(int)*pin] != IDENT) {
                c = *p;
                *p = '\0';
                pperror("bad formal: %s", pin);
                *p = c;
            } else if (pf >= &formal[MAXFRM]) {
                c = *p;
                *p = '\0';
                pperror("too many formals: %s", pin);
                *p = c;
            } else {
                *pf++ = cf;
                while (pin < p)
                    *cf++ = *pin++;
                *cf++ = '\0';
                ++params;
            }
        }
        if (params == 0)
            --params;
    } else if (*pin == '\n') {
        --lineno[ifno];
        --p;
    }
    oldsavch = psav = savch;
    defining = 1;
    for (;;) {
        outptr = inptr = p;
        p = cotoken(p);
        pin = inptr;
        if (*pin == '\\' && pin[1] == '\n')
            continue;
        if (*pin == '\n')
            break;
        if (params) {
            if ((toktyp + COFF)[(int)*pin] == IDENT) {
                for (qf = pf; --qf >= formal;) {
                    if (equfrm(*qf, pin, p)) {
                        *psav++ = (char)(qf - formal + 1);
                        *psav++ = WARN;
                        pin = p;
                        break;
                    }
                }
            } else if (*pin == '"' || *pin == '\'') {
                quoc = *pin;
                for (*psav++ = *pin++; pin < p && *pin != quoc;) {
                    while (pin < p && !isid(*pin))
                        *psav++ = *pin++;
                    cf = pin;
                    while (cf < p && isid(*cf))
                        ++cf;
                    for (qf = pf; --qf >= formal;) {
                        if (equfrm(*qf, pin, cf)) {
                            *psav++ = (char)(qf - formal + 1);
                            *psav++ = WARN;
                            pin = cf;
                            break;
                        }
                    }
                    while (pin < cf)
                        *psav++ = *pin++;
                }
            }
        }
        while (pin < p) {
            if (*pin == warnc) {
                *psav++ = WARN;
            }
            *psav++ = *pin++;
        }
    }
    *psav++ = params;
    *psav++ = '\0';
    defining = 0;
    if ((cf = oldval) != NULL) {
        --cf;
        while (*--cf);
        if (0 != xstrcmp(++cf, oldsavch)) {
            --lineno[ifno];
            ppwarn("%s redefined", np->name);
            ++lineno[ifno];
            np->value = psav - 1;
        } else
            psav = oldsavch;
    } else
        np->value = psav - 1;
    --flslvl;
    inptr = pin;
    savch = psav;
    return (p);
}

#define fasscan() ptrtab = fastab + COFF
#define sloscan() ptrtab = slotab + COFF

STATIC void control(register char *p) {
    register struct symtab *np;

    for (;;) {
        fasscan();
        p = cotoken(p);
        if (*inptr == '\n')
            ++inptr;
        dump();
        sloscan();
        p = skipbl(p);
        *--inptr = SALT;
        outptr = inptr;
        ++flslvl;
        np = slookup(inptr, p, 0);
        --flslvl;
        if (np == defloc) {
            if (flslvl == 0) {
                p = dodef(p);
                continue;
            }
        } else if (np == incloc) {
            if (flslvl == 0) {
                p = doincl(p);
                continue;
            }
        } else if (np == ifnloc) {
            ++flslvl;
            p = skipbl(p);
            np = slookup(inptr, p, 0);
            --flslvl;
            if (flslvl == 0 && np->value == 0)
                ++trulvl;
            else
                ++flslvl;
        } else if (np == ifdloc) {
            ++flslvl;
            p = skipbl(p);
            np = slookup(inptr, p, 0);
            --flslvl;
            if (flslvl == 0 && np->value != 0)
                ++trulvl;
            else
                ++flslvl;
        } else if (np == eifloc) {
            if (flslvl) {
                if (--flslvl == 0)
                    sayline();
            } else if (trulvl)
                --trulvl;
            else
                pperror("If-less endif");

            if (flslvl == 0)
                elflvl = 0;
            elslvl = 0;
        } else if (np == elifloc) {
            if (flslvl == 0)
                elflvl = trulvl;
            if (flslvl) {
                if (elflvl > trulvl) {
                    ;
                } else if (--flslvl != 0) {
                    ++flslvl;
                } else {
                    newp = p;
                    if (yyparse()) {
                        ++trulvl;
                        sayline();
                    } else {
                        ++flslvl;
                    }
                    p = newp;
                }
            } else if (trulvl) {
                ++flslvl;
                --trulvl;
            } else
                pperror("If-less elif");

        } else if (np == elsloc) {
            if (flslvl) {
                if (elflvl > trulvl)
                    ;
                else if (--flslvl != 0)
                    ++flslvl;
                else {
                    ++trulvl;
                    sayline();
                }
            } else if (trulvl) {
                ++flslvl;
                --trulvl;
            } else
                pperror("If-less else");

            if (elslvl == trulvl + flslvl)
                pperror("Too many #else's");
            elslvl = trulvl + flslvl;

        } else if (np == udfloc) {
            if (flslvl == 0) {
                ++flslvl;
                p = skipbl(p);
                slookup(inptr, p, DROP);
                --flslvl;
            }
        } else if (np == ifloc) {
            newp = p;
            if (flslvl == 0 && yyparse())
                ++trulvl;
            else
                ++flslvl;
            p = newp;
        } else if (np == pragmaloc) {
            ppwarn("#pragma ignored");
            ++flslvl;

            while (*inptr != '\n') {
                outptr = inptr = p;
                p = cotoken(p);
            }
            --flslvl;

        } else if (np == errorloc) {
            if (flslvl == 0) {
                char ebuf[BUFFERSIZ];
                char * Ptr = ebuf;
                while (*inptr != '\n') {
                    if (*inptr == '\0')
                        if (eob(--inptr)) {
                            inptr = refill(inptr);
                            continue;
                        }
                    *Ptr++ = *inptr++;
                    if (Ptr >= &ebuf[BUFFERSIZ - 1])
                        break;
                }
                *Ptr = '\0';
                pperror(ebuf);
                exit(exfail);
            }
        } else if (np == lneloc) {
            if (flslvl == 0 && pflag == 0) {
#ifndef SMALL
                register char *s;
                register int n;
#endif

                outptr = inptr = p;
#ifndef SMALL
                s = p;
                while (*s && *s != '\n')
                    s++;
                if (eob(s))
                    p = refill(s);

                s = inptr;
                while ((toktyp + COFF)[(int)*s] == BLANK)
                    s++;
                n = 0;
                while (isdigit(*s)) {
                    register int c;

                    if (n > MAXMULT) {
                        pperror("bad number for #line");
                        n = MAXVAL;
                        break;
                    }
                    n *= 10;
                    c = *s++ - '0';
                    if ((MAXVAL - n) < c) {
                        pperror("bad number for #line");
                        n = MAXVAL;
                        break;
                    }
                    n += c;
                }
                if (n == 0)
                    pperror("bad number for #line");
                else
                    lineno[ifno] = n - 1;

                while ((toktyp + COFF)[(int)*s] == BLANK)
                    s++;
                if (*s != '\n') {
                    register char *f;

                    f = s;
                    while (*f && *f != '\n')
                        f++;

                    if (savch >= sbf + SBSIZE - (f - s)) {
                        newsbf();
                    }
                    f = savch;
                    if (*s != '"')
                        *f++ = *s;
                    s++;
                    while (*s) {
                        if (*s == '"' || *s == '\n')
                            break;
                        *f++ = *s++;
                    }
                    *f++ = '\0';
                    if (strcmp(savch, fnames[ifno])) {
                        fnames[ifno] = savch;
                        savch = f;
                    }
                }
#endif
                *--outptr = '#';
                while (*inptr != '\n')
                    p = cotoken(p);
                continue;
            }
        } else if (np == asmloc || np == easloc) {
            while (*inptr != '\n')
                p = cotoken(p);
        } else if (*++inptr == '\n')
            outptr = inptr;
        else
            pperror("undefined control");
        ++flslvl;
        while (*inptr != '\n') {
            outptr = inptr = p;
            p = cotoken(p);
        }
        --flslvl;
    }
}

STATIC struct symtab *stsym(register char *s) {
    register char *p;
    char buf[BUFFERSIZ];

    p = buf;
    while ((*p++ = *s++) != '\0');
    p = buf;
    while (isid(*p++));
    if (*--p == '=') {
        *p++ = ' ';
        while (*p++);
    } else {
        s = " 1";
        while ((*p++ = *s++) != '\0');
    }
    pend = p;
    *--p = '\n';
    sloscan();
    dodef(buf);
    return (lastsym);
}

STATIC struct symtab *ppsym(char *s) {
    register struct symtab *sp;
    cinit = SALT;
    *savch++ = SALT;
    sp = stsym(s);
    --sp->name;
    cinit = 0;
    return (sp);
}

void _pperror(char *fmt, va_list args) {
    if (fnames[ifno] && fnames[ifno][0])
        fprintf(stderr, "%s: line ", fnames[ifno]);
    fprintf(stderr, "%d: ", lineno[ifno]);

    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
    exfail++;
}

void pperror(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _pperror(fmt, args);
    va_end(args);
}

void yyerror(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _pperror(fmt, args);
    va_end(args);
}

STATIC void ppwarn(char *fmt, ...) {
    va_list args;
    int fail = exfail;
    exfail = -1;
    va_start(args, fmt);
    _pperror(fmt, args);
    va_end(args);
    exfail = fail;
}

struct symtab *lookup(char *namep, int enterf) {
    register char *np, *snp;
    register unsigned int c, i;
    register struct symtab *sp;
#ifdef SMALL
    int around = 0;
#else
    struct symtab *prev;
    static struct symtab nsym;
#endif

    np = namep;
    i = cinit;
    while (np < namep + 8 && (c = *(unsigned char *)np++))
        i += i + c;
    c = i % symsiz;
#ifdef SMALL
    sp = &stab[c];
    while (snp = sp->name) {
        np = namep;
        while (*snp++ == *np)
            if (*np++ == '\0') {
                if (enterf == DROP) {
                    sp->name[0] = DROP;
                    sp->value = 0;
                }
                return (lastsym = sp);
            }
        if (--sp < &stab[0])
            if (around) {
                pperror("too many defines");
                exit(exfail);
            } else {
                ++around;
                sp = &stab[symsiz - 1];
            }
    }
    if (enterf > 0)
        sp->name = namep;
    return (lastsym = sp);
#else
    sp = stab[c];
    prev = sp;
    while (sp != NULL) {
        snp = sp->name;
        np = namep;
        while (*snp++ == *np) {
            if (*np++ == '\0') {
                if (enterf == DROP) {
                    sp->name[0] = DROP;
                    sp->value = 0;
                }
                return (lastsym = sp);
            }
        }
        prev = sp;
        sp = sp->next;
    }
    if (enterf > 0) {
        sp = newsym();
        sp->name = namep;
        sp->value = NULL;
        sp->next = NULL;
        if (prev)
            prev->next = sp;
        else
            stab[c] = sp;
    }
    if (sp == NULL)
        sp = &nsym;
    return (lastsym = sp);
#endif
}

STATIC struct symtab *slookup(register char *p1, register char *p2, int enterf) {
    register char *p3;
    char c2, c3;
    struct symtab *np;
    c2 = *p2;
    *p2 = '\0';
    if ((p2 - p1) > SYMLEN)
        p3 = p1 + SYMLEN;
    else
        p3 = p2;
    c3 = *p3;
    *p3 = '\0';
    if (enterf == 1)
        p1 = copy(p1);
    np = lookup(p1, enterf);
    *p3 = c3;
    *p2 = c2;
    if (np->value != 0 && flslvl == 0)
        newp = subst(p2, np);
    else
        newp = 0;
    return (np);
}

STATIC char *subst(register char *p, struct symtab *sp) {
    static char match[] = "%s: argument mismatch";
    register char *ca, *vp;
    int params;
    register char **pa;
    char *actual[MAXFRM];
    char acttxt[BUFFERSIZ];

    if (0 == (vp = sp->value))
        return (p);
    if ((p - macforw) <= macdam) {
        if (++maclvl > symsiz && !rflag) {
            pperror("%s: macro recursion", sp->name);
            return (p);
        }
    } else
        maclvl = 0;
    macforw = p;
    macdam = 0;
    macnam = sp->name;
    dump();
    if (sp == ulnloc) {
        vp = acttxt;
        *vp++ = '\0';
        sprintf(vp, "%d", lineno[ifno]);
        while (*vp++);
    } else if (sp == uflloc) {
        vp = acttxt;
        *vp++ = '\0';
        ca = fnames[ifno];
        *vp++ = '"';
        while (*ca) {
            if (*ca == '\\')
                *vp++ = '\\';
            *vp++ = *ca++;
        }
        *vp++ = '"';
        *vp++ = '\0';
    }
    if (0 != (params = *--vp & 0xFF)) {
        ca = acttxt;
        pa = actual;
        if (params == 0xFF)
            params = 1;
        sloscan();
        ++flslvl;
        plvl = -1;
        do
            p = skipbl(p);
        while (*inptr == '\n');
        if (*inptr == '(') {
            maclin = lineno[ifno];
            macfil = fnames[ifno];
            for (plvl = 1; plvl != 0;) {
                *ca++ = '\0';
                for (;;) {
                    outptr = inptr = p;
                    p = cotoken(p);
                    if (*inptr == '(')
                        ++plvl;
                    if (*inptr == ')' && --plvl == 0) {
                        --params;
                        break;
                    }
                    if (plvl == 1 && *inptr == ',') {
                        --params;
                        break;
                    }
                    while (inptr < p)
                        *ca++ = *inptr++;
                    if (ca > &acttxt[BUFFERSIZ])
                        pperror("%s: actuals too long", sp->name);
                }
                if (pa >= &actual[MAXFRM])
                    ppwarn(match, sp->name);
                else
                    *pa++ = ca;
            }
        }
        if (params != 0)
            ppwarn(match, sp->name);
        while (--params >= 0) {
            static char empty_string[] = "";
            *pa++ = &empty_string[1];
        }
        --flslvl;
        fasscan();
    }
    for (;;) {
        while (!iswarn(*--vp)) {
            if (bob(p)) {
                outptr = inptr = p;
                p = unfill(p);
            }
            *--p = *vp;
        }
        if (*vp == warnc) {
            if (vp[-1] == warnc) {
                *--p = *--vp;
                continue;
            }
            ca = actual[*--vp - 1];
            while (*--ca) {
                if (bob(p)) {
                    outptr = inptr = p;
                    p = unfill(p);
                }
                *--p = *ca;
            }
        } else
            break;
    }
    outptr = inptr = p;
    return (p);
}

STATIC char *trmdir(register char *s) {
    register char *p;

    p = strchr(s, '\0');
    while (--p > s && !ISDIRSEP(*p));

#ifndef CPM
    if (p == s && !ISDIRSEP(*p))
    {
        *p++ = '.';
    } else if (ISDIRSEP(*p)) {
        /* Keep the separator */
    } else {
       /* case p > s and not a separator, do nothing*/
    }
#else
    if (*p == ':') {
        p++;
    }
#endif
    *p = '\0';
    return (s);
}

STATIC char *copy(register char *s) {
    register char *old;
    old = savch;
    while ((*savch++ = *s++));
    return (old);
}

int yywrap(void) {
    return (1);
}

#define VERSION "2.3.modern"
#define VERSION_DATE "2025/06/12"

STATIC void printHelp(void);

/*
 * main - Main program.
 */
int main(int argc, char *argv[]) {
    register int i, c;
    register char *p;
    char *tf, **cp2;

#ifdef USE_GETARGS
    if (argc <= 1) {
        argv = _getargs(NULL, "cpp");
        argc = _argc_;
    }
#endif

    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printHelp();
        } else if (strcmp(argv[1], "--version") == 0) {
            fprintf(stdout, "cpp version %s (%s)\n", VERSION, VERSION_DATE);
            printf("\n");
            printf("Copyright (C) 1978 AT&T (John F. Reiser)\n");
            printf("Copyright (C) 2010-2021 Joerg Schilling\n");
            printf("Additional Changes Mark Ogden\n");
            fflush(stdout);
            exit(0);
        }
    }

    fin = stdin;
    fout = stdout;

    p = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    i = 0;
    while ((c = *p++)) {
        (fastab + COFF)[c] |= IB | NB | SB;
        (toktyp + COFF)[c] = IDENT;
    }
    p = "0123456789.";
    while ((c = *p++) != '\0') {
        (fastab + COFF)[c] |= NB | SB;
        (toktyp + COFF)[c] = NUMBR;
    }
    p = "\n\"'/\\";
    while ((c = *p++) != '\0')
        (fastab + COFF)[c] |= SB;
    p = "\n\"'\\";
    while ((c = *p++) != '\0')
        (fastab + COFF)[c] |= QB;
    p = "*\n";
    while ((c = *p++) != '\0')
        (fastab + COFF)[c] |= CB;
    (fastab + COFF)[(int)warnc] |= WB;
    (fastab + COFF)['\0'] |= CB | QB | SB | WB;
    for (i = ALFSIZ; --i >= 0;)
        slotab[i] = fastab[i] | SB;
    p = " \t\v\f\r";
    while ((c = *p++))
        (toktyp + COFF)[c] = BLANK;

    fnames[ifno = 0] = "";
#ifndef SMALL
    newsbf();
#endif
    dirs[0] = dirnams[0] = ".";
    
    if (argc == 1) {
        printHelp();
    }

    for (i = 1; i < argc && argv[i][0] == '-'; i++) {
        switch (toupper(argv[i][1])) {
        case 'P': pflag++; break;
        case 'R': ++rflag; break;
        case 'C': passcom++; break;
        case 'D':
            if (predef > prespc + NPREDEF) {
                pperror("too many -D options, ignoring %s", argv[i]);
                break;
            }
            if (*(argv[i] + 2))
                *predef++ = argv[i] + 2;
            break;
        case 'U':
            if (argv[i][2]) {
                if (prund > punspc + NPREDEF) {
                    pperror("too many -U options, ignoring %s", argv[i]);
                    break;
                }
                *prund++ = argv[i] + 2;
            } else
                nopredef = 1;
            break;
        case 'I':
            if (nd >= MAXIDIRS)
                pperror("excessive -I file (%s) ignored", argv[i]);
            else
                dirs[nd++] = argv[i] + 2;
            break;
#ifndef SMALL
        case 'H': hflag++; break;
        case 'M': mflag++; break;
        /* case 'Y': sysdir = argv[i] + 2; break; */
        case '\0': break;
        case '-': /* This case is for --help, --version, --noinclude */
            /* These are handled at the top, so only handle --noinclude here */
#ifndef CPM
            if (strcmp(argv[i], "--noinclude") == 0)
                noinclude = 1;
            else
#endif
                goto unknown; /* Fall through to unknown if not --noinclude */
            break;
        unknown:
#endif
        default:
            pperror("unknown flag %s", argv[i]);
            break;
        }
    }

    if (i < argc) {
        if ((fin = freopen(argv[i], "r", stdin)) == NULL) {
            pperror("No source file %s", argv[i]);
            exit(8);
        }
        fnames[ifno] = copy(argv[i]);
#ifndef SMALL
        input = copy(argv[i]);
#endif
        dirs[0] = dirnams[ifno] = trmdir(argv[i]);
        if (++i < argc) {
            if ((fout = freopen(argv[i], "w", stdout)) == NULL) {
                pperror("Can't create %s", argv[i]);
                exit(8);
            }
        }
    }

#ifndef SMALL
    if (mflag) {
        if (input == NULL) {
            pperror("cpp: no input file specified with -M flag");
            exit(8);
        }
        input = fname(input);
        p = strrchr(input, '.');
        if (p == NULL || p[1] == '\0') {
            pperror("cpp: no filename suffix");
            exit(8);
        }
        char *s = malloc(strlen(input) + 5);
        if (s == NULL) {
             pperror("cpp: malloc failed");
             exit(8);
        }
        strcpy(s, input);
        strcpy(s + (p - input), ".obj");
        input = s;
        mout = fout;
        if (NULL == (fout = fopen(NULDEV, "w"))) {
            pperror("Can't create " NULDEV);
            exit(8);
        }
    }
#endif

    fins[ifno] = fin;
    exfail = 0;

    dirs[nd++] = 0;
    defloc = ppsym("define");
    udfloc = ppsym("undef");
    incloc = ppsym("include");
    elsloc = ppsym("else");
    eifloc = ppsym("endif");
    elifloc = ppsym("elif");
    ifdloc = ppsym("ifdef");
    ifnloc = ppsym("ifndef");
    ifloc = ppsym("if");
    lneloc = ppsym("line");
    asmloc = ppsym("asm");
    easloc = ppsym("endasm");
    pragmaloc = ppsym("pragma");
    errorloc = ppsym("error");

    memset(macbit, 0, sizeof(macbit));

    if (!nopredef) {
        stsym("z80");
        stsym("HI_TECH_C");
#ifndef CPM
        stsym("_HOSTED");
#endif
    }

    ulnloc = stsym("__LINE__");
    uflloc = stsym("__FILE__");

    tf = fnames[ifno];
    fnames[ifno] = "command line";
    lineno[ifno] = 1;
    cp2 = punspc;
    while (cp2 < prund) {
        if ((p = strchr(*cp2, '=')) != NULL)
            *p++ = '\0';
        lookup(*cp2++, DROP);
    }
    cp2 = prespc;
    while (cp2 < predef)
        stsym(*cp2++);
    fnames[ifno] = tf;
    pbeg = buffer + SYMLEN;
    pbuf = pbeg + BUFFERSIZ;
    pend = pbuf + BUFFERSIZ;

    trulvl = 0;
    flslvl = 0;
    outptr = inptr = pend;
#ifndef SMALL
    if (mflag)
        fprintf(mout, "%s: %s\n", input, fnames[ifno]);
#endif
    
    control(pend);
    if (fclose(stdout) == -1) {
        fprintf(stderr, "CPP: Error closing output file\n");
        return 1;
    }
    return (exfail);
}

#ifndef SMALL
STATIC void newsbf() {
    if ((sbf = malloc(SBSIZE)) == NULL) {
        pperror("no buffer space");
        exit(exfail);
    }
    savch = sbf;
}

STATIC struct symtab *newsym() {
    static int nelem = 0;
    static struct symtab *syms = NULL;

    if (nelem <= 0) {
        syms = malloc(SYMINCR * sizeof(struct symtab));
        if (syms == NULL) {
            pperror("too many defines");
            exit(exfail);
        }
        nelem = SYMINCR;
    }
    nelem--;
    return (syms++);
}

STATIC void printHelp(void) {
    fprintf(stdout, "Usage: cpp [options] [input-file]\n");
    fprintf(stdout, "       [output-file]]\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "    -C         Pass all comments.\n");
    fprintf(stdout, "    -Dname     Defines name as 1.\n");
    fprintf(stdout, "    -Dname=var Defines name as val.\n");
    fprintf(stdout, "    -H         Print include paths.\n");
    fprintf(stdout, "    -Idirectory Adds dir to search path.\n");
    fprintf(stdout, "    -M         Generate dependencies.\n");
    fprintf(stdout, "    -P         No line control info.\n");
    fprintf(stdout, "    -R         Allow recursive macros.\n");
    fprintf(stdout, "    -Uname     Remove definition of name.\n");
    fprintf(stdout, "    -U         Remove all predefined macros.\n");
    fprintf(stdout, "    -Ydirectory Use dir instead of std include.\n");
    fprintf(stdout, "    -h, --help Display usage info.\n");
    fprintf(stdout, "    --noinclude Ignore std system include path.\n");
    fprintf(stdout, "    --version  Show cpp version info.\n");
    printf("\n");
    printf("Copyright (C) 1978 AT&T (John F. Reiser)\n");
    printf("Copyright (C) 2010-2021 Joerg Schilling\n");
    printf("Additional Changes Mark Ogden\n");
    g_skip_sayline_on_startup = true;
    fflush(stdout);
    exit(0);
}
#endif