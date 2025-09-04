# =============================================================================
# Makefile para HI-TECH C Compiler Code Generator (cgen)
# Adaptado para a estrutura de diretórios src, include, build, bin.
# =============================================================================

# --- Compilador e Flags ---
CC = gcc
# Adiciona a flag -I$(INC_DIR) para que o compilador encontre os headers.
CFLAGS = -std=c89 -g -Wall -Wextra -O2

# --- Definição de Diretórios ---
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin

# Adiciona o caminho do diretório de include às flags
CFLAGS += -I$(INC_DIR)

# --- Lista de Arquivos Fonte (apenas os nomes base) ---
LEX_SRCS = lex1u.c lex2.c
SYM_SRCS = sym1.c sym2s.c sym3.c
TREE_SRCS = tree1.c tree2.c tree3.c
CGEN_SRCS = cgen1.c cgen2s.c cgen3.c
LOCAL_SRCS = local1s.c local2.c
OTHER_SRCS = code.c data.c getchar.c main.c

# Combina todos os nomes base dos arquivos fonte em uma única lista
_SRCS = $(LEX_SRCS) $(SYM_SRCS) $(TREE_SRCS) $(CGEN_SRCS) $(LOCAL_SRCS) $(OTHER_SRCS)

# --- Mapeamento de Arquivos ---
# Adiciona o prefixo do diretório de fontes (src/) a cada arquivo .c
SRCS = $(addprefix $(SRC_DIR)/, $(_SRCS))
# Cria a lista de arquivos objeto, colocando-os no diretório de build (build/)
OBJS = $(addprefix $(OBJ_DIR)/, $(_SRCS:.c=.o))
# Define o caminho completo do executável final
TARGET = $(BIN_DIR)/cgen
# Define a lista de headers para usar como dependências
HEADERS = $(addprefix $(INC_DIR)/, cgen.h portab.h)

# --- Regras Principais ---

# A regra 'all' é a padrão. Depende do executável final.
all: $(TARGET)

# Regra para linkar o executável final a partir dos arquivos objeto.
# Depende de todos os arquivos .o.
$(TARGET): $(OBJS)
	@echo "==> Linking target: $@"
	@mkdir -p $(BIN_DIR) # Garante que o diretório 'bin' exista
	$(CC) $(CFLAGS) -o $@ $^

# Regra de padrão para compilar arquivos .c em .o.
# Para cada arquivo em 'build/%.o', procura por 'src/%.c'.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "==> Compiling: $<"
	@mkdir -p $(OBJ_DIR) # Garante que o diretório 'build' exista
	$(CC) $(CFLAGS) -c $< -o $@

# --- Regras de Limpeza ---

# A regra 'clean' remove os diretórios de build e binários.
clean:
	@echo "==> Cleaning project..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# --- Phony Targets ---
# Define alvos que não representam arquivos reais.
.PHONY: all clean