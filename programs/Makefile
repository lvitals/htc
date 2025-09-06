# Makefile for programs

LIBC_PATH = ../libc
LIB_DIR = $(LIBC_PATH)/lib
OBJ_DIR = .
BIN_DIR = .
TMP_DIR = .

include ../compile.mk

CFLAGS = -I./include -I$(LIBC_PATH)/include -DCPM -DHI_TECH_C -Dz80
ASFLAGS = -J -N -I./include -I$(LIBC_PATH)/include

LIBS = $(LIB_DIR)/libc.lib $(LIB_DIR)/libovr.lib $(LIB_DIR)/libf.lib
CRTOBJS = $(LIBC_PATH)/obj/crtcpm.obj $(LIBC_PATH)/obj/wcr.obj

all: symtoas.com c.com enhuff.com dehuff.com

$exec.com: exec.obj
	$(LINK) -l -ptext=0,bss exec.obj $(LIB_DIR)/libc.lib
	$(OBJTOHEX) l.obj exec.com
	mv exec.com '$exec.com'
	-rm l.obj

symtoas.com: symtoas.obj $(LIBS) $(CRTOBJS) c.com
	$(LINK) -osymtoas.com symtoas.obj $(CRTOBJS) $(LIBS)

c.com: ec.obj $(LIBS) $(CRTOBJS) $exec.com
	$(LINK) -z -Ptext=0,data,bss -C100h -oc.com $(CRTOBJS) ec.obj $(LIBS)

enhuff.com: enhuff.obj encode.obj hmisc.obj $(LIBS) c.com $(CRTOBJS)
	$(LINK) -oenhuff.com enhuff.obj encode.obj hmisc.obj $(LIBS) $(CRTOBJS)

dehuff.com: dehuff.obj decode.obj hmisc.obj $(LIBS) c.com $(CRTOBJS)
	$(LINK) -odehuff.com dehuff.obj decode.obj hmisc.obj $(LIBS) $(CRTOBJS)

%.obj: %.as
	$(ZAS) $(ASFLAGS) $< -o $@

%.obj: %.c
	$(call compile_c,$<,$@)

clean:
	rm -f *.com *.obj l.obj '$exec.com' *.i *.p1 *.sym *.cgen *.optim
