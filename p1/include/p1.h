/*
 * The p1.h file is part of the restored P1.COM program
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
 * See the readme.md file for additional commentary
 *
 * Mark Ogden
 * 09-Jul-2022
 */
#ifndef _P1_H
#define _P1_H

#ifndef __bool_true_false_are_defined
typedef char bool;
#define true 1
#define false 0
#endif

/* Core includes needed by all platforms */
#include "cclass.h"
#include "tok.h"
#include "portab.h" /* Now using centralized portability header */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/* Include platform-specific headers through portab.h */
/* All platform detection and type definitions are now handled by portab.h */

#define HASHTABSIZE 271

/*
 * Structural declarations
 */
typedef union
{
    char *yStr;
    int32_t yNum;
    uint8_t yVal;
    struct _sym *ySym;
} YYTYPE;

typedef struct _s8
{
    union
    {
        struct _sym *_nextSym;
        struct _s8 *_nextAttr; /* short hand for &_nextSym->attr */
        int16_t _labelId;
    } u1;
    union
    {
        struct _expr *_pExpr;
        struct _args *_pFargs;
    } u2;
    uint16_t indirection;
    uint8_t dataType;
    char nodeType;
} attr_t;

#define nextSym u1._nextSym
#define nextAttr u1._nextAttr /* short hand for &nextSym->attr */
#define labelId u1._labelId
#define pExpr u2._pExpr
#define pFargs u2._pFargs

typedef struct _sym
{
    attr_t attr;
    struct _sym *symList;
    struct _sym *memberList;
    int16_t symId;
    int16_t memberId;
    int16_t bwidth;
    int16_t flags;
    uint8_t sclass;
    char level;
    char nRefCnt;
    char *nVName;
} sym_t;

/* flags flags */
#define S_MEM 1
#define S_REG 4
#define S_VAR 0x10
#define S_ARGDECL 0x20
#define S_IMPLICIT 0x40
#define S_NAMEID 0x80
#define S_EMITTED 0x100
#define S_ARG 0x200
#define S_BITFIELD 0x400

#define a_labelId attr.labelId
#define a_indirection attr.indirection
#define a_dataType attr.dataType
#define a_nodeType attr.nodeType
#define a_nextSym attr.nextSym
#define a_expr attr.pExpr
#define a_args attr.pFargs

typedef struct
{
    char name[3];
    char prec;
    uint8_t operandFlags;
    int16_t operatorFlags;
    uint8_t nodeType;
} op_t;

/* operand flags */
#define O_LEAF 1   /* leaf expression */
#define O_BINARY 2 /* binary expression */
#define O_ALT 4    /* unary/binary expression */
#define O_RTOL 8
#define O_16 16

/* operator flags */
#define OP_RBOOL 1 /* requires right bool */
#define OP_LBOOL 2 /* requires left bool */
#define OP_SCALE 4 /* operation scales for pointers */
#define OP_FLOAT 0x10
#define OP_INT 0x20
#define OP_UNSIGNED 0x40
#define OP_VOIDFUNC 0x80 /* promote void in function args */
#define OP_SIZEOF 0x100  /* sizeof op */
#define OP_SEP 0x200     /* separates expressions */
#define OP_MEMBER 0x800  /* access member */
#define OP_AREL 0x1000   /* arithmetic rel */
#define OP_RTOL 0x2000   /* right to left associative */
#define OP_DREF 0x4000   /* deref */
#define OP_EREL 0x8000   /* equality rel*/

typedef struct _args
{
    int16_t cnt;
    attr_t argVec[1];
} args_t;

typedef struct _s12
{
    sym_t *pSym1;
    attr_t *pAttr;
    sym_t *pSym2;
    uint16_t indirection;
    bool badInd;
    bool needDim;
    bool uca;
    bool ucb;
} decl_t;

typedef struct _expr
{
    uint8_t tType;
    union
    {
        unsigned long _t_ul;
        long _t_l;
        char *_t_s;
        struct _sym *_t_pSym;
        struct
        {
            struct _expr *_lhs;
            struct _expr *_rhs;
        } s1;
        struct
        {
            int16_t _id;
            int16_t _chCnt;
        } s2;
    } u1;
#define t_ul u1._t_ul
#define t_l u1._t_l
#define t_s u1._t_s
#define t_lhs u1.s1._lhs
#define t_rhs u1.s1._rhs
#define t_id u1.s2._id
#define t_chCnt u1.s2._chCnt
#define t_pSym u1._t_pSym
    attr_t attr;
} expr_t;

typedef struct
{
    expr_t *caseVal;
    int16_t caseLabel;
} s4_t;

typedef struct
{
    expr_t *switchExpr;
    int16_t caseCnt;
    int16_t defLabel;
    s4_t caseOptions[255];
} case_t;

typedef struct
{
    uint8_t op;
    uint8_t prec;
} opStk_t;

