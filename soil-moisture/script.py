import serial
from datetime import datetime
import matplotlib.pyplot as plt
import keyboard
import pandas as pd
import time, threading

state = True

PORT = 'COM5'
df = pd.DataFrame([], columns=["M1", "M2", "M3", "Datetime"])

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
                m1, m2, m3 = parse_serial(line)
                #print(m1, m2, m3)
                if m1.strip() != '' and m2.strip() != '' and m3.strip() != '':
                    now = datetime.now()
                    add_row_df([int(m1), int(m2), int(m3), datetime.now().minute]) #f"{now.hour:now.minute}"
                    if state:
                        state = False
                        scheduled()
            
                    
        except:
            continue

    #time.sleep(10)

def scheduled():
    save_csv()
    plot_static()
    #df = df.iloc[0:0]
    threading.Timer(30, scheduled).start()


def save_csv():
    df.to_csv(f"data-{int(time.time())}.csv", index=False)


def parse_serial(line):
    return line.strip().split(',')


def add_row_df(vals):
    df.loc[len(df)] = vals


def plot_static():
    x = df["M1"].values.tolist()
    y = df["M2"].values.tolist()
    z = df["M3"].values.tolist()
    u = df["Datetime"].values.tolist()
    plt.switch_backend('agg')

    plt.plot(u, x, label="M1", color="red")
    plt.plot(u, y, label="M2", color="blue")
    plt.plot(u, z, label="M3", color="black")
    plt.xlabel('Datetime', fontsize=8)

    plt.ylabel('Units')
    plt.title('Moisture vs. Datetime', fontsize=20)
    plt.legend()
    plt.xticks(rotation = 60)
    plt.tight_layout()

    plt.autoscale()
    plt.savefig(f"plot-{int(time.time())}.png")
    plt.clf()
    #plt.show()



if __name__ == "__main__":
    read_serial_data()