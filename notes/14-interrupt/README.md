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
