MCU = atmega32
MCU_CLOCK = 8000000UL

BIN_FOLDER = ./bin
CORE_FOLDER = ./core
MCU_FOLDER = ${CORE_FOLDER}/mcus
OBJ_FOLDER = ./obj
SRC_FOLDER = ./src

TARGET = firmware

AVRDUDE = avrdude
PROGRAMMER = usbasp
AVR_HFUSE = 0xD1
AVR_LFUSE = 0xE4
AVR_FLASH = ${BIN_FOLDER}/${TARGET}.hex

CC_HEXSIZE = avr-size

CC_OBJCOPY = avr-objcopy
CC_OBJCOPY_FLAGS = -j .text -j .data -O ihex

CC = avr-gcc
CC_FLAGS = -Wall -mmcu=${MCU} -DGCC_MEGA_AVR -Os -DF_CPU=${MCU_CLOCK} -g \
		   -fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -I${SRC_FOLDER}
LDFLAGS = -Wl,-Map=${BIN_FOLDER}/$(TARGET).map,--cref -lm

REMOVE = rm -f

# Makefile msg constants
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
MSG_CLEANING = Cleaning project...

# Help functions
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))


WIRING_INC_FLAG = ${sort $(dir $(call rwildcard,${MCU_FOLDER}/${MCU}/,*.h))} ${MCU_FOLDER}
WIRING_MCU =  ${sort $(call rwildcard,${MCU_FOLDER}/${MCU}/,*.c)}

LIB_INC_FOLDERS = ${sort $(dir $(call rwildcard,${SRC_FOLDER}/,*.h))} ${WIRING_INC_FLAG}
CC_LIB_INC_FLAG = ${addprefix -I,${LIB_INC_FOLDERS}} -I./
SRC =  ${sort $(call rwildcard,${SRC_FOLDER}/,*.c)} ${WIRING_MCU}
OBJ = ${SRC:.c=.o}

deprectated:
	$(error This makefile is useless because the project is now setting up by cmake)

build: begin gccversion ${TARGET}.hex finished program_size end

fuse:
	@echo Setting fuses from brand new device
	@${AVRDUDE} -p ${MCU} -c ${PROGRAMMER} -v -Uhfuse:w:${AVR_HFUSE}:m -Ulfuse:w:${AVR_LFUSE}:m -B11

flash:
	@echo Uploading flash
	@${AVRDUDE} -p ${MCU} -c ${PROGRAMMER} -v -Uflash:w:${AVR_FLASH}:i -B11

begin:
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)

gccversion: 
	@$(CC) --version

program_size:
	@${CC_HEXSIZE} -C ${BIN_FOLDER}/firmware.bin --mcu=${MCU}

clean:
	@echo $(MSG_CLEANING)
	@$(REMOVE) ${wildcard ${OBJ_FOLDER}/*.o}
	@$(REMOVE) $(wildcard ${BIN_FOLDER}/*.elf)
	@$(REMOVE) $(wildcard ${BIN_FOLDER}/*.map)
	@$(REMOVE) $(wildcard ${BIN_FOLDER}/*.bin)
	@$(REMOVE) $(wildcard ${BIN_FOLDER}/*.hex)

%.elf: $(OBJ)
	@echo $(MSG_LINKING) $@
	@$(CC) $(ALL_CFLAGS) ${wildcard ${OBJ_FOLDER}/*.o} --output ${BIN_FOLDER}/$@ $(LDFLAGS)

%.o: %.c
	@echo $(MSG_COMPILING) $<
	@${eval filename := ${notdir $<}}
	@${CC} ${CC_FLAGS} -c $< -o ${OBJ_FOLDER}/${filename}.o -I${CC_LIB_INC_FLAG}

${TARGET}.bin: $(TARGET).elf
	@echo ${MSG_LINKING} $@
	@${CC} ${CC_FLAGS} ${wildcard ${OBJ_FOLDER}/*.o} -o ${BIN_FOLDER}/$@

${TARGET}.hex: ${TARGET}.bin
	@echo ${MSG_FLASH} $@
	@${CC_OBJCOPY} ${CC_OBJCOPY_FLAGS} ${BIN_FOLDER}/$< ${BIN_FOLDER}/$@