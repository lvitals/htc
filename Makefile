# Root Makefile

TOOL_DIRS = cpp p1 cgen optim zas link libr objtohex

all: tools libc

tools:
	@for dir in $(TOOL_DIRS); do \
		$(MAKE) -C $$dir; \
	done

libc:
	$(MAKE) -C libc

clean:
	$(MAKE) -C libc clean
	@for dir in $(TOOL_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: all tools libc clean