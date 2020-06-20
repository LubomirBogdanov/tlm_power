#ifndef PORTED_H__
#define PORTED_H__

#include "main.h"
#include "aux_func.h"
#include "MemoryMap.h"

int lpc_wait_start(void);
void lpc_send_stop(void);
void microblaze_bread_datafsl(int *value, int fifo_channel_number);
void microblaze_bwrite_datafsl(int value, int fifo_channel_number);

#endif
