# Reusable compilation rules

# Tool paths
CPP = $(LIBC_PATH)/bin/cpp
P1 = $(LIBC_PATH)/bin/p1
CGEN = $(LIBC_PATH)/bin/cgen
OPTIM = $(LIBC_PATH)/bin/optim
ZAS = $(LIBC_PATH)/bin/zas
LINK = $(LIBC_PATH)/bin/link
LIBR = $(LIBC_PATH)/bin/libr
OBJTOHEX = $(LIBC_PATH)/bin/objtohex

# Compilation function for C files
define compile_c
	$(info Compiling $(1) to $(2))
	$(CPP) $(CFLAGS) $(1) $(TMP_DIR)/$(notdir $(1)).i
	$(P1) $(TMP_DIR)/$(notdir $(1)).i $(TMP_DIR)/$(notdir $(1)).p1 $(TMP_DIR)/$(notdir $(1)).sym
	$(CGEN) $(TMP_DIR)/$(notdir $(1)).p1 $(TMP_DIR)/$(notdir $(1)).cgen
	$(OPTIM) $(TMP_DIR)/$(notdir $(1)).cgen $(TMP_DIR)/$(notdir $(1)).optim
	$(ZAS) $(ASFLAGS) $(TMP_DIR)/$(notdir $(1)).optim -o $(2)
	@rm -f $(TMP_DIR)/$(notdir $(1)).i $(TMP_DIR)/$(notdir $(1)).p1 $(TMP_DIR)/$(notdir $(1)).sym $(TMP_DIR)/$(notdir $(1)).cgen $(TMP_DIR)/$(notdir $(1)).optim
endef
