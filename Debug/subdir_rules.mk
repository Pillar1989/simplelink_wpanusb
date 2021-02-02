################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/baozhu/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDeviceFamily_CC13X2 -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc" -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc/Debug" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/source" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/source/ti/posix/gcc" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include/newlib-nano" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include" -I"/home/baozhu/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1018650447: ../rfEasyLinkWpan.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/home/baozhu/ti/sysconfig_1.7.0/sysconfig_cli.sh" -s "/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/.metadata/product.json" -s "/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/.metadata/product.json" -o "syscfg" --compiler gcc "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_devices_config.c: build-1018650447 ../rfEasyLinkWpan.syscfg
syscfg/ti_radio_config.c: build-1018650447
syscfg/ti_radio_config.h: build-1018650447
syscfg/ti_drivers_config.c: build-1018650447
syscfg/ti_drivers_config.h: build-1018650447
syscfg/ti_utils_build_linker.cmd.genlibs: build-1018650447
syscfg/syscfg_c.rov.xs: build-1018650447
syscfg/ti_utils_runtime_model.gv: build-1018650447
syscfg/ti_utils_runtime_Makefile: build-1018650447
syscfg/: build-1018650447

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/baozhu/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDeviceFamily_CC13X2 -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc" -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc/Debug" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/source" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/source/ti/posix/gcc" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include/newlib-nano" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include" -I"/home/baozhu/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


