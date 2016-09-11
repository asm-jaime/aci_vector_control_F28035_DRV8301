################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./PM_Sensorless.obj" \
"./PM_Sensorless-DevInit_F2803x.obj" \
"./DSP2803x_usDelay.obj" \
"./DSP2803x_GlobalVariableDefs.obj" \
"./DRV8301_SPI.obj" \
"./DLOG4CHC.obj" \
"Z:/device_support/f2803x/v124/DSP2803x_headers/cmd/DSP2803x_Headers_nonBIOS.cmd" \
"../F28035_RAM_PM_Sensorless.CMD" \
"Z:/libs/math/IQmath/v15c/lib/IQmath.lib" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: PM_Sensorless_DRV8301_F2803x.out

# Tool invocations
PM_Sensorless_DRV8301_F2803x.out: $(OBJS) $(CMD_SRCS) $(CMD_UPPER_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 -z -m"PM_Sensorless_DRV8301_F2803x.map" --stack_size=0x380 --warn_sections -i"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/lib" -i"D:/CCS5/ccsv5/tools/compiler/c2000_6.2.0/include" --reread_libs --xml_link_info="PM_Sensorless_DRV8301_F2803x_linkInfo.xml" --rom_model -o "PM_Sensorless_DRV8301_F2803x.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QUOTED) "PM_Sensorless_DRV8301_F2803x.out"
	-$(RM) "DRV8301_SPI.pp" "DSP2803x_GlobalVariableDefs.pp" "PM_Sensorless-DevInit_F2803x.pp" "PM_Sensorless.pp" 
	-$(RM) "DLOG4CHC.obj" "DRV8301_SPI.obj" "DSP2803x_GlobalVariableDefs.obj" "DSP2803x_usDelay.obj" "PM_Sensorless-DevInit_F2803x.obj" "PM_Sensorless.obj" 
	-$(RM) "DLOG4CHC.pp" "DSP2803x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

