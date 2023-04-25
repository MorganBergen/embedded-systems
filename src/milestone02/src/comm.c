import serial

ser1 = serial.Serial("/dev/ttyAMA1")
ser1.baudrate = 115200

while(1) :
    speed = input("Input Speed: ")
    angle = input("Input Angle: ")
    command = "speed: " + str(speed) + "angle: " + str(angle)
    ser1.write(bytes(command))

ser1.close()

