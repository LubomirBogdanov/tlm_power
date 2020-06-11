#ifndef __AUX_FUNC_H__
#define __AUX_FUNC_H__

#include <math.h>

#include "sort_func.h"

typedef int tCH_1;
typedef int tCH_2;
typedef int tCH_3;
typedef int tCH_4;
typedef int tCH_5;
typedef int tCH_6;
typedef int tCH_7;
typedef int tCH_8;
typedef int tCH_9;
typedef int tCH_10;
typedef int tCH_11;

// Parameters

void  _in_numbers_stream( tCH_11 *out_0ND_0 ) {
    in_numbers_stream( (int *)out_0ND_0 );
}

void  _out_numbers_stream( tCH_10 *in_0ND_3 ) {
    out_numbers_stream( in_0ND_3 );
}

void  _compare_numbers( tCH_5 *in_0ND_2, tCH_6 *in_1ND_2, tCH_9 *out_2ND_2, tCH_10 *out_3ND_2 ) {
    compare_numbers( (int *)in_0ND_2, (int *)in_1ND_2, (int *)out_2ND_2, (int *)out_3ND_2 );
}


#define min(a,b) ((a)<=(b))?(a):(b)
#define max(a,b) ((a)>=(b))?(a):(b)

int ddiv(int a, int b ){
    //return (int)(a/b);
    return ( (int) (((a)<0) ? ((a)-(b)+1)/(b) : (a)/(b)) ); 
    //return ( (int) (((a)<0)^((b)<0) ? ((a) < 0 ? ((a)-(b)+1)/(b) : ((a)-(b)-1)/(b)) : (a)/(b)) ); 
}

int mod(int a, int b){
    return mod(a, b);
}

int ceil1(int a){
    return a; /* return (int) ceil(a);*/
}

int floor1(int a){
    return a; /* return (int) floor(a);*/
}

#define readFSL(pos, value, len) \
    do {\
        int i;\
        for (i = 0; i < len; i++) \
            microblaze_bread_datafsl(((volatile int *) value)[i], pos);\
    } while(0)
        
#define writeFSL(pos, value, len) \
    do {\
        int i;\
        for (i = 0; i < len; i++)  \
            microblaze_bwrite_datafsl(((volatile int *) value)[i], pos);\
    } while(0)
        
#define read(pos, value, len) \
    do {\
        int i;\
        volatile int *isEmpty;\
        volatile int *inPort = (volatile int *)pos;\
        isEmpty = inPort + 1;\
        for (i = 0; i < len; i++) {\
            while (*isEmpty) { };\
            ((volatile int *) value)[i] = *inPort;\
        }\
    } while(0)
        
#define write(pos, value, len) \
    do {\
        int i;\
        volatile int *isFull;\
        volatile int *outPort = (volatile int *)pos;\
        isFull = outPort + 1;\
        for (i = 0; i < len; i++) {\
            while (*isFull) { };\
                *outPort = ((volatile int *) value)[i];\
            }\
    } while(0)

#define readDyn(pos, value, len) \
    do {\
        int i;\
        volatile int *isEmpty;\
        volatile int *inPort = (volatile int *)pos;\
        isEmpty = inPort + 1;\
        for (i = 0; i < len; i++) {\
            while (*isEmpty) { yield(); };\
                ((volatile int *) value)[i] = *inPort;\
             }\
    } while(0)

#define writeDyn(pos, value, len) \
    do {\
        int i;\
        volatile int *isFull;\
        volatile int *outPort = (volatile int *)pos;\
        isFull = outPort + 1;\
        for (i = 0; i < len; i++) {\
            while (*isFull) { yield(); };\
            *outPort = ((volatile int *) value)[i];\
        }\
    } while(0)

#define readMF(pos, value, n) \
    do {\
        int i;\
        volatile int *isEmpty;\
        int inPort = (int) pos;\
        volatile int *dataReg_requestReg = (volatile int *) 0xE0000000;\
        isEmpty = dataReg_requestReg + 1;\
        *dataReg_requestReg = 0x80000000|(inPort);\
        for (i = 0; i < n; i++) {\
            while (*isEmpty != 2) { };\
            ((volatile int *) value)[i] = *dataReg_requestReg;\
        }\
        *dataReg_requestReg = 0x7FFFFFFF&(inPort);\
    } while(0)

