# Reusable compilation rules

# Tool paths
CPP = ../cpp/bin/cpp
P1 = ../p1/bin/p1
CGEN = ../cgen/bin/cgen
OPTIM = ../optim/bin/optim
ZAS = ../zas/bin/zas
LINK = ../link/link
LIBR = ../libr/libr
OBJTOHEX = ../objtohex/objtohex

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
