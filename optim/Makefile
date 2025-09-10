#
# Makefile for the Optimizer (optim)
# Originally part of the Hi-Tech C toolchain, now ported for modern compilation with GCC/Clang.
# Revision Date: June 12, 2025
#

# --- Project Configuration and Tools ---
# Defines the C compiler to be used. Can be switched to 'clang'.
CC = gcc
# Defines the removal tool for the 'clean' rule.
RM = rm -rf

# --- Names and Directories ---
# Name of the final executable to be generated.
TARGET_NAME = optim

# Defines the project's directory structure for organization.
SRCDIR   = src
INCDIR   = include
BUILDDIR = build
BINDIR   = bin

# Generates the full path for the final target (e.g., bin/optim).
TARGET = $(BINDIR)/$(TARGET_NAME)


# --- Compilation and Linker Flags ---
#
# CFLAGS: Flags for the C compiler.
# -g                   -> Adds debugging information (for use with gdb).
# -Wall -Wextra        -> Enables the maximum number of useful warnings. Essential for quality code.
# -O2                  -> Optimization level 2. A good balance between speed and compilation time.
# -std=c89             -> Ensures the code follows the C89 standard, avoiding old constructs.
# -I$(INCDIR)          -> Tells the compiler to look for #includes in our 'include' directory.
# -Wno-unused-function -> Suppresses the warning about unused static functions, which can occur
#                        due to how the original files were structured.
# -Wno-unused-label    -> Suppresses the warning about unused labels.
CFLAGS = -g -Wall -Wextra -O2 -std=c89 -I$(INCDIR) -Wno-unused-function -Wno-unused-label -D_POSIX_C_SOURCE=200809L

# LDFLAGS: Flags for the linker. Used to include libraries (e.g., -lm for the math library).
# Our project has no external dependencies, so it is empty.
LDFLAGS =


# --- Automatic File List Generation ---
#
# SRCS: Creates a list of all .c files inside the 'src' directory.
# The 'wildcard' function expands the pattern to find the file names.
SRCS = $(wildcard $(SRCDIR)/*.c)

# OBJS: Creates the list of corresponding object files (.o).
# The 'patsubst' (pattern substitution) function transforms each item in the SRCS list
# (e.g., src/main.c) into its equivalent in the build directory (e.g., build/main.o).
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))


# --- Compilation Rules (Targets) ---
#
# .PHONY: Declares targets that are not file names. This forces 'make' to execute
# the rule whenever it is called, even if a file with the same name exists.
.PHONY: all clean re

# 'all' is the default rule, executed when 'make' is called without arguments.
# Its dependency is the final executable.
all: $(TARGET)

# 'clean' removes all generated files, cleaning the project.
# Uses the $(RM) variable defined at the top.
clean:
	@echo "Cleaning the project..."
	$(RM) $(BUILDDIR) $(BINDIR)

# 're' is a convenience rule for "rebuild".
# Executes 'clean' and then 'all'.
re: clean all


# --- Pattern and specific Rules ---
#
# Linker Rule: Describes how to create the final executable.
# It is triggered when all its prerequisites (the .o files in $(OBJS)) are ready.
# $@ -> Represents the target name (in this case, $(TARGET)).
# $^ -> Represents the list of all prerequisites (in this case, $(OBJS)).
$(TARGET): $(OBJS)
	@echo "Linking the executable: $@"
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Project compiled successfully! Executable at: $(TARGET)"

# Generic Compilation Rule: This is a pattern rule that teaches 'make'
# how to create a .o file in 'build' from a .c file in 'src'.
# $< -> Represents the name of the first prerequisite (in this case, the corresponding .c file).
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "   Compiling: $<"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@