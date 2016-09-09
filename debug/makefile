################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/tools/ti/ccsv6.1/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./DSP2803x_Gpio.obj" \
"./main.obj" \
"./SRC/DLOG4CHC.obj" \
"./SRC/DRV8301_SPI.obj" \
"./SRC/DSP2803x_CodeStartBranch.obj" \
"./SRC/DSP2803x_CpuTimers.obj" \
"./SRC/DSP2803x_DefaultIsr.obj" \
"./SRC/DSP2803x_GlobalVariableDefs.obj" \
"./SRC/DSP2803x_PieCtrl.obj" \
"./SRC/DSP2803x_PieVect.obj" \
"./SRC/DSP2803x_SysCtrl.obj" \
"./SRC/DSP2803x_TempSensorConv.obj" \
"./SRC/DSP2803x_usDelay.obj" \
"./SRC/com.obj" \
"../28035_RAM_lnk.cmd" \
"../DSP2803x_Headers_nonBIOS.cmd" \
"../IQmath.lib" \
"../SRC/IQmath.lib" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"E:\DRV8301\PMSM_SD\IQmath.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include SRC/subdir_vars.mk
-include subdir_rules.mk
-include SRC/subdir_rules.mk
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
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
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
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
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
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
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
EXE_OUTPUTS += \
PMSM_SD.out \

EXE_OUTPUTS__QUOTED += \
"PMSM_SD.out" \


# All Target
all: PMSM_SD.out

# Tool invocations
PMSM_SD.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/tools/ti/ccsv6.1/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --define=SARAM --diag_warning=225 --display_error_number -z -m"PMSM_SD.map" --stack_size=0x300 --warn_sections -i"D:/tools/ti/ccsv6.1/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/lib" -i"D:/tools/ti/ccsv6.1/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" -i"E:/DRV8301/common/include" --reread_libs --xml_link_info="PMSM_SD_linkInfo.xml" --rom_model -o "PMSM_SD.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "DSP2803x_Gpio.pp" "main.pp" "SRC\DRV8301_SPI.pp" "SRC\DSP2803x_CpuTimers.pp" "SRC\DSP2803x_DefaultIsr.pp" "SRC\DSP2803x_GlobalVariableDefs.pp" "SRC\DSP2803x_PieCtrl.pp" "SRC\DSP2803x_PieVect.pp" "SRC\DSP2803x_SysCtrl.pp" "SRC\DSP2803x_TempSensorConv.pp" "SRC\com.pp" 
	-$(RM) "DSP2803x_Gpio.obj" "main.obj" "SRC\DLOG4CHC.obj" "SRC\DRV8301_SPI.obj" "SRC\DSP2803x_CodeStartBranch.obj" "SRC\DSP2803x_CpuTimers.obj" "SRC\DSP2803x_DefaultIsr.obj" "SRC\DSP2803x_GlobalVariableDefs.obj" "SRC\DSP2803x_PieCtrl.obj" "SRC\DSP2803x_PieVect.obj" "SRC\DSP2803x_SysCtrl.obj" "SRC\DSP2803x_TempSensorConv.obj" "SRC\DSP2803x_usDelay.obj" "SRC\com.obj" 
	-$(RM) "SRC\DLOG4CHC.pp" "SRC\DSP2803x_CodeStartBranch.pp" "SRC\DSP2803x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

