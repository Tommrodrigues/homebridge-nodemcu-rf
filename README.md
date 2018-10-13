# homebridge-nodemcu-rf
#### A simple way to control RF outlets with Siri using homebridge and a NodeMCU

## What is it?

homebridge-nodemcu-rf allows for the cheap and easy control of an RF transmitter with a NodeMCU via [homebridge](https://github.com/nfarina/homebridge).

## How does it work?

homebridge-nodemcu-rf provides an Arduino script designed to be flashed onto a NodeMCU. After successful flashing, you will be able to quickly and simply integrate it into your pre-existing homebridge setup with the use of an http plugin such as [homebridge-http](https://github.com/rudders/homebridge-http).

## Requirements

* [NodeMCU](https://en.wikipedia.org/wiki/NodeMCU) (Or another [ESP8266](https://en.wikipedia.org/wiki/ESP8266) based board)

* RF Transmitter module (Like [this](https://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/) one)

* Knowledge of the RF codes and pulse lengths required to activate your RF outlets.

* [Pin Header Cables](https://learn.sparkfun.com/tutorials/connector-basics/pin-header-connectors) (To connect the NodeMCU to the relay module)

* Micro-USB cable (for flashing and power)

* A method for flashing the NodeMCU with Arduino scripts (NodeMCU method described [below](#how-to))

## How-to

The following is the process used to flash a NodeMCU with the Arduino IDE. Steps may vary if you are using a board other than the NodeMCU. For a video of a walkthrough of how to use the Arduino IDE to flash the NodeMCU, click [here](https://www.youtube.com/watch?v=G6CqvhXpBKM&list=LLgF700LhcjqMmwWtcsFs92Q&index=14&t=0s&frags=pl%2Cwn).

1. Download the `NodeMCU-RF.ino` script from this repository.

2. Download and install the Arduino IDE from [here](https://www.arduino.cc/en/Main/Software).

3. In the Preferences pane, under "Additional Board Manager URLs", enter the following link:
http://arduino.esp8266.com/versions/2.4.2/package_esp8266com_index.json

4. Go to the "Tools" window and select "Board Manager". Search for `ESP8266` and click on install.

5. Ensure to download the USB to UART drivers for your operating system from [this](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) link in order to be able to flash our NodeMCU.

6. Restart the Arduino IDE.

7. Add the "rc-switch" library from the "Manage Libraries" option in the "Sketch" tab.

8. Select NodeMCU from "Tools" then "Boards".

9. Now, copy and paste the contents of the `NodeMCU-RF.ino` script we downloaded from this repository earlier into the Arduino IDE window.

10. Make sure to change the variables where asked to do so. The variables you can change are surrounded by slashes (`/`) to ensure that they stand out and to help avoid you acciddentaly changing other parts of the script. Below is an example:

```C
/////////////////// CHANGE THESE VALUES //////////////////////
const char* ssid = "MyWifi"; //Name of your network
const char* password = "examplepassword"; //Password for your network
//////////////////////////////////////////////////////////////
```

11. Next, after you have plugged in your NodeMCU using a Micro-USB cable capable of data transfer, click on the "Right Arrow" (➡) icon in the top left of the Arduino IDE to start flashing.

12. Once the flashing has finished, you should see a red LED turn on, on the NodeMCU and turn off shortly after; when the red LED shows, it indicates that the NodeMCU is attempting to connect to the network you specified and the LED will turn off once it has connected successfully.

13. At this point, we have finished configuring the NodeMCU and can focus on setting up homebridge to be able to communicate with the NodeMCU. It is important to note that the NodeMCU should be available as `nodemcu.local` on your network. However, if you want to find its IP address, you can either `ping nodemcu.local` or use the Serial Output feature in the Arduino IDE when the NodeMCU is booting up and plugged into your computer.

14. Assuming that you already have [homebridge](https://github.com/nfarina/homebridge#installation) already set up, the next thing you will have to do is install the http plugin you wish to use. It is recommended that you use [homebridge-http](https://github.com/rudders/homebridge-http) due to its stability and wide usage. To install [homebridge-http](https://github.com/rudders/homebridge-http), use the command:
```
sudo npm install -g homebridge-http
```

15. Below is the example `config.json` file, showing just 2 switches,  which assumes that you want to use [homebridge-http](https://github.com/rudders/homebridge-http) to communicate with your NodeMCU. Make sure to change the appropriate `CODE` and `PULSE` values to match your outlets:

```json
{
    "bridge": {
        "name": "Homebridge",
        "username": "CC:22:3D:E3:CE:30",
        "port": 51826,
        "pin": "031-45-154"
    },
   

    "accessories": [
        {
          "accessory": "Http",
          "name": "Light 1",
          "on_url": "http://nodemcu.local/CODE-10176012/PULSE-172",
          "off_url": "http://nodemcu.local/CODE-10176009/PULSE-172",
          "http_method": "GET"
        },
        
        {
          "accessory": "Http",
          "name": "Light 2",
          "on_url": "http://nodemcu.local/CODE-10176019/PULSE-172",
          "off_url": "http://nodemcu.local/CODE-10176016/PULSE-172",
          "http_method": "GET"
        }
    ],

    "platforms": [
    ]
}
```

16. And that's it! You can add as many `accessories` as you want, making sure to change the appropriate values in each url
