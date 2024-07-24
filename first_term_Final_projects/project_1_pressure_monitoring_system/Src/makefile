#made by: Hazem Shaaban Bakry
#as part of learn in depth:master embedded systems diploma


#FLAGS TO ADJUST
#################################################################################################################
CC = arm-none-eabi-
DEBUGGING = 
OPTIMIZATION = 
CFLAGS = -I ./driver -I ./pressure_monitoring_system -I ./LED_controller -I ./pressure_sensor
CPU = -mcpu=cortex-m3
PROJECT_NAME = project1_pressure_monitor
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
	
	
#list all C files and their corresponding object files
CFILES = $(wildcard *.c) $(wildcard */*.c)
C_OBJECTS = $(CFILES:.c=.o)

#list all assembly files and their corresponding object files
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
clean_dump:
	rm -r objdumps_and_symbols
	
clean_all:
	rm $(C_OBJECTS) $(ASM_OBJECTS) $(wildcard *.elf) $(wildcard *.bin) $(wildcard *.map)
	rm -r objdumps_and_symbols
	@echo "=========================DIRECTORY IS CLEAN============================"
	
clean:
	rm $(wildcard *.elf) $(wildcard *.bin) $(wildcard *.map)
	@echo "=========================Removed executables============================"
#################################################################################################################


#OBJECT DUMP
#################################################################################################################
#obj dump flags
OBJ_DUMP_FLAGS = -h -D

#if directory is not there, make it
objdumps_and_symbols:
	mkdir $@

#any dump file requested, here is the recipe 
%.txt:%.o objdumps_and_symbols
	$(CC)objdump $(OBJ_DUMP_FLAGS) $< >> ./objdumps_and_symbols/$(notdir $@)
	$(CC)nm $< >> ./objdumps_and_symbols/$(notdir $@)

DUMP_FILES = $(C_OBJECTS:.o=.txt) $(ASM_OBJECTS:.o=.txt)
dump_all: $(DUMP_FILES)
	@echo "=============================info dumped================================"
	
dump_elf:$(PROJECT_NAME).elf objdumps_and_symbols
	$(CC)objdump $(OBJ_DUMP_FLAGS) $< >> ./objdumps_and_symbols/$(PROJECT_NAME).txt
	$(CC)nm $< >> ./objdumps_and_symbols/$(PROJECT_NAME).txt
	@echo "=============================info dumped================================"
	
#################################################################################################################


	