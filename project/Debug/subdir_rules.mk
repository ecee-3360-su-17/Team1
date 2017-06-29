################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
EK_TM4C1294XL.obj: ../EK_TM4C1294XL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/dannylangevin/Desktop/School/Senior/Digital Design Lab/Team1/project" --include_path="/Users/dannylangevin/Desktop/School/Senior/Digital Design Lab/Team1/project" --include_path="/Applications/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="/Applications/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="EK_TM4C1294XL.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

empty.obj: ../empty.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/dannylangevin/Desktop/School/Senior/Digital Design Lab/Team1/project" --include_path="/Users/dannylangevin/Desktop/School/Senior/Digital Design Lab/Team1/project" --include_path="/Applications/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="/Applications/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="empty.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

build-309025937:
	@$(MAKE) -Onone -f subdir_rules.mk build-309025937-inproc

build-309025937-inproc: ../empty.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"/Applications/ti/xdctools_3_32_00_06_core/xs" --xdcpath="/Applications/ti/tirtos_tivac_2_16_00_08/packages;/Applications/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages;/Applications/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages;/Applications/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages;/Applications/ti/tirtos_tivac_2_16_00_08/products/uia_2_00_05_50/packages;/Applications/ti/tirtos_tivac_2_16_00_08/products/ns_1_11_00_10/packages;/Applications/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TM4C1294NCPDT -r release -c "/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path=\"/Users/dannylangevin/Desktop/School/Senior/Digital Design Lab/Team1/project\" --include_path=\"/Users/dannylangevin/Desktop/School/Senior/Digital Design Lab/Team1/project\" --include_path=\"/Applications/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b\" --include_path=\"/Applications/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix\" --include_path=\"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include\" --define=ccs=\"ccs\" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: build-309025937 ../empty.cfg
configPkg/compiler.opt: build-309025937
configPkg/: build-309025937


