#  milestone

###  contents

1.  [tree](#tree)
2.  [intro](#intro)
3.  [milestone 01](#milestone-01)
4.  [**part 01** setting up the i2c via the metal library](#part-1-setting-up-the-i2c-via-the-metal-library)
5.  [**part 02** configuring the pca9685](#part-02-configuring-the-pca9685)
6.  [**task 01** the breakup function](#task-01-the-breakup-function)
7.  [**task 02** the streering function](#task-02-the-steering-function)

```
❯ tree
.
├── docs
│   ├── FE310-G002.pdf
│   ├── hifive1-revb-pinout.png
│   ├── hifive1b-getting-started-guide_v1.1.pdf
│   └── sg90_microservo_datasheet.pdf
├── include
│   └── README
├── lib
│   └── README
├── platformio.ini
├── src
│   ├── eecs388_i2c.c
│   ├── eecs388_lib.c
│   └── eecs388_lib.h
└── test
    └── README

6 directories, 11 files
```

##  intro

this src will implement an rc car's components by incorporating elements from the previous labs.  I also will be using a new board i.e. `pca9695` for driving servo and dc motors.  `pca9695` users `i2c` to receive commands from hi-five board to generate pwm signal for the servo and dc motors.  the final project weighs `15%` of your total course grade.

the car prototype that you are going to use has seven main components

1.  hi-five board
2.  pi board
3.  motot driver `pca9695` 4-lidar
4.  dc motot
5.  servo motot
6.  electronic speed controller ecs

your goal in this project is to first use the hi-five board to send i2c commands to `pca9695` to drive the servo motot (for streering) and dc motots (for moving forward and backwards) (milestone 1).  then connect pi to hi-five board using `uart`.  this is to set up a connection between the two boards for sending steering commands from the pi to the hi-five board (milestone 2).  lastly, you are going to control the car using a sequence of commands sending the streering commands from the pi to the hi-five board using `uart` and then to the motors using `pwm` i1c controller (milestone 3).

the project must have a group of 4 individuals

##  milestone 01

in this milestoen you will configure the `pwm` controller and use the hi-five board to drive the servo and dc motor.  your milestone 1 source code (`milestone1.tar.gz`) is uploaded a:wq
:wq