/* Global variables */
extern opStk_t *opSP;
extern int16_t strId;
extern uint8_t byte_8f85;
extern bool lexMember;
extern char *keywords[];
extern char *tmpFile;
extern op_t opTable[68];
extern uint8_t byte_968b;
extern int16_t word_968c;
extern int16_t tmpLabelId;
extern int16_t lastLineNo;
extern char emittedSrcFile[64];
extern expr_t **exprSP;
extern opStk_t opStk[20];
extern expr_t eZero;
extern expr_t eOne;
extern expr_t *exprFreeList;
extern uint8_t byte_9d37;
extern expr_t *exprStk[20];
extern char lastEmitSrc[64];
extern bool sInfoEmitted;
extern int16_t inCnt;
extern char lastEmitFunc[40];
extern YYTYPE yylval;
extern char nameBuf[32];
extern uint8_t ungetTok;
extern int16_t strChCnt;
extern bool lInfoEmitted;
extern int16_t startTokCnt;
extern int16_t ungetCh;
extern char errBuf[512];
extern FILE *crfFp;
extern char crfNameBuf[30];
extern char srcFile[100];
extern char *crfFile;
extern bool s_opt;
extern bool w_opt;
extern int16_t lineNo;
extern char *srcFileArg;
extern bool l_opt;
extern FILE *tmpFp;
extern char inBuf[512];
extern int16_t errCnt;
extern int8_t depth;
extern uint8_t voidReturn;
extern bool unreachable;
extern int16_t returnLabel;
extern sym_t *curFuncNode;
extern sym_t *p25_a28f;
extern sym_t *tmpSyms;
extern sym_t *symFreeList;
extern sym_t **hashtab;
extern decl_t *curDecl;
extern uint8_t defSClass;
extern uint8_t byte_a29a;

/* Function declarations */
/* emit.c */
void emitDependentVar(sym_t *p);
void prFuncBrace(uint8_t tok);
void emitLocalLabelDef(int16_t p);
void emitLabelDef(sym_t *st);
void emitCase(case_t *p1);
void emitStructUnion(sym_t *p, char c);
void emitCast(expr_t *p);
void emitVar(sym_t *st);
void emitAscii(expr_t *st, char *pc);
void sub_05b5(expr_t *p1);
void sub_05d3(expr_t *p1);
void resetExprStack(void);

/* expr.c */
expr_t *sub_07f5(char p1);
expr_t *parseConstExpr(uint8_t n);
expr_t *sub_0bfc(void);
expr_t *parseExpr(uint8_t p1, expr_t *lhs, expr_t *rhs);
expr_t *newIntLeaf(long num, uint8_t p2);
bool isZero(expr_t *st);
bool releaseExprList(void);
expr_t *cloneExpr(expr_t *st);
expr_t *newIdLeaf(sym_t *st);
expr_t *newIConstLeaf(long p1);
expr_t *newSTypeLeaf(attr_t *p1);
void pushExpr(expr_t *p1);
void freeExpr(expr_t *st);
expr_t *sub_25f7(expr_t *st);

/* lex.c */
uint8_t yylex(void);
void prMsgAt(char *buf);
void emitSrcInfo(void);
int16_t peekCh(void);
void skipStmt(uint8_t tok);
void expect(uint8_t etok, char *msg);
void skipToSemi(void);

/* main.c */
int main(int argc, char *argv[]);
void prError(const char *fmt, ...);
void fatalErr(const char *fmt, ...);
void prWarning(const char *fmt, ...);
void expectErr(char *p);
void *xalloc(size_t size);

/* program.c */
void sub_3adf(void);
void sub_3c7e(sym_t *p1);

/* stmt.c */
void parseFunction(void);

/* sym.c */
void sub_4d92(void);
sym_t *sub_4e90(char *buf);
sym_t *sub_4eed(sym_t *st, uint8_t p2, attr_t *p3, sym_t *p4);
void defineArg(sym_t *st);
void sub_51cf(sym_t *st);
void defineFuncSig(void);
bool releaseSymFreeList(void);
void enterScope(void);
void exitScope(void);
void releaseScopeSym(void);
sym_t *newTmpSym(void);
sym_t *findMember(sym_t *p1, char *p2);
void emitSymName(sym_t *st, FILE *fp);
int16_t newTmpLabel(void);
args_t *cloneArgs(args_t *p);
void cloneAttr(attr_t *st, attr_t *p2);
bool haveSameDataType(attr_t *st, attr_t *p2);
bool isVoidStar(attr_t *st);
bool isVarOfType(attr_t *st, uint8_t p2);
bool isLogicalType(attr_t *st);
bool isSimpleType(attr_t *st);
bool isIntType(attr_t *st);
bool isFloatType(attr_t *st);
bool isValidIndex(attr_t *st);
void delIndirection(attr_t *st);

/* type.c */
void addIndirection(attr_t *st);
void sub_5c19(uint8_t p1);
uint8_t sub_5dd1(uint8_t *pscType, attr_t *attr);
sym_t *sub_60db(uint8_t p1);
sym_t *sub_6360(void);
sym_t *sub_69ca(uint8_t p1, attr_t *p2, uint8_t p3, sym_t *p4);
void emitAttr(attr_t *st);

#endif /* _P1_H */