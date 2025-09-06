# Root Makefile

all: libc programs tests

libc:
	$(MAKE) -C libc

programs: libc
	$(MAKE) -C programs

tests: libc
	$(MAKE) -C tests

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C programs clean
	$(MAKE) -C tests clean

.PHONY: all libc programs tests clean
