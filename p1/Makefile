# --- Variáveis de Configuração ---
# Nome do executável final
TARGET_NAME = p1
# Compilador C
CC = gcc
# Flags de compilação
CFLAGS = -std=c89 -g -Wall -Wextra -O2

# --- Estrutura de Diretórios ---
# Diretório para o executável final
BIN_DIR = bin
# Diretório para os arquivos objeto (.o)
BUILD_DIR = build
# Diretório para os arquivos fonte (.c)
SRC_DIR = src
# Diretório para os arquivos de cabeçalho (.h)
INCLUDE_DIR = include

# --- Geração Automática de Caminhos ---
# Caminho completo do executável
TARGET = $(BIN_DIR)/$(TARGET_NAME)

# Lista todos os arquivos fonte (.c) no diretório 'src'
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera os nomes dos arquivos objeto (.o) correspondentes, colocando-os no diretório 'build'
# Ex: src/main.c -> build/main.o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Adiciona o diretório 'include' ao caminho de busca do compilador
CFLAGS += -I$(INCLUDE_DIR)

# --- Regras de Compilação ---

# Regra principal: 'all' é o alvo padrão. .PHONY indica que não é um arquivo.
.PHONY: all
all: $(TARGET)

# Regra para linkar o executável final a partir dos arquivos objeto.
# A regra também garante que o diretório 'bin' exista.
# $@ : O nome do alvo (bin/p1)
# $^ : Os nomes de todas as dependências (todos os .o)
$(TARGET): $(OBJS)
	@echo "Linkando o executável final: $@"
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regra de padrão para compilar um arquivo .c em um .o.
# A regra garante que o diretório 'build' exista para cada arquivo objeto.
# $< : O nome da primeira dependência (o arquivo .c correspondente)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando: $< -> $@"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados (objetos e executável)
.PHONY: clean
clean:
	@echo "Limpando diretórios de build e bin..."
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Regra para executar o compilador com argumentos de teste
.PHONY: run
run: all
	@echo "Executando o compilador P1 em um arquivo de teste..."
	./$(TARGET) test_input.c test_output.asm