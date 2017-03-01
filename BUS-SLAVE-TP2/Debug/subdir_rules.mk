################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/CodeComposer/ccsv6/tools/compiler/ti-cgt-msp430_15.12.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="D:/CodeComposer/ccsv6/ccs_base/msp430/include" --include_path="D:/CodeComposer/ccsv6/tools/compiler/ti-cgt-msp430_15.12.4.LTS/include" --advice:power=all -g --define=__MSP430G2231__ --display_error_number --diag_warning=225 --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


