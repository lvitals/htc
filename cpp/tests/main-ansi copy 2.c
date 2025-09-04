/*
 * =============================================================================
 * main.c -- Um Showcase da Linguagem C (Padrão ANSI C)
 * =============================================================================
 * Corrigido para ser compatível com as limitações do compilador Hi-Tech C
 * que possui suporte parcial ao padrão ANSI C89/C90.
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

/* Definições para clareza */
#define BOOL int
#define TRUE 1
#define FALSE 0
#define DEBUG_MODE 1

/*
 * CORREÇÃO: O qualificador 'const' não é suportado.
 * A forma correta de criar uma constante é usando #define.
 */
#define PI 3.14159f

/* Protótipos de funções no estilo ANSI C (suportado) */
void demonstrate_variables_and_types(void);
void demonstrate_storage_classes(void);
void demonstrate_operators(void);
void demonstrate_control_flow(void);
void demonstrate_functions_and_pointers(void);
void demonstrate_arrays_and_strings(void);
void demonstrate_structs_unions_enums(void);
void demonstrate_dynamic_memory(void);
void demonstrate_preprocessor(void);
void demonstrate_file_io(void);

void increment_static_counter(void);

int global_variable = 100;

/*
 * =============================================================================
 * Função Principal
 * =============================================================================
 */
int main(int argc, char *argv[]) {
    int i;
    printf("====================================================\n");
    printf("== Showcase da Linguagem C (para Hi-Tech C) ==\n");
    printf("====================================================\n");

    printf("\nExecutando programa: %s\n", argv[0]);
    printf("Numero de argumentos: %d\n", argc);
    for (i = 1; i < argc; i++) {
        printf("  Argumento %d: %s\n", i, argv[i]);
    }

    demonstrate_variables_and_types();
    demonstrate_storage_classes();
    demonstrate_operators();
    demonstrate_control_flow();
    demonstrate_functions_and_pointers();
    demonstrate_arrays_and_strings();
    demonstrate_structs_unions_enums();
    demonstrate_dynamic_memory();
    demonstrate_preprocessor();
    demonstrate_file_io();

    printf("\n\nDemonstracao concluida com sucesso.\n");
    return 0;
}

/* 1. Variáveis, Tipos e Qualificadores */
void demonstrate_variables_and_types(void) {
    char      char_var     = 'C';
    short     short_var    = 20;
    int       integer_var  = 42;
    long      long_var     = 123456789L;
    unsigned  unsigned_var = 200; /* CORREÇÃO: Removido o sufixo 'U' */
    float     float_var    = 3.14f;
    double    double_var   = 2.71828;
    /* REMOVIDO: O tipo 'long double' e o sufixo 'L' para float/double não são suportados. */

    /* CORREÇÃO: O qualificador 'volatile' não é suportado. */
    /* A variável é declarada como um int normal. Para acesso a hardware, */
    /* seriam necessárias técnicas específicas do compilador. */
    int sensor_reading;
    sensor_reading = 10;

    printf("\n--- 1. Variaveis, Tipos e Qualificadores ---\n");
    printf("char:      %c (tamanho: %lu byte)\n", char_var, (unsigned long)sizeof(char_var));
    printf("short:     %d (tamanho: %lu bytes)\n", short_var, (unsigned long)sizeof(short_var));
    printf("int:       %d (tamanho: %lu bytes)\n", integer_var, (unsigned long)sizeof(integer_var));
    printf("long:      %ld (tamanho: %lu bytes)\n", long_var, (unsigned long)sizeof(long_var));
    printf("unsigned:  %u (tamanho: %lu bytes)\n", unsigned_var, (unsigned long)sizeof(unsigned_var));
    printf("float:     %f (tamanho: %lu bytes)\n", float_var, (unsigned long)sizeof(float_var));
    printf("double:    %f (tamanho: %lu bytes)\n", double_var, (unsigned long)sizeof(double_var));
    printf("\nQualificadores (simulados):\n");
    printf("const PI (via #define): %f\n", PI);
    printf("volatile sensor (como int): %d\n", sensor_reading);
}


