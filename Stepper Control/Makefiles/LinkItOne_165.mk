#
# embedXcode
# ----------------------------------
# Embedded Computing on Xcode
#
# Copyright © Rei VILO, 2010-2016
# http://embedxcode.weebly.com
# All rights reserved
#
#
# Last update: Jan 16, 2016 release 4.1.7


include $(MAKEFILE_PATH)/About.mk

# LinkIt One specifics
# ----------------------------------
#
PLATFORM         := linkitone
PLATFORM_TAG      = ARDUINO=10601 ARDUINO_ARCH_MTK EMBEDXCODE=$(RELEASE_NOW) __LINKIT_ONE__ LINKIT
APPLICATION_PATH := $(LINKIT_PATH)
PLATFORM_VERSION := $(LINKIT_ONE_RELEASE) for Arduino $(ARDUINO_CC_RELEASE)

HARDWARE_PATH     = $(APPLICATION_PATH)/hardware/arm/$(LINKIT_ONE_RELEASE)
TOOL_CHAIN_PATH   = $(APPLICATION_PATH)/tools/arm-none-eabi-gcc/4.8.3-2014q1
OTHER_TOOLS_PATH  = $(APPLICATION_PATH)/tools/linkit_tools/$(LINKIT_ONE_RELEASE)

BOARDS_TXT      := $(HARDWARE_PATH)/boards.txt
BUILD_CORE       = $(call PARSE_BOARD,$(BOARD_TAG),build.core)
BUILD_BOARD      = ARDUINO_$(call PARSE_BOARD,$(BOARD_TAG),build.board)

ESP_POST_COMPILE   = $(OTHER_TOOLS_PATH)/PackTag
#BOOTLOADER_ELF     = $(APPLICATION_PATH)/hardware/esp8266com/esp8266/bootloaders/eboot/eboot.elf
BUILD_FLASH_SIZE   = $(call PARSE_BOARD,$(BOARD_TAG),build.maximum_size)
BUILD_FLASH_FREQ   = $(call PARSE_BOARD,$(BOARD_TAG),build.f_cpu)


#ifeq ($(UPLOADER),esptool.py)
#    UPLOADER_PATH       = $(APPLICATION_PATH)/hardware/tools/esp8266
#    UPLOADER_EXEC       = $(UPLOADER_PATH)/esptool.py
#    UPLOADER_OPTS       = --baud $(call PARSE_BOARD,$(BOARD_TAG),upload.speed)
#else
    UPLOADER            = PushTool
    UPLOADER_PATH       = $(OTHER_TOOLS_PATH)
    UPLOADER_EXEC       = $(UPLOADER_PATH)/PushTool
    UPLOADER_OPTS       = -d arduino
#endif

APP_TOOLS_PATH      := $(TOOL_CHAIN_PATH)/bin
CORE_LIB_PATH       := $(HARDWARE_PATH)/cores/arduino

#BUILD_CORE_LIB_PATH  = $(APPLICATION_PATH)/hardware/panstamp/avr/cores/panstamp
#BUILD_CORE_LIBS_LIST = $(subst .h,,$(subst $(BUILD_CORE_LIB_PATH)/,,$(wildcard $(BUILD_CORE_LIB_PATH)/*.h))) # */
#BUILD_CORE_C_SRCS    = $(wildcard $(BUILD_CORE_LIB_PATH)/*.c) # */

#BUILD_CORE_CPP_SRCS  = $(filter-out %program.cpp %main.cpp,$(wildcard $(BUILD_CORE_LIB_PATH)/*.cpp)) # */

#BUILD_CORE_OBJ_FILES = $(BUILD_CORE_C_SRCS:.c=.c.o) $(BUILD_CORE_CPP_SRCS:.cpp=.cpp.o)
#BUILD_CORE_OBJS      = $(patsubst $(BUILD_CORE_LIB_PATH)/%,$(OBJDIR)/%,$(BUILD_CORE_OBJ_FILES))


