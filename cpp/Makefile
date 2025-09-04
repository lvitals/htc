#
# Makefile para o pré-processador C (cpp)
# Originalmente parte da toolchain Hi-Tech C, agora portado para compilação moderna com GCC/Clang.
# Data da Revisão: 12 de Junho de 2025
#

# --- Configuração do Projeto e Ferramentas ---
# Define o compilador C a ser usado. Pode ser trocado por 'clang'.
CC = gcc
# Define a ferramenta de remoção para a regra 'clean'.
RM = rm -rf

# --- Nomes e Diretórios ---
# Nome do executável final que será gerado.
TARGET_NAME = cpp

# Define a estrutura de diretórios do projeto para organização.
SRCDIR   = src
INCDIR   = include
BUILDDIR = build
BINDIR   = bin

# Gera o caminho completo para o alvo final (ex: bin/cpp).
TARGET = $(BINDIR)/$(TARGET_NAME)


# --- Flags de Compilação e Ligação ---
#
# CFLAGS: Flags para o compilador C.
# -g                   -> Adiciona informações de depuração (para usar com gdb).
# -Wall -Wextra        -> Ativa o máximo de avisos úteis. Essencial para código de qualidade.
# -O2                  -> Nível de otimização 2. Um bom balanço entre velocidade e tempo de compilação.
# -std=c11             -> Garante que o código siga o padrão C de 2011, evitando construções antigas.
# -I$(INCDIR)          -> Informa ao compilador para procurar por #includes (como "cpp.h") no nosso diretório 'include'.
# -DUSE_GETARGS        -> Ativa, via pré-processador, o código de 'getargs.c' que expande argumentos
#                        na linha de comando (globbing), uma funcionalidade do cpp original.
# -Wno-unused-function -> Suprime o aviso sobre funções estáticas não usadas, que pode ocorrer
#                        devido à forma como os arquivos originais foram estruturados.
CFLAGS = -g -Wall -Wextra -O2 -std=c89 -I$(INCDIR) -DUSE_GETARGS -Wno-unused-function

# LDFLAGS: Flags para o ligador (linker). Usado para incluir bibliotecas (ex: -lm para a biblioteca matemática).
# Nosso projeto não tem dependências externas, então fica vazio.
LDFLAGS =


# --- Geração Automática de Listas de Arquivos ---
#
# SRCS: Cria uma lista de todos os arquivos .c dentro do diretório 'src'.
# A função 'wildcard' expande o padrão para encontrar os nomes dos arquivos.
SRCS = $(wildcard $(SRCDIR)/*.c)

# OBJS: Cria a lista de arquivos objeto (.o) correspondentes.
# A função 'patsubst' (pattern substitution) transforma cada item da lista SRCS
# (ex: src/main.c) em seu equivalente no diretório de compilação (ex: build/main.o).
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))


# --- Regras de Compilação (Targets) ---
#
# .PHONY: Declara alvos que não são nomes de arquivos. Isso força 'make' a executar
# a regra sempre que chamada, mesmo que um arquivo com o mesmo nome exista.
.PHONY: all clean re

# 'all' é a regra padrão, executada quando 'make' é chamado sem argumentos.
# Sua dependência é o executável final.
all: $(TARGET)

# 'clean' remove todos os arquivos gerados, limpando o projeto.
# Usa a variável $(RM) definida no topo.
clean:
	@echo "🧹 Limpando o projeto..."
	$(RM) $(BUILDDIR) $(BINDIR)

# 're' é uma regra de conveniência para "rebuild" (recompilar).
# Executa 'clean' e depois 'all'.
re: clean all


# --- Regras de Padrão e Específicas ---
#
# Regra de Ligação: Descreve como criar o executável final.
# É acionada quando todos os seus pré-requisitos (os arquivos .o em $(OBJS)) estão prontos.
# $@ -> Representa o nome do alvo (neste caso, $(TARGET)).
# $^ -> Representa a lista de todos os pré-requisitos (neste caso, $(OBJS)).
$(TARGET): $(OBJS)
	@echo "🔗 Ligando o executável: $@"
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "✅ Projeto compilado com sucesso! Executável em: $(TARGET)"

# Regra de Compilação Genérica: É uma regra de padrão que ensina ao 'make'
# como criar um arquivo .o em 'build' a partir de um arquivo .c em 'src'.
# $< -> Representa o nome do primeiro pré-requisito (neste caso, o arquivo .c correspondente).
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "   Compilando: $<"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de Compilação Específica: Esta regra sobrescreve a genérica APENAS para o arquivo 'expr_parser.c'.
# A necessidade dela é para adicionar a flag '-Wno-unused-label' e suprimir o aviso inofensivo
# sobre 'yyerrlab', que é um artefato do código gerado pela ferramenta Yacc.
$(BUILDDIR)/expr_parser.o: $(SRCDIR)/expr_parser.c
	@echo "   Compilando parser: $< (suprimindo aviso de label)"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -Wno-unused-label -c $< -o $@