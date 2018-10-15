# homebridge-nodemcu-rf
#### A simple way to control RF outlets with Siri using homebridge and a NodeMCU.

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

1. First, follow [this](https://gist.github.com/Tommrodrigues/8d9d3b886936ccea9c21f495755640dd) gist which walks you through how to flash a NodeMCU using the Arduino IDE with the addage that you must add the `rc-switch` library to the Arduino IDE for the script to work. The `.ino` file reffered to is the `NodeMCU-RF.ino` file included in this repository.

2. Assuming that you already have [homebridge](https://github.com/nfarina/homebridge#installation) already set up, the next thing you will have to do is install the http plugin you wish to use. It is recommended that you use [homebridge-http](https://github.com/rudders/homebridge-http) due to its stability and wide usage. To install [homebridge-http](https://github.com/rudders/homebridge-http), use the command:
```
sudo npm install -g homebridge-http
```

3. Below is the example `config.json` file, showing just 2 switches,  which assumes that you want to use [homebridge-http](https://github.com/rudders/homebridge-http) to communicate with your NodeMCU. Make sure to change the appropriate `CODE` and `PULSE` values to match your outlets:

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

4. And that's it! You can add as many `accessories` as you want, making sure to change the appropriate values in each url

## Wiring

![Diagram](https://image.ibb.co/gN9e19/RF-Diagram.jpg)

## Usage

As shown in the example `config.json` file above, HTTP requests must follow this example format: `http://nodemcu.local/CODE-10176012/PULSE-172`. I.e. `http://<IP address of NodeMCU>/CODE-<RF Code (8-bit)>/PULSE-<RF Pulse Length>`

You can test whether it is working by using the Terminal and typing: `curl http://nodemcu.local/CODE-10176012/PULSE-172`.
This also means that you can integrate this with any command-based plugins by writing the command above.
