MCU_INDEX		= 0
#The name of the top-level source file
PROJECT			= main
#Add additional files here. The ${PROJECT}.c should be at the end.
SRC			= cr_startup_lpc8xx.c crp.c mtb.c user_delay.c user_gpio.c user_i2c.c ${PROJECT}_${MCU_INDEX}.c   

INDIR			= src
OUTDIR			= gcc
OBJ			= ${SRC:%.c=${OUTDIR}/%.o}

TOOLCHAIN_PATH		= /usr/local/mcuxpressoide-11.1.1_3241/ide/plugins/com.nxp.mcuxpresso.tools.linux_11.1.0.202001081728/tools/bin
FLASHCMD_PATH		= /usr/local/mcuxpressoide-11.1.1_3241/ide/plugins/com.nxp.mcuxpresso.tools.bin.linux_11.1.0.202002241259/binaries
SWDMULTIPLEX_DEV	= /dev/ttyUSB0
PROC_LIST		= 0 1 2 3 4 5 6 7 8 9

TOOLCHAIN_PREFIX	= arm-none-eabi
CPU			= cortex-m0
INSTRSET		= thumb
CC              	= ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-gcc
LD			= ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-ld
OBJCOPY			= ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objcopy
OBJDUMP			= ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objdump
SIZE			= ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-size
PREPROCESSOR		= -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_DISABLE -D__MTB_BUFFER_SIZE=256 -D__LPC8XX__ -D__REDLIB__
IPATH			= ../lpc_chip_8xx/inc
OPTFLAGS		= -O0 -fno-common -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -specs=redlib.specs -MMD -MP -MF"${@:${OUTDIR}/%.o=${OUTDIR}/%.d}" -MT"${@:${OUTDIR}/%.o=${OUTDIR}/%.o}" -MT"${@:${OUTDIR}/%.o=${OUTDIR}/%.d}"
DEBUGFLAGS		= -g3
CFLAGS          	= ${PREPROCESSOR} -I${IPATH} -mcpu=${CPU} -m${INSTRSET} ${OPTFLAGS} ${DEBUGFLAGS} -DMCU_TARGET_${MCU_INDEX}
LINKER_FILE		= ${PROJECT}.ld
LDFLAGS			= -nostdlib -mcpu=${CPU} -m${INSTRSET} -Xlinker -Map="${OUTDIR}/${PROJECT}.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -T "${LINKER_FILE}"
OBJDUMPFLAGS		= -D -S
SIZEFLAGS		= -d
OBJCOPYFLAGS		= -O ihex
FLASHCMD		= ${FLASHCMD_PATH}/crt_emu_cm_redlink
FLASHCMDFLAGS		= -pLPC810 -vendor=NXP -flash-load-exec
SWDMULTIPLEX_PORT_CMD	= stty
SWDMULTIPLEX_PORT_PARAM	= -F ${SWDMULTIPLEX_DEV} 2400 -parenb cs8 -cstopb -crtscts raw
SWDMULTIPLEX_CMD	= echo
SWDMULTIPLEX_PARAM	= -e -n 

#stty -F /dev/ttyUSB0 2400 -parenb cs8 -cstopb -crtscts raw
#echo -e -n "\x35" > /dev/ttyUSB0

.PHONY: ${OUTDIR}/${PROJECT}_${MCU_INDEX}.axf ${OBJ} ${OUTDIR}/${PROJECT}_${MCU_INDEX}.lst empty
all: ${OUTDIR} ${OUTDIR}/${PROJECT}_${MCU_INDEX}.axf ${OUTDIR}/${PROJECT}_${MCU_INDEX}.lst size ${OUTDIR}/${PROJECT}_${MCU_INDEX}.a43


${OUTDIR}:
	@mkdir -p ${OUTDIR}
	
${OUTDIR}/${PROJECT}_${MCU_INDEX}.axf: ${OBJ}
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	${CC} ${LDFLAGS} -o "${OUTDIR}/${PROJECT}_${MCU_INDEX}.axf" ${SRC:%.c=${OUTDIR}/%.o} 
	@echo ' '

${OBJ}: ${SRC:${INDIR}/%.c}
	@echo 'Building file: $@'
	@echo 'Invoking: MCU C Compiler'
	${CC} ${CFLAGS} -o ${@} ${@:${OUTDIR}/%.o=${INDIR}/%.c}
	@echo ' '
	
${OUTDIR}/${PROJECT}.lst: 
	${OBJDUMP} ${OBJDUMPFLAGS} ${OUTDIR}/${PROJECT}_${MCU_INDEX}.axf > ${OUTDIR}/${PROJECT}_${MCU_INDEX}.lst

size:
	${SIZE} ${SIZEFLAGS} ${OUTDIR}/${PROJECT}_${MCU_INDEX}.axf
	
${OUTDIR}/${PROJECT}_${MCU_INDEX}.a43:
	${OBJCOPY} ${OBJCOPYFLAGS} ${OUTDIR}/${PROJECT}_${MCU_INDEX}.axf ${OUTDIR}/${PROJECT}_${MCU_INDEX}.a43

flash:
	${MAKE}
	${MAKE} multiplex
	@echo 'Flashing file: ${PROJECT}_${MCU_INDEX}.axf'
	${FLASHCMD} ${FLASHCMDFLAGS} ${OUTDIR}/${PROJECT}_${MCU_INDEX}.axf
	@echo ' '

flash_all:
	@echo 'Flashing system ...'
	@for i in ${PROC_LIST};			\
	  do 					\
	         ${MAKE} flash MCU_INDEX=$$i; 	\
	done
	@echo ' '

multiplex:
	@echo 'Configuring serial port ...'
	${SWDMULTIPLEX_PORT_CMD} ${SWDMULTIPLEX_PORT_PARAM}
	@echo 'Multiplexing SWD to target ${MCU_INDEX}...'
	${SWDMULTIPLEX_CMD} ${SWDMULTIPLEX_PARAM} "${MCU_INDEX}" > ${SWDMULTIPLEX_DEV}
	@echo ' '

empty:
	@echo 'Flashing system with empty firmware ...'
	${MAKE}	MCU_INDEX=empty
	@for i in ${PROC_LIST};									\
	  do 											\
		${MAKE} multiplex MCU_INDEX=$$i;						\
		@echo 'Flashing file: ${PROJECT}_empty_${MCU_INDEX}.axf'; 			\
		${FLASHCMD} ${FLASHCMDFLAGS} ${OUTDIR}/${PROJECT}_empty.axf; 			\
	done
	@echo ' '

clean:
	@echo 'Removing directory: ${OUTDIR}'
	rm -r ${OUTDIR} 
	@echo ' '
