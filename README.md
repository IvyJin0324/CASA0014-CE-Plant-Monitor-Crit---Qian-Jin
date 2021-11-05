# CASA0014-CE Plant Monitor
## Brief
This is the project presentation Crit 2 and I present my plant monitor design and how it works. This is a based on Arduiro and Rpi to get soil data and visualisation data. This is my plant, Eve. Eve is a peace lily, and I need to water it when the top inch soil feels dry. As it said in *Little Prince* 
> You become responsible, forever, for what you have tamed.
Eve is my flower, and I want to know more about her and take care. Especially, water, what Eve need most.

<img width="772" alt="Screenshot 2021-11-04 at 18 01 03" src="https://user-images.githubusercontent.com/67747655/140394420-84bf050e-7e8e-499d-99b8-a284f75d3cf2.png">


### Goals
- Monitor the plant data(temperature, humidity, and soil moisture levels)
- Store data on a Rpi gateway
- Visualise time series data
- Water the plant automately

### Hardware Needed
- Ardurio Board
- Huzzah Board
- DHT22sensor
- 2 nails
- 

![141636030760_ pic](https://user-images.githubusercontent.com/67747655/140321345-109f7500-7ad2-4b1a-a84d-e9365d33f8d3.jpg)


### Software Needed
- [Arduino IDE](https://www.arduino.cc/en/software)
- [MQTT Explorer](http://mqtt-explorer.com/)
- 
- 
- d
- d
-

### MQTT Library Needed

<img width="560" alt="Screenshot 2021-11-04 at 18 00 00" src="https://user-images.githubusercontent.com/67747655/140394242-59168f3e-e4f3-46c6-819e-d7940265a36d.png">


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
Then upload this code to the board, and it get the wifi signal.

***

#### Step2 Getting the Time
This step use [ezTime library](https://github.com/ropg/ezTime) to make the Arduino know when it is. Copy the code (Getting the time.ino) into a new Arduino sketch.

The ssid and password need to be modified to the lab wifi network and password. And the Timezone is GB since we are in London. If you are in other timezone, please check the [tz database list](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones).
```
const char* ssid     = "ssid here";
const char* password = "your password here";
Timezone GB;
```
Then upload the code to the board. The board could get the London time.

<img width="843" alt="Screenshot 2021-11-04 at 17 14 39" src="https://user-images.githubusercontent.com/67747655/140387259-2fde647c-67b7-4e7b-879f-6a7ba1afdb87.png">

***

#### Step3 Publish Data to an MQTT Sever

1.As did in step 2 and 3, connect to wifi and get the time. If you want to protect your wifi ssid and password. The secrects.h is useful.

2.Initialise the builtin LED, and MQTT can turn on and off the LED.

3.Use function sendmqtt 

4.Use function reconnect to repeat the loop until the client is connected.

5.Use callback function holds the code to process messages that have been subscribed to by the sketch.

6.Use the MQTT to turn on or out LED.

***

#### Step4 Monitor soil and Environment





