#The name of the top-level source file
PROJECT         = main
#Add additional files here. The ${PROJECT}.c should be at the end.
SRC		= ${PROJECT}.c
#The name of the directory with the output files
OUTDIR		= gcc
OBJ		= ${SRC:%.c=${OUTDIR}/%.o}
#Toolchain prefix
TOOLCHAIN	= msp430-elf
#Instruction sets:  430(msp430), 430x(mdsp430x), 430xv2(msp430xv2)
#CPU		= 430
#Target microcontroller
MCU             = msp430g2101
CC              = ${TOOLCHAIN}-gcc
LD		= ${TOOLCHAIN}-ld
OBJCOPY		= ${TOOLCHAIN}-objcopy
OBJDUMP		= ${TOOLCHAIN}-objdump
SIZE		= ${TOOLCHAIN}-size
IPATH		= /home/lbogdanov/ti/msp430-gcc/include
OPTFLAGS	= -Os
DEBUGFLAGS	= -ggdb
CFLAGS          = -mmcu=${MCU} ${OPTFLAGS} ${DEBUGFLAGS} -std=gnu99 -Wall -ffunction-sections -fdata-sections -I${IPATH}
#LDFLAGS	= -Wl,-L"/home/crusader/programs/ti/gcc_redhat/lib/gcc/msp430-elf/4.9.1",-L"/home/crusader/programs/ti/gcc_redhat/msp430-elf/lib",-lc,-lgcc,-gc-sections
LDFLAGS		= -Wl,-gc-sections
OBJDUMPFLAGS	= -D -S
SIZEFLAGS	= -d
OBJCOPYFLAGS	= -O ihex
FLASHCMD	= mspdebug
FLASHCMDFLAGS	= rf2500 "prog ${OUTDIR}/${PROJECT}.elf" "verify ${OUTDIR}/${PROJECT}.elf" "reset"

all: ${OUTDIR} ${OUTDIR}/${PROJECT}.elf ${OUTDIR}/${PROJECT}.lst size ${OUTDIR}/${PROJECT}.a43
flash_device: flash

${OUTDIR}:
	@mkdir -p ${OUTDIR}
	
${OUTDIR}/${PROJECT}.elf: ${SRC}
	${CC} ${CFLAGS} ${LDFLAGS} -o ${OUTDIR}/${PROJECT}.elf ${SRC}
	
${OUTDIR}/${PROJECT}.lst: 
	${OBJDUMP} ${OBJDUMPFLAGS} ${OUTDIR}/${PROJECT}.elf > ${OUTDIR}/${PROJECT}.lst

size:
	${SIZE} ${SIZEFLAGS} ${OUTDIR}/${PROJECT}.elf
	
${OUTDIR}/${PROJECT}.a43:
	${OBJCOPY} ${OBJCOPYFLAGS} ${OUTDIR}/${PROJECT}.elf ${OUTDIR}/${PROJECT}.a43

flash:
	${FLASHCMD} ${FLASHCMDFLAGS}

clean:
	rm -r ${OUTDIR} 
