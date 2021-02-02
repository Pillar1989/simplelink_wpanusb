################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
wpanusb/%.o: ../wpanusb/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/home/baozhu/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DDeviceFamily_CC13X2 -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc" -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc/Debug" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/source" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/source/ti/posix/gcc" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include/newlib-nano" -I"/home/baozhu/ti/simplelink_cc13x2_26x2_sdk_4_40_00_44/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include" -I"/home/baozhu/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -I"/home/baozhu/ti/workspace_v11/rfEasyLinkWpan_CC1352P_2_LAUNCHXL_tirtos_gcc/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


