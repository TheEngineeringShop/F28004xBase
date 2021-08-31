################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Base.obj" \
"./BaseAdc.obj" \
"./BaseCla.obj" \
"./BaseDac.obj" \
"./BaseECap.obj" \
"./BaseEPwm.obj" \
"./BaseGpio.obj" \
"./BaseInterrupts.obj" \
"./Base_main.obj" \
"./CodeStartBranch.obj" \
"./SineTable.obj" \
"./Watchdog.obj" \
"./device.obj" \
"./f28004x_globalvariabledefs.obj" \
"../F28004xBase.cmd" \
"../f28004x_headers_nonbios.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-ldriverlib.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
F28004xBase.out \

EXE_OUTPUTS__QUOTED += \
"F28004xBase.out" \

BIN_OUTPUTS += \
F28004xBase.hex \

BIN_OUTPUTS__QUOTED += \
"F28004xBase.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "F28004xBase.out"

# Tool invocations
F28004xBase.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --advice:performance=all --define=_LAUNCHXL_F280049C --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"F28004xBase.map" --stack_size=0x200 --warn_sections -i"C:/ti/lib" -i"C:/F28004x/Labs/f28004x_driverlib/driverlib/ccs/Debug" -i"C:/ti/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="F28004xBase_linkInfo.xml" --rom_model -o "F28004xBase.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

F28004xBase.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/bin/hex2000" --diag_wrap=off -o "F28004xBase.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Base.obj" "BaseAdc.obj" "BaseCla.obj" "BaseDac.obj" "BaseECap.obj" "BaseEPwm.obj" "BaseGpio.obj" "BaseInterrupts.obj" "Base_main.obj" "CodeStartBranch.obj" "SineTable.obj" "Watchdog.obj" "device.obj" "f28004x_globalvariabledefs.obj" 
	-$(RM) "BaseAdc.d" "BaseCla.d" "BaseDac.d" "BaseECap.d" "BaseEPwm.d" "BaseGpio.d" "BaseInterrupts.d" "Base_main.d" "SineTable.d" "Watchdog.d" "device.d" "f28004x_globalvariabledefs.d" 
	-$(RM) "Base.d" 
	-$(RM) "CodeStartBranch.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

