#The name of the top-level source file
PROJECT			= main
#Add additional files here. The ${PROJECT}.c should be at the end.
SRC			= cr_startup_lpc8xx.c crp.c mtb.c ${PROJECT}.c   
#The name of the directory with the output files
INDIR			= src
OUTDIR			= gcc
OBJ			= ${SRC:%.c=${OUTDIR}/%.o}

TOOLCHAIN_PATH		= /usr/local/mcuxpressoide-10.3.1_2233/ide/plugins/com.nxp.mcuxpresso.tools.linux_10.3.0.201811011841/tools/bin
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
CFLAGS          	= ${PREPROCESSOR} -I${IPATH} -mcpu=${CPU} -m${INSTRSET} ${OPTFLAGS} ${DEBUGFLAGS} 
LINKER_FILE		= ${PROJECT}.ld
LDFLAGS			= -nostdlib -mcpu=${CPU} -m${INSTRSET} -Xlinker -Map="${OUTDIR}/${PROJECT}.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -T "${LINKER_FILE}"
OBJDUMPFLAGS		= -D -S
SIZEFLAGS		= -d
OBJCOPYFLAGS		= -O ihex
FLASHCMD_PATH		= /usr/local/mcuxpressoide-10.3.1_2233/ide/plugins/com.nxp.mcuxpresso.tools.bin.linux_10.3.1.201902141129/binaries
FLASHCMD		= ${FLASHCMD_PATH}/crt_emu_cm_redlink
FLASHCMDFLAGS		= -pLPC810 -vendor=NXP -flash-load-exec

all: ${OUTDIR} ${OUTDIR}/${PROJECT}.axf ${OUTDIR}/${PROJECT}.lst size ${OUTDIR}/${PROJECT}.a43
#flash_device: flash	

${OUTDIR}:
	@mkdir -p ${OUTDIR}
	
${OUTDIR}/${PROJECT}.axf: ${OBJ}
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	${CC} ${LDFLAGS} -o "${OUTDIR}/${PROJECT}.axf" ${SRC:%.c=${OUTDIR}/%.o} 
	@echo ' '

${OBJ}: ${SRC:${INDIR}/%.c}
	@echo 'Building file: $@'
	@echo 'Invoking: MCU C Compiler'
	${CC} ${CFLAGS} -o ${@} ${@:${OUTDIR}/%.o=${INDIR}/%.c}
	@echo ' '
	
${OUTDIR}/${PROJECT}.lst: 
	${OBJDUMP} ${OBJDUMPFLAGS} ${OUTDIR}/${PROJECT}.axf > ${OUTDIR}/${PROJECT}.lst

size:
	${SIZE} ${SIZEFLAGS} ${OUTDIR}/${PROJECT}.axf
	
${OUTDIR}/${PROJECT}.a43:
	${OBJCOPY} ${OBJCOPYFLAGS} ${OUTDIR}/${PROJECT}.axf ${OUTDIR}/${PROJECT}.a43

flash:
	@echo 'Flashing file: ${PROJECT}.axf'
	${FLASHCMD} ${FLASHCMDFLAGS} ${OUTDIR}/${PROJECT}.axf
	@echo ' '

clean:
	@echo 'Removing directory: ${OUTDIR}'
	rm -r ${OUTDIR} 
	@echo ' '
