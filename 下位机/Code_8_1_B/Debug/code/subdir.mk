################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/ALL_Variables.c \
../code/Data.c \
../code/Motor.c \
../code/My_Device.c \
../code/Page.c \
../code/UART_Analysis.c 

COMPILED_SRCS += \
./code/ALL_Variables.src \
./code/Data.src \
./code/Motor.src \
./code/My_Device.src \
./code/Page.src \
./code/UART_Analysis.src 

C_DEPS += \
./code/ALL_Variables.d \
./code/Data.d \
./code/Motor.d \
./code/My_Device.d \
./code/Page.d \
./code/UART_Analysis.d 

OBJS += \
./code/ALL_Variables.o \
./code/Data.o \
./code/Motor.o \
./code/My_Device.o \
./code/Page.o \
./code/UART_Analysis.o 


# Each subdirectory must supply rules for building sources it contributes
code/%.src: ../code/%.c code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fE:/FILE_ADS/Code_8_1_B/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/%.o: ./code/%.src code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code

clean-code:
	-$(RM) ./code/ALL_Variables.d ./code/ALL_Variables.o ./code/ALL_Variables.src ./code/Data.d ./code/Data.o ./code/Data.src ./code/Motor.d ./code/Motor.o ./code/Motor.src ./code/My_Device.d ./code/My_Device.o ./code/My_Device.src ./code/Page.d ./code/Page.o ./code/Page.src ./code/UART_Analysis.d ./code/UART_Analysis.o ./code/UART_Analysis.src

.PHONY: clean-code

