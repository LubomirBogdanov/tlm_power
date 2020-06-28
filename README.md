Description  
===================================================================   
The project is a multi-processor system made of 10 microcontrollers.  
The microcontrollers are NXP's LPC810. They are connected on a single  
I2C bus. A multi-master mode is being used. Register access is preferred  
due to the small memory size (4kB flash, 1 kB SRAM).  
Some of the examples loaded in this project are examples with Polyhedral  
Process Networks (PPN). The user could use any type of algorithm for  
his/her multi-processor system.  


INSTALL  
===================================================================
The project main sources are located in multi_proc_system. Enter  
this directory and type:  
  
make  
  
to build the source for target number 0. If you want to build the sources  
for target number 1 type:  

make MCU_INDEX=1  

and so on. The project is closely related to "swd_plex" - this SWD multiplexer  
is being used to flash all of the targets.  
For debugging the MCUXpresso IDE could be used. Only one target at a time could  
be debugged.
  
Example usage  
===================================================================
If you want to use the multi-processor system stand alone then link with  
the <b>user_i2c_standard</b>.  
If you want to build a multi-processor system with PPN networks, then link  
with <b>user_i2c_daedalus</b>.  
Change the respective sources in the Makefile to use only one of the two i2c  
drivers.  


