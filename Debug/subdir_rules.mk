################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --include_path="C:/Users/justi/workspace_v10/F28004xBase" --include_path="C:/F28004x/Labs/f28004x_headers/include" --include_path="C:/F28004x/Labs/f28004x_driverlib/driverlib" --include_path="C:/F28004x/Labs/f28004x_driverlib/driverlib/inc" --include_path="C:/F28004x/Labs/Lab_common/include" --include_path="C:/ti/include" --advice:performance=all --define=_LAUNCHXL_F280049C --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --include_path="C:/Users/justi/workspace_v10/F28004xBase" --include_path="C:/F28004x/Labs/f28004x_headers/include" --include_path="C:/F28004x/Labs/f28004x_driverlib/driverlib" --include_path="C:/F28004x/Labs/f28004x_driverlib/driverlib/inc" --include_path="C:/F28004x/Labs/Lab_common/include" --include_path="C:/ti/include" --advice:performance=all --define=_LAUNCHXL_F280049C --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --include_path="C:/Users/justi/workspace_v10/F28004xBase" --include_path="C:/F28004x/Labs/f28004x_headers/include" --include_path="C:/F28004x/Labs/f28004x_driverlib/driverlib" --include_path="C:/F28004x/Labs/f28004x_driverlib/driverlib/inc" --include_path="C:/F28004x/Labs/Lab_common/include" --include_path="C:/ti/include" --advice:performance=all --define=_LAUNCHXL_F280049C --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


