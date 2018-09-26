# Makefile (adapted from Taulabs project)
.DEFAULT_GOAL := help

WHEREAMI := $(dir $(lastword $(MAKEFILE_LIST)))
ROOT_DIR := $(realpath $(WHEREAMI)/ )

# configure some directories that are relative to wherever ROOT_DIR is located
BUILD_DIR := $(ROOT_DIR)/build

export RM := rm
export CCACHE_BIN := $(shell which ccache 2>/dev/null)

# make sure this isn't being run as root, not relevant for windows
ifndef WINDOWS
  # Deal with unreasonable requests
  # See: http://xkcd.com/149/
  ifeq ($(MAKECMDGOALS),me a sandwich)
    ifeq ($(shell whoami),root)
      $(error Okay)
    else
      $(error What? Make it yourself)
    endif
  endif

  # Seriously though, you shouldn't ever run this as root
  ifeq ($(shell whoami),root)
    $(error You should not be running this as root)
  endif
endif

# Function for converting an absolute path to one relative
# to the top of the source tree.
toprel = $(subst $(realpath $(ROOT_DIR))/,,$(abspath $(1)))

# Clean out undesirable variables from the environment and command-line
# to remove the chance that they will cause problems with our build
define SANITIZE_VAR
$(if $(filter-out undefined,$(origin $(1))),
  $(info *NOTE*      Sanitized $(2) variable '$(1)' from $(origin $(1)))
  MAKEOVERRIDES = $(filter-out $(1)=%,$(MAKEOVERRIDES))
  override $(1) :=
  unexport $(1)
)
endef

# These specific variables can influence gcc in unexpected (and undesirable) ways
SANITIZE_GCC_VARS := TMPDIR GCC_EXEC_PREFIX COMPILER_PATH LIBRARY_PATH
SANITIZE_GCC_VARS += CFLAGS CPATH C_INCLUDE_PATH CPLUS_INCLUDE_PATH OBJC_INCLUDE_PATH DEPENDENCIES_OUTPUT
SANITIZE_GCC_VARS += ARCHFLAGS
$(foreach var, $(SANITIZE_GCC_VARS), $(eval $(call SANITIZE_VAR,$(var),disallowed)))

# These specific variables used to be valid but now they make no sense
SANITIZE_DEPRECATED_VARS := USE_BOOTLOADER
$(foreach var, $(SANITIZE_DEPRECATED_VARS), $(eval $(call SANITIZE_VAR,$(var),deprecated)))

# Decide on a verbosity level based on the V= parameter
export AT := @

ifndef V
export V0    :=
export V1    := $(AT)
else ifeq ($(V), 0)
export V0    := $(AT)
export V1    := $(AT)
else ifeq ($(V), 1)
endif

ALL_BOARDS :=
include $(ROOT_DIR)/src/targets/*/target-defs.mk

# And the flight build configuration (debug | default | release)
export FW_BUILD_CONF ?= default

##############################
#
# Check that environmental variables are sane
#
##############################

# Checking for $(FW_BUILD_CONF) to be sane
ifdef FW_BUILD_CONF
 ifneq ($(FW_BUILD_CONF), release)
  ifneq ($(FW_BUILD_CONF), debug)
   ifneq ($(FW_BUILD_CONF), default)
    $(error Only debug or release are allowed for FW_BUILD_CONF)
   endif
  endif
 endif
endif

.PHONY: all
all: all_ground all_flight

.PHONY: all_clean
all_clean:
	[ ! -d "$(BUILD_DIR)" ] || $(RM) -r "$(BUILD_DIR)"

$(TOOLS_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

##############################
#
# Flight related components
#
##############################

# Define some pointers to the various important pieces of the flight code
# to prevent these being repeated in every sub makefile
MAKE_INC_DIR  := $(ROOT_DIR)/make
SRC_ROOT_DIR  := $(ROOT_DIR)/src
COMMONLIB_DIR := $(SRC_ROOT_DIR)/libraries
OPMODULEDIR   := $(SRC_ROOT_DIR)/modules

# $(1) = Canonical board name all in lower case (e.g. coptercontrol)
# $(2) = Unused
# $(3) = Short name for board (e.g CC)
define FW_TEMPLATE
.PHONY: $(1) 
# $(1): $(1)_build
$(1): TARGET=fw_$(1)
$(1): OUTDIR=$(BUILD_DIR)/$$(TARGET)
$(1): BOARD_ROOT_DIR=$(ROOT_DIR)/src/targets/$(1)
$(1): 
	$(V1) mkdir -p $$(OUTDIR)/dep
	$(V1) cd $$(BOARD_ROOT_DIR)/firmware && \
		$$(MAKE) -r --no-print-directory \
		BOARD_NAME=$(1) \
		BOARD_SHORT_NAME=$(3) \
		BUILD_TYPE=fw \
		TCHAIN_PREFIX=arm-none-eabi- \
		REMOVE_CMD="$(RM)" OOCD_EXE="$(OPENOCD)" \
		\
		MAKE_INC_DIR=$(MAKE_INC_DIR) \
		ROOT_DIR=$(ROOT_DIR) \
		SRC_ROOT_DIR=$(SRC_ROOT_DIR) \
		COMMONLIB_DIR=$(COMMONLIB_DIR) \
		OPMODULEDIR=$(OPMODULEDIR) \
		BOARD_ROOT_DIR=$$(BOARD_ROOT_DIR) \
		TARGET=$$(TARGET) \
		OUTDIR=$$(OUTDIR) \
		\
		$$*

.PHONY: $(1)_clean
$(1)_clean: TARGET=fw_$(1)
$(1)_clean: OUTDIR=$(BUILD_DIR)/$$(TARGET)
$(1)_clean:
	$(V0) @echo " CLEAN      $$@"
	$(V1) [ ! -d "$$(OUTDIR)" ] || $(RM) -r "$$(OUTDIR)"
endef

# When building any of the "all_*" targets, tell all sub makefiles to display
# additional details on each line of output to describe which build and target
# that each line applies to.
ifneq ($(strip $(filter all_%,$(MAKECMDGOALS))),)
export ENABLE_MSG_EXTRA := yes
endif
ifneq (,$(filter sim_%, $(MAKECMDGOALS)))
export ENABLE_MSG_EXTRA := yes
endif

# When building more than one goal in a single make invocation, also
# enable the extra context for each output line
ifneq ($(word 2,$(MAKECMDGOALS)),)
export ENABLE_MSG_EXTRA := yes
endif

# $(1) = Canonical board name all in lower case (e.g. coptercontrol)
define BOARD_PHONY_TEMPLATE
.PHONY: all_$(1)
all_$(1): $$(filter fw_$(1), $$(FW_TARGETS))

.PHONY: all_$(1)_clean
all_$(1)_clean: $$(addsuffix _clean, $$(filter fw_$(1), $$(FW_TARGETS)))
endef

# Start out assuming that we'll build fw all boards
FW_BOARDS  := $(ALL_BOARDS)

# Generate the targets for whatever boards are left in each list
FW_TARGETS := $(addprefix fw_, $(FW_BOARDS))

# .PHONY: all_fw all_fw_clean 
# all_fw:        $(FW_TARGETS)
# all_fw_clean:  $(addsuffix _clean, $(FW_TARGETS))

# Expand the groups of targets for each board
# $(foreach board, $(ALL_BOARDS), $(eval $(call BOARD_PHONY_TEMPLATE,$(board))))

# Expand the firmware rules
$(foreach board, $(FW_BOARDS), $(eval $(call FW_TEMPLATE,$(board),$($(board)_friendly),$($(board)_short))))
