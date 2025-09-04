#ifndef _CPP_H
#define _CPP_H
/*
 * =============================================================================
 * cpp.h -- Cabeçalho Principal do Pré-processador Hi-Tech C
 * =============================================================================
 * Este arquivo serve como o "coração" do projeto, definindo a interface
 * interna do pré-processador. Ele centraliza as estruturas de dados,
 * os protótipos de funções globais e as variáveis compartilhadas entre os
 * diferentes módulos (.c) do programa.
 * =============================================================================
 */

/* --- Inclusões de Cabeçalhos --- */
/* Bibliotecas Padrão C */
#include <stdio.h>
#define bool int
#define true 1
#define false 0

/* Cabeçalho de Portabilidade do Projeto (deve vir primeiro) */
#include <portab.h>

/* --- Macros de Configuração e Definições --- */
/* Desabilita avisos de segurança do CRT da Microsoft ao compilar com MSVC */
#define _CRT_SECURE_NO_WARNINGS 1

/* 'LOCAL' e 'EXPORT' são macros de conveniência para melhorar a legibilidade */
#define LOCAL static
#define EXPORT

/* Usado para exibir na mensagem da flag --version */
#define HOST_CPU    "Z80"
#define HOST_VENDOR "Hi-Tech"

/* Macro para portabilidade de arquitetura (manuseio de 'char' como índice) */
#if defined(pdp11) || defined(vax) || ('\377' < 0)
#define COFF 128
#else
#define COFF 0
#endif

/* Constante para a tabela de classificação de caracteres 'fastab' */
#define IB 1

/* --- Definições de Tipos (Estruturas) --- */
/* Define a estrutura de um nó na tabela de símbolos (Symbol Table).
 * Usada para armazenar as macros definidas com '#define'. */
struct symtab {
    char *name;         /* Nome da macro (ex: "MINHA_MACRO") */
    char *value;        /* Corpo da macro a ser substituído (ex: "123") */
    struct symtab *next;/* Ponteiro para o próximo símbolo em caso de colisão de hash. */
};

/* --- Variáveis Globais Externas --- */
/* Definidas em um .c (geralmente main.c) e declaradas aqui com 'extern'
 * para serem acessíveis por todos os módulos do projeto. */

extern char *outptr, *inptr; /* Ponteiros para o buffer principal de processamento. */
extern int flslvl;           /* Nível de aninhamento de condicionais falsas (#if 0). */
extern char *newp;           /* Ponteiro de lookahead, usado pelo lexer/parser. */
extern int yylval;           /* Valor associado ao token retornado por yylex(). */
extern char fastab[];        /* Tabela de lookup rápido para classificação de caracteres. */
#ifdef USE_GETARGS
    extern int _argc_;       /* Contador de argumentos após a expansão de curingas. */
#endif


/* --- Protótipos de Funções (API Interna do Projeto) --- */
/* Agrupados pelo arquivo fonte onde são definidos. */

/* Funções de 'main.c' */
void pperror(char *fmt, ...);
struct symtab *lookup(char *namep, int enterf);
int  yywrap(void);
char *skipbl(char *p);

/* Funções de 'expr_parser.c' (Analisador Sintático) */
int  yyparse(void);
void yyerror(char *fmt, ...);

/* Funções de 'expr_lexer.c' (Analisador Léxico) */
int yylex(void);

/* Funções de 'cmdline.c' (Processamento da Linha de Comando) */
#ifdef USE_GETARGS
    char **_getargs(char *_str, char *_name);
#endif

/* Funções de 'path_utils.c' (ou similar) */
char *fname(char *name);


/* --- Macros de Funções --- */
/* Macro de alta performance para verificar se um caractere é parte de um identificador. */
#define isid(a) ((fastab + COFF)[(int)a] & IB)


#endif /* _CPP_H */