# Take assembler file as first
#
APP_LIB_PATH        := $(HARDWARE_PATH)/libraries
CORE_AS_SRCS         = $(wildcard $(CORE_LIB_PATH)/*.S) # */
#esp001               = $(patsubst %.S,%.S.o,$(filter %S, $(CORE_AS_SRCS)))
#FIRST_O_IN_A         = $(patsubst $(APPLICATION_PATH)/%,$(OBJDIR)/%,syscalls_mtk.c.o)
#FIRST_O_IN_A     = $(filter %/$(esp001),$(BUILD_CORE_OBJS))
FIRST_O_IN_A         = $$(find . -name syscalls_mtk.c.o)

#BUILD_APP_LIB_PATH  := $(APPLICATION_PATH)/hardware/panstamp/avr/libraries

#ifndef APP_LIBS_LIST
#    ps01             = $(realpath $(sort $(dir $(wildcard $(APP_LIB_PATH)/*/*.h $(APP_LIB_PATH)/*/*/*.h $(APP_LIB_PATH)/*/*/*/*.h)))) # */
#    APP_LIBS_LIST    = $(subst $(APP_LIB_PATH)/,,$(filter-out $(EXCLUDE_LIST),$(ps01)))

#    ps02             = $(realpath $(sort $(dir $(wildcard $(BUILD_APP_LIB_PATH)/*/*.h $(BUILD_APP_LIB_PATH)/*/*/*.h $(BUILD_APP_LIB_PATH)/*/*/*/*.h)))) # */
#    BUILD_APP_LIBS_LIST = $(subst $(BUILD_APP_LIB_PATH)/,,$(filter-out $(EXCLUDE_LIST),$(ps02)))
#else
#    ps01              = $(patsubst %,$(BUILD_APP_LIB_PATH)/%,$(APP_LIBS_LIST))
#    ps02             += $(realpath $(sort $(dir $(foreach dir,$(ps01),$(wildcard $(dir)/*.h $(dir)/*/*.h $(dir)/*/*/*.h))))) # */
#    BUILD_APP_LIBS_LIST = $(subst $(BUILD_APP_LIB_PATH)/,,$(filter-out $(EXCLUDE_LIST),$(ps02)))
#endif
#
#ifneq ($(APP_LIBS_LIST),0)
#    ps04              = $(patsubst %,$(APP_LIB_PATH)/%,$(APP_LIBS_LIST))
#    ps04             += $(patsubst %,$(APP_LIB_PATH)/%/$(BUILD_CORE),$(APP_LIBS_LIST))
#    APP_LIBS        = $(realpath $(sort $(dir $(foreach dir,$(ps04),$(wildcard $(dir)/*.h $(dir)/*/*.h $(dir)/*/*/*.h))))) # */

#    APP_LIB_CPP_SRC = $(realpath $(sort $(foreach dir,$(APP_LIBS),$(wildcard $(dir)/*.cpp $(dir)/*/*.cpp $(dir)/*/*/*.cpp))))
#    APP_LIB_C_SRC   = $(realpath $(sort $(foreach dir,$(APP_LIBS),$(wildcard $(dir)/*.c $(dir)/*/*.c $(dir)/*/*/*.c))))

#    APP_LIB_OBJS    = $(patsubst $(APP_LIB_PATH)/%.cpp,$(OBJDIR)/libs/%.cpp.o,$(APP_LIB_CPP_SRC))
#    APP_LIB_OBJS   += $(patsubst $(APP_LIB_PATH)/%.c,$(OBJDIR)/libs/%.c.o,$(APP_LIB_C_SRC))

#    BUILD_APP_LIBS        = $(patsubst %,$(BUILD_APP_LIB_PATH)/%,$(BUILD_APP_LIBS_LIST))

#    BUILD_APP_LIB_CPP_SRC = $(wildcard $(patsubst %,%/*.cpp,$(BUILD_APP_LIBS))) # */
#    BUILD_APP_LIB_C_SRC   = $(wildcard $(patsubst %,%/*.c,$(BUILD_APP_LIBS))) # */

#    BUILD_APP_LIB_OBJS    = $(patsubst $(BUILD_APP_LIB_PATH)/%.cpp,$(OBJDIR)/libs/%.cpp.o,$(BUILD_APP_LIB_CPP_SRC))
#    BUILD_APP_LIB_OBJS   += $(patsubst $(BUILD_APP_LIB_PATH)/%.c,$(OBJDIR)/libs/%.c.o,$(BUILD_APP_LIB_C_SRC))
#endif


# IDE version management, based on the SDK version
#
#$(eval SDK_VERSION = $(shell cat $(UPLOADER_PATH)/sdk/version))
#ifeq ($(SDK_VERSION),1.0.0)
#    BOARD_TAG      := generic
#    L_FLAGS         = -lm -lgcc -lhal -lphy -lnet80211 -llwip -lwpa -lmain -lpp -lsmartconfig
#    ADDRESS_BIN1     = 00000
#    ADDRESS_BIN2    = 40000
#else
# For ESP8266 1.6.1
#    L_FLAGS         = -lm -lc -lgcc -lhal -lphy -lnet80211 -llwip -lwpa -lmain -lpp -lsmartconfig
#    ADDRESS_BIN2    = 10000
#endif


# Sketchbook/Libraries path
# wildcard required for ~ management
# ?ibraries required for libraries and Libraries
#
ifeq ($(USER_LIBRARY_DIR)/Arduino15/preferences.txt,)
    $(error Error: run Arduino or panStamp once and define the sketchbook path)
endif

ifeq ($(wildcard $(SKETCHBOOK_DIR)),)
    SKETCHBOOK_DIR = $(shell grep sketchbook.path $(wildcard ~/Library/Arduino15/preferences.txt) | cut -d = -f 2)
endif

ifeq ($(wildcard $(SKETCHBOOK_DIR)),)
    $(error Error: sketchbook path not found)
endif

USER_LIB_PATH  = $(wildcard $(SKETCHBOOK_DIR)/?ibraries)

VARIANT      = $(call PARSE_BOARD,$(BOARD_TAG),build.variant)
VARIANT_PATH = $(HARDWARE_PATH)/variants/$(VARIANT)

VARIANT_CPP_SRCS  = $(wildcard $(VARIANT_PATH)/*.cpp) # */
VARIANT_OBJ_FILES = $(VARIANT_CPP_SRCS:.cpp=.cpp.o)
VARIANT_OBJS      = $(patsubst $(APPLICATION_PATH)/%,$(OBJDIR)/%,$(VARIANT_OBJ_FILES))

# Rules for making a c++ file from the main sketch (.pde)
#
PDEHEADER      = \\\#include \"WProgram.h\"  


# Tool-chain names
#
CC      = $(APP_TOOLS_PATH)/arm-none-eabi-gcc
CXX     = $(APP_TOOLS_PATH)/arm-none-eabi-g++
AR      = $(APP_TOOLS_PATH)/arm-none-eabi-ar
OBJDUMP = $(APP_TOOLS_PATH)/arm-none-eabi-objdump
# /Applications/LinkIT.app/Contents/Java/hardware/tools/mtk/PackTag
OBJCOPY = $(ESP_POST_COMPILE)
SIZE    = $(APP_TOOLS_PATH)/arm-none-eabi-size
NM      = $(APP_TOOLS_PATH)/arm-none-eabi-nm

MCU_FLAG_NAME    = mcpu
MCU              = $(call PARSE_BOARD,$(BOARD_TAG),build.mcu)
F_CPU            = $(call PARSE_BOARD,$(BOARD_TAG),build.f_cpu)
OPTIMISATION     = -Os

INCLUDE_PATH     = $(HARDWARE_PATH)/system/libmtk
INCLUDE_PATH    += $(HARDWARE_PATH)/system/libmtk/include
INCLUDE_PATH    += $(CORE_LIB_PATH)
INCLUDE_PATH    += $(VARIANT_PATH)

# /Applications/IDE/LinkIT.app/Contents/Java/hardware/arduino/mtk/variants/linkit_one/libmtk.a
CORE_A   = $(VARIANT_PATH)/$(call PARSE_BOARD,$(BOARD_TAG),build.variant_system_lib)

# USB PID VID
#
USB_VID     := $(call PARSE_BOARD,$(BOARD_TAG),build.vid)
USB_PID     := $(call PARSE_BOARD,$(BOARD_TAG),build.pid)
USB_PRODUCT := $(call PARSE_BOARD,$(BOARD_TAG),build.usb_product)

USB_FLAGS    = -DUSB_VID=$(USB_VID)
USB_FLAGS   += -DUSB_PID=$(USB_PID)
USB_FLAGS   += -DUSBCON
USB_FLAGS   += -DUSB_MANUFACTURER='Unknown'
USB_FLAGS   += -DUSB_PRODUCT='$(USB_PRODUCT)'

# ~
ifeq ($(MAKECMDGOALS),debug)
    OPTIMISATION   = -O0 -g
else
    OPTIMISATION   = -Os
endif
# ~~


# Flags for gcc, g++ and linker
# ----------------------------------
#
# Common CPPFLAGS for gcc, g++, assembler and linker
#
CPPFLAGS     = -g $(OPTIMISATION) $(WARNING_FLAGS)
CPPFLAGS    += -fvisibility=hidden -fpic -mlittle-endian -nostdlib
# Solution 1
# $(call PARSE_BOARD,$(BOARD_TAG),build.extra_flags)
# -D__COMPILER_GCC__ -D__LINKIT_ONE__ -D__LINKIT_ONE_RELEASE__ -mthumb {build.usb_flags}
#CPPFLAGS    += $(addprefix -D, printf=iprintf __LINKIT_ONE_RELEASE__ __COMPILER_GCC__ ARDUINO_MTK_ONE)
#CPPFLAGS    += $(addprefix -D, printf=iprintf ARDUINO_MTK_ONE) $(lko02)
# Solution 2
CPPFLAGS    += $(addprefix -D, printf=iprintf __LINKIT_ONE_RELEASE__ __COMPILER_GCC__ ARDUINO_MTK_ONE)
#CPPFLAGS    += $(USB_FLAGS)
CPPFLAGS    += -$(MCU_FLAG_NAME)=$(MCU) -DF_CPU=$(F_CPU)
CPPFLAGS    += $(addprefix -D, $(PLATFORM_TAG) $(BUILD_BOARD))
CPPFLAGS    += $(addprefix -I, $(INCLUDE_PATH))



# Specific CFLAGS for gcc only
# gcc uses CPPFLAGS and CFLAGS
#
CFLAGS       = -mthumb
# was -std=c99

# Specific CXXFLAGS for g++ only
# g++ uses CPPFLAGS and CXXFLAGS
#
CXXFLAGS     = -mthumb -fno-non-call-exceptions -fno-rtti -fno-exceptions

# Specific ASFLAGS for gcc assembler only
# gcc assembler uses CPPFLAGS and ASFLAGS
#
ASFLAGS      = -x assembler-with-cpp

# Specific LDFLAGS for linker only
# linker uses CPPFLAGS and LDFLAGS
#
LDFLAGS      = $(OPTIMISATION) $(WARNING_FLAGS)
# -Wl,--gc-sections
# -mcpu=arm7tdmi-s -T/Applications/IDE/LinkIT.app/Contents/Java/hardware/arduino/mtk/variants/linkit_one/linker_scripts/gcc/scat.ld
# -Wl,-Map,Builds/Battery.cpp.map
# -o Builds/Battery.cpp.elf
# -LBuilds -lm -fpic -pie
# -Wl,--entry=gcc_entry -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-unresolved-symbols
# -Wl,--start-group
# Builds/syscalls_mtk.c.o Builds/Battery.cpp.o Builds/LBattery/LBattery.cpp.o Builds/LBattery/utility/Battery.cpp.o Builds/variant.cpp.o /Applications/IDE/LinkIT.app/Contents/Java/hardware/arduino/mtk/variants/linkit_one/libmtk.a Builds/core.a
# -Wl,--end-group
#-Wl,--gc-sections
LDFLAGS     += -$(MCU_FLAG_NAME)=$(MCU) -DF_CPU=$(F_CPU)
# -T/Applications/IDE/LinkIT.app/Contents/Java/hardware/arduino/mtk/variants/linkit_one/linker_scripts/gcc/scat.ld
# linkit_one.build.ldscript=linker_scripts/gcc/scat.ld
LDFLAGS     += -T $(VARIANT_PATH)/$(call PARSE_BOARD,$(BOARD_TAG),build.ldscript)

LDFLAGS     += -Wl,--gc-sections -Wl,--entry=gcc_entry -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-unresolved-symbols
#LDFLAGS     += -L$(APPLICATION_PATH)/hardware/esp8266com/esp8266/tools/sdk/lib
#LDFLAGS     += -L$(APPLICATION_PATH)/hardware/esp8266com/esp8266/tools/sdk/ld
#LDFLAGS     += -Wl,-wrap,system_restart_local


# Specific OBJCOPYFLAGS for objcopy only
# objcopy uses OBJCOPYFLAGS only
#
OBJCOPYFLAGS  = $(call PARSE_BOARD,$(BOARD_TAG),build.flash_mode)

# Target
#
TARGET_HEXBIN = $(TARGET_VXP)


# Commands
# ----------------------------------
# Link command
#
COMMAND_LINK    = $(CXX) $(LDFLAGS) $(OUT_PREPOSITION)$@ -Wl,--start-group $(LOCAL_OBJS) $(CORE_A) $(TARGET_A) -Wl,--end-group -LBuilds -lm -fpic -pie

# Upload command
#
COMMAND_UPLOAD  = $(UPLOADER_EXEC) $(UPLOADER_OPTS) -b $(USED_SERIAL_PORT) -p $(TARGET_VXP)
