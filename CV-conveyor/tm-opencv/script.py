import cv2
import serial
import time
from time import sleep

from teachable_machine import TeachableMachine

ser = serial.Serial('COM12', 9600)

cap = cv2.VideoCapture(0)
model = TeachableMachine(model_path="model/keras_model.h5", labels_file_path="model/labels.txt")

image_path = "screen.jpg"
while True:
    _, frame = cap.read()
    frame = frame[240:,:]

    if (frame is not None):
        cv2.imwrite(image_path, frame)
        prediction = model.classify_image(image_path)
        pred = prediction["class_name"]
        print(pred, prediction["class_confidence"])
        #print(prediction)

        cv2.imshow("v", frame)

        if pred == "Blue\n":
            ser.write(b'0')
        elif pred == "Green\n":
            ser.write(b'1')

    if cv2.waitKey(1) & 0xFF==ord('q'):
        break

cap.release()
cv2.destroyAllWindows()