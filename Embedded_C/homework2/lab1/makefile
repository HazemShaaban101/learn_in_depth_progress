# makefile to build simple uart string sending app for versatilepb
#made by: Hazem Shaaban Bakry


CC =arm-none-eabi-
CPU_TYPE=-mcpu=arm926ej-s

#Debugger: state needed debugging using -g flag, if no debugging wanted, leave it empty
DEBUGGER = -g

#automating input files -o output file process		$^ means likst all depencencies, $< means list first dependency, and $@ means list target
IO_FILES = $^ -o $@

debugging-off: learn_in_depth.bin
	@echo "==========Build complete=========="
	@echo "==========Debugging = "$(DEBUGGER)"========="

# automates generation of object files for any input c file, output file is with the same name
%.o: %.c
	@echo "building "$@
	$(CC)gcc -c $(DEBUGGER) $(CPU_TYPE) $(IO_FILES)

startup.o: startup.s
	@echo "making startup.o"
	$(CC)as $(DEBUGGER) $(CPU_TYPE) $(IO_FILES)

learn_in_depth.elf: startup.o main.o uart.o
	@echo "linking objects together"
	$(CC)ld -T linker_script.ld $(IO_FILES)

learn_in_depth.bin: learn_in_depth.elf
	@echo "extracting binary file"
	$(CC)objcopy -O binary learn_in_depth.elf learn_in_depth.bin


CLEAN-ALL:
	rm *.o *.elf *.bin

CLEAN:
	rm *.elf *.bin