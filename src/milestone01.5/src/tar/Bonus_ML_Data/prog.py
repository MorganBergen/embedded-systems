import csv
import serial
import time
import filecmp
ser1 = serial.Serial("/dev/ttyAMA1", 115200)

csv_filename = "milestone2.csv"
csv_filename2 = "milestone22.csv"

with open(csv_filename,'r') as csv_file, open(csv_filename2,'r') as csv_file2:
    csv_reader = csv.reader(csv_file,delimiter=",")
    csv_reader2 = csv.reader(csv_file2,delimiter=",")



    for row1,row2 in zip(csv_reader,csv_reader2):
        if row1==row2:
            angle = row1[0]
            speed = row1[1]
            duration = row1[2]
            command_string = angle+ " " +speed+ " " +duration+ "\n"
        else:
            angle="0"
            speed="0"
            duration="4"
            command_string= angle + " " + speed + " " + duration +  "\n"








        print(command_string)



        ser1.write(bytes(command_string,encoding='utf-8'))


        time.sleep(float(duration))
        # if it was 30 for that one?

ser1.close()
