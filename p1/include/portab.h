#ifndef _PORTAB_H
#define _PORTAB_H

/*
 * =============================================================================
 * portab.h -- Header for Portability
 * =============================================================================
 * This header uses standard predefined macros to detect the target operating
 * system during compilation. The if/elif/else structure ensures that only
 * one set of definitions is active.
 *
 * This specific portab.h is tailored for the p1.h component of the
 * Hi-Tech CP/M Z80 C v3.09 restored compiler, while also aiming for
 * better compatibility with modern GCC in C89 mode.
 * =============================================================================
 */

/* --- Standard C Includes --- */
/* <stdbool.h> for 'bool' type (C99+). */
/* <stdint.h> for fixed-width integer types (C99+). */
/* We will include these conditionally, only for non-CP/M systems,
 * to avoid redefinition errors on modern compilers.
 * For CP/M, fixed-width types and bool may need to be defined elsewhere
 * (e.g., directly in p1.h or a CP/M-specific header). */

/* --- System-Specific Includes & Definitions for p1.h --- */

/* --- Detection for Unix-like Systems (Linux, macOS, FreeBSD, etc.) --- */
#if defined(__unix__) || defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#include <unistd.h>
#include <limits.h> /* For PATH_MAX */
#include <stdbool.h> /* Include stdbool for bool, true, false */
#include <stdint.h>  /* Include stdint for fixed-width types */

#define _MAX_PATH PATH_MAX /* Map for compatibility with Windows paths */
#define initMemAddr()      /* Not needed on these systems for data segment checks */
#ifdef __APPLE__
#include <malloc/malloc.h>
#define inData(p) (!malloc_zone_from_ptr(p)) /* Check if pointer is NOT from malloc */
#else
/* For other Unix-like, assume data/bss segments are contiguous and within specific bounds */
extern const char *_Ldata; /* Start of data segment */
extern const char *_Hbss;  /* End of BSS segment */
#define inData(p) (_Ldata <= ((const char *)p) && ((const char *)p) < _Hbss)
#endif
#define HOST_OS "Unix"

/* --- Detection for Windows Systems --- */
#elif defined(_WIN32)
#include <stdbool.h> /* Include stdbool for bool, true, false */
#include <stdint.h>  /* Include stdint for fixed-width types */
/* On Windows, the initMemAddr function is specifically needed for data segment range detection. */
void initMemAddr(void);
/* inData is omitted here as per original p1.h behavior for WIN32. */
#define HOST_OS "Windows"

/* --- Detection for CP/M (requires manual flag -DCPM) --- */
#elif defined(CPM)
/* For CP/M, stdbool.h and stdint.h are typically NOT available. */
/* Fixed-width types (int8_t, uint32_t etc.) and 'bool' */
/* MUST be defined elsewhere, e.g., directly in p1.h or a dedicated */
/* CP/M-specific header if they are truly needed. */
/* Assuming they will be defined by the Hi-Tech C headers or compiler-specific pragmas. */

#undef initMemAddr    /* Ensure it's not defined */
#define initMemAddr() /* Define as empty for CP/M */

/* For CP/M, the data segment check uses a single `_Hbss` marker. */
extern char _Hbss; /* End of BSS segment */
#define inData(p) (((char *)p) < &_Hbss)
#define HOST_OS "CP/M"

/* --- Default Case: Unknown Platform --- */
/* If none of the above systems are detected, compilation will fail with a clear */
/* message, which is safer than using incorrect definitions. */
#else
#error "Unsupported or undetected compilation platform for p1.h. Please edit include/portab.h"
#endif

/* --- Common Definitions (apply to all platforms unless specifically overridden) --- */

/* Define _Noreturn if not available (from stdnoreturn.h, C11). */
/* For C89/older compilers, use attributes if supported, otherwise empty. */
#ifndef _Noreturn
#if defined(__GNUC__) && __GNUC__ >= 2
#define _Noreturn __attribute__((__noreturn__))
#else
#define _Noreturn /* empty */
#endif
#endif

/* --- `register` keyword handling for C17+ --- */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201710L)
#define register /* 'register' keyword is deprecated in C17, remove it */
#endif

/* --- Common Hi-Tech Function Mappings (from original p1.h) --- */
#ifndef CPM /* These mappings are only for non-CP/M systems */
#define rindex strrchr
#define blkclr(p, s) memset(p, 0, s)
#endif

/* --- FORCEINIT Macro (from original p1.h) --- */
#ifdef CPM
#define FORCEINIT /* For CP/M, it's typically an empty macro */
/* The original p1.h also undefines putchar and redeclares it for CPM. */
/* This could be placed here if putchar behavior varies, but leaving it */
/* in p1.h for now as it seems specific to its internal compilation. */
/* undef putchar is likely for linking to a custom putchar in the CPM runtime. */
#else
#define FORCEINIT = 0 /* For other systems, initialize to 0 */
#endif

#endif /* _PORTAB_H */