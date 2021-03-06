// File automatically generated by ESPAM


#ifndef __MEMORYMAP_H_
#define __MEMORYMAP_H_

#define PCTRL_BRAM1_microblaze_1 0x00000000 //read from PCTRL_BRAM1_microblaze_1 address for microblaze_1

#define PCTRL_BRAM1_microblaze_1 0x00000000 //write to PCTRL_BRAM1_microblaze_1 address for microblaze_1

#define DCTRL_BRAM1_microblaze_1 0x00000000 //read from DCTRL_BRAM1_microblaze_1 address for microblaze_1

#define DCTRL_BRAM1_microblaze_1 0x00000000 //write to DCTRL_BRAM1_microblaze_1 address for microblaze_1

//microblaze_1 FIFOs
#define ND_0_OG_1_CH_1 0 //write to CDChannelCH_1 address for microblaze_1

#define PCTRL_BRAM1_microblaze_2 0x00000000 //read from PCTRL_BRAM1_microblaze_2 address for microblaze_2

#define PCTRL_BRAM1_microblaze_2 0x00000000 //write to PCTRL_BRAM1_microblaze_2 address for microblaze_2

#define DCTRL_BRAM1_microblaze_2 0x00000000 //read from DCTRL_BRAM1_microblaze_2 address for microblaze_2

#define DCTRL_BRAM1_microblaze_2 0x00000000 //write to DCTRL_BRAM1_microblaze_2 address for microblaze_2

//microblaze_2 FIFOs
#define ND_1_IG_1_CH_1 0 //read from CDChannelCH_1 address for microblaze_2

#define clk_cntr (volatile int *)0xf8000000
#define DDR_MEM (volatile char *)0xA0000000
#define FIN_SIGNAL (volatile int *)0xf9000000
#define START (volatile int *)0xf9000000

#endif
