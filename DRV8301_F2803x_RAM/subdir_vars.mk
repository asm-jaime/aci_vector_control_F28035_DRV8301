################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
Z:/device_support/f2803x/v124/DSP2803x_headers/cmd/DSP2803x_Headers_nonBIOS.cmd 

CMD_UPPER_SRCS += \
../F28035_RAM_PM_Sensorless.CMD 

LIB_SRCS += \
Z:/libs/math/IQmath/v15c/lib/IQmath.lib 

ASM_SRCS += \
../DLOG4CHC.asm \
../DSP2803x_usDelay.asm 

C_SRCS += \
../DRV8301_SPI.c \
Z:/device_support/f2803x/v124/DSP2803x_headers/source/DSP2803x_GlobalVariableDefs.c \
../PM_Sensorless-DevInit_F2803x.c \
../PM_Sensorless.c 

OBJS += \
./DLOG4CHC.obj \
./DRV8301_SPI.obj \
./DSP2803x_GlobalVariableDefs.obj \
./DSP2803x_usDelay.obj \
./PM_Sensorless-DevInit_F2803x.obj \
./PM_Sensorless.obj 

ASM_DEPS += \
./DLOG4CHC.pp \
./DSP2803x_usDelay.pp 

C_DEPS += \
./DRV8301_SPI.pp \
./DSP2803x_GlobalVariableDefs.pp \
./PM_Sensorless-DevInit_F2803x.pp \
./PM_Sensorless.pp 

C_DEPS__QUOTED += \
"DRV8301_SPI.pp" \
"DSP2803x_GlobalVariableDefs.pp" \
"PM_Sensorless-DevInit_F2803x.pp" \
"PM_Sensorless.pp" 

OBJS__QUOTED += \
"DLOG4CHC.obj" \
"DRV8301_SPI.obj" \
"DSP2803x_GlobalVariableDefs.obj" \
"DSP2803x_usDelay.obj" \
"PM_Sensorless-DevInit_F2803x.obj" \
"PM_Sensorless.obj" 

ASM_DEPS__QUOTED += \
"DLOG4CHC.pp" \
"DSP2803x_usDelay.pp" 

ASM_SRCS__QUOTED += \
"../DLOG4CHC.asm" \
"../DSP2803x_usDelay.asm" 

C_SRCS__QUOTED += \
"../DRV8301_SPI.c" \
"Z:/device_support/f2803x/v124/DSP2803x_headers/source/DSP2803x_GlobalVariableDefs.c" \
"../PM_Sensorless-DevInit_F2803x.c" \
"../PM_Sensorless.c" 


