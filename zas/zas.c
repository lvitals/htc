#include "zas.h"
#include <stdlib.h> /* For malloc */

FILE *crfFp;          /* 9e18 */
char crfNameBuf[30];  /* 9e1a */
bool i_opt;           /* 9e38 */
char l_opt;           /* 9e39 */
char phase;           /* 9e3a */
char objNameBuf[30];  /* 9e3b */
bool j_opt;           /* 9e59 */
bool s_opt;           /* 9e5a */
int nInput;           /* 9e5b */
char *crfFileName;    /* 9e5d */
int inputFileCnt;     /* 9e5f */
uint8_t c_opt;        /* 9e61 */
char **inputFileList; /* 9e62 */
bool u_opt;           /* 9e64 */
int numerror;         /* 9e65 */
bool e_opt;           /* 9e67 */
bool n_opt;           /* 9e68 */
bool x_opt;           /* 9e69 */
char *lstFileName;    /* 9e6a */
char *objFileName;    /* 9e6c */
FILE *objFp;          /* 9e6e */
char *includePath;    /* New global for include path */

/***************************************************************
 59	main	sub_2ef4 +++
 * a block of 3 basic blocks is located differently, specifically
 * the for block code just after the if (!objFileName)
 * also uses bc instead of hl for assignment in case 'o'
 * code is otherwise same
 ***************************************************************/
int main(int argc, char **argv) {
    size_t extPt;
    int i;
    char **collectedInputFiles = NULL;
    int collectedInputFileCount = 0;

    /* Allocate space for collected input files (max argc - 1) */
    if (argc > 1) {
        collectedInputFiles = (char **)malloc((argc - 1) * sizeof(char *));
        if (collectedInputFiles == NULL) {
            fatalErr("Memory allocation failed for input files.");
        }
    }

    /* Skip program name (argv[0]) */
    for (i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') { /* It's an option */
            switch (argv[i][1]) {
            case 'E':
            case 'e': /* Change default fatalErr message format */
                e_opt = true;
                break;
            case 'L':
            case 'l': /* Place an assembly listing in the file */
                if (argv[i][2]) {
                    lstFileName = &argv[i][2];
                } else {
                    if (i + 1 >= argc) fatalErr("No arg to -l");
                    lstFileName = argv[++i]; /* Consume next argument */
                }
                l_opt = true;
                break;
            case 'U':
            case 'u': /* Treat undefined symbols as  external */
                u_opt = true;
                break;
            case 'J':
            case 'j': /* Attempt to optimize jumps to branches */
                j_opt = true;
                break;
            case 'W':
            case 'w': /* Set page width */
                if (argv[i][2]) {
                    if ((width = atoi(&argv[i][2])) < 41)
                        fatalErr("Page width must be >= 41");
                } else {
                    if (i + 1 >= argc) fatalErr("No arg to -w");
                    if ((width = atoi(argv[++i])) < 41)
                        fatalErr("Page width must be >= 41");
                }
                break;
            case 'N':
            case 'n': /* Ignore arithmetic overflow in expressions */
                n_opt = true;
                break;
            case 'I': /* Specify include path */
                if (argv[i][2]) {
                    includePath = &argv[i][2];
                } else {
                    if (i + 1 >= argc) fatalErr("No arg to -I");
                    includePath = argv[++i]; /* Consume next argument */
                }
                break;
            case 'i': /* Print listing macro extensions */
                i_opt = true;
                break;
            case 'S':
            case 's': /* Suppress "Size fatalErr" messages */
                s_opt = true;
                break;
            case 'O':
            case 'o': /* Place the object code in file */
                if (argv[i][2]) {
                    objFileName = &argv[i][2];
                } else {
                    if (i + 1 >= argc) fatalErr("No arg to -o");
                    objFileName = argv[++i]; /* Consume next argument */
                }
                break;
            case 'X':
            case 'x': /* Prevent inclusion of local symbols in object file */
                x_opt = true;
                break;
            case 'C':
            case 'c': /* Produce cross reference information in a file */
                ++c_opt;
                break;
            default:
                fatalErr("Illegal switch %c", argv[i][1]);
                break;
            }
        } else { /* Not an option, it's an input file */
            if (collectedInputFileCount >= argc - 1) { /* Should not happen with correct allocation */
                fatalErr("Too many input files.");
            }
            collectedInputFiles[collectedInputFileCount++] = argv[i];
        }
    }

    if (collectedInputFileCount == 0) {
        fatalErr("No input files specified.");
    }

    inputFileList = collectedInputFiles;
    inputFileCnt = collectedInputFileCount;

    if (!objFileName || c_opt) { /* PMO fix incase -O and -C specified */
        char *name = fname(inputFileList[0]); /* Use the first input file for default name */
        char *dot = strrchr(name, '.');
        extPt     = dot ? (size_t)(dot - name) : strlen(name);
        if (extPt > 25)
            extPt = 25;
        if (!objFileName) {
            strncpy(objNameBuf, name, extPt);
            strcat(objNameBuf, ".obj"); /* relies on objNameBuf having all zeros at start */
            objFileName = objNameBuf;
        }
        strncpy(crfNameBuf, name, extPt); /* relies on crfNameBuf having all zeros at start */
        strcat(crfNameBuf, ".crf");
        crfFileName = crfNameBuf;
    }
    nInput        = 0;
    /* inputFileList and inputFileCnt are already set */
    enterAbsPsect();
    phase = 0;
    if (j_opt) { /* jump optimizations */
        doPass();
        resetVals();
        nInput = 0;
        phase  = 1;
    }
    doPass();
    phase = 2;
    resetVals();
    if (c_opt && !(crfFp = fopen(crfFileName, "w"))) 
        fatalErr("Can't create cross reference file %s", crfFileName);
    nInput = 0;
    if (!(objFp = fopen(objFileName, "wb"))) 
        fatalErr("Can't create %s", objFileName);

    if ((controls = l_opt) && lstFileName && !freopen(lstFileName, "w", stdout))
        fatalErr("Can't create %s", lstFileName);
    setHeading("");
    if (l_opt && width == 0)
        width = 80;

    writeObjHeader();
    doPass();
    writeRecords();
    sortSymbols();
    if (l_opt) {
        prSymbols();
        if (l_opt && j_opt)
            printf("\n%d jump optimizations\n", jmpOptCnt);
        topOfPage();
    }
    addObjAllSymbols(); /* m31: */
    addObjEnd();
    exit(numerror != 0);
}

