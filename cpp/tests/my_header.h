// my_header.h - Um cabeçalho de exemplo para o teste.

#define FRAMEWORK_VERSION "1.2.3-beta"

// Declaração de uma função hipotética
void initialize_system(void);

// --- Bloco de Compatibilidade Booleana ---
// Se não estivermos compilando para CP/M (ou seja, um host moderno),
// usamos o cabeçalho padrão C99 para o tipo bool.
#ifndef CPM
    #include <stdbool.h>
#else
    // Se estivermos compilando para CP/M (que é C89 e não tem stdbool.h),
    // definimos 'bool', 'true' e 'false' manualmente. Esta é uma prática
    // padrão para escrever código C retrocompatível.
    // Usamos 'char' para eficiência em sistemas de 8-bits.
    typedef char bool;
    #define true  1
    #define false 0
#endif