#
# Makefile for the DUMP utility
# Based on the cpp/Makefile, adapted for dump.c.
# Revision Date: September 10, 2025
#

# --- CP/M Tool Paths (MUST be defined before including compile.mk) ---
CPP = /home/leandro/workspaces/estudo-compilador/htc/cpp/bin/cpp
P1 = /home/leandro/workspaces/estudo-compilador/htc/p1/bin/p1
CGEN = /home/leandro/workspaces/estudo-compilador/htc/cgen/bin/cgen
OPTIM = /home/leandro/workspaces/estudo-compilador/htc/optim/optim
ZAS = /home/leandro/workspaces/estudo-compilador/htc/zas/zas
LINK = /home/leandro/workspaces/estudo-compilador/htc/link/link
LIBR = /home/leandro/workspaces/estudo-compilador/htc/libr/libr
OBJTOHEX = /home/leandro/workspaces/estudo-compilador/htc/objtohex/objtohex

# Compiler flags for CP/M
CFLAGS = -I/home/leandro/workspaces/estudo-compilador/htc/libc/include -DCPM -DHI_TECH_C -Dz80 -Dconst=
ASFLAGS = -J -N -I/home/leandro/workspaces/estudo-compilador/htc/libc/include -I/home/leandro/workspaces/estudo-compilador/htc/libc/arch/z80

# Library paths for CP/M
LIBC_LIB = /home/leandro/workspaces/estudo-compilador/htc/libc/lib/libc.lib
LIBF_LIB = /home/leandro/workspaces/estudo-compilador/htc/libc/lib/libf.lib
CRTCPM_OBJ = /home/leandro/workspaces/estudo-compilador/htc/libc/obj/crtcpm.obj

include ../compile.mk

# --- Project Configuration and Tools ---
CC = gcc
RM = rm -rf

# --- Names and Directories ---
TARGET_NAME = dump

SRCDIR   = .
INCDIR   = include
BUILDDIR = build
BINDIR = bin

TARGET = $(BINDIR)/$(TARGET_NAME)

# Temporary directory for intermediate files from compile.mk
TMP_DIR = $(BUILDDIR)

# --- Compilation and Linker Flags for Native Build ---
# CFLAGS for native compilation
NATIVE_CFLAGS = -g -Wall -Wextra -O2 -std=c89 -Wno-unused-function -Wno-unused-label -D_POSIX_C_SOURCE=200809L

# LDFLAGS for native compilation
NATIVE_LDFLAGS =


# --- Automatic File List Generation ---
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))


# --- Compilation Rules (Targets) ---
.PHONY: all clean re cpm

all: $(TARGET)

clean:
	@echo "Cleaning the project..."
	$(RM) $(BUILDDIR) $(BINDIR)

re: clean all

# CP/M target
CPM_TARGET = $(BINDIR)/DUMP.COM
CPM_OBJ = $(BUILDDIR)/dump_cpm.obj

cpm: $(CPM_TARGET)

$(CPM_TARGET): $(CPM_OBJ)
	@echo "Linking CP/M executable: $@"
	@mkdir -p $(BINDIR)
	$(LINK) -Z -Ptext=0,data,bss -C100H -o$@ $(CRTCPM_OBJ) $(CPM_OBJ) $(LIBC_LIB) $(LIBF_LIB) $(LIBF_LIB)
	@echo "CP/M executable compiled successfully! Executable at: $(CPM_TARGET)"

$(CPM_OBJ): $(SRCDIR)/dump.c
	@echo "Compiling for CP/M: $<"
	@mkdir -p $(BUILDDIR)
	$(call compile_c, $<, $@)


# --- Pattern and specific Rules for Native Build ---
# Linker Rule for native compilation:
$(TARGET): $(OBJS)
	@echo "Linking the native executable: $@"
	@mkdir -p $(BINDIR)
	$(CC) $(NATIVE_LDFLAGS) -o $@ $^
	@echo "Native executable compiled successfully! Executable at: $(TARGET)"

# Generic Compilation Rule for native compilation:
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "   Compiling native: $<"
	@mkdir -p $(BUILDDIR)
	$(CC) $(NATIVE_CFLAGS) -c $< -o $@