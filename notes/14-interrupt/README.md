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

**polling**
> I have to repeatedly check if the keyboard is sending a data

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
