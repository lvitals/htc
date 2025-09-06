# Makefile for tests

LIBC_PATH = ../libc
LIB_DIR = $(LIBC_PATH)/lib
OBJ_DIR = .
TMP_DIR = .

include ../compile.mk



CFLAGS = -I$(LIBC_PATH)/include -DCPM -DHI_TECH_C -Dz80
ASFLAGS = -J -N -I$(LIBC_PATH)/include

LIBS = $(LIB_DIR)/libc.lib $(LIB_DIR)/libovr.lib $(LIB_DIR)/libf.lib
CRTOBJS = $(LIBC_PATH)/obj/crtcpm.obj $(LIBC_PATH)/obj/wcr.obj

TESTS = testfsiz.com testfile.com testpr.com testpwd.com testsub.com teststr.com testver.com testio.com testovr.com testbdos.com testargs.com testrel.com testhell.com testrc.com testuid.com testbios.com testview.com testftim.com

all: $(TESTS) run

run: $(TESTS)
	@echo "Running tests..."
	
	$(foreach p,$(TESTS), echo "--- Running $(p) ---"; cd ../cpm/ && ./cpm $(p); echo "")

testfile.obj: testfile.c
	$(call compile_c,$<,$@)

testfile.com: testfile.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testfile.obj $(CRTOBJS) $(LIBS)

testfsiz.obj: testfsiz.c
	$(call compile_c,$<,$@)

testfsiz.com: testfsiz.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testfsiz.obj $(CRTOBJS) $(LIBS)

testaes.com: testaes.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testaes.obj $(CRTOBJS) $(LIBS)

testaes.obj: testaes.c
	$(call compile_c,$<,$@)

testpr.com: testpr.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testpr.obj $(CRTOBJS) $(LIBS)

testpr.obj: testpr.c
	$(call compile_c,$<,$@)

testpwd.com: testpwd.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testpwd.obj $(CRTOBJS) $(LIBS)

testpwd.obj: testpwd.c
	$(call compile_c,$<,$@)

testsub.com: testsub.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testsub.obj $(CRTOBJS) $(LIBS)

testsub.obj: testsub.c
	$(call compile_c,$<,$@)

teststr.com: teststr.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ teststr.obj $(CRTOBJS) $(LIBS)

teststr.obj: teststr.c
	$(call compile_c,$<,$@)

testver.com: testver.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otver.com testver.obj $(CRTOBJS) $(LIBS)

testver.obj: testver.c
	$(call compile_c,$<,$@)

testio.com: testio.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otio.com testio.obj $(CRTOBJS) $(LIBS)

testio.obj: testio.c
	$(call compile_c,$<,$@)

testovr.com testovrx.sym: testovr.c $(LIBS) $(CRTOBJS)
	$(LINK) -dtestovrx.sym -o testovr.com testovr.obj $(LIBS) $(CRTOBJS) -lovr

testovr.obj: testovr.c
	$(call compile_c,$<,$@)

testovr2.ovr: testovr2.obj testovrx.sym
	$(LINK) -r -o$@ testovr2.obj

testovr1.ovr: testovr1.obj testovrx.sym
	$(LINK) -r -o $@ testovr1.obj

testbdos.com: testbdos.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otbdos.com testbdos.obj $(CRTOBJS) $(LIBS)

testbdos.obj: testbdos.c
	$(call compile_c,$<,$@)


testargs.com: testargs.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otargs.com testargs.obj $(CRTOBJS) $(LIBS)

testargs.obj: testargs.c
	$(call compile_c,$<,$@)


testrel.com: testrel.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otrel.com testrel.obj $(CRTOBJS) $(LIBS)

testrel.obj: testrel.c
	$(call compile_c,$<,$@)


testhell.com: testhell.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -othell.com testhell.obj $(CRTOBJS) $(LIBS)

testhell.obj: testhell.c
	$(call compile_c,$<,$@)


testrc.com: testrc.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otrc.com testrc.obj $(CRTOBJS) $(LIBS)

testrc.obj: testrc.c
	$(call compile_c,$<,$@)


testuid.com: testuid.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otuid.com testuid.obj $(CRTOBJS) $(LIBS)

testuid.obj: testuid.c
	$(call compile_c,$<,$@)


testbios.com: testbios.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otbios.com testbios.obj $(CRTOBJS) $(LIBS)

testbios.obj: testbios.c
	$(call compile_c,$<,$@)


testtrig.com: testtrig.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -ottrig.com testtrig.obj $(CRTOBJS) $(LIBS) $(LIB_DIR)/libf.lib

testtrig.obj: testtrig.c
	$(call compile_c,$<,$@)


testview.com: testview.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -otview.com testview.obj $(CRTOBJS) $(LIBS)

testview.obj: testview.c
	$(call compile_c,$<,$@)


testftim.com: testftim.obj  $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -oftim.com testftim.obj $(CRTOBJS) $(LIBS)

testftim.obj: testftim.c
	$(call compile_c,$<,$@)

.c.obj:
	$(call compile_c,$<,$@)

test: $(TESTS)
	../cpm/cpm testhell
	../cpm/cpm testver
	rm -f testio.sta testio.out testio.err
	../cpm/cpm testovr
	../cpm/cpm teststr
	../cpm/cpm testsub a b c
	../cpm/cpm testtrig
	../cpm/cpm testftim
	../cpm/cpm testbdos
	../cpm/cpm testfile
	../cpm/cpm testaes
	../cpm/cpm testuid
	../cpm/cpm testrc || echo testrc=$?
	../cpm/cpm testargs -*.i
	../cpm/cpm testfsiz
	../cpm/cpm testpr
	../cpm/cpm testpwd
	../cpm/cpm testview test.sub

clean:
	rm -f *.com *.sym *.ovr *.obj testio.sta testio.out testio.err *.i *.p1 *.cgen *.



