/**************************************************************************
 60	getNextFile	+++
 **************************************************************************/
char *getNextFile() {
    if (nInput < inputFileCnt)
        return inputFileList[nInput++];
    return 0;
}
/**************************************************************************
 61	fatalErr	sub_32bfh	+++
 **************************************************************************/
#ifndef __GNUC__
_Noreturn void fatalErr(p1, p2, p3) char *p1;
{
    prMsg(p1, p2, p3);
    exit(1);
}
#else
_Noreturn void fatalErr(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    prMsg(fmt, args);
    va_end(args);
    exit(1);
}
#endif

/**************************************************************************
 62	error	sub-32e6h	+++
 **************************************************************************/
#ifdef CPM
void error(p1, p2, p3) char *p1;
{
    if (phase != 2)
        return;
    prMsg(p1, p2, p3);
    putErrCode(*p1);
    if (++numerror < 100)
        return;
    fatalErr("Too many errors");
}
#else
void error(char const *fmt, ...) {
    if (phase != 2)
        return;

    va_list args;
    va_start(args, fmt);
    prMsg(fmt, args);
    va_end(args);
    putErrCode(*fmt);
    if (++numerror < 100)
        return;
    fatalErr("Too many errors");
}

#endif

/**************************************************************************
 63	prMsg	+++
 **************************************************************************/
#ifdef CPM
void prMsg(p1, p2, p3) char *p1;
{
    if (curFileName && *curFileName)
        fprintf(stderr, "%s:%d:\t", curFileName, curLineno);

    fprintf(stderr, p1, p2, p3);
    fputc('\n', stderr);
}
#else
void prMsg(char const *fmt, va_list args) {
    if (curFileName && *curFileName)
        fprintf(stderr, "%s:%d:\t", curFileName, curLineno);

    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}
#endif
