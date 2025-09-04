/*
 *
 * The main.c file is part of the restored P1.COM program
 * from the Hi-Tech CP/M Z80 C v3.09
 *
 * Not a commercial goal of this laborious work is to popularize among
 * potential fans of 8-bit computers the old HI-TECH Z80 C compiler V3.09
 * (HI-TECH Software) and extend its life, outside of the CP/M environment
 * for full operation in windows 32/64 and Unix-like operating systems
 *
 * The HI-TECH Z80 C cross compiler V3.09 is provided free of charge for any use,
 * private or commercial, strictly as-is. No warranty or product support
 * is offered or implied including merchantability, fitness for a particular
 * purpose, or non-infringement. In no event will HI-TECH Software or its
 * corporate affiliates be liable for any direct or indirect damages.
 *
 * You may use this software for whatever you like, providing you acknowledge
 * that the copyright to this software remains with HI-TECH Software and its
 * corporate affiliates.
 *
 * All copyrights to the algorithms used, binary code, trademarks, etc.
 * belong to the legal owner - Microchip Technology Inc. and its subsidiaries.
 * Commercial use and distribution of recreated source codes without permission
 * from the copyright holderis strictly prohibited.
 *
 *
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 09-Jul-2022
 */
#include "p1.h"
#include <errno.h> /* For errno */

char *tmpFile = "p1.tmp"; /* 91db */
char errBuf[512];         /* 9df7 */
FILE *crfFp;              /* 9ff7 */
char crfNameBuf[30];      /* 9ff9 */
char srcFile[100];        /* a017 */
char *crfFile;            /* a07b */
bool s_opt;               /* a07d */
bool w_opt;               /* a07e */
int16_t lineNo;           /* a07f */
char *srcFileArg;         /* a081 */
bool l_opt;               /* a083 */
FILE *tmpFp;              /* a084 */
char inBuf[512];          /* a086 */
int16_t errCnt;           /* a286 */

int main(int argc, char *argv[]);
void prMsg(const char *fmt, va_list args);
void copyTmp(void);
void closeFiles(void);
void mainParseLoop(void);

/**************************************************
 * 71: 367E PMO +++
 * basic blocks located differently
 * strcpy 2nd arg optimisation missed
 **************************************************/
int main(int argc, char *argv[]) {
    /* char *st; */

    initMemAddr(); /* get data area range */

    for (--argc, ++argv; argc > 0 && argv[0][0] == '-'; --argc, argv++) {
        switch (argv[0][1]) {
        case 'E':
        case 'e':
            if (!freopen(*argv + 2, "a", stderr)) {
                perror("Failed to open error file");
                exit(EXIT_FAILURE);
            }
            setvbuf(stderr, errBuf, _IOLBF, sizeof(errBuf));
            break;
        case 'S':
        case 's':
            s_opt = true;
            break;
        case 'W':
        case 'w':
            w_opt = true;
            break;
        case 'L':
        case 'l':
            l_opt = true;
            break;
        case 'C':
        case 'c':
            if (argv[0][2] != '\0') {
                crfFile = argv[0] + 2;
            } else {
                crfFile = crfNameBuf;
            }
            break;
        default:
            fprintf(stderr, "Unknown option: %s\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    sub_4d92();
    resetExprStack();
    if (argc > 0) {
        if (freopen(argv[0], "r", stdin) == NULL) {
            perror("Failed to open input file");
            fatalErr("can't open %s", *argv);
        }
        srcFileArg = argv[0];
        strcpy(srcFile, srcFileArg);
        if (argc > 1 && freopen(argv[1], "w", stdout) == NULL) {
            perror("Failed to open output file");
            fatalErr("can't open %s", argv[1]);
        }
        if (argc == 3) {
            tmpFile = argv[2];
        }
    } else {
        strcpy(srcFile, srcFileArg = "(stdin)");
    }

    if (crfFile) {
        if (*crfFile == '\0') {
            crfFile = crfNameBuf;
            strcpy(crfNameBuf, srcFile);
            char *dot = strrchr(crfNameBuf, '.');
            if (dot) {
                strcpy(dot, ".crf");
            } else {
                strcat(crfNameBuf, ".crf");
            }
        }
        if (!(crfFp = fopen(crfFile, "a"))) {
            prWarning("Can't create xref file %s", crfFile);
        } else {
            fprintf(crfFp, "~%s\n", srcFile);
        }
    }
    if (!(tmpFp = fopen(tmpFile, "w"))) {
        perror("Failed to open temporary file");
        fatalErr("can't open %s", tmpFile);
    }

    eOne.tType = T_ICONST;
    eZero.tType = T_ICONST;
    eZero.attr.dataType = eOne.attr.dataType = DT_INT;
    eZero.t_l = 0;
    eOne.t_l = 1;

    mainParseLoop();
    copyTmp();

    if (fclose(stdout) == EOF) {
        prError("close error (disk space?)");
    }
    closeFiles();
    exit(errCnt != 0);
}

void prMsg(const char *fmt, va_list args) {
    char buf[128];
    vsnprintf(buf, sizeof(buf), fmt, args);
    prMsgAt(buf);
}

void prError(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ++errCnt;
    prMsg(fmt, args);
    va_end(args);
    fputc('\n', stderr);
}

void fatalErr(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ++errCnt;
    prMsg(fmt, args);
    va_end(args);
    fputc('\n', stderr);
    closeFiles();
    exit(EXIT_FAILURE);
}

void prWarning(const char *fmt, ...) {
    if (w_opt) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    prMsg(fmt, args);
    va_end(args);
    fprintf(stderr, " (warning)\n");
}

/**************************************************
 * 76: 39F3 PMO +++
 **************************************************/
void expectErr(char *p) {
    prError("%s expected", p);
}

/**************************************************
 * 77: 3A07 PMO +++
 **************************************************/
void copyTmp(void) {
    int ch;

    if (fclose(tmpFp) == EOF) {
        perror("Failed to close temporary file for reading");
        fatalErr("Can't close %s", tmpFile);
    }

    if ((tmpFp = fopen(tmpFile, "r")) == NULL) {
        perror("Failed to reopen temporary file for reading");
        fatalErr("Can't reopen %s", tmpFile);
    }

    while ((ch = fgetc(tmpFp)) != EOF) {
        if (fputc(ch, stdout) == EOF) {
            prError("Error writing to stdout (disk space?)");
            break;
        }
    }
}

/**************************************************
 * 78: 3A5E PMO +++
 **************************************************/
void closeFiles(void) {
    fclose(stdin);
    fclose(stdout);
    if (tmpFp) {
        fclose(tmpFp);
        if (unlink(tmpFile) != 0) {
            perror("Failed to delete temporary file");
            prWarning("Could not delete temporary file: %s", tmpFile);
        }
    }
    if (crfFp) { /* PMO - close missing in original */
        fclose(crfFp);
    }
}
/**************************************************
 * 79: 3A80 PMO +++
 **************************************************/
void *xalloc(size_t size) {
    char *ptr;

    do {
        ptr = malloc(size);
        if (ptr != NULL) {
            goto done;
        }
    } while (releaseSymFreeList() || releaseExprList());
    fatalErr("Out of memory");
done:
    memset(ptr, 0, size);
    return ptr;
}

/**************************************************
 * 80: 3ABF PMO +++
 **************************************************/
void mainParseLoop(void) {
    uint8_t tok;

    while ((tok = yylex()) != T_EOF) {
        ungetTok = tok;
        sub_3adf();
    }
    releaseScopeSym();
}