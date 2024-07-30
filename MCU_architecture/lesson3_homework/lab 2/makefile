#  	 UNIVERSAL MAKEFILE		 #
#MADE BY: Hazem SHaaban bakry#

#Toolchain used, leave empty if using native toolchain
CC= arm-none-eabi-
#CPU architecture, leave empty if using native toolchain
CPU_TYPE= -mcpu=cortex-m3
#extra flags sent to compiler
CFLAGS= -I .
#debugging option, leave empty if you don't want debugging, or add -g if you want debugging
DEBUGGING=-gdwarf-2
#optimization level option, leave empty for no optimization
OPTIMIZATION=
#MAP file for review after linking, leave empty if not desired, or type -Map=project_MAP.map
MAP_FILE=-Map=project_MAP.map
#project name for hex and bin files
PROJECT_NAME=blinking_led_stm32


#list of all expected c based object files
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
#list of all expected s based object files
ASM_SRC= $(wildcard *.s)
ASM_OBJ= $(ASM_SRC:.s=.o)
#macro for (all dependancies -o target)
IO_FILES= $^ -o $@




#BUILD ENTIRE project
all: $(PROJECT_NAME).bin
	@echo "Build done!"

#Target: object file with same name as c file from dependancies
%.o: %.c
	@echo "Building "$@
	$(CC)gcc -c $(DEBUGGING) $(OPTIMIZATION) $(CFLAGS) $(CPU_TYPE) $(IO_FILES)
	@echo "==================================================="
	
#Target: object file with same name as S file fro dependancies
%.o: %.s
	@echo "Building "$@
	$(CC)as -c $(DEBUGGING) $(OPTIMIZATION) $(CFLAGS) $(CPU_TYPE) $(IO_FILES)
	@echo "==================================================="
	
#Target: project elf file, Dependancies: all object files
$(PROJECT_NAME).elf: $(OBJ) $(ASM_OBJ)
	@echo "linking objects into "$@
	$(CC)ld -T linker_script.ld $(MAP_FILE) $(IO_FILES)
	@echo "==================================================="
	
#Target: project bin file with same name as project elf file
$(PROJECT_NAME).bin: $(PROJECT_NAME).elf
	@echo "Exporting "$@" from "$<
	$(CC)objcopy -O binary $< $@
	@echo "==================================================="
	
	
	
#CLEAN ALL FILES MADE BY MAKEFILE
CLEAN_ALL:
	rm $(wildcard *.o) $(wildcard *.elf) $(wildcard *.bin) $(wildcard *.map)
	rm -r objdump_and_symbols
	
#CLEAN PROJECT FILES ONLY(elf, bin)
CLEAN:
	rm $(wildcard *.elf) $(wildcard *.bin) $(wildcard *.map)
	rm -r objdump_and_symbols





# THIS SECTION IS FOR ASSEMBLY DUMP, SECTION DUMP, AND SYMBOLS
OBJDUMP_FLAGS= -h -D
ALL_OBJ= $(wildcard *.o)
OBJ_FILES= $(ALL_OBJ:.o=.txt)

#make directory for objdump files if not created
objdump_and_symbols:
	mkdir $@
#dump object info of a file
%.txt:%.o objdump_and_symbols
	$(CC)objdump $(OBJDUMP_FLAGS) $< >> ./objdump_and_symbols/$@
	$(CC)nm $< >> ./objdump_and_symbols/$@
	
#dump all object files info
DUMP_ALL: $(OBJ_FILES)
	@echo "all objects and symbols dumped!"
	
	
#dump info from elf file
DUMP_ELF: $(PROJECT_NAME).elf objdump_and_symbols
	$(CC)objdump $(OBJDUMP_FLAGS) $< >> ./objdump_and_symbols/$(PROJECT_NAME).txt
	$(CC)nm $< >> ./objdump_and_symbols/$(PROJECT_NAME).txt