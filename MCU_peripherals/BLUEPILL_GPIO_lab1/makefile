#made by: Hazem Shaaban Bakry
#as part of learn in depth:master embedded systems diploma


#FLAGS TO ADJUST
#################################################################################################################
# Toolchain used, leave empty for native
CC = arm-none-eabi-
# debugging flag, leave empty for no debugging
DEBUGGING = -gdwarf-2
# optimization flag, leave empty for no optimization
OPTIMIZATION = 
# Flags for compilation, includes, and any other desired flags
CFLAGS = -I .
# CPU architecture, leave empty when using native toolchain
CPU = -mcpu=cortex-m3
# Name of the project, this name will reflect on output elf and bin files
PROJECT_NAME = BLUEPILL_GPIO_lab
# Map file from linking process, leave empty for no map file, or change the name to suit your needs
MAPFILE = -Map=project_MAP.map
#################################################################################################################


#BUILDING PROJECT
#################################################################################################################
#build entire project
all:$(PROJECT_NAME).bin
	@echo "======================================================================="
	@echo "=============================Build is done============================="
	@echo "======================================================================="


#extract binary image from elf file
$(PROJECT_NAME).bin:$(PROJECT_NAME).elf
	@echo "Extracting "$@ " from "$<
	$(CC)objcopy -O binary $< $@
	
	
#list all C files and their corresponding object files in main directory and any sub directory. this does not reach any files in sub-sub directories
CFILES = $(wildcard *.c) $(wildcard */*.c)
C_OBJECTS = $(CFILES:.c=.o)

#list all assembly files and their corresponding object files main directory and any sub directory. this does not reach any files in sub-sub directories
ASMFILES = $(wildcard *.s) $(wildcard */*.s)
ASM_OBJECTS = $(ASMFILES:.s=.o)


#link all object files from c files and from assembly files
$(PROJECT_NAME).elf:$(C_OBJECTS) $(ASM_OBJECTS)
	@echo "linking objects..."
	$(CC)ld -T linker_script.ld $(MAPFILE) $^ -o $@
	@echo "======================================================================="


#compile and assemble C files
%.o : %.c
	@echo "building "$@
	$(CC)gcc -c $(DEBUGGING) $(OPTIMIZATION) $(CFLAGS) $(CPU) $^ -o $@
	@echo "======================================================================="
	
	
#assemble assembly files
%.o : %.s
	echo "building "$@
	$(CC)as -c $(DEBUGGING) $(OPTIMIZATION) $(CFLAGS) $(CPU) %^ -o %@
	@echo "======================================================================="
#################################################################################################################


#clean directory
#################################################################################################################
# delete objdump folder alongside its content
clean_dump:
	rm -r objdumps_and_symbols

# delete all files made by this makefile
clean_all:
	rm $(C_OBJECTS) $(ASM_OBJECTS) $(wildcard *.elf) $(wildcard *.bin) $(wildcard *.map)
	rm -r objdumps_and_symbols
	@echo "=========================DIRECTORY IS CLEAN============================"

# only delete project build, and map file. all object files remain untouched
clean:
	rm $(wildcard *.elf) $(wildcard *.bin) $(wildcard *.map)
	@echo "=========================Removed executables============================"
#################################################################################################################


#OBJECT DUMP
#################################################################################################################
#obj dump flags
OBJ_DUMP_FLAGS = -h -D

# if objdump directory is not there, make it
objdumps_and_symbols:
	mkdir $@

# recipe for any object's dump file, saved in objdump folder
%.txt:%.o objdumps_and_symbols
	$(CC)objdump $(OBJ_DUMP_FLAGS) $< >> ./objdumps_and_symbols/$(notdir $@)
	$(CC)nm $< >> ./objdumps_and_symbols/$(notdir $@)

# list all object files possible, and create a dump file for each
DUMP_FILES = $(C_OBJECTS:.o=.txt) $(ASM_OBJECTS:.o=.txt)
dump_all: $(DUMP_FILES)
	@echo "=============================info dumped================================"

# create a dump file for project elf file, it contains info header, sections, assembly code, and symbols
dump_elf:$(PROJECT_NAME).elf objdumps_and_symbols
	$(CC)readelf -h $< >> ./objdumps_and_symbols/$(PROJECT_NAME).txt
	$(CC)objdump $(OBJ_DUMP_FLAGS) $< >> ./objdumps_and_symbols/$(PROJECT_NAME).txt
	$(CC)nm $< >> ./objdumps_and_symbols/$(PROJECT_NAME).txt
	@echo "=============================info dumped================================"
	
#################################################################################################################


	