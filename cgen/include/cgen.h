/*
 * =============================================================================
 * cgen.h -- Header principal para o Code Generator
 * =============================================================================
 * Contém as definições de estruturas de dados, constantes de tokens,
 * variáveis globais e protótipos de funções para o cgen.
 *
 * A responsabilidade de portabilidade foi movida para "portab.h".
 * =============================================================================
 */
#ifndef _CGEN_H
#define _CGEN_H 1

/* Inclui o header de portabilidade que define tipos, macros e funções
 * dependentes de plataforma/compilador. */
#include "portab.h"

/*
#define DEBUG
*/

#undef max /* Garante o uso da nossa função `max`, se existir */

/*
 * Constantes de tokens e opcodes do compilador
 */
#define MAXFUN 0x20  /* Limite máximo de aninhamento de funções */
#define MAXBUF 60    /* Tamanho máximo de buffer */
#define MAXNAME 40   /* Tamanho máximo de nome de arquivo */
#define MAXERR 30    /* Número máximo de erros não fatais */

#define NULSTR 0     /* 0  "" */
#define NOT 1        /* 1  "!"    */
#define NEQL 2       /* 2  "!="   */
#define HASHSIGN 3   /* 3  "#"    */
#define DOLLAR 4     /* 4  "$"    */
#define DOLLAR_U 5   /* 5  "$U"   */
#define MOD 6        /* 6  "%"    */
#define BAND 7       /* 7  "&"    */
#define LAND 8       /* 8  "&&"   */
#define GADDR 9      /* 9  "&U"   */
#define LPAREN 0xA   /* 10  "("    */
#define RPAREN 0xB   /* 11  ")"    */
#define MUL 0xC      /* 12  "*"    */
#define MUL_U 0xD    /* 13  "*U"   */
#define ADD 0xE      /* 14  "+"    */
#define INCR 0xF     /* 15  "++"   */
#define PLUS_U 0x10  /* 16  "+U"   */
#define COMMA 0x11   /* 17  ","    */
#define SUB 0x12     /* 18  "-"    */
#define DECR 0x13    /* 19  "--"   */
#define CONV 0x14    /* 20  "->"   */
#define MINUS_U 0x15 /* 21  "-U"   */
#define DOT 0x16     /* 22  "."    */
#define MEMBER 0x16  /* Alias for use in class*/
#define DOT_DOT 0x17 /* 23  ".."   */
#define DIV 0x18     /* 24  "/"    */
#define COLON 0x19   /* 25  ":"    */
#define COLON_U 0x1A /* 26  ":U"   */
#define COLON_S 0x1B /* 27  ":s"   */
#define SCOLON 0x1C  /* 28  ";"    */
#define T_SCOLON 0x1D/* 29  ";;"   */
#define LT 0x1E      /* 30  "<"    */
#define LSHIFT 0x1F  /* 31  "<<"   */
#define LEQ 0x20     /* 32  "<="   */
#define ASSIGN 0x21  /* 33  "="    */
#define ASMOD 0x22   /* 34  "=%"   */
#define ASAND 0x23   /* 35  "=&"   */
#define ASMUL 0x24   /* 36  "=*"   */
#define ASADD 0x25   /* 37  "=+"   */
#define ASSUB 0x26   /* 38  "=-"   */
#define ASDIV 0x27   /* 39  "=/"   */
#define ASLSHIFT 0x28/* 40  "=<<"  */
#define EQL 0x29     /* 41  "=="   */
#define ASRSHIFT 0x2A/* 42  "=>>"  */
#define ASEXOR 0x2B  /* 43  "=^"   */
#define ASEOR 0x2C   /* 44  "=|"   */
#define GT 0x2D      /* 45  ">"    */
#define GEQ 0x2E     /* 46  ">="   */
#define RSHIFT 0x2F  /* 47  ">>"   */
#define QUEST 0x30   /* 48  "?"    */
#define ATGIGN 0x31  /* 49  "@"    */
#define CASE 0x32    /* 50  "[\\"  */
#define UNKNOWN 0x33 /* 51  "[a"   */
#define ENUM 0x34    /* 52  "[c"   */
#define EXPR 0x35    /* 53  "[e"   */
#define INIT 0x36    /* 54  "[i"   */
#define STRUCT 0x37  /* 55  "[s"   */
#define UNION 0x38   /* 56  "[u"   */
#define VAR 0x39     /* 57  "[v"   */
#define BXOR 0x3A    /* 58  "^"    */
#define LBRACE 0x3B  /* 59  "{"    */
#define BOR 0x3C     /* 60  "|"    */
#define LOR 0x3D     /* 61  "||"   */
#define RBRACE 0x3E  /* 62  "}"    */
#define BNOT 0x3F    /* 63  "~"    */
#define RECIP 0x40   /* 64  "RECIP"   */
#define TYPE 0x41    /* 65  "TYPE"    */
#define IDOP 0x42    /* 66  "ID"   */
#define CONST 0x43   /* 67  "CONST"   */
#define FCONST 0x44  /* 68  "FCONST"  */
#define USEREG 0x45  /* 69  "REG"     */
#define INAREG 0x46  /* 70  "INAREG"  */
#define BFIELD 0x47  /* 71  "BITFIELD"*/

