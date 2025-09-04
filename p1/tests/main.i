# 1 "main-ansi-old.c"









# 1 "/usr/local/lib/cpm/include80/stdio.h"









# 13 "/usr/local/lib/cpm/include80/stdio.h"





extern	struct	_iobuf
{
    char		*_ptr;
    int			 _cnt;
    char		*_base;
    unsigned short	 _flag;
    char		 _file;
} _iob[	8];










































# 71 "/usr/local/lib/cpm/include80/stdio.h"














extern int	 fclose(	struct _iobuf *);
extern int	 fflush(	struct _iobuf *);
extern int	 fgetc(	struct _iobuf *);
extern int	 ungetc(int, 	struct _iobuf *);
extern int	 fputc(int, 	struct _iobuf *);
extern int	 getw(	struct _iobuf *);
extern int	 putw(int, 	struct _iobuf *);
extern char	*gets(char *);
extern int	 puts(char *);
extern int	 fputs(char *, 	struct _iobuf *);
extern int	 fread(void *, unsigned, unsigned, 	struct _iobuf *);
extern int	 fwrite(void *, unsigned, unsigned, 	struct _iobuf *);
extern int	 fseek(	struct _iobuf *, long, int);
extern int	 rewind(	struct _iobuf *);
extern int	 setbuf(	struct _iobuf *, char *);
extern int	 printf(char *, ...);
extern int	 fprintf(	struct _iobuf *, char *, ...);
extern int	 sprintf(char *, char *, ...);
extern int	 scanf(char *, ...);
extern int	 fscanf(	struct _iobuf *, char *, ...);
extern int	 sscanf(char *, char *, ...);
extern int	 remove(char *);
extern 	struct _iobuf	*fopen(char *, char *);
extern 	struct _iobuf	*freopen(char *, char *, 	struct _iobuf *);
extern 	struct _iobuf	*fdopen(int, char *);
extern long	 ftell(	struct _iobuf *);
extern char	*fgets(char *, int, 	struct _iobuf *);
extern char	*_bufallo(void);



# 10 "main-ansi-old.c"

# 1 "/usr/local/lib/cpm/include80/stdlib.h"






typedef	int		ptrdiff_t;
typedef	unsigned	size_t;





# 16 "/usr/local/lib/cpm/include80/stdlib.h"


extern int	errno;




extern double	 atof(char *);
extern int	 atoi(char *);
extern long	 atol(char *);
extern int	 rand(void);
extern void	 srand(unsigned int);
extern void	*calloc(size_t, size_t);
extern void	 free(void *);
extern void	*malloc(size_t);
extern void	*realloc(void *, size_t);
extern void	 abort(void);
extern void	 exit(int);
extern char	*getenv(char *);
extern int	 system(char *);
typedef int (*__qsort_compf)(void *, void *);
extern void	 qsort(void *, size_t, size_t, __qsort_compf);
extern int	 abs(int);
extern long	 labs(long);



# 11 "main-ansi-old.c"

# 1 "/usr/local/lib/cpm/include80/string.h"





# 11 "/usr/local/lib/cpm/include80/string.h"


# 15 "/usr/local/lib/cpm/include80/string.h"


extern int	errno;

extern void	*memcpy(void *, void *, size_t);
extern void	*memmove(void *, void *, size_t);
extern char	*strcpy(char *, char *);
extern char	*strncpy(char *, char *, size_t);
extern char	*strcat(char *, char *);
extern char	*strncat(char *, char *, size_t);
extern int	 memcmp(void *, void *, size_t);
extern int	 strcmp(char *, char *);
extern int	 strcasecmp(char *, char *);

extern int	 strncmp(char *, char *, size_t);
extern int	 strncasecmp(char *, char *, size_t);


extern void	*memchr(void *, int, size_t);



extern char	*strstr(char *, char *);
extern char	*strtok(char *, char *);
extern void	*memset(void *, int, size_t);
extern char	*strerror(int);
extern size_t	 strlen(char *);
extern char	*strchr(char *, int);

extern char	*index(char *, int);
extern char	*strrchr(char *, int);

extern char	*rindex(char *, int);
extern char	*strcasestr(char *, char *);

extern char	*strncasestr(char *, char *, size_t);




# 12 "main-ansi-old.c"







void demonstrate_variables_and_types(void);
void demonstrate_operators(void);
void demonstrate_control_flow(void);
void demonstrate_functions_and_pointers(void);
void demonstrate_arrays_and_strings(void);
void demonstrate_structs_unions_enums(void);
void demonstrate_file_io(void);


int main(void) {
    printf("=================================================\n");
    printf("== Showcase Portatil da Linguagem C (ANSI)\n");
    printf("=================================================\n");

    demonstrate_variables_and_types();
    demonstrate_operators();
    demonstrate_control_flow();
    demonstrate_functions_and_pointers();
    demonstrate_arrays_and_strings();
    demonstrate_structs_unions_enums();
    demonstrate_file_io();

    printf("\nDemonstracao concluida com sucesso.\n");
    return 0;
}


