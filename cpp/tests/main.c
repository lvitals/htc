/*
 * =============================================================================
 * main.c -- Um Showcase da Linguagem C
 * =============================================================================
 * Este arquivo demonstra uma ampla variedade de funcionalidades padrão da
 * linguagem C (com foco em C99/C11). Ele serve como um bom exemplo
 * de referência e um teste robusto para uma toolchain de compilação.
 *
 * Última Revisão: 12 de Junho de 2025, 11:22, Jundiaí/SP
 * =============================================================================
 */

// --- 1. Inclusão de Cabeçalhos ---
// Inclui as bibliotecas padrão necessárias para as funcionalidades demonstradas.
#include <stdio.h>    // Para entrada e saída (printf, fopen, etc.)
#include <stdlib.h>   // Para alocação de memória (malloc, free) e conversões.
#include <string.h>   // Para manipulação de strings (strcpy, strlen, etc.).
#include <limits.h>   // Para constantes como INT_MAX.
// #include <stdbool.h>  // Para usar o tipo 'bool' e os valores 'true'/'false'.

#include "my_header.h" 

// --- 2. Protótipos de Funções ---
// Declarar as funções antes de usá-las é uma boa prática em C.
void demonstrate_variables_and_types();
void demonstrate_operators();
void demonstrate_control_flow();
void demonstrate_functions_and_pointers();
void demonstrate_arrays_and_strings();
void demonstrate_structs_unions_enums();
void demonstrate_file_io();

// --- 3. Função Principal (Ponto de Entrada) ---
int main(int argc, char *argv[]) {
    printf("=================================================\n");
    printf("== Showcase Completo da Linguagem C\n");
    printf("=================================================\n");
    printf("Programa executado com %d argumento(s).\n\n", argc);

    // Chama cada função de demonstração em sequência.
    demonstrate_variables_and_types();
    demonstrate_operators();
    demonstrate_control_flow();
    demonstrate_functions_and_pointers();
    demonstrate_arrays_and_strings();
    demonstrate_structs_unions_enums();
    demonstrate_file_io();

    printf("\n Demonstração concluída com sucesso.\n");
    return 0; // Retorna 0 para indicar sucesso ao sistema operacional.
}

// --- 4. Demonstrações Detalhadas ---

/**
 * Mostra a declaração e uso de variáveis com tipos de dados fundamentais.
 */
void demonstrate_variables_and_types() {
    printf("\n--- 1. Variáveis e Tipos de Dados ---\n");
    int integer_var = 42;
    float float_var = 3.14f;
    double double_var = 2.71828;
    char char_var = 'C';
    bool bool_var = true;
    const float PI = 3.14159f; // Variável constante

    printf("Integer: %d (tamanho: %zu bytes)\n", integer_var, sizeof(integer_var));
    printf("Float:   %f (tamanho: %zu bytes)\n", float_var, sizeof(float_var));
    printf("Double:  %lf (tamanho: %zu bytes)\n", double_var, sizeof(double_var));
    printf("Char:    %c (tamanho: %zu byte)\n", char_var, sizeof(char_var));
    printf("Bool:    %d (tamanho: %zu byte)\n", bool_var, sizeof(bool_var));
    printf("Constante PI: %f\n", PI);
}

/**
 * Demonstra os operadores aritméticos, lógicos e bit-a-bit.
 */
void demonstrate_operators() {
    printf("\n--- 2. Operadores ---\n");
    int a = 10, b = 3;
    printf("Aritméticos: a=%d, b=%d\n", a, b);
    printf("  Soma (a + b)      = %d\n", a + b);
    printf("  Resto (a %% b)      = %d\n", a % b);

    int x = 0b1010; // 10 em binário
    int y = 0b1100; // 12 em binário
    printf("\nBit-a-bit: x=10 (1010), y=12 (1100)\n");
    printf("  AND (x & y)       = %d (bin: %s)\n", x & y, "1000"); // 8
    printf("  OR  (x | y)       = %d (bin: %s)\n", x | y, "1110"); // 14
    printf("  Shift Esq (x << 1)= %d (bin: %s)\n", x << 1, "10100"); // 20

    printf("\nLógicos e Ternário:\n");
    bool cond = (a > b) && (x != 0);
    printf("  (a > b) && (x != 0) é %s\n", cond ? "true" : "false");
    char* result_str = (b > 5) ? "b é maior que 5" : "b não é maior que 5";
    printf("  Resultado do ternário: %s\n", result_str);
}

/**
 * Demonstra as estruturas de controle de fluxo: if, switch, for, while, etc.
 */
