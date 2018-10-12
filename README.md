# Arduino Real-Time Sensors
I programmed temperature and light level sensors controlled by an Arduino to provide real time output to an LCD display and the serial bus (for connection to a computer and potentially the internet).

### Application

I chose to use the device to monitor my office.

I regularly feel that my office is cold in the morning and hot in the afternoon 
so I was interested to see what those temps actually were. 
I also think it's interesting to see the differences in light levels 
produced by my various lighting setups - bright fluorescents, dim incandescent, 
and even computer screens in the dark room.

I ended up completing the same project on two different Arduino boards:

- An advanced version with color backlight on the LCD display: [Arduino Office Sensors with Backlight](https://twitter.com/jdsandifer/status/960298575291826176).

- The original version with the standard LCD display: [Arduino Office Sensors](https://twitter.com/jdsandifer/status/956687926884118528).

### Output

Sample LCD output:
```
.------------------.
| - JD's Office -  |
|  76.5°F  28 fc   |
'------------------'
```
Sample serial data:
```
Lighting - raw: 703, fc: 27;   Temperature - raw: 153, voltage: 0.75, °C: 24.72, °F: 76.50;
```

### Source Code

You can view the source for both versions here: [Colored Backlight Version](https://github.com/jdsandifer/Arduino-real-time-sensors/blob/master/src/Arduino-101/JDs_Office_Sensors.ino) and [Original Version](https://github.com/jdsandifer/Arduino-real-time-sensors/blob/master/src/Spark-fun/JDs_Office_Sensors.ino)
