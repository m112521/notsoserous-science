import serial
from datetime import datetime
import matplotlib.pyplot as plt
import keyboard
import pandas as pd
import time, threading


PORT = 'COM5'
df = pd.DataFrame([], columns=["Light", "Moisture", "Datetime"])

ser = serial.Serial(PORT, 9600, timeout=1)
time.sleep(2)


def read_serial_timer():
    #print(time.ctime())
    line = ser.readline().decode()
    if (len(parse_serial(line))):
        light, moisture = parse_serial(line)
        print(light, moisture)
        add_row_df([int(light), int(moisture), datetime.now()])
    
    threading.Timer(10, read_serial_timer).start()


def read_serial_data():
    while True:
        if keyboard.read_key() == "p":
            save_csv()
            plot_static()
            break 

        line = ser.readline().decode()
        if (len(parse_serial(line))):
            light, moisture = parse_serial(line)
            print(light, moisture)
            add_row_df([int(light), int(moisture), datetime.now()])
        
        time.sleep(10)


def save_csv():
    df.to_csv("data.csv", index=False)


def parse_serial(line):
    return line.strip().split(',')


def add_row_df(vals):
    df.loc[len(df)] = vals


def plot_static():
    x = df["Light"].values.tolist()
    y = df["Moisture"].values.tolist()
    u = df["Datetime"].values.tolist()
    plt.plot(x, u, label="Light", color="red")
    plt.plot(y, u, label="Moist", color="blue")
    plt.xlabel('Datetime', fontsize=8)

    plt.ylabel('Units, ppm')
    plt.title('Kight/Moist vs. Datetime', fontsize=20)
    plt.legend()
    plt.xticks(rotation = 60)
    plt.tight_layout()

    #plt.autoscale()
    plt.savefig(f"plot-{int(time.time())}.png")
    plt.show()


if __name__ == "__main__":
    read_serial_data()
