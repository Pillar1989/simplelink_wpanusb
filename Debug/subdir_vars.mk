################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../rfEasyLinkWpan.syscfg 

LDS_SRCS += \
../cc13x2_cc26x2_tirtos.lds 

C_SRCS += \
../main_tirtos.c \
../rfEasyLinkWpan.c \
./syscfg/ti_easylink_config.c \
./syscfg/ti_devices_config.c \
./syscfg/ti_radio_config.c \
./syscfg/ti_drivers_config.c 

GEN_FILES += \
./syscfg/ti_easylink_config.c \
./syscfg/ti_devices_config.c \
./syscfg/ti_radio_config.c \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./main_tirtos.d \
./rfEasyLinkWpan.d \
./syscfg/ti_easylink_config.d \
./syscfg/ti_devices_config.d \
./syscfg/ti_radio_config.d \
./syscfg/ti_drivers_config.d 

OBJS += \
./main_tirtos.o \
./rfEasyLinkWpan.o \
./syscfg/ti_easylink_config.o \
./syscfg/ti_devices_config.o \
./syscfg/ti_radio_config.o \
./syscfg/ti_drivers_config.o 

GEN_MISC_FILES += \
./syscfg/ti_easylink_config.h \
./syscfg/ti_radio_config.h \
./syscfg/ti_drivers_config.h \
./syscfg/ti_utils_build_linker.cmd.genlibs \
./syscfg/syscfg_c.rov.xs \
./syscfg/ti_utils_runtime_model.gv \
./syscfg/ti_utils_runtime_Makefile 

GEN_MISC_DIRS__QUOTED += \
"syscfg/" 

OBJS__QUOTED += \
"main_tirtos.o" \
"rfEasyLinkWpan.o" \
"syscfg/ti_easylink_config.o" \
"syscfg/ti_devices_config.o" \
"syscfg/ti_radio_config.o" \
"syscfg/ti_drivers_config.o" 

GEN_MISC_FILES__QUOTED += \
"syscfg/ti_easylink_config.h" \
"syscfg/ti_radio_config.h" \
"syscfg/ti_drivers_config.h" \
"syscfg/ti_utils_build_linker.cmd.genlibs" \
"syscfg/syscfg_c.rov.xs" \
"syscfg/ti_utils_runtime_model.gv" \
"syscfg/ti_utils_runtime_Makefile" 

C_DEPS__QUOTED += \
"main_tirtos.d" \
"rfEasyLinkWpan.d" \
"syscfg/ti_easylink_config.d" \
"syscfg/ti_devices_config.d" \
"syscfg/ti_radio_config.d" \
"syscfg/ti_drivers_config.d" 

GEN_FILES__QUOTED += \
"syscfg/ti_easylink_config.c" \
"syscfg/ti_devices_config.c" \
"syscfg/ti_radio_config.c" \
"syscfg/ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../main_tirtos.c" \
"../rfEasyLinkWpan.c" \
"./syscfg/ti_easylink_config.c" \
"./syscfg/ti_devices_config.c" \
"./syscfg/ti_radio_config.c" \
"./syscfg/ti_drivers_config.c" 

SYSCFG_SRCS__QUOTED += \
"../rfEasyLinkWpan.syscfg" 


