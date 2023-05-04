import csv
import serial
import time

ser1 = serial.Serial("/dev/ttyAMA1/", 115200)

csv_filename = "milestone02.csv"
with open(csv_filename, newline='') as csv_file:
    csv_reader = csv.reader(cvs_file, delimiter=',')

    for row in csv_reader:
        angle = row[0]
        speed = row[1]
        duration = row[2]

        command_string = f"{angle},{speed}"
        ser1.write(command_string.encode())
        print(command_string.len())
        time.sleep(duration)
        # how large is the string
        # if it was 30 for that one?

ser1.close()
