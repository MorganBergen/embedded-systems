# interrupt

### contents

1.  [context](#context)
2.  [interrupt driven vs polling](#interrupt-driven-vs-polling)
3.  [polling example with keyboard](#polling-example-with-keyboard)
4.  [polling](#polling)
5.  [interrupt](#interrupt)
6.  [interrupt operation](#interrupt-operation)
7.  [two parts to interrupt drive io](two-parts-to-interrupt-drive-io)
8.  [causing the interrupt to occur](#causing-the-interrupt-to-occur)
9.  [conditions for having an interrupt](#conditions-for-having-an-interrupt)

## context

we saw that interrupt was sent by adc to cpu when data conversion is done and digital output is read, but interrupt is not the only way an external device can communicate with the cpu.  

## interrupt driven vs polling

-  **polling**  the cpu checks the keybaord repeatedly if it wants to send data
-  **interrupt** the io device interrupts when its ready to send data

-  **polling** [cpu] <- [keyboard]
-  **example**  starting at the clock all night to do so that we can have breakfast at 7:00 am

>  "I have to repeatedly check if the keyboard is sending a data..."

-  **interrupt** [cpu] <- [keyboard]
-  **example**  setting up an alarm for 7:00 am to interrupt the sleep

>  "hey cpu a key has been struck.  the ascii code is in the input device register, please stop and read it now"

## polling example with keyboard

-  two io registers are needed to facilitate polling for an input device like keyboard
    -  **status register** indicates a key struck
    -  **data register** stores the input data from keyboard

-  cpu regularly checks the status register
-  if the specific the specific bit of the status register is set
    -  cpu reads from the data register

## polling

## interrupt

-  interrupt can be thought of as notifications for the processor
-  hardware interrupt devices include timer, desk, keyboard to cpu

## interrupt operation

## two parts to interrupt drive io

1.  causes the interrupt to occur
2.  handling the interrupt request

## causing the interrupt to occur

## conditions for having an interrupt

## io device must want service

## io device has the right to request the service

## the urgency of the interrupt

## generation of an interrupt signal

## interrupts can happen at anytime

## interrupt signal

## handling the interrupt request

## handling an interrupt goes through 3 strages

## 1 initiate the interrupt

## vector interrupts

## 2 service the interrupt

## 3 return from the interrupt

## execution flow for interrupt driven io

## references

## review

## vector interrupts

## direct mode interrupts

1.  interrupt signal
2.  jump to trap handler
3.  read cause register and jump to the corresponding isr
4.  start executing interrupt handler

## question

suppose we are asked to write a program that takes a sequence of 100 characters typed on a keyboard and processes the information contained in those 100 characters.

-  assume the characters are typed at a rate of one character at every 0.125 seconds
-  assume the processing of the 100 character sequence takes 12.4999 seconds

how much cpu time will it take to complete the task with a polling driven keyboard?

the cpu does not know when the data is coming so it polls constantly.  thus the time needed to recieve 100 character sequence = 100 * 0.125 seconds = 12.5 seconds

total time = time to read + time to process = 12.5 + 12.4999 = 24.9999 seconds

## case study si five interrupts

## si-five interrupt architecture

based on the source of interrupts, there are two main forms of interrupt in the si-five processor.  local and global (external) interrupts.  FE310-G002 interrupt archietcure block diagram

## local and global interrupts

## control and status registers (csrs)

-  privilege registers for software / hardware communication
-  use special instructions to read/write
-  interrupt related csrs
-  `mstatus` used to enable or disable global interrupt
-  `mie` enable / disable individaul interrupts

## machine status register `mstatus`

## machine interrupt enable `mie`

## machine interrupt pending `mip`

## machine trap vector `mtvec`

## machine cause `mcause`

## interrupt priorities

-  we discussed priorities in last class
-  in sifive there are the local and global interrupts that have different priorities
-  sifive interrupts are prioritized as follows, in decreasing order of priority 
    -  machine external/global interrupts
    -  machine software interrupts
    -  machine timer interrupts
-  individual priorities of global interrupts are determined by the plic

## setting external/global interrupts

-  each plic interrupt source can be assigned a priority by writing to its 31 bit memory mapped `priority` register
-  supports 7 levels of priority (0 being lowest)
