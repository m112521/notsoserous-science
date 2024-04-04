# ESP8266


NodeMCU 1.0

/Botfather
/mybotid


```c++
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```


Buzzer:

```c++
pinMode (PinBuzzer, OUTPUT);
tone(PinBuzzer, 1500); // f=1500 Hz
delay(200);
tone(PinBuzzer, 1000); // f=1000 Hz
delay(200);
tone(PinBuzzer, 500);
delay(200);

noTone(PinBuzzer); 
```