/* 2. Classes de Armazenamento */
void demonstrate_storage_classes(void) {
    auto int auto_var = 1;
    register int i;
    extern int global_variable;

    printf("\n--- 2. Classes de Armazenamento ---\n");
    printf("Variavel 'auto': %d\n", auto_var);
    printf("Variavel 'extern' global: %d\n", global_variable);
    
    printf("Variavel 'static' (em uma funcao):\n");
    increment_static_counter();
    increment_static_counter();
    increment_static_counter();

    printf("Loop com variavel 'register': ");
    for (i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

void increment_static_counter(void) {
    static int counter = 0;
    counter++;
    printf("  O contador estatico agora e: %d\n", counter);
}


/* 3. Operadores - Sem alterações necessárias */
void demonstrate_operators(void) {
    int a = 10, b = 3;
    int c = 5;
    
    printf("\n--- 3. Operadores ---\n");
    printf("Valores iniciais: a=10, b=3, c=5\n");
    printf("Aritmeticos: a + b = %d, a * b = %d, a / b = %d (divisao inteira), a %% b = %d\n", a + b, a * b, a / b, a % b);
    printf("Unarios: c++ = %d (pos-incremento), ", c++);
    printf("c atual = %d\n", c);
    c = 5; /* reset */
    printf("         ++c = %d (pre-incremento), ", ++c);
    printf("c atual = %d\n", c);
    c = 10;
    c += 5;
    printf("Atribuicao Composta: c += 5 resulta em %d\n", c);
    printf("Relacionais e Logicos: (a > b) && (c != 15) -> %s\n", ((a > b) && (c != 15)) ? "TRUE" : "FALSE");
    printf("Bit-a-bit: a(10) & b(3) = %d\n", a & b);
}


/* 4. Controle de Fluxo - Sem alterações necessárias */
void demonstrate_control_flow(void) {
    int i = 0;
    int j;

    printf("\n--- 4. Controle de Fluxo ---\n");
    printf("Laco do-while: ");
    do {
        printf("%d ", i);
        i++;
    } while (i < 5);
    printf("\n");

    printf("Laco for com 'continue': ");
    for (j = 0; j < 10; j++) {
        if (j % 2 != 0) {
            continue;
        }
        printf("%d ", j);
    }
    printf("\n");
}


/* 5. Funções e Ponteiros - Sem alterações necessárias */
void add_one(int *num_ptr) { (*num_ptr)++; }

void demonstrate_functions_and_pointers(void) {
    int my_number = 10;
    int *num_ptr = &my_number;
    int *null_ptr = NULL;

    printf("\n--- 5. Funcoes e Ponteiros ---\n");
    printf("Numero original: %d\n", my_number);
    add_one(num_ptr);
    printf("Numero apos chamada por referencia: %d\n", my_number);
    
    if (null_ptr == NULL) {
        printf("O ponteiro 'null_ptr' e NULO (NULL).\n");
    }
}


/* 6. Arrays e Strings */
void demonstrate_arrays_and_strings(void) {
    /*
     * CORREÇÃO: Não é possível inicializar arrays locais (auto aggregates).
     * A solução é declará-los como 'static'.
     */
    static int simple_array[] = {10, 20, 30, 40, 50};
    static int matrix[2][3] = { {1, 2, 3}, {4, 5, 6} };
    static char str1[] = "Primeira string"; /* 'str1' é usado implicitamente, o warning pode ser ignorado */
    char str2[20];
    int i, j;

    printf("\n--- 6. Arrays e Strings ---\n");
    printf("Terceiro elemento do array simples: %d\n", simple_array[2]);

    strcpy(str2, "Copia");
    printf("String copiada (strcpy): %s\n", str2);
    if (isupper(str2[0])) {
        printf("O primeiro caractere de '%s' e maiusculo (verificado com isupper).\n", str2);
    }

    printf("Array multidimensional (matriz):\n");
    for (i = 0; i < 2; i++) {
        printf("  ");
        for (j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


/* 7. Structs, Unions e Enums - Sem alterações necessárias */
typedef struct {
    unsigned int active : 1;
    unsigned int mode   : 2;
    unsigned int        : 5;
} StatusFlags;

typedef union {
    int   i;
    float f;
    char  s[4];
} Data;

typedef enum { RED, GREEN, BLUE } Color;

void demonstrate_structs_unions_enums(void) {
    StatusFlags status;
    Data data;
    Color my_color = GREEN;

    printf("\n--- 7. Structs, Unions e Enums ---\n");
    status.active = 1;
    status.mode = 2;
    printf("Struct com Bit-Fields: Ativo=%u, Modo=%u (Tamanho: %lu bytes)\n", 
           status.active, status.mode, (unsigned long)sizeof(StatusFlags));

    data.f = 3.14f;
    printf("Union: data.f = %f\n", data.f);
    strcpy(data.s, "Hi!");
    printf("Union: data.s = \"%s\"\n", data.s);
    printf("Enum: A cor selecionada e %d (GREEN).\n", my_color);
}


/* 8. Alocação Dinâmica de Memória - Sem alterações necessárias */
void demonstrate_dynamic_memory(void) {
    int *dynamic_array;
    int n = 5;

    printf("\n--- 8. Alocacao Dinamica de Memoria ---\n");
    dynamic_array = (int*)malloc(n * sizeof(int));
    if (dynamic_array == NULL) {
        printf("Falha na alocacao de memoria com malloc!\n");
        return;
    }
    printf("Memoria para 5 inteiros alocada com malloc.\n");
    free(dynamic_array);
    printf("Memoria liberada com free.\n");
}


/* 9. Diretivas do Pré-processador */
void demonstrate_preprocessor(void) {
    printf("\n--- 9. Diretivas do Pre-processador ---\n");

#if DEBUG_MODE == 1
    printf("Modo DEBUG esta ATIVADO.\n");
#else
    printf("Modo DEBUG esta DESATIVADO.\n");
#endif

#ifdef __STDC__
    printf("O compilador se identifica como compativel com o padrao C (ANSI C).\n");
#endif

    /* REMOVIDO: As macros predefinidas __DATE__ e __TIME__ não são suportadas. */
    printf("Nome do arquivo: %s, Linha atual: %d\n", __FILE__, __LINE__);
}


/* 10. Entrada e Saída de Arquivos (File I/O) */
void demonstrate_file_io(void) {
    FILE *file_ptr;
    char buffer[100];
    /* CORREÇÃO: 'auto aggregate' - o array deve ser 'static' para ser inicializado. */
    static int numbers[] = {1, 2, 3, 4, 5};
    int read_numbers[5];

    printf("\n--- 10. Entrada e Saida de Arquivos (File I/O) ---\n");
    file_ptr = fopen("texto.txt", "w");
    if (file_ptr == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo texto.txt!\n");
        return;
    }
    fprintf(file_ptr, "Ola do C!\nLinha 2.\n");
    fclose(file_ptr);
    printf("Arquivo 'texto.txt' escrito com sucesso.\n");

    /* Leitura em modo binário */
    file_ptr = fopen("dados.bin", "wb");
    if (file_ptr == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo dados.bin!\n");
        return;
    }
    fwrite(numbers, sizeof(int), 5, file_ptr);
    fclose(file_ptr);
    printf("\nArquivo 'dados.bin' escrito com sucesso.\n");
}