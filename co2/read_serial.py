import serial
import keyboard
import pandas as pd
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
from datetime import datetime
from mpl_toolkits import mplot3d

import matplotlib.dates as mdates


PORT = 'COM5'
plant_number = 0
people_number = 1

ser = serial.Serial(PORT, 9600, timeout=1)
time.sleep(2)

df = pd.DataFrame([], columns=["CO2", "Light", "Moisture", "Datetime"])

# realtime plot
xs = []  
ys = [] 
dt = []  
us = []

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

# plt read file -> plot timeseries: all period, one day
# plt show realtime graph


def read_serial_data():
    while True:
        if keyboard.read_key() == "p":
            save_csv()
            break 

        line = ser.readline().decode()
        if (len(parse_serial(line))):
            co2, light, moisture = parse_serial(line)
            print(co2, light, moisture)
            add_row_df([int(co2), int(light), int(moisture), datetime.now()])
            

def parse_serial(line):
    return line.strip().split(',')


def add_row_df(vals):
    df.loc[len(df)] = vals


def save_csv():
    df.to_csv("data.csv", index=False)


def read_csv(filename):
    global df
    df = pd.read_csv(filename)
    #print(datetime.strptime(df["datetime"].loc[0], '%Y-%m-%d %H:%M:%S.%f'))
    
    #plot_static()
    plot_static3D()


def plot_static():
    x = df["datetime"].values.tolist()
    y = df["CO2"].values.tolist()
    z = df["Moisture"].values.tolist()
    u = df["Moisture"].values.tolist()
    plt.plot(x, y, label="CO2", color="red")
    plt.plot(x, u, label="Light", color="black")
    plt.plot(x, u, label="Moist", color="blue")
    plt.xlabel('Datetime', fontsize=8)

    plt.ylabel('CO2, ppm')
    plt.title('CO2 vs. Datetime', fontsize=20)
    plt.legend()
    plt.xticks(rotation = 60)
    plt.tight_layout()

    #plt.autoscale()
    plt.savefig(f"plot-{int(time.time())}.png")
    plt.show()

def f(x, y):
    return np.sin(np.sqrt(x ** 2 + y ** 2))

def plot_static3D():
    fig = plt.figure()
    ax = plt.axes(projection='3d')

    # Data for a three-dimensional line
    zline = np.linspace(0, 15, 1000)
    xline = np.sin(zline)
    yline = np.cos(zline)
    ax.plot3D(xline, yline, zline, 'gray')

    # Data for three-dimensional scattered points
    zdata = 15 * np.random.random(100)
    xdata = np.sin(zdata) + 0.1 * np.random.randn(100)
    ydata = np.cos(zdata) + 0.1 * np.random.randn(100)
    ax.scatter3D(xdata, ydata, zdata, c=zdata, cmap='Greens')
    # surface
    x = np.linspace(-6, 6, 30)
    y = np.linspace(-6, 6, 30)
    X, Y = np.meshgrid(x, y)
    Z = f(X, Y)
    print([])

    ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap='viridis', edgecolor='none')

    plt.show()


def plot_realtime(i, xs, ys):
    line = ser.readline().decode()
    if (len(parse_serial(line))):
        co2, tvoc, moisture = parse_serial(line)
        xs.append(int(co2))
        ys.append(int(tvoc))
        dt.append(datetime.now())
        us.append(int(tvoc))

        ax.clear()
        ax.plot(xs, dt, label="CO2")
        ax.plot(ys, dt, label="TVOC")

        plt.xticks(rotation=45, ha='right')
        plt.subplots_adjust(bottom=0.30)
        plt.title('CO2 vs Datetime')
        plt.ylabel('CO2, ppm')
        #plt.legend()
        plt.axis([1, None, 0, 1.1]) #Use for arbitrary number of trials


if __name__ == "__main__":
    #read_serial_data()
    read_csv("data.csv")

    #ani = animation.FuncAnimation(fig, plot_realtime, fargs=(xs, ys), interval=1)
    #plt.show()