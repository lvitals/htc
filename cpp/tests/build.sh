#!/bin/bash

# =============================================================================
# build.sh - Script de Teste para o Pré-processador cpp
# =============================================================================
# Este script executa um pipeline de compilação de teste:
# 1. Usa o nosso './bin/cpp' para pré-processar um arquivo de exemplo,
#    forçando-o a usar os cabeçalhos e definições do ambiente CP/M.
# 2. Usa o 'gcc' do sistema para compilar o resultado e gerar um
#    executável nativo para teste.
# =============================================================================

# Sair imediatamente se qualquer comando falhar
set -e

# --- Variáveis de Configuração ---
BOLD=$(tput bold)
GREEN=$(tput setaf 2)
NC=$(tput sgr0) # Sem Cor

CPP_TOOL="../bin/cpp"
# SOURCE_FILE="main-ansi.c"
SOURCE_FILE="main-ansi-old.c"
# SOURCE_FILE="main-ansi-copy.c"

# Caminho para os includes da toolchain Hi-Tech C para CP/M
CPM_INCLUDE_PATH="/usr/local/lib/cpm/include80"

# Arquivos de saída
PREPROCESSED_FILE="main.i"
TARGET_APP="test_app"

# --- Script Principal ---

echo "${BOLD}🚀 Iniciando build de teste com configuração CP/M...${NC}"

# Limpeza de arquivos antigos
# rm -f "$PREPROCESSED_FILE" "$TARGET_APP"

# 1. Pré-processar usando nossa ferramenta e os includes do CP/M.
#    -DCPM, -DHI_TECH_C, -DZ80 simulam o ambiente de compilação alvo,
#    ativando as diretivas #ifdef corretas nos cabeçalhos.
echo "1. Pré-processando ${SOURCE_FILE} com ${BOLD}${CPP_TOOL}${NC}..."
"$CPP_TOOL" -DCPM -DHI_TECH_C -DZ80 -I"$CPM_INCLUDE_PATH" "$SOURCE_FILE" > "$PREPROCESSED_FILE"
echo "   -> Arquivo pré-processado salvo como ${BOLD}${PREPROCESSED_FILE}${NC}"

# 2. Compilar o arquivo pré-processado com o gcc do host.
#    Os avisos de "incompatible redeclaration" são esperados aqui.
echo ""
echo "2. Compilando ${PREPROCESSED_FILE} com ${BOLD}gcc${NC} para teste no host..."
gcc "$PREPROCESSED_FILE" -o "$TARGET_APP"

# 3. Limpar o arquivo intermediário.
# rm -f "$PREPROCESSED_FILE"

echo ""
echo "${GREEN}✅ Teste concluído com sucesso!${NC}"
echo "   -> Executável de teste criado: ${BOLD}${TARGET_APP}${NC}"
echo "   -> Para executar: ./${TARGET_APP}"