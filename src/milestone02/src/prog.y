import csv
import serial
import time

ser1 = serial.Serial("/dev/ttyAMA1", 115200)

csv_filename = "milestone2.csv"
with open(csv_filename,'r') as csv_file:
    csv_reader = csv.reader(csv_file,delimiter=",")

    for row in csv_reader:

        angle = row[0]
        speed = row[1]
        duration = row[2]

        command_string = angle+ " " +speed+ " " +duration+ "\n"
        ser1.write(bytes(command_string,encoding='utf-8'))
        print(command_string)

        time.sleep(float(duration))
        # if it was 30 for that one?

ser1.close()