#define writeMF(pos, value, n) \
    do {\
        int i;\
        volatile int *isFull;\
        volatile int *outPort = (volatile int *)pos;\
        isFull = outPort + 1;\
        for (i = 0; i < n; i++) {\
            while (*isFull) { };\
                *outPort = ((volatile int *) value)[i];\
            }\
        } while(0)\
        
#define readDynMF(pos, value, n) \
    do {\
        int i;\
        volatile int *isEmpty;\
        int inPort = (int) pos;\
        volatile int *dataReg_requestReg = (volatile int *) 0xE0000000;\
        isEmpty = dataReg_requestReg + 1;\
        *dataReg_requestReg = 0x80000000|(inPort);\
        for (i = 0; i < n; i++) {\
            while (*isEmpty != 2) {\
                if( *isEmpty == 3 ) {\
                    *dataReg_requestReg = 0x7FFFFFFF&(inPort);\
                    yield();\
                    *dataReg_requestReg = 0x80000000|(inPort);\
                }\
            }\
            ((volatile int *) value)[i] = *dataReg_requestReg;\
        }\
        *dataReg_requestReg = 0x7FFFFFFF&(inPort);\
    } while(0)
     
#define writeDynMF(pos, value, n) \
    do {\
        int i;\
        volatile int *isFull;\
        volatile int *outPort = (volatile int *)pos;\
        isFull = outPort + 1;\
        for (i = 0; i < n; i++) {\
            while (*isFull) { yield(); };\
            *outPort = ((volatile int *) value)[i];\
        }\
    } while(0)
    
///////////////////////////////////// Primitives for SW FIFOs
        
#define readSWF(pos, value, len, fifo_size) \
    do {\
        volatile int *fifo = (int *)pos;\
        int r_cnt = fifo[1];\
        while (1) {\
            volatile int w_cnt = fifo[0];\
            if ( w_cnt != r_cnt ) {\
                for (int i = 0; i < len; i++) {\
                    ((volatile int *) value)[i] = fifo[(r_cnt & 0x7FFFFFFF) + 2 + i];\
                }\
                r_cnt += len;\
                if( (r_cnt & 0x7FFFFFFF) == fifo_size ) {\
                    r_cnt &= 0x80000000;\
                    r_cnt ^= 0x80000000;\
                }\
                fifo[1] = r_cnt;\
                break;\
            }\
       }\
    } while(0)
        
#define writeSWF(pos, value, len, fifo_size) \
    do {\
        volatile int *fifo = (int *)pos;\
        int w_cnt = fifo[0];\
        while (1) {\
            volatile int r_cnt = fifo[1];\
            if ( r_cnt != (w_cnt ^ 0x80000000) ) {\
                for (int i = 0; i < len; i++) {\
                    fifo[(w_cnt & 0x7FFFFFFF) + 2 + i] = ((volatile int *) value)[i];\
                }\
                w_cnt += len;\
                if( (w_cnt & 0x7FFFFFFF) == fifo_size ) {\
                    w_cnt &= 0x80000000;\
                    w_cnt ^= 0x80000000;\
                }\
                fifo[0] = w_cnt;\
                break;\
            }\
        }\
    } while(0)
        
////////// currently not used //////// Primitives for SW FIFOs 
        
inline volatile void *acquire_write_ptr(int f, int len) {
    volatile long *fifo = (long *)f;
    register long fifoSize = fifo[0];
    register long fifo_2 = fifo[2];

    while( (fifo_2^fifo[5]) == 0x80000000) { }; // full

    void *ptr = (void *)(fifo + 6 + (fifo_2 & 0x7FFFFFFF));
    
    fifo_2 += len;      // wr index + token size in dwords (32 bits)

    if( (fifo_2 & 0x7FFFFFFF) == fifoSize ) { 
        fifo_2 = fifo_2 & 0x80000000;
        fifo_2 = fifo_2 ^ 0x80000000; // toggle the flag
    }

    fifo[2] = fifo_2;

    return ptr;
}

inline void release_write_ptr(int f) {
    volatile long *fifo = (volatile long *)f;
    fifo[3] = fifo[2];
}

