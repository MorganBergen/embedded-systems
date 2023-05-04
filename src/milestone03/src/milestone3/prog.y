import csv 
import serial
import time

ser1 = serial.Serial("/dev/ttyAMA1", 115200)

csv_filename = "milestone2.csv"
with open(csv_filename,'r') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')

    for row in csv_reader:
        angle = row[0]
        speed = row[1]
        duration = row[2]

        command_string = "angle: "+angle +" speed: "+ speed +" duration: "+ duration
        ser1.write(bytes(command_string))
        print(command_string)
        time.sleep(float(duration))
        # how large is the string
        # if it was 30 for that one?

ser1.close()
