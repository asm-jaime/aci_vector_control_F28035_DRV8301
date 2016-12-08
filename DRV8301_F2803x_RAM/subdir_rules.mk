################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DLOG4CHC.obj: ../DLOG4CHC.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/include" --include_path="Z:/libs/math/IQmath/v15c/include" --include_path="Z:/development_kits/~SupportFiles/F2803x_headers" --include_path="Z:/device_support/f2803x/v124/DSP2803x_headers/include" --include_path="Z:/device_support/f2803x/v124/DSP2803x_common/include" --include_path="Z:/libs/app_libs/motor_control/math_blocks/v3.1" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="DLOG4CHC.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DRV8301_SPI.obj: ../DRV8301_SPI.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/include" --include_path="Z:/libs/math/IQmath/v15c/include" --include_path="Z:/development_kits/~SupportFiles/F2803x_headers" --include_path="Z:/device_support/f2803x/v124/DSP2803x_headers/include" --include_path="Z:/device_support/f2803x/v124/DSP2803x_common/include" --include_path="Z:/libs/app_libs/motor_control/math_blocks/v3.1" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="DRV8301_SPI.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_GlobalVariableDefs.obj: Z:/WORKS/projects/aci_vector_control_F28035_DRV8301/libs_f2803x_v124/DSP2803x_headers/source/DSP2803x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/include" --include_path="Z:/libs/math/IQmath/v15c/include" --include_path="Z:/development_kits/~SupportFiles/F2803x_headers" --include_path="Z:/device_support/f2803x/v124/DSP2803x_headers/include" --include_path="Z:/device_support/f2803x/v124/DSP2803x_common/include" --include_path="Z:/libs/app_libs/motor_control/math_blocks/v3.1" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="DSP2803x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2803x_usDelay.obj: ../DSP2803x_usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/include" --include_path="Z:/libs/math/IQmath/v15c/include" --include_path="Z:/development_kits/~SupportFiles/F2803x_headers" --include_path="Z:/device_support/f2803x/v124/DSP2803x_headers/include" --include_path="Z:/device_support/f2803x/v124/DSP2803x_common/include" --include_path="Z:/libs/app_libs/motor_control/math_blocks/v3.1" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="DSP2803x_usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

PM_Sensorless-DevInit_F2803x.obj: ../PM_Sensorless-DevInit_F2803x.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/include" --include_path="Z:/libs/math/IQmath/v15c/include" --include_path="Z:/development_kits/~SupportFiles/F2803x_headers" --include_path="Z:/device_support/f2803x/v124/DSP2803x_headers/include" --include_path="Z:/device_support/f2803x/v124/DSP2803x_common/include" --include_path="Z:/libs/app_libs/motor_control/math_blocks/v3.1" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="PM_Sensorless-DevInit_F2803x.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

PM_Sensorless.obj: ../PM_Sensorless.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/include" --include_path="Z:/libs/math/IQmath/v15c/include" --include_path="Z:/development_kits/~SupportFiles/F2803x_headers" --include_path="Z:/device_support/f2803x/v124/DSP2803x_headers/include" --include_path="Z:/device_support/f2803x/v124/DSP2803x_common/include" --include_path="Z:/libs/app_libs/motor_control/math_blocks/v3.1" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="PM_Sensorless.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


