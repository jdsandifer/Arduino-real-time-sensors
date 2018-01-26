# Arduino Real Time Sensors
I created temperature and light level sensors controlled by an Arduino to provide real time output to a LCD display and the serial bus (for connection to a computer and potentially the internet).

I chose to set up the device to monitor my office for the fun of it!

I regularly feel that my office is cold in the morning and hot in the afternoon 
so it will be interesting to see what those temps actually are. 
I also think it's interesting to see the differences in light levels 
produced by my various lighting setups - bright flourescents, incandescents, 
and even computer screens in the dark room.

See an image of it in action here: [Arduino Office Sensors](http://www.jdsandifer.com/software-developer/image/Arduino_office_sensors.JPG).

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
