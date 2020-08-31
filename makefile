MCU = atmega328p
MCU_CLOCK = 8000000UL

BIN_FOLDER = ./bin
OBJ_FOLDER = ./obj
SRC_FOLDER = ./src

TARGET = firmware

CC_HEXSIZE = avr-size

CC_OBJCOPY = avr-objcopy
CC_OBJCOPY_FLAGS = -j .text -j .data -O ihex

CC = avr-gcc
CC_FLAGS = -Wall -mmcu=${MCU} -DGCC_MEGA_AVR -I${SRC_FOLDER} -Os -DF_CPU=${MCU_CLOCK} -g \
		   -fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
LDFLAGS = -Wl,-Map=${BIN_FOLDER}/$(TARGET).map,--cref -lm


REMOVE = rm -f


MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before: 
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:

SRC = ${wildcard ${SRC_FOLDER}/*.c}
OBJ = ${SRC:.c=.o}

%.elf: $(OBJ)
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) ${wildcard ${OBJ_FOLDER}/*.o} --output ${BIN_FOLDER}/$@ $(LDFLAGS)

%.o: %.c
	@echo $(MSG_COMPILING) $<
	@${eval filename := ${notdir $<}}
	@${CC} ${CC_FLAGS} -c $< -o ${OBJ_FOLDER}/${filename}.o -I${SRC_FOLDER}

${TARGET}.bin: $(TARGET).elf
	@echo ${MSG_LINKING} $@
	@${CC} ${CC_FLAGS} ${wildcard ${OBJ_FOLDER}/*.o} -o ${BIN_FOLDER}/$@

${TARGET}.hex: ${TARGET}.bin
	@echo ${MSG_FLASH} $@
	@${CC_OBJCOPY} ${CC_OBJCOPY_FLAGS} ${BIN_FOLDER}/$< ${BIN_FOLDER}/$@

build: begin gccversion ${TARGET}.hex finished program_size end

begin:
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)

gccversion: 
	@$(CC) --version

program_size:
	@${CC_HEXSIZE} -C ${BIN_FOLDER}/firmware.bin

clean:
	@echo $(MSG_CLEANING)
	$(REMOVE) ${wildcard ${OBJ_FOLDER}/*.o}
	$(REMOVE) $(wildcard ${BIN_FOLDER}/*.elf)
	$(REMOVE) $(wildcard ${BIN_FOLDER}/*.map)
	$(REMOVE) $(wildcard ${BIN_FOLDER}/*.bin)
	$(REMOVE) $(wildcard ${BIN_FOLDER}/*.hex)