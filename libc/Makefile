.SUFFIX: .obj .c .as .lib

# Compiler and assembler flags
CFLAGS = -I./include -DCPM -DHI_TECH_C -Dz80
ASFLAGS = -J -N -I./include -I./arch/z80
TAG = $(shell git describe --tags 2>/dev/null || echo "vdev")

# Directory definitions
SRC_DIR = src
INC_DIR = include
ARCH_DIR = arch/z80
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin
TMP_DIR = tmp

LIBC_PATH = .
include ../compile.mk

# Ensure directories exist
DIRS = $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) $(TMP_DIR)
$(DIRS):
	@mkdir -p $@

# Build tools
build-tools: $(DIRS)
	@[ -f $(CPP) ] || $(MAKE) -C ../cpp && echo "BIN_DIR is: $(BIN_DIR)" && cp ../cpp/bin/cpp $(BIN_DIR)/ 
	@[ -f $(P1) ] || $(MAKE) -C ../p1 && cp ../p1/bin/p1 $(BIN_DIR)/ 
	@[ -f $(CGEN) ] || $(MAKE) -C ../cgen && cp ../cgen/bin/cgen $(BIN_DIR)/ 
	@[ -f $(OPTIM) ] || $(MAKE) -C ../optim && cp ../optim/optim $(BIN_DIR)/ 
	@[ -f $(ZAS) ] || $(MAKE) -C ../zas && cp ../zas/zas $(BIN_DIR)/ 
	@[ -f $(LINK) ] || $(MAKE) -C ../link && cp ../link/link $(BIN_DIR)/ 
	@[ -f $(LIBR) ] || $(MAKE) -C ../libr && cp ../libr/libr $(BIN_DIR)/ 
	@[ -f $(OBJTOHEX) ] || $(MAKE) -C ../objtohex && cp ../objtohex/objtohex $(BIN_DIR)/ 

# Rule for C files
$(OBJ_DIR)/%.obj: $(SRC_DIR)/%.c | $(DIRS) build-tools
	$(call compile_c,$<,$@)

# Rule for assembly files
$(OBJ_DIR)/%.obj: $(ARCH_DIR)/%.as | $(DIRS) build-tools
	$(info Assembling $< to $@)
	$(ZAS) $(ASFLAGS) $< -o $@

# List of object files for libc.lib
COBJS = $(patsubst %,$(OBJ_DIR)/%, \
getargs.obj assert.obj printf.obj fprintf.obj sprintf.obj \
doprnt.obj gets.obj puts.obj fwrite.obj getw.obj \
strtok.obj strdup.obj strstr.obj stristr.obj strnstr.obj strnistr.obj \
putw.obj getenv.obj putchar.obj perror.obj fputc.obj \
flsbuf.obj fopen.obj freopen.obj fseek.obj fread.obj \
rewind.obj remove.obj setbuf.obj fscanf.obj ctime.obj \
cgets.obj cputs.obj sscanf.obj scanf.obj doscan.obj \
ungetc.obj fgetc.obj filbuf.obj stdclean.obj fclose.obj \
fflush.obj buf.obj exit.obj start1.obj start2.obj \
open.obj read.obj write.obj seek.obj stat.obj \
chmod.obj fcbname.obj rename.obj creat.obj time.obj \
convtime.obj timezone.obj isatty.obj close.obj unlink.obj \
dup.obj execl.obj getfcb.obj srand1.obj srand.obj abort.obj \
getch.obj signal.obj getuid.obj bdos.obj \
bios.obj cleanup.obj _exit.obj fakeclea.obj fakecpcl.obj \
sys_err.obj memcpy.obj memcmp.obj memset.obj abs.obj \
asallsh.obj allsh.obj asalrsh.obj asar.obj asdiv.obj \
asladd.obj asland.obj asll.obj asllrsh.obj aslmul.obj \
aslor.obj aslsub.obj aslxor.obj strftime.obj asmod.obj \
atoi.obj atol.obj blkclr.obj blkcpy.obj calloc.obj asmul.obj \
bitfield.obj ctype_.obj getsp.obj index.obj strchr.obj \
inout.obj iregset.obj isalpha.obj isdigit.obj islower.obj \
isspace.obj isupper.obj ladd.obj land.obj linc.obj \
llrsh.obj longjmp.obj lor.obj brelop.obj wrelop.obj \
lrelop.obj frelop.obj lsub.obj lxor.obj malloc.obj \
max.obj idiv.obj pnum.obj ldiv.obj qsort.obj \
swap.obj aslr.obj bmove.obj imul.obj rand.obj \
alrsh.obj lmul.obj rindex.obj strrchr.obj sbrk.obj \
shar.obj shll.obj shlr.obj strcat.obj strcmp.obj \
strcpy.obj strlen.obj stricmp.obj strncat.obj \
strncmp.obj strnicmp.obj strncpy.obj csv.obj rcsv.obj tolower.obj \
toupper.obj xtoi.obj newfsiz.obj mktime.obj \
)

