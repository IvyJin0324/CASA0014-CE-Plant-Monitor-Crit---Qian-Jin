# CASA0014-CE Plant Monitor
## Brief
This is the project presentation Crit 2 and I present my plant monitor design and how it works. This is a based on Arduiro and Rpi to get soil data and visualisation data. This is my plant, Eve. Eve is a peace lily, and I need to water it when the top inch soil feels dry. As it said in *Little Prince* 
> You become responsible, forever, for what you have tamed.
Eve is my flower, and I want to know more about her and take care. Especially, water, what Eve need most.

![121636029333_ pic ](https://user-images.githubusercontent.com/67747655/140314441-6c35af7e-b3f0-427e-a944-171cab27b181.jpg)



### Goals
- Monitor the plant data(temperature, humidity, and soil moisture levels)
- Store data on a Rpi gateway
- Visualise time series data
- Water the plant automately

### Hardware Needed
- Ardurio Board
- 
-
-

### Software Needed
- [Arduino IDE](https://www.arduino.cc/en/software)
- [MQTT Explorer](http://mqtt-explorer.com/)
- 
- d
- d
-

***
### Process
#### Step1 Connecting to Wifi
This step makes the Ardurio board have wifi. Copy the code (wifi.ino) in to a new Arduino sketch.

The ssid and password need to be modified to the lab wifi network and password.
```
const char* ssid     = "SSID here";
const char* password = "password here";
const char* host = "iot.io";
```
#### Step2 Getting the Time
This step use [ezTime library](https://github.com/ropg/ezTime) to make the Arduino know when it is. Copy the code (Getting the time.ino) into a new Arduino sketch.

The ssid and password need to be modified to the lab wifi network and password. And the Timezone is GB since we are in London. If you are in other timezone, please check the [tz database list](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones).
```
const char* ssid     = "ssid here";
const char* password = "your password here";
Timezone GB;
```
#### Step3 Publish Data to an MQTT Sever

1.

