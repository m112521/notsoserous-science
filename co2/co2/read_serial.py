import serial
import pandas 
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

PORT = 'COM5'
plant_number = 0
people_number = 1

ser = serial.Serial(PORT, 9600, timeout=1)
time.sleep(2)


while True:
    line = ser.readline().decode()
    print(line)

# Read from serial (string of a type CO2: 7992ppm, TVOC: 1156)


# input # of plants
# save to file: date - co2,tvoc - # of plants
# plt show realtime graph
# plt read file -> graph timeseries