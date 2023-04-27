#  milestone 02

1.  [general](#general)
2.  [commands in pseudo](#commands-in-pseudo)
3.  [tasks](#tasks)
4.  [submission](#submission)

##  general

instead of using terminals, you will now create a python program on the pi to communicate with the hifive.  your task is to send formatted command strings to the hifive that can control the steering angle, speed and duration of a command.  these commands will be supplied from a **csv** file on the pi.  in this milestone, you will implement the necessary code for parsing that input file and sending the correct values to the hifive from the pi.

the following flowchart describes this milestone:

<img src="./assets/diagram.png">

a "command" consists of a speed value and a steering angle value that the car should be set to, and a duration value for how long to hold that configuration.  the commands in the input csv file will have the following format

### command format `<angle value>, <speed value>, <duration>`

-  the angle value will be an integer between -45 and 45
-  the speed value will be 1, 2, 3 for driving forward at different speeds
-  the speed value will be -1, -2, -3 for drive backward at different speeds
-  the duraction will be the time, in _seconds_, for which that command should run

### command literal `30, 2, 3`

the command above means the car should steer to 30 degrees, move forward with speed flag 2, and hold this configuration for 3 seconds.  to read in the input file you can use python's **csv** library.  [here is a tutorial to on how ot use the csv library](https://realpython.com/python-csv/) for reference.  

after reading these values in from the input file on the pi, you will generate your command strings conatining the information you collected to be sent to the hifive.  the actual format of the command string is up to you; you can send them as is (i,e. as a string containing three values separated by commas), add additional text to indicate each parameter or you can use the sample format you will find below.

after generating a command string, you will need to send it via the serial connection **uart** to the hifive from the pi.  at the hifive end, you will need to read in these command strings being sent from the pi and repeat them back to the pi using a different uart commection similar to what we did in this [board to board communication](../lab09/).

the following pseudo-code provides a general idea of the code you will need to write

##  commands in pseudo

```python
#  pseudo code
open a serial connection to /dev/ttyAMA1
open csv input file
for each line in input file:
    read angle value    -> angle
    read speed value    -> speed
    read duration value -> duration 
    command_str = "angle: " + angle + "speed: " + speed + "duration: " + duration
    write command to /dev/ttyAMA1
close serial connection
```

to achieve the functionality from above, you need to use pythons `pySerial` api which can be used by importing the `serial` package.  view tutorial [here](https://pyserial.readthedocs.io/en/latest/shortintro.html) 

###  `import serial`

with pySerial, you should create a serial channel for writing to the hifive over `/dev/ttyAMA1`.  note that the channel should be opened with the baudrate `115200` bps.

###  `ser1 = serial.Serial(...)`

the command strings you generate can then be sent to the hifive by using the serial write function:

###  `ser1.write(command_str)`

however, the **write** function requires a byte value, which must be formed from whatever type your command variable is in order to send it to the hifive.

###  `ser1.write(bytes(command_str))`

finally, after all of the commands are sent, the serial commections can be closed by invoking the serial close function 

###  `ser1.close()`

##  tasks 

1.  wire up the hifive and the pi the way you did for lab 9 [board to board communication](../lab09/) 
2.  on the hifive use the same program you wrote for lab 9 [board to board communication](../lab09/) for communicating between the hifive and raspeberry pi.  build and upload it to the hifive to get it ready to receive the command strings from the pi.
3.  on the pi, create a python source file called `prog.py` and write your python code inside this file.
4.  download the input csv file, you need to read this file in your python code to get the commands.
5.  open a new terminal window and run the screen command which receives characters (i.e. run screen with `/dev/ttyAMA2`) run your python program and demonstrate the transferring of information. execute the program as `python prog.py` 

##  submission

`prog.py`


