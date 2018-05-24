################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
AFE4400/AFE44x0.obj: C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release/AFE4400/AFE44x0.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.7/bin/cl430" -vmspx --abi=eabi --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.2.7/include" --include_path="C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release" --include_path="C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release/HAL" --include_path="C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release/AFE4400" --include_path="C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release/USB/USB_config" --include_path="C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release/USB/USB_User" --include_path="C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release/USB/USB_API/USB_CDC_API" --include_path="C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release/USB/USB_API/USB_Common" --include_path="C:/Users/a0273681/Documents/Aroul/Projects/Others/F5529/MSP430F5529__Projects/AFE4400-AFE4490EVM_FW_SRC/AFE4400EVM_FW_SRC_v1.4_Release/USB/USB_API/USB_HID_API" --advice:power=all -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="AFE4400/AFE44x0.pp" --obj_directory="AFE4400" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


