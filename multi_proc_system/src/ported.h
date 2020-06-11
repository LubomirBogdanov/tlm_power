#ifndef PORTED_H__
#define PORTED_H__


//microblaze_1 FIFOs
#define ND_0_OG_1_CH_11 0 //write to CDChannelCH_11 address for microblaze_1
//microblaze_1 FIFOs
#define ND_3_IG_1_CH_7 0 //read from CDChannelCH_7 address for microblaze_1
//microblaze_1 FIFOs
#define ND_3_IG_2_CH_8 1 //read from CDChannelCH_8 address for microblaze_1
//microblaze_1 FIFOs
#define ND_3_IG_3_CH_9 2 //read from CDChannelCH_9 address for microblaze_1
//microblaze_1 FIFOs
#define ND_3_IG_4_CH_10 3 //read from CDChannelCH_10 address for microblaze_1

//microblaze_2 FIFOs
#define ND_2_OG_1_CH_2 0 //write to CDChannelCH_2 address for microblaze_2
//microblaze_2 FIFOs
#define ND_2_OG_2_CH_4 1 //write to CDChannelCH_4 address for microblaze_2
//microblaze_2 FIFOs
#define ND_2_OG_3_CH_9 2 //write to CDChannelCH_9 address for microblaze_2
//microblaze_2 FIFOs
#define ND_2_OG_4_CH_10 3 //write to CDChannelCH_10 address for microblaze_2
//microblaze_2 FIFOs
#define ND_2_IG_1_CH_5 0 //read from CDChannelCH_5 address for microblaze_2
//microblaze_2 FIFOs
#define ND_2_IG_2_CH_6 1 //read from CDChannelCH_6 address for microblaze_2


//microblaze_3 FIFOs
#define ND_1_OG_1_CH_1 0 //write to CDChannelCH_1 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_OG_2_CH_3 1 //write to CDChannelCH_3 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_OG_3_CH_5 2 //write to CDChannelCH_5 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_OG_4_CH_6 3 //write to CDChannelCH_6 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_OG_5_CH_7 4 //write to CDChannelCH_7 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_OG_6_CH_8 5 //write to CDChannelCH_8 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_IG_1_CH_1 0 //read from CDChannelCH_1 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_IG_2_CH_2 1 //read from CDChannelCH_2 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_IG_3_CH_3 2 //read from CDChannelCH_3 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_IG_4_CH_4 3 //read from CDChannelCH_4 address for microblaze_3
//microblaze_3 FIFOs
#define ND_1_IG_5_CH_11 4 //read from CDChannelCH_11 address for microblaze_3



int lpc_wait_start(void);
void lpc_send_stop(void);
void microblaze_bread_datafsl(int value, int pos);
void microblaze_bwrite_datafsl(int value, int pos);

#endif
