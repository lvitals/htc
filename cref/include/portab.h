/* ============================================================================
 *
 * Arquivo: portab.h
 *
 * Cabeçalho de Portabilidade para o utilitário CREF do HI-TECH C
 *
 * ============================================================================
 * Este header centraliza todas as diretivas de pré-processador e definições
 * para garantir que o código compile em diversas plataformas, como
 * CP/M, Windows, Linux, macOS, etc.
 * ============================================================================
 */

#ifndef _PORTAB_H
#define _PORTAB_H

/*===========================================================================
 * SEÇÃO DE CABEÇALHOS PADRÃO
 *===========================================================================*/
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclui headers de tipos de dados de C99 se disponíveis */
#if defined(__STDC__) && __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#include <stdint.h>
#endif

/*===========================================================================
 * SEÇÃO DE DETECÇÃO DE PLATAFORMA E COMPILADOR
 *===========================================================================*/

/* Detecta Windows (32 ou 64 bits) */
#if defined(_WIN32) || defined(__WIN32__)
#define PLATFORM_WINDOWS 1
#endif

/* Detecta sistemas Unix-like (Linux, macOS, etc.) */
#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#define PLATFORM_UNIX 1
#endif

/*===========================================================================
 * SEÇÃO DE COMPATIBILIDADE DE TIPOS E PALAVRAS-CHAVE
 *===========================================================================*/

/* Fallback para 'bool' se <stdbool.h> não estiver disponível (pré-C99) */
#if !defined(__STDC__) || __STDC_VERSION__ < 199901L
#ifndef bool
#define bool unsigned char
#define true 1
#define false 0
#endif
#endif

/* Fallback para `_Noreturn` se não for C11 ou superior */
#if !defined(__STDC__) || __STDC_VERSION__ < 201112L
#define _Noreturn
#endif

/* Fallback para `const` em compiladores muito antigos pré-C89 */
#if !defined(__STDC__) && !defined(__STDC_VERSION__)
#define const
#endif

/* Fallback para tipos de inteiros de tamanho fixo se <stdint.h> não foi incluído */
#if !defined(UINT8_MAX)
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
#endif

/*===========================================================================
 * SEÇÃO DE FUNCIONALIDADES ESPECÍFICAS DE PLATAFORMA
 *===========================================================================*/

/*
 * CP/M tem uma linha de comando limitada. A função _getargs do HI-TECH C
 * contorna isso permitindo entrada de múltiplas linhas.
 */
#ifdef CPM
#define USE_GETARGS 1
#endif

/* Em alguns compiladores antigos como o HI-TECH C, vfprintf era _doprnt */
#ifdef HI_TECH_C
#define vfprintf _doprnt
#endif

/* Protótipo para a função de argumentos, se utilizada */
#ifdef USE_GETARGS
extern int _argc_;
char **_getargs(char *_str, const char *_name);
#endif

/*
 * Abstração para normalizar quebras de linha.
 * Em Unix, \r\n de arquivos DOS/Windows pode ser um problema. Esta macro
 * remove o \r antes do \n. 's' é o início do buffer, 't' é o ponteiro para o \0.
 */
#if defined(PLATFORM_UNIX)
#define NORMALIZE_LINE_ENDING(s, t) \
    if ((s) != (t) && *--(t) == '\r') *t = '\0'
#else
/* Em outras plataformas como Windows e CP/M, não faz nada. */
#define NORMALIZE_LINE_ENDING(s, t)
#endif

#endif /* _PORTAB_H */