/* Índices de registradores */
enum
{ /* REG_A=1, REG_C, REG_B, REG_E, REG_D, REG_L*/
    REG_H = 7,
    /* REG_IX, REG_IY, REG_SP */
    REG_AF = 11,
    /* REG_BC, REG_DE, REG_HL */
    REG_DEHL = 15
};

/* Seções de programa (psects) */
enum psect
{
    P_BSS = 1,
    P_TEXT,
    P_DATA
};

/*
 * Declarações de Estruturas
 */
typedef struct node
{
    uint8_t a_c0;
    uint8_t a_c1;
    uint8_t a_c2; /* two bits used */
    uint8_t a_c3[6];
    uint8_t a_uc9[6];
    uint8_t a_reg[6];
    uint16_t a_i15;
    struct member *pm; /* pointer to member */
    union {
        long l;             /* long */
        unsigned long ul;   /* unsigned long, to avoid cast*/
        struct node *np[2]; /* node pair */
        struct member *mp[2]; /* member pair */
        struct
        { /* string + int value */
            char *s;
            int v;
        } sv;
    } info;
} node_t;

typedef struct member
{
    char *b_name;          /* Pointer to Name identifier  */
    char b_class;          /* MEMBER, ENUM, STRUCT, UNION, TYPE */
    char b_sloc;           /* Storage location flags */
    uint8_t b_ndpth;       /* Nesting depth of block */
    uint8_t bWidth;
    uint8_t bOffset;
    struct member *b_next;
    uint16_t b_size;  /* Type size */
    uint16_t b_nelem;
    uint16_t b_refl;
    struct member *b_type;
    int b_off; /* Type align size stack frame */
    union {
        int16_t i;
        struct _memb
        {
            int16_t cnt;
            struct member *vals[1];
        } *mlist;
        struct _memi
        {
            int16_t cnt;
            int16_t vals[1];
        } *ilist;
    } b_memb;
    char b_flag;
} member_t;

struct codeFrag_t
{
    char c_0;
    char c_1;
    char c_2;
    char c_3;
    uint8_t c_4;
    uint8_t c_5;
    char *p_6;
    char *p_8;
};

/*
 * Descrições de Variáveis Globais e Arrays (extern)
 */
/* ===== Seção BSS ===== */
extern int lineno;
extern char progname[MAXNAME];
extern member_t *typeLong;
extern int array_AE13[MAXFUN];
extern member_t *typeUChar;
extern uint16_t nstdpth;
extern int array_AE57[MAXFUN];
extern int array_AE97[MAXFUN];
extern member_t *typeDouble;
extern member_t *typeChar;
extern member_t *array_AEDB[MAXFUN];
extern member_t *typeB;
extern member_t *typeX;
#define HASHTABSIZE 101
extern member_t *hashtab[HASHTABSIZE];
extern member_t *typeVar;
extern int lvlidx;
extern int word_AFF8;
extern char byte_AFFA;
extern int word_AFFB;
extern node_t *array_AFFD[0x14];
extern void *nodeFreeList;
extern bool byte_B013;
extern uint8_t byte_B014;
extern char *warningMsg;
extern int word_B017;
extern bool wflag;
extern int errcnt;
extern char *baseHeap;
extern bool rflag;

/* ===== Seção Data ===== */
extern char *otherFrag[];
extern struct codeFrag_t codeFrag[];
extern uint16_t dopetab[72];
extern char array_A94A[];
extern int array_AAE8[];
extern uint8_t array_AB24[];
extern uint8_t array_AB54[];
extern char *regNames[];

