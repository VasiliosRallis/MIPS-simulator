###################################################
## MIPS Compilation path

MIPS_CC = mips-linux-gnu-g++
MIPS_OBJCOPY = mips-linux-gnu-objcopy

# Turn on all warnings, and enable optimisations
MIPS_CPPFLAGS = -W -Wall -O3 -fno-builtin -std=c++11

# Avoid standard libraries etc. being brought in, and link statically
MIPS_LDFLAGS = -nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic
MIPS_LDFLAGS += -Wl,--build-id=none

# Compile a c file into a MIPS object file
%.mips.o : %.c
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

# Link a MIPS object file and place it at the locations required in the
# spec using linker.ld
%.mips.elf : %.mips.o
	$(MIPS_CC) $(MIPS_CPPFLAGS) $(MIPS_LDFLAGS) -T src/linker.ld $< -o $@

# Extract just the binary instructions from the object file
%.mips.bin : %.mips.elf
	$(MIPS_OBJCOPY) -O binary --only-section=.text $< $@

# For example, if you have testbench/test.c, you can do:
#
# make testbench/test.mips.bin

###################################################
## Simulator


SIM_DEP = src/main.cpp src/setUp.cpp
G++_FLAGS = -w -Wall -std=c++11

# Build the simulation binary
bin/mips_simulator : $(SIM_DEP)
	mkdir -p bin
	g++ $(G++_FLAGS) $(SIM_DEP) -o bin/mips_simulator


# In order to comply with spec
simulator : bin/mips_simulator

###################################################
## Testbench

testbench :
	echo "No testbench yet"
	exit 1
