/*
 * =============================================================================
 * main.c -- Um Showcase Completo da Linguagem C (Padrão ANSI C)
 * =============================================================================
 * Adaptado e expandido para cobrir mais recursos do ANSI C (C89/C90).
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* Incluído para isupper() */
#include <stddef.h> /* Incluído para NULL */

/* Definições para compatibilidade e clareza */
#define BOOL int
#define TRUE 1
#define FALSE 0
#define DEBUG_MODE 1 /* Usado na seção do pré-processador */

/* Protótipos de funções */
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

/* Função auxiliar para a seção de classes de armazenamento */
void increment_static_counter(void);

/* Variável externa (definida fora de qualquer função) */
int global_variable = 100;

/*
 * =============================================================================
 * Função Principal
 * =============================================================================
 * Aceita argumentos de linha de comando (argc, argv).
 */
int main(int argc, char *argv[]) {
    int i;
    printf("====================================================\n");
    printf("== Showcase Completo da Linguagem C (ANSI C89/90) ==\n");
    printf("====================================================\n");

    printf("\nExecutando programa: %s\n", argv[0]);
    printf("Numero de argumentos da linha de comando: %d\n", argc);
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
    /* Tipos básicos */
    char      char_var     = 'C';
    short     short_var    = 20;
    int       integer_var  = 42;
    long      long_var     = 123456789L;
    unsigned  unsigned_var = 200U;
    float     float_var    = 3.14f;
    double    double_var   = 2.71828;
    long double long_double_var = 3.1415926535L;

    /* Qualificadores */
    const float PI = 3.14159f; /* 'const' previne a modificação da variável */
    volatile int sensor_reading; /* 'volatile' indica que o valor pode mudar a qualquer momento */
    sensor_reading = 10; /* Exemplo de uso */


    printf("\n--- 1. Variaveis, Tipos e Qualificadores ---\n");
    printf("char:      %c (tamanho: %lu byte)\n", char_var, (unsigned long)sizeof(char_var));
    printf("short:     %d (tamanho: %lu bytes)\n", short_var, (unsigned long)sizeof(short_var));
    printf("int:       %d (tamanho: %lu bytes)\n", integer_var, (unsigned long)sizeof(integer_var));
    printf("long:      %ld (tamanho: %lu bytes)\n", long_var, (unsigned long)sizeof(long_var));
    printf("unsigned:  %u (tamanho: %lu bytes)\n", unsigned_var, (unsigned long)sizeof(unsigned_var));
    printf("float:     %f (tamanho: %lu bytes)\n", float_var, (unsigned long)sizeof(float_var));
    printf("double:    %f (tamanho: %lu bytes)\n", double_var, (unsigned long)sizeof(double_var));
    printf("long double: %Lf (tamanho: %lu bytes)\n", long_double_var, (unsigned long)sizeof(long_double_var));
    printf("\nQualificadores:\n");
    printf("const PI: %f\n", PI);
    printf("volatile sensor: %d\n", sensor_reading);
    /* PI = 3.14; */ /* Isto causaria um erro de compilação */
}


/* 2. Classes de Armazenamento */
void demonstrate_storage_classes(void) {
    /* 'auto' é o padrão para variáveis locais, raramente é escrito */
    auto int auto_var = 1;

    /* 'register' sugere ao compilador para armazenar a variável em um registrador da CPU */
    register int i;

    /* 'extern' refere-se a uma variável global definida em outro lugar */
    extern int global_variable;

    printf("\n--- 2. Classes de Armazenamento ---\n");
    printf("Variavel 'auto': %d\n", auto_var);
    printf("Variavel 'extern' global: %d\n", global_variable);
    
    printf("Variavel 'static' (em uma funcao):\n");
    increment_static_counter(); /* chamada 1 */
    increment_static_counter(); /* chamada 2 */
    increment_static_counter(); /* chamada 3 */

    printf("Loop com variavel 'register': ");
    for (i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

/* Função com uma variável estática local */
void increment_static_counter(void) {
    /* 'static' em uma variável local mantém seu valor entre as chamadas da função */
    static int counter = 0;
    counter++;
    printf("  O contador estatico agora e: %d\n", counter);
}


/* 3. Operadores */
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
    c += 5; /* Equivalente a c = c + 5; */
    printf("Atribuicao Composta: c += 5 resulta em %d\n", c);
    
    printf("Relacionais e Logicos: (a > b) && (c != 15) -> %s\n", ((a > b) && (c != 15)) ? "TRUE" : "FALSE");
    
    printf("Bit-a-bit: a(10) & b(3) = %d (AND), a | b = %d (OR), ~b = %d (NOT), a ^ b = %d (XOR)\n", a & b, a | b, ~b, a ^ b);
    
    c = (a++, b++); /* Operador vírgula: avalia o primeiro, descarta o resultado, avalia o segundo. */
    printf("Operador Virgula: a=%d, b=%d, c=%d (c recebe o valor de b++)\n", a, b, c);
}


/* 4. Controle de Fluxo */
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
            continue; /* Pula para a próxima iteração se j for ímpar */
        }
        printf("%d ", j);
    }
    printf("\n");
    
    printf("Uso de 'goto' (usar com extrema cautela!):\n");
    i = 0;
