# quiz 7

1.  assume an interrupt-driven keyboard that takes 100 ns for executing the isr (handling an interrupt).  how much cpu time does it take for the interrupt driven keyboard to read the 100 characters?  

total time for reading 100 characters = 100 * 100 ns

total time = time to read + time to process = 100 * 100 ns + 12.5

therefore compared to polling we are saving = 24.99 - 12.99 = 12.499

which part of the polling makes it slow?  the fact that it is continually waiting for an input for polling.