void demonstrate_variables_and_types(void) {
    int integer_var = 42;
    float float_var = 3.14f;
    double double_var = 2.71828;
    char char_var = 'C';
    int bool_var = 1;

    float PI = 3.14159f;

    printf("\n--- 1. Variaveis e Tipos de Dados ---\n");
    printf("Integer: %d (tamanho: %lu bytes)\n", integer_var, (unsigned long)sizeof(integer_var));
    printf("Float:   %f (tamanho: %lu bytes)\n", float_var, (unsigned long)sizeof(float_var));
    printf("Double:  %f (tamanho: %lu bytes)\n", double_var, (unsigned long)sizeof(double_var));
    printf("Char:    %c (tamanho: %lu byte)\n", char_var, (unsigned long)sizeof(char_var));
    printf("Bool:    %d (tamanho: %lu byte)\n", bool_var, (unsigned long)sizeof(bool_var));
    printf("Constante PI: %f\n", PI);
}


void demonstrate_operators(void) {
    int a = 10, b = 3;
    int x = 0xA;
    int y = 0xC;
    int cond;
    char *result_str;

    printf("\n--- 2. Operadores ---\n");
    printf("Aritmeticos: a=%d, b=%d\n", a, b);
    printf("  Soma (a + b)      = %d\n", a + b);
    printf("  Resto (a %% b)      = %d\n", a % b);

    printf("\nBit-a-bit: x=10 (0xA), y=12 (0xC)\n");
    printf("  AND (x & y)       = %d\n", x & y);
    printf("  OR  (x | y)       = %d\n", x | y);
    printf("  Shift Esq (x << 1)= %d\n", x << 1);

    printf("\nLogicos e Ternario:\n");
    cond = (a > b) && (x != 0);
    printf("  (a > b) && (x != 0) e %s\n", cond ? "TRUE" : "FALSE");
    result_str = (b > 5) ? "b e maior que 5" : "b nao e maior que 5";
    printf("  Resultado do ternario: %s\n", result_str);
}


void demonstrate_control_flow(void) {
    int i = 5;
    char grade = 'B';
    int j;
    int k = 0;

    printf("\n--- 3. Controle de Fluxo ---\n");
    if (i > 10) {
        printf("if: i e maior que 10\n");
    } 
    else if (i == 5) {
        printf("if: i e exatamente 5\n");
    }

    printf("switch: A nota e %c. ", grade);
    switch (grade) {
        case 'A': 
            printf("Excelente!\n"); 
            break;
        case 'B': 
            printf("Muito Bom!\n"); 
            break;
        default: 
            printf("Precisa estudar mais.\n"); 
            break;
    }

    printf("for loop: ");
    for (j = 0; j < 5; j++) {
        printf("%d ", j);
    }
    printf("\n");

    printf("while loop: ");
    while (k < 5) {
        printf("%d ", k);
        k++;
    }
    printf("\n");
}


static void add_one_by_reference(int *num_ptr)
{
    (*num_ptr)++;
}

long factorial(int n)
{
    if (n <= 1) return 1L;
    return n * factorial(n - 1);
}

void demonstrate_functions_and_pointers(void) {
    int my_number = 10;
    int fact_num = 6;
    long (*factorial_ptr)(int);

    printf("\n--- 4. Funcoes e Ponteiros ---\n");
    
    add_one_by_reference(&my_number);
    printf("Numero apos chamada por referencia: %d\n", my_number);

    printf("Fatorial de %d e %ld\n", fact_num, factorial(fact_num));
    
    factorial_ptr = factorial;
    printf("Fatorial de 5 (via ponteiro) e %ld\n", factorial_ptr(5));
}


void demonstrate_arrays_and_strings(void) {
    int numbers[5];
    char greeting[20];
    int i;

    printf("\n--- 5. Arrays e Strings ---\n");
    for (i = 0; i < 5; i++) {
        numbers[i] = (i + 1) * 10;
    }
    printf("O terceiro elemento do array e: %d\n", numbers[2]);

    strcpy(greeting, "Ola");
    strcat(greeting, ", Mundo!");
    printf("String final: %s\n", greeting);
    printf("Comprimento (strlen): %lu\n", (unsigned long)strlen(greeting));
}


typedef struct {
    char name[50];
    int id;
} Employee;

typedef enum {
    STATE_IDLE,
    STATE_RUNNING
} MachineState;

void demonstrate_structs_unions_enums(void) {
    Employee emp1;
    MachineState current_state = STATE_RUNNING;

    printf("\n--- 6. Structs, Unions e Enums ---\n");
    strcpy(emp1.name, "Leandro");
    emp1.id = 123;
    printf("Empregado: %s (ID: %d)\n", emp1.name, emp1.id);

    if (current_state == STATE_RUNNING) {
        printf("Enum: A maquina esta no estado RUNNING (%d).\n", current_state);
    }
}


void demonstrate_file_io(void) {
    	struct _iobuf *file_ptr;
    char buffer[100];

    printf("\n--- 7. Entrada e Saida de Arquivos (File I/O) ---\n");


    file_ptr = fopen("teste.txt", "w");
    if (file_ptr == ((void *)0)) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    fprintf(file_ptr, "Ola do mundo do C!\n");
    fclose(file_ptr);
    printf("Arquivo 'teste.txt' escrito com sucesso.\n");


    file_ptr = fopen("teste.txt", "r");
    if (file_ptr == ((void *)0)) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }
    printf("Lendo do arquivo 'teste.txt':\n");
    while (fgets(buffer, sizeof(buffer), file_ptr) != ((void *)0)) {
        printf("  > %s", buffer);
    }
    fclose(file_ptr);
}