void demonstrate_control_flow() {
    printf("\n--- 3. Controle de Fluxo ---\n");
    // IF-ELSE IF-ELSE
    int i = 5;
    if (i > 10) {
        printf("if: i é maior que 10\n");
    } else if (i == 5) {
        printf("if: i é exatamente 5\n");
    } else {
        printf("if: i não é maior que 10 nem igual a 5\n");
    }

    // SWITCH
    char grade = 'B';
    printf("switch: A nota é %c. ", grade);
    switch (grade) {
        case 'A': printf("Excelente!\n"); break;
        case 'B': printf("Muito Bom!\n"); break;
        case 'C': printf("Bom.\n"); break;
        default: printf("Precisa estudar mais.\n"); break;
    }

    // FOR loop
    printf("for loop: ");
    for (int j = 0; j < 5; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // WHILE loop
    printf("while loop: ");
    int k = 0;
    while (k < 5) {
        printf("%d ", k);
        k++;
    }
    printf("\n");
}

// --- Funções Auxiliares para a Seção 4 ---
// Função estática, visível apenas neste arquivo.
static void add_one_by_reference(int *num_ptr) {
    (*num_ptr)++; // Incrementa o valor no endereço de memória apontado.
}
// Função recursiva para calcular fatorial.
long factorial(int n) {
    if (n <= 1) return 1;          // Caso base
    return n * factorial(n - 1); // Chamada recursiva
}

void demonstrate_functions_and_pointers() {
    printf("\n--- 4. Funções e Ponteiros ---\n");
    // Passagem por referência usando ponteiros
    int my_number = 10;
    printf("Número original: %d\n", my_number);
    add_one_by_reference(&my_number); // Passa o endereço de memória da variável
    printf("Número após chamada de função por referência: %d\n", my_number);

    // Recursão
    int fact_num = 6;
    printf("Fatorial de %d é %ld\n", fact_num, factorial(fact_num));

    // Ponteiro para função
    long (*factorial_ptr)(int) = &factorial;
    printf("Fatorial de 5 (via ponteiro de função) é %ld\n", factorial_ptr(5));
}

void demonstrate_arrays_and_strings() {
    printf("\n--- 5. Arrays e Strings ---\n");
    // Array de inteiros
    int numbers[5] = {10, 20, 30, 40, 50};
    printf("O terceiro elemento do array de números é: %d\n", numbers[2]);

    // String (array de caracteres terminado por nulo)
    char greeting[20] = "Olá";
    printf("String inicial: %s\n", greeting);

    // Manipulação de strings
    strcat(greeting, ", Mundo!"); // Concatena
    printf("String após strcat: %s\n", greeting);
    printf("Comprimento da string (strlen): %zu\n", strlen(greeting));
}

// --- Definições de Tipos para a Seção 6 ---
typedef struct {
    char name[50];
    int id;
    float salary;
} Employee;

typedef union {
    int i;
    float f;
    char c;
} DataUnion;

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR = -1
} MachineState;

void demonstrate_structs_unions_enums() {
    printf("\n--- 6. Structs, Unions e Enums ---\n");
    // STRUCT
    Employee emp1;
    strcpy(emp1.name, "Leandro");
    emp1.id = 123;
    emp1.salary = 95000.50f;

    // Acesso com ponteiro e alocação dinâmica
    Employee *emp_ptr = (Employee*) malloc(sizeof(Employee));
    if (emp_ptr == NULL) {
        printf("Falha ao alocar memória para o empregado!\n");
        return;
    }
    strcpy(emp_ptr->name, "Gemini");
    emp_ptr->id = 456;
    emp_ptr->salary = 150000.0f;
    printf("Empregado 1: %s (ID: %d)\n", emp1.name, emp1.id);
    printf("Empregado 2: %s (ID: %d, via ponteiro)\n", emp_ptr->name, emp_ptr->id);
    free(emp_ptr); // Libera a memória alocada

    // UNION
    DataUnion data;
    data.i = 10;
    printf("Union: como int = %d, ", data.i);
    data.f = 2.5f;
    printf("como float = %f, ", data.f);
    printf("agora o int vale %d (lixo!)\n", data.i); // Mostra que a memória é compartilhada

    // ENUM
    MachineState current_state = STATE_RUNNING;
    if (current_state == STATE_RUNNING) {
        printf("Enum: A máquina está no estado RUNNING (%d).\n", current_state);
    }
}

void demonstrate_file_io() {
    printf("\n--- 7. Entrada e Saída de Arquivos (File I/O) ---\n");
    const char* filename = "teste.txt";
    FILE *file_ptr;

    // Escrita no arquivo
    printf("Escrevendo no arquivo '%s'...\n", filename);
    file_ptr = fopen(filename, "w"); // "w" para escrita (write)
    if (file_ptr == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    fprintf(file_ptr, "Olá do mundo do C!\n");
    fprintf(file_ptr, "Esta é a segunda linha.\n");
    fclose(file_ptr);

    // Leitura do arquivo
    printf("Lendo do arquivo '%s':\n", filename);
    file_ptr = fopen(filename, "r"); // "r" para leitura (read)
    if (file_ptr == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
        printf("  > %s", buffer);
    }
    fclose(file_ptr);
}