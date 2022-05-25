import csv
import serial
#from serial.serialwin32 import Serial

SerialIn = serial.Serial("COM5",9600)

with open('ECGdata5.csv', mode='w', newline='') as ecg_file:
    ecg_writer = csv.writer(ecg_file)
    line_count=0
    try:
        while True:
            while line_count<3000:
                data_in = SerialIn.readline()
                data_raw = data_in.decode('utf-8')
                print(data_raw)
                
                
                if line_count==0:
                    ecg = str(data_raw[0:11])
                       
                else:
                  # Turn string into float value:   
                   ecg = (str(data_raw[0:5]))
                
                
                ecg_writer.writerow([ecg])
                line_count = line_count+1
            if line_count==3000:
                break
            

    except KeyboardInterrupt:
        SerialIn.close()