import serial
from datetime import datetime
import matplotlib.pyplot as plt
import keyboard
import pandas as pd
import time, threading

state = True

PORT = 'COM14'
df = pd.DataFrame([], columns=["Light", "Moisture", "CO2", "Datetime"])

ser = serial.Serial(PORT, 9600, timeout=1)
time.sleep(2)



def read_serial_data():
    global state
    while True:
        if keyboard.is_pressed('q'):
            break

        try:
            line = ser.readline().decode()
            if (len(parse_serial(line)) == 3):
                light, moisture, co2 = parse_serial(line)
                print(light, moisture, co2)
                if light.strip() != '' and moisture.strip() != '' and co2.strip() != '':
                    add_row_df([int(light), int(moisture), int(co2), datetime.now()])
                    if state:
                        state = False
                        scheduled()
            
                    
        except:
            continue

    time.sleep(10)

def scheduled():
    save_csv()
    plot_static()
    #df = df.iloc[0:0]
    threading.Timer(3600, scheduled).start()


def save_csv():
    df.to_csv(f"data-{int(time.time())}.csv", index=False)


def parse_serial(line):
    return line.strip().split(',')


def add_row_df(vals):
    df.loc[len(df)] = vals


def plot_static():
    x = df["Light"].values.tolist()
    y = df["Moisture"].values.tolist()
    z = df["CO2"].values.tolist()
    u = df["Datetime"].values.tolist()
    plt.plot(u, x, label="Light", color="red")
    plt.plot(u, y, label="Moist", color="blue")
    plt.plot(u, z, label="CO2", color="black")
    plt.xlabel('Datetime', fontsize=8)

    plt.ylabel('Units')
    plt.title('Light/Moist/CO2 vs. Datetime', fontsize=20)
    plt.legend()
    plt.xticks(rotation = 60)
    plt.tight_layout()

    plt.autoscale()
    plt.savefig(f"plot-{int(time.time())}.png")
    plt.clf()
    #plt.show()


if __name__ == "__main__":
    read_serial_data()