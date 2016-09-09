################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DSP2803x_Gpio.obj: ../DSP2803x_Gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/tools/ti/ccsv6.1/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -O2 --include_path="D:/tools/ti/ccsv6.1/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="E:/DRV8301/user/include" --include_path="E:/DRV8301/common/include" --include_path="E:/DRV8301/dmclib/mathlib" --include_path="E:/DRV8301/dmclib/drvlib" --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="DSP2803x_Gpio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/tools/ti/ccsv6.1/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -O2 --include_path="D:/tools/ti/ccsv6.1/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="E:/DRV8301/user/include" --include_path="E:/DRV8301/common/include" --include_path="E:/DRV8301/dmclib/mathlib" --include_path="E:/DRV8301/dmclib/drvlib" --define=FLASH --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