loop_start:
    if (i < 3) {
        printf("  i = %d\n", i);
        i++;
        goto loop_start;
    }
    printf("  Fim do 'loop' com goto.\n");
}


/* 5. Funções e Ponteiros */
void add_one(int *num_ptr) { (*num_ptr)++; }

void process_data(void *data, char type) {
    printf("Ponteiro void*: ");
    if (type == 'i') {
        printf("Recebido um int com valor %d\n", *(int*)data);
    } else if (type == 'c') {
        printf("Recebido um char com valor '%c'\n", *(char*)data);
    }
}

void demonstrate_functions_and_pointers(void) {
    int my_number = 10;
    int *num_ptr = &my_number;
    int *null_ptr = NULL; /* Ponteiro nulo */
    int some_int = 42;
    char some_char = 'Z';

    printf("\n--- 5. Funcoes e Ponteiros ---\n");
    printf("Numero original: %d\n", my_number);
    add_one(num_ptr);
    printf("Numero apos chamada por referencia: %d\n", my_number);
    
    printf("Aritmetica de ponteiros: num_ptr aponta para %p. num_ptr+1 apontaria para %p\n", (void*)num_ptr, (void*)(num_ptr + 1));
    
    if (null_ptr == NULL) {
        printf("O ponteiro 'null_ptr' e NULO (NULL).\n");
    }

    process_data(&some_int, 'i');
    process_data(&some_char, 'c');
}


/* 6. Arrays e Strings */
void demonstrate_arrays_and_strings(void) {
    int simple_array[] = {10, 20, 30, 40, 50}; /* Inicialização na declaração */
    int matrix[2][3] = { {1, 2, 3}, {4, 5, 6} }; /* Array multidimensional */
    char str1[] = "Primeira string"; /* String literal (imutável em algumas arquiteturas) */
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


/* 7. Structs, Unions e Enums */
/* Struct com campo de bit (bit-field) */
typedef struct {
    unsigned int active : 1; /* usa apenas 1 bit */
    unsigned int mode   : 2; /* usa 2 bits */
    unsigned int        : 5; /* preenchimento para completar o byte (opcional) */
} StatusFlags;

/* Union: armazena um valor de cada vez, mas pode ser um de vários tipos */
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
    printf("Struct com Bit-Fields: Ativo=%u, Modo=%u (Tamanho da struct: %lu bytes)\n", 
           status.active, status.mode, (unsigned long)sizeof(StatusFlags));

    data.f = 3.14f;
    printf("Union: data.f = %f\n", data.f);
    data.i = 1094795585; /* Este int tem a mesma representação em bits que 3.14f */
    printf("Union: data.i = %d (mesmo local de memoria que o float)\n", data.i);
    strcpy(data.s, "Hi!");
    printf("Union: data.s = \"%s\"\n", data.s);

    printf("Enum: A cor selecionada e %d (GREEN).\n", my_color);
}