inline volatile void *acquire_read_ptr(int f, int len) {
    volatile long *fifo = (long *)f;
    register long fifoSize = fifo[0];
    register long fifo_4 = fifo[4];

    while( fifo[3] == fifo_4 ) { }; // empty

    void *ptr = (void *)(fifo + 6 + (fifo_4 & 0x7FFFFFFF));

    fifo_4 += len;      // rd index + token size in dwords (32 bits)

    if( (fifo_4 & 0x7FFFFFFF) == fifoSize ) {
        fifo_4 = fifo_4 & 0x80000000;
        fifo_4 = fifo_4 ^ 0x80000000; // toggle the flag
    }
    fifo[4] = fifo_4;
    
    return ptr;
}

inline void release_read_ptr(int f) {
    volatile int *fifo = (volatile int *)f;
    fifo[5] = fifo[4];
}

// Read and Write primitives for Xilkernel
#define readSWF_Dyn1(pos, value, len, fifo_size) \
    do {\
        volatile int *fifo = (int *)pos;\
        int r_cnt = fifo[1];\
        int w_cnt = fifo[0];\
        while ( w_cnt == r_cnt ) { yield(); w_cnt = fifo[0]; }\
        for (int i = 0; i < len; i++) {\
             ((volatile int *) value)[i] = fifo[(r_cnt & 0x7FFFFFFF) + 2 + i];\
        }\
        r_cnt += len;\
        if( (r_cnt & 0x7FFFFFFF) == fifo_size ) {\
            r_cnt &= 0x80000000;\
            r_cnt ^= 0x80000000;\
        }\
        fifo[1] = r_cnt;\
    } while(0)
        
#define writeSWF_Dyn1(pos, value, len, fifo_size) \
    do {\
        volatile int *fifo = (int *)pos;\
        int w_cnt = fifo[0];\
        int r_cnt = fifo[1];\
        while ( r_cnt == (w_cnt ^ 0x80000000) ) { yield(); r_cnt = fifo[1]; }\
        for (int i = 0; i < len; i++) {\
            fifo[(w_cnt & 0x7FFFFFFF) + 2 + i] = ((volatile int *) value)[i];\
        }\
        w_cnt += len;\
        if( (w_cnt & 0x7FFFFFFF) == fifo_size ) {\
            w_cnt &= 0x80000000;\
            w_cnt ^= 0x80000000;\
        }\
        fifo[0] = w_cnt;\
    } while(0)
        
// Read and Write primitives for FreeRTOS 
#define readSWF_Dyn2(pos, value, len, fifo_size, S, T) \
    do {\
        volatile int *fifo = (int *)pos;\
        int r_cnt = fifo[1];\
        int w_cnt = fifo[0];\
        while ( w_cnt == r_cnt ) { taskDISABLE_INTERRUPTS(); xil_printf("PANIC! Buffer underflow\\n"); for(;;); }\
        for (int i = 0; i < len; i++) {\
            ((volatile int *) value)[i] = fifo[(r_cnt & 0x7FFFFFFF) + 2 + i];\
        }\
        r_cnt += len;\
        if( (r_cnt & 0x7FFFFFFF) == fifo_size ) {\
            r_cnt &= 0x80000000;\
            r_cnt ^= 0x80000000;\
        }\
        fifo[1] = r_cnt;\
    } while(0)\
        
#define writeSWF_Dyn2(pos, value, len, fifo_size, S, T) \
    do {\
        volatile int *fifo = (int *)pos;\
        int w_cnt = fifo[0];\
        int r_cnt = fifo[1];\
        while ( r_cnt == (w_cnt ^ 0x80000000) ) { taskDISABLE_INTERRUPTS(); xil_printf("PANIC! Buffer overflow\\n"); for(;;); }\
        for (int i = 0; i < len; i++) {\
            fifo[(w_cnt & 0x7FFFFFFF) + 2 + i] = ((volatile int *) value)[i];\
        }\
        w_cnt += len;\
        if( (w_cnt & 0x7FFFFFFF) == fifo_size ) {\
            w_cnt &= 0x80000000;\
            w_cnt ^= 0x80000000;\
        }\
        fifo[0] = w_cnt;\
    } while(0);


#endif
