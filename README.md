# CASA0014-CE Plant Monitor

- Name: Qian Jin(Ashley)
- Student ID: uncfqji
- Email: unfnqji@ucl.ac.uk
- Date: 8,Nov,2021
- Professor: Duncan Wilson

## Brief

This is the project presentation Crit 2 and I will present my plant monitor design and how it works. This project is based on Arduino and Rpi to get soil data and visualise data. This is my plant, Eve. Eve is a peace lily, and I need to water it when the top inch soil feels dry. As it said in *Little Prince* 
> You become responsible, forever, for what you have tamed.
Eve is my flower, so I want to know more about her and take care. Especially, water, what Eve need most.

<img width="600" alt="Screenshot 2021-11-04 at 18 01 03" src="https://user-images.githubusercontent.com/67747655/140394420-84bf050e-7e8e-499d-99b8-a284f75d3cf2.png">

***
## Content List
- Goals
- Hardware Needed
- Software Needed
- MQTT Library Needed
- Process
- In the Future
- References
***
### Goals
- Monitor the plant data(temperature, humidity, and soil moisture levels)
- Store data on a Rpi gateway
- Visualise collected data

### Hardware Needed
- Huzzah Board with ESP8266 Wifi
- ![Image 08-11-2021 at 03 29](https://user-images.githubusercontent.com/67747655/140679992-59962a5e-21b8-47d1-b527-2c47eb4a30a5.jpg)
(Source: https://www.amazon.co.uk/Adafruit-HUZZAH32-ESP32-Feather-Board/dp/B0743FNXK5/ref=pd_sbs_1/259-8957207-7995649?pd_rd_w=5IyS0&pf_rd_p=b3232d54-1e37-435b-b370-81046eef630a&pf_rd_r=6RHGYX6QD9NY1YMX42FP&pd_rd_r=c959d6aa-70ab-4913-802f-4771438597ec&pd_rd_wg=YPLxE&pd_rd_i=B0743FNXK5&psc=1)
- DHT22 sensor
- ![Image 08-11-2021 at 03 14](https://user-images.githubusercontent.com/67747655/140678836-b6d5cf4f-595d-4ac2-bd19-d9a2bda0480f.jpg)
(Source:https://www.amazon.co.uk/Wishiot-Temperature-Humidity-Raspberry-Project%EF%BC%88Pack/dp/B08V8SYV66/ref=sr_1_1_sspa?crid=1HCYT6I9FK8WW&keywords=DHT22&qid=1636342390&s=computers&sprefix=dht22%2Ccomputers%2C91&sr=1-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExUzBPTTg3SDRWQlBRJmVuY3J5cHRlZElkPUEwNzg0NDc1M0xOQUcxMkE2OFJUViZlbmNyeXB0ZWRBZElkPUEwMjQ2MTI1WVkwMjJXTDNJWFdaJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
- 2 nails
- Raspberry Pi
- ![Image 08-11-2021 at 03 43](https://user-images.githubusercontent.com/67747655/140681201-d45c756b-7501-4668-86bd-45e1509a4029.jpg)

### Software Needed
- [Arduino IDE](https://www.arduino.cc/en/software)
- [MQTT Explorer](http://mqtt-explorer.com/)
- [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
- [Grafana](https://grafana.com/)

### MQTT Library Needed

<img width="800" alt="Screenshot 2021-11-04 at 18 00 00" src="https://user-images.githubusercontent.com/67747655/140394242-59168f3e-e4f3-46c6-819e-d7940265a36d.png">

***
### Process
#### Step1 Connect to Wifi
This step makes the Arduino board having wifi function. Copy the script (wifi.ino) as a new Arduino sketch.

The SSID and password need to be modified for the network connection.
```
const char* ssid     = "SSID here";
const char* password = "password here";
const char* host = "iot.io";
```
Then upload this script to the board, and it get the wifi signal.
<img width="600" alt="wifi" src="https://user-images.githubusercontent.com/67747655/141293097-7e447bbb-bd7e-4310-b70c-42f06b48ced1.png">

***

#### Step2 Get the Time
This step uses [ezTime library](https://github.com/ropg/ezTime) to make the Arduino get to know the time. Copy the script (Getting the time.ino) into a new Arduino sketch.

The ssid and password need to be modified as step1. And the set Timezone to GB since we are in London. If you are in other timezone, please check the [tz database list](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones).
```
const char* ssid     = "ssid here";
const char* password = "your password here";
Timezone GB;
```
Then upload the script to the board. The board could get the London time.

<img width="843" alt="eztime" src="https://user-images.githubusercontent.com/67747655/141293417-f058fd63-8198-41bd-a410-72b3369a1194.png">

***

#### Step3 Publish Data to an MQTT Sever

1.As did in step 1 and 2, connect to wifi and get the time. If you want to protect your wifi ssid and password. The secrets.h should be used to protect your privacy content.

2.Initialise the builtin LED, and MQTT Explorer can turn on and off the LED.

3.Use function sendmqtt to view information saved in MQTT Explorer.
```
void sendMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  ++value;
  snprintf (msg, 50, "hello world #%ld", value);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucjnqji", msg);
}
```
4.Use function reconnect to repeat the loop until the client is connected.
```
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {    // while not (!) connected....
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      // ... and subscribe to messages on broker
      client.subscribe("student/CASA0014/plant/ucfnqji/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
```
5.Use callback function holds the code to process messages that have been subscribed to by the sketch.
```
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}
```
6.Use the MQTT to turn on or out LED. Publish "1" to student/CASA0014/plant/ucfnqji/inTopic


![light](https://user-images.githubusercontent.com/67747655/141294412-ec5f3332-6df2-4b6a-af05-7825a5d3c01c.jpg)

***

#### Step4 Monitor soil and Environment

<img width="600" alt="7FFB9554-1675-45F7-B587-B5180DE76F8A" src="https://user-images.githubusercontent.com/67747655/140656272-8074928f-f19c-4804-80ff-cda9e8920c45.png">

Following the fritzing diagram, I connected the DHT22 sensor(temperature / humidity sensor) and two nails(test the soil moisture).

Then I upload and run the testMoisture script(provided by Duncan) and DHT(Arduino>Files>Examples) to test sensors.

Finally, we used a CASA Plant Monitor shield which makes the packaging a little tidier.

<img width="600" alt="testmoisture" src="https://user-images.githubusercontent.com/67747655/141294709-65a1b845-3222-41ca-beee-afce086d36fe.png">
![test](https://user-images.githubusercontent.com/67747655/141296580-4c566889-25c1-4c5f-b20e-4df6c2b9aba2.png)

***
#### Step5 Publish data to MQTT Explorer

Publish the sensor data to my topic name?????? "ucfnqji" and get the temperature, humidity and soil moisture information.

In this step, I used the 'sendMQTT' fuction, and 'reconnect' fuction to get the data(like step3).

```
void sendMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  snprintf (msg, 50, "%.1f", Temperature);
  Serial.print("Publish message for t: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnqji/temperature", msg);

  Humidity = dht.readHumidity(); // Gets the values of the humidity
  snprintf (msg, 50, "%.0f", Humidity);
  Serial.print("Publish message for h: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnqji/humidity", msg);

  //Moisture = analogRead(soilPin);   // moisture read by readMoisture function
  snprintf (msg, 50, "%.0i", Moisture);
  Serial.print("Publish message for m: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnqji/moisture", msg);

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect with clientID, username and password
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");

      // ... and resubscribe
      client.subscribe("student/CASA0014/plant/ucfnqji/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
```
<img width="600" alt="MQTT" src="https://user-images.githubusercontent.com/67747655/141295441-ec914837-4d45-4d97-a7d6-de05ab32e1a1.png">


***
#### Step6: Store data by Raspberry Pi

1. Assemble Paspberry Pi box.

2. Install Paspberry Pi software and login.

`
ssh pi@celab-pi-casa0014.local
`
3.Change the device hostname.
`
device hostname
`
4. Repeat for hosts file.
`
sudo nano /etc/hosts
`
5. Quick update / upgrade
```
sudo apt update
sudo apt upgrade -y
reboot
```
6. Installing [InfluxDB](https://portal.influxdata.com/downloads/#influxdb) on RPi


#### Step7 Visualise Data

Based on the grafana, I got the beautiful chart shows the Eve's environmental information.

Now, I can know whether Eve is healthy and take care her better.

<img width="200" alt="visualisation" src="https://user-images.githubusercontent.com/67747655/141296203-e75af882-3a72-4a81-aa81-fc3b7121bf67.png">

***
## In the Future
#### Shortage

1. The final result is showed on the website. But I want to know Eve's condition whenever and wherever, so a mobile phone page is more useful because I use my phone all the day. 

2. We use two nails to minitor the soil moisture. But it is not accurate and reliable. 

#### Improvement

1. Develop an app to show Eve's environmental information.

2. Use the specific sensor to detect the soil moisture. Just like this:
![image](https://user-images.githubusercontent.com/67747655/140677633-29e53975-d32a-4d91-bd73-74c11da67a6a.png)
(Soursed: https://www.amazon.co.uk/Aideepen-Hygrometer-capacitive-Capacitive-Corrosion/dp/B08GCRZVSR/ref=sr_1_3_sspa?crid=B0J9P53GABUJ&keywords=soil+moisture+sensor&qid=1636343597&sprefix=soil+%2Caps%2C71&sr=8-3-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzVUZOQ1ZFOUdBQ1hZJmVuY3J5cHRlZElkPUEwNDc1NDY5MjlDVDhHOE9IWUhXOCZlbmNyeXB0ZWRBZElkPUEwNTA4MzYwMllTT1dJVjROQldHWiZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=)

3. Design a beautiful house for Eve and her friends.(Use 3dmax to build the model and 3D print technology to make it).

4. Achieve the watering automactically.

***
## Reference
1. https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/index.html?index=..%2F..casa0014#0
2. https://github.com/ucl-casa-ce/casa0014
3. https://github.com/balenalabs-incubator/balena-plant-saver
4. https://www.influxdata.com/
5. https://www.amazon.co.uk/Aideepen-Hygrometer-capacitive-Capacitive-Corrosion/dp/B08GCRZVSR/ref=sr_1_3_sspa?crid=14564YCQWSYYP&keywords=soil+moisture+sensor&qid=1636340476&sprefix=soil+moisture+sensor%2Caps%2C70&sr=8-3-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFDUTdPQ0ZaM0tHNkUmZW5jcnlwdGVkSWQ9QTAzNjEyMTcyTzIzQzIyRFQwRElaJmVuY3J5cHRlZEFkSWQ9QTA1MDgzNjAyWVNPV0lWNE5CV0daJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==
6. https://www.amazon.co.uk/Arduino-A000066-ARDUINO-UNO-REV3/dp/B008GRTSV6/ref=sr_1_3?crid=3TMXS6NQ4IPZ0&keywords=Arduino%2Buno&qid=1636342528&sprefix=arduino%2Buno%2Caps%2C75&sr=8-3&th=1
7. https://www.amazon.co.uk/Adafruit-HUZZAH32-ESP32-Feather-Board/dp/B0743FNXK5/ref=pd_sbs_1/259-8957207-7995649?pd_rd_w=5IyS0&pf_rd_p=b3232d54-1e37-435b-b370-81046eef630a&pf_rd_r=6RHGYX6QD9NY1YMX42FP&pd_rd_r=c959d6aa-70ab-4913-802f-4771438597ec&pd_rd_wg=YPLxE&pd_rd_i=B0743FNXK5&psc=1
8. https://www.amazon.co.uk/Wishiot-Temperature-Humidity-Raspberry-Project%EF%BC%88Pack/dp/B08V8SYV66/ref=sr_1_1_sspa?crid=1HCYT6I9FK8WW&keywords=DHT22&qid=1636342390&s=computers&sprefix=dht22%2Ccomputers%2C91&sr=1-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExUzBPTTg3SDRWQlBRJmVuY3J5cHRlZElkPUEwNzg0NDc1M0xOQUcxMkE2OFJUViZlbmNyeXB0ZWRBZElkPUEwMjQ2MTI1WVkwMjJXTDNJWFdaJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==
9. https://www.amazon.co.uk/Raspberry-Pi-3-Model-B/dp/B07BDR5PDW/ref=sr_1_4?crid=2J82CZ1IEZTJU&keywords=Raspberry%2BPi&qid=1636342929&sprefix=raspberry%2Bpi%2Caps%2C165&sr=8-4&th=1