# List of object files for libf.lib
FOBJS = $(patsubst %,$(OBJ_DIR)/%, \
printf.obj fprintf.obj sprintf.obj scanf.obj fscanf.obj sscanf.obj fdoprnt.obj \
fdoscan.obj atof.obj fnum.obj fbcd.obj tan.obj acos.obj asin.obj atan2.obj atan.obj \
cos.obj sin.obj sinh.obj cosh.obj tanh.obj exp.obj log.obj evalpoly.obj sqrt.obj \
frexp.obj fabs.obj ceil.obj floor.obj finc.obj asfloat.obj frndint.obj ftol.obj \
ltof.obj float.obj \
)

# List of object files for libovr.lib
OVROBJS = $(patsubst %,$(OBJ_DIR)/%, ovrload.obj ovrbgn.obj)
CRTOBJS = $(patsubst %,$(OBJ_DIR)/%, crtcpm.obj wcr.obj)
ZCRTOBJS = $(patsubst %,$(OBJ_DIR)/%, zcrtcpm.obj zrrtcpm.obj)

LIBS = $(patsubst %,$(LIB_DIR)/%, libc.lib libovr.lib libf.lib)

# Build libraries
$(LIB_DIR)/libc.lib: $(COBJS) | $(DIRS)
	$(info Building libc.lib)
	$(LIBR) r $@ $(COBJS)

$(LIB_DIR)/libf.lib: $(FOBJS) | $(DIRS)
	$(info Building libf.lib)
	$(LIBR) r $@ $(FOBJS)

$(LIB_DIR)/libovr.lib: $(OVROBJS) | $(DIRS)
	$(info Building libovr.lib)
	$(LIBR) r $@ $(OVROBJS)

# CRT objects
$(OBJ_DIR)/zcrtcpm.obj: $(ARCH_DIR)/zcrtcpm.as | $(DIRS)
	$(info Assembling $< to $@)
	$(ZAS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/wcr.obj: $(ARCH_DIR)/wcr.as | $(DIRS)
	$(info Assembling $< to $@)
	$(ZAS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/zrrtcpm.obj: $(ARCH_DIR)/zrrtcpm.as | $(DIRS)
	$(info Assembling $< to $@)
	$(ZAS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/crtcpm.obj: $(OBJ_DIR)/zcrtcpm.obj | $(DIRS)
	$(info Copying $< to $@)
	cp $< $@

$(OBJ_DIR)/rrtcpm.obj: $(OBJ_DIR)/zrrtcpm.obj | $(DIRS)
	$(info Copying $< to $@)
	cp $< $@

# Main target
all: build-tools $(LIBS) $(CRTOBJS) $(ZCRTOBJS)

# Clean targets
clean:
	$(info Cleaning object and temporary files)
	rm -rf $(OBJ_DIR)/*.obj $(TMP_DIR)/* $(BIN_DIR)/*

distclean: clean
	$(info Cleaning binary files)
	rm -rf $(BIN_DIR)/*

.PHONY: all clean distclean build-tools
