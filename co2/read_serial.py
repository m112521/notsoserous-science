import serial
import pandas as pd
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

PORT = 'COM10'
plant_number = 0
people_number = 1

ser = serial.Serial(PORT, 9600, timeout=1)
time.sleep(2)

df = pd.DataFrame()


def read_serial_data():
    while True:
        line = ser.readline().decode()
        if (len(parse_serial(line))):
            co2, tvoc = parse_serial(line)
            print(co2, tvoc)


def parse_serial(line):
    return line.strip().split(',')


def save_csv():
    df.to_csv("data.csv")


if __name__ == "__main__":
    read_serial_data()

# input # of plants
# save to file: date - co2,tvoc - # of plants
# plt show realtime graph
# plt read file -> graph timeseries