/*
 * Protótipos de Funções Específicas do CGEN
 */
#ifndef MINI
/* lex.c */
int sub_13D(int, int);
char sub_1B2(char *);
member_t **gethashptr(char *);
member_t *sub_265(char *);
char *getToken();
void leaveBlock();
member_t *sub_627(char *, uint16_t *);
void badIntCode();
void parseStmt();
void expect(char);
void parseData();
/* code.c */
int sub_808(member_t *, node_t *);
void parseInit();
void prFrameHead(int);
void prFrameTail(int, int);
void sub_BEE(int, int);
void prGlobalDef(member_t *);
void sub_C57(member_t *);
void sub_CAB(member_t *);
void prDefb0s(int);
void prPsect(int);
void sortCaseLabels(int *pCase, int *pLabel, int nCase);
void parseSwitch();
void sub_1420(int);
void prPush(uint8_t);
void prPop(uint8_t);
void prIXnPush(member_t *);
uint8_t sub_14F3(node_t *);
void sub_153A(node_t *);
void prDefb(char *, int);
void prJmpLabel(int);
void prJump(int);
void sub_15FB(member_t *, int, int);
int max(int, int);
void sub_1680();
int newLocal();
member_t *sub_1754(char *, uint8_t);
/* sym.c */
void parseVariable();
void parseMembers(int);
void parseEnum();
int sub_1C6D(int, int);
int varSize(member_t *);
int sub_1CC4(member_t *);
void sub_1CEF(member_t *);
void sub_1EDF();
int sub_1F4B(node_t *, int, int, int, int *);
int sub_283E(node_t *, int);
int sub_2B2A(node_t *);
uint8_t sub_2B79(node_t *);
/* cgen.c */
void sub_2BD0(node_t *);
long sub_2C5E(node_t *, long);
void sub_2CE0(node_t *, long);
void sub_2D09(node_t *, char *, char);
void sub_3564(node_t *);
void sub_35E6(node_t *);
void freeNode(node_t *);
node_t *allocNode(void);
bool releaseNodeFreeList(void);
node_t *sub_377A(node_t *);
void sub_37ED(node_t *);
void sub_385B(node_t *);
uint16_t sub_387A(node_t *);
bool sub_38CA(node_t *, int);
bool sub_393C(node_t *);
bool sub_3952(node_t *);
bool sub_3968(node_t *);
uint16_t nodesize(node_t *); /*sub_3993*/
node_t *sub_39CA(node_t *);
void sub_3A79(node_t *, node_t *);
void sub_3B65(unsigned long *, long, int);
void sub_3BC6(long *, long, int);
node_t *sub_3CDF(node_t *);
/* tree.c */
void sub_3DC9(node_t *);
node_t *sub_3EAA(node_t *);
node_t *sub_415E(long);
node_t *parseExpr(void);
node_t *sub_43EF(uint8_t, node_t *, node_t *);
uint8_t sub_46F7(long);
void sub_475C(node_t *);
uint8_t sub_47B2(node_t *, int);
bool sub_4B89(node_t *);
bool sub_4BE5(node_t *);
int sub_4C12(node_t *);
bool sub_4C6D(node_t *);
node_t *sub_4C8B(node_t *);
node_t *sub_4DA3(node_t *);
node_t *sub_4E8D(node_t *);
node_t *sub_4FA8(node_t *);
node_t *sub_4FCE(node_t *);
node_t *sub_508A(node_t *);
node_t *sub_53EE(node_t *);
/* local.c */
node_t *sub_54B6(node_t *);
void sub_5CF5(member_t *, int);
node_t *sub_5DF6(node_t *);
node_t *sub_5F52(node_t *);
node_t *sub_600E(node_t *);
int invertTest(int);
bool sub_60A8(node_t *, node_t *);
bool sub_61AA(member_t *, int);
bool sub_6246(node_t *, node_t *);
bool sub_628F(node_t *, node_t *);
bool sub_62BE(node_t *, node_t *);
uint8_t sub_63B8(int, int, int);
uint8_t sub_6589(int, int);
uint16_t sub_665B(uint16_t, uint8_t);
int sub_66BC(int, int, int, char *);
#endif /* MINI */

#endif /* _CGEN_H */