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

TESTS = testfile.com testfsiz.com testaes.com testpr.com testpwd.com \
        testsub.com teststr.com testver.com testio.com testovr.com \
        testbdos.com testargs.com testrel.com testhell.com testrc.com \
        testuid.com testbios.com testtrig.com testview.com testftim.com

all: $(TESTS) run

run: $(TESTS)
	@echo "Running tests..."
	@for p in $(TESTS); do 
		echo "--- Running $p ---"; 
		../cpm/cpm $p; 
		echo ""; 
	done

testfile.obj: testfile.c
	$(call compile_c,$<,$@)

testfile.com: testfile.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testfile.obj $(CRTOBJS) $(LIBS)

testfsiz.com: testfsiz.obj $(LIBS) $(CRTOBJS)
	$(LINK) -o $@ testfsiz.obj $(LIBS) $(CRTOBJS)

testaes.com: testaes.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testaes.obj $(CRTOBJS) $(LIBS)

testpr.com: testpr.obj $(LIBS) $(CRTOBJS)
	$(LINK) -o $@ testpr.obj $(LIBS) $(CRTOBJS)

testpwd.com: testpwd.obj $(LIBS) $(TOOLS) $(CRTOBJS)
	$(LINK) -o $@ testpwd.obj $(CRTOBJS) $(LIBS)

testsub.com: testsub.obj $(LIBS) $(CRTOBJS)
	$(LINK) -o $@ testsub.obj $(LIBS) $(CRTOBJS)

teststr.com: teststr.obj $(LIBS) $(CRTOBJS)
	$(LINK) -o $@ teststr.obj $(CRTOBJS) $(LIBS)

testver.com: testver.obj $(LIBS) $(CRTOBJS)
	$(LINK) -otver.com testver.obj $(CRTOBJS) $(LIBS)

testio.com: testio.obj $(LIBS) $(CRTOBJS)
	$(LINK) -otio.com testio.obj $(CRTOBJS) $(LIBS)

testovr.com testovrx.sym: testovr.c $(LIBS) $(CRTOBJS)
	$(LINK) --ftestovrx.sym -o testovr.com testovr.obj $(LIBS) $(CRTOBJS) --lovr

testovr2.ovr: testovr2.obj testovrx.sym
	$(LINK) -r -o$@ testovr2.obj

testovr1.ovr: testovr1.obj testovrx.sym
	$(LINK) -r -o $@ testovr1.obj

testbdos.com: testbdos.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -otbdos.com testbdos.obj $(CRTOBJS) $(LIBS)


testargs.com: testargs.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -otargs.com testargs.obj $(CRTOBJS) $(LIBS)


testrel.com: testrel.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -A -otrel.com testrel.obj $(CRTOBJS) $(LIBS)


testhell.com: testhell.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -othell.com testhell.obj $(CRTOBJS) $(LIBS)


testrc.com: testrc.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -otrc.com testrc.obj $(CRTOBJS) $(LIBS)


testuid.com: testuid.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -otuid.com testuid.obj $(CRTOBJS) $(LIBS)


testbios.com: testbios.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -otbios.com testbios.obj $(CRTOBJS) $(LIBS)


testtrig.com: testtrig.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -ottrig.com testtrig.obj $(CRTOBJS) $(LIBS) --lf


testview.com: testview.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -otview.com testview.obj $(CRTOBJS) $(LIBS)


testftim.com: testftim.obj  $(LIBS) $(CRTOBJS)
	$(LINK) -oftim.com testftim.obj $(CRTOBJS) $(LIBS)

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



































