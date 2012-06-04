##===- lib/Transforms/Mutation/Makefile -----------------------*- Makefile -*-===##
#
#  Marcelo Sousa <dipython@gmail.com> 
#
##===----------------------------------------------------------------------===##

LEVEL = ../../..
LIBRARYNAME = LLVMMutation
LOADABLE_MODULE = 1
#BUILD_ARCHIVE = 1

USEDLIBS =

# If we don't need RTTI or EH, there's no reason to export anything
# from the mutation plugin.
ifneq ($(REQUIRES_RTTI), 1)
ifneq ($(REQUIRES_EH), 1)
EXPORTED_SYMBOL_FILE = $(PROJ_SRC_DIR)/Mutation.exports
endif
endif

include $(LEVEL)/Makefile.common