/* 8. Alocação Dinâmica de Memória */
void demonstrate_dynamic_memory(void) {
    int *dynamic_array;
    int n = 5;

    printf("\n--- 8. Alocacao Dinamica de Memoria ---\n");

    /* Alocando memória para 5 inteiros com malloc */
    dynamic_array = (int*)malloc(n * sizeof(int));
    if (dynamic_array == NULL) {
        printf("Falha na alocacao de memoria com malloc!\n");
        return; /* Em um programa real, tratar o erro mais robustamente */
    }
    printf("Memoria para 5 inteiros alocada com malloc.\n");
    free(dynamic_array); /* Liberando a memória */
    printf("Memoria liberada com free.\n");

    /* Alocando e inicializando com calloc */
    dynamic_array = (int*)calloc(n, sizeof(int));
    if (dynamic_array == NULL) {
        printf("Falha na alocacao de memoria com calloc!\n");
        return;
    }
    printf("Memoria para 5 inteiros alocada com calloc (inicializada com 0): Primeiro elemento = %d\n", dynamic_array[0]);

    /* Realocando para 10 inteiros com realloc */
    dynamic_array = (int*)realloc(dynamic_array, (n * 2) * sizeof(int));
    if (dynamic_array == NULL) {
        printf("Falha na realocacao de memoria com realloc!\n");
        free(dynamic_array); /* libera o ponteiro original se realloc falhar */
        return;
    }
    printf("Memoria realocada para 10 inteiros com realloc.\n");
    free(dynamic_array);
    printf("Memoria final liberada.\n");
}


/* 9. Diretivas do Pré-processador */
void demonstrate_preprocessor(void) {
    printf("\n--- 9. Diretivas do Pre-processador ---\n");

#if DEBUG_MODE == 1
    printf("Modo DEBUG esta ATIVADO.\n");
#elif DEBUG_MODE == 2
    printf("Modo DEBUG esta no nivel 2.\n");
#else
    printf("Modo DEBUG esta DESATIVADO.\n");
#endif

#ifdef __STDC__
    printf("O compilador se identifica como compativel com o padrao C (ANSI C).\n");
#else
    printf("O compilador NAO se identifica como compativel com o padrao C.\n");
#endif

    printf("Este codigo foi compilado em: %s as %s\n", __DATE__, __TIME__);
    printf("Nome do arquivo: %s, Linha atual: %d\n", __FILE__, __LINE__);
}


/* 10. Entrada e Saída de Arquivos (File I/O) */
void demonstrate_file_io(void) {
    FILE *file_ptr;
    char buffer[100];
    int numbers[] = {1, 2, 3, 4, 5};
    int read_numbers[5];

    printf("\n--- 10. Entrada e Saida de Arquivos (File I/O) ---\n");

    /* Escrita em modo texto */
    file_ptr = fopen("texto.txt", "w");
    if (file_ptr == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo texto.txt!\n");
        return;
    }
    fprintf(file_ptr, "Ola do C!\nLinha 2.\n");
    fclose(file_ptr);
    printf("Arquivo 'texto.txt' escrito com sucesso.\n");

    /* Leitura em modo texto */
    file_ptr = fopen("texto.txt", "r");
    if (file_ptr == NULL) {
        fprintf(stderr, "Erro ao ler o arquivo texto.txt!\n");
        return;
    }
    printf("Lendo de 'texto.txt':\n");
    while (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
        printf("  > %s", buffer);
    }
    fclose(file_ptr);

    /* Escrita em modo binário */
    file_ptr = fopen("dados.bin", "wb");
    if (file_ptr == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo dados.bin!\n");
        return;
    }
    fwrite(numbers, sizeof(int), 5, file_ptr);
    fclose(file_ptr);
    printf("\nArquivo 'dados.bin' escrito com sucesso.\n");

    /* Leitura em modo binário */
    file_ptr = fopen("dados.bin", "rb");
    if (file_ptr == NULL) {
        fprintf(stderr, "Erro ao ler o arquivo dados.bin!\n");
        return;
    }
    fread(read_numbers, sizeof(int), 5, file_ptr);
    printf("Lendo de 'dados.bin': %d, %d, %d, %d, %d\n", 
           read_numbers[0], read_numbers[1], read_numbers[2], read_numbers[3], read_numbers[4]);
    fclose(file_ptr);
}