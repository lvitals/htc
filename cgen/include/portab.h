/*
 * =============================================================================
 * portab.h -- Header para Portabilidade
 * =============================================================================
 * Este header utiliza macros pré-definidas padrão para detectar o sistema
 * operacional e o compilador de destino durante a compilação. Ele centraliza
 * todas as definições de tipos, macros e protótipos necessários para
 * abstrair as diferenças de plataforma.
 * =============================================================================
 */

#ifndef _PORTAB_H
#define _PORTAB_H 1

/*===========================================================================*/
/*=                                                                         =*/
/*=                    SEÇÃO DE CABEÇALHOS PADRÃO                           =*/
/*=                                                                         =*/
/*===========================================================================*/

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*===========================================================================*/
/*=                                                                         =*/
/*=         SEÇÃO DE COMPATIBILIDADE DE TIPOS E PADRÕES C                     =*/
/*=                                                                         =*/
/*===========================================================================*/

/* Detecta o padrão C para incluir headers e definir funcionalidades como
 * _Noreturn e a palavra-chave 'register'. */
#if defined(__STDC__) && __STDC_VERSION__ >= 199901L /* C99 ou posterior */
#include <stdint.h>
#if __STDC_VERSION__ < 201112L
#define _Noreturn
#endif
#if __STDC_VERSION__ >= 201710L
#define register /* 'register' é obsoleto a partir do C17 */
#endif
#else
/* Fallback para compiladores antigos ou não conformes (C89) */
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;
/* Os tipos de 32 bits (uint32_t, int32_t) foram removidos daqui
   porque compiladores modernos os fornecem através dos headers
   padrão, mesmo em modo C89, o que causava um erro de redefinição. */

/* Definição manual de booleano se <stdbool.h> não estiver disponível */
#ifndef bool
#define bool char
#define true 1
#define false 0
#endif
#define _Noreturn
#endif

/* Macro para forçar a inicialização de variáveis, evitando warnings de
 * "uso de variável não inicializada" em compiladores modernos. */
#if defined(__STDC__) || defined(__STDC_VERSION__)
#define FORCEINIT = 0
#else
#define FORCEINIT
#endif

/*===========================================================================*/
/*=                                                                         =*/
/*=                  SEÇÃO DE CONSTANTES DE PORTABILIDADE                   =*/
/*=                                                                         =*/
/*===========================================================================*/

#define MININT -32768 /* Valor mínimo para um 'int' de 16 bits */
#define MAXINT 32767  /* Valor máximo para um 'int' de 16 bits */

/*===========================================================================*/
/*=                                                                         =*/
/*=            SEÇÃO DE MACROS DE MEMÓRIA, STRING E I/O                     =*/
/*=                                                                         =*/
/*===========================================================================*/

#ifdef CPM
/* Funções e macros para o ambiente CP/M */
long atol(char *str);
void blkclr(char *, uint16_t size);
void *sbrk(int);
#define vfprintf _doprnt /* vfprintf era implementado como _doprnt no HI-TECH C */

#else
/* Funções e macros para sistemas modernos (Unix-like, Windows) */
#define bmove(src, dst, cnt) memcpy(dst, src, (size_t)(cnt))
#define blkclr(buf, len) memset(buf, 0, (size_t)(len))
#endif

#if defined(_WIN32)
/* Para Windows, mapeia diretamente para as funções padrão de I/O */
#define FGETCHAR_PORTABLE getchar
#define FPUTC_PORTABLE putchar
#else
/* Para outros sistemas (POSIX, CP/M), assume implementações customizadas */
int fgetchar(void);
int fputchar(int);
#define FGETCHAR_PORTABLE fgetchar
#define FPUTC_PORTABLE fputchar
#endif

/*===========================================================================*/
/*=                                                                         =*/
/*=              SEÇÃO DE PROTÓTIPOS DE FUNÇÕES UTILITÁRIAS                 =*/
/*=                                                                         =*/
/*===========================================================================*/

/* Funções de manipulação de memória e mensagens de erro */
void *allocMem(size_t);
_Noreturn void fatalErr(char *fmt, ...);
void prWarning(char *fmt, ...);
void prError(char *fmt, ...);
void prMsg(char *fmt, va_list args);

#endif /* _PORTAB_H */