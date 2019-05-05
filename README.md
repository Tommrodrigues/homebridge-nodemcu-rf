# homebridge-nodemcu-rf

![GitHub last commit](https://img.shields.io/github/last-commit/Tommrodrigues/homebridge-nodemcu-rf.svg) ![GitHub issues](https://img.shields.io/github/issues/Tommrodrigues/homebridge-nodemcu-rf.svg)

## Description

This script interfaces with a [homebridge](https://github.com/nfarina/homebridge) plugin to expose an RF devices to Apple's [HomeKit](http://www.apple.com/ios/home/), adding smart-home functionality to 'dumb' devices.

## Requirements

* NodeMCU

* RF Transmitter module (Like [this](https://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/) one)

* Knowledge of the RF codes and pulse lengths required to activate your RF outlets.

* Pin Header Cables

* Micro-USB cable

* A method for flashing the NodeMCU with Arduino scripts (NodeMCU method described [below](#how-to))

## How-to

1. First, ensure that you have added the `rc-switch` library to the Arduino IDE. Next, follow [this](https://gist.github.com/Tommrodrigues/8d9d3b886936ccea9c21f495755640dd) gist which walks you through how to flash a NodeMCU using the Arduino IDE. The `.ino` file reffered to is the `NodeMCU-RF.ino` file included in this repository.

2. Assuming that you already have [homebridge](https://github.com/nfarina/homebridge#installation) set up, the next thing you will have to do is install the http plugin you wish to use. It is recommended that you use [homebridge-http](https://github.com/rudders/homebridge-http) due to its stability and wide usage. To install [homebridge-http](https://github.com/rudders/homebridge-http), use the command:
```
sudo npm install -g homebridge-http
```

3. Below is the example `config.json` file, showing just 2 switches,  which assumes that you want to use [homebridge-http](https://github.com/rudders/homebridge-http) to communicate with your NodeMCU. Make sure to change the appropriate `CODE` and `PULSE` values to match your outlets:

```json
"accessories": [
    {
      "accessory": "Http",
      "name": "Light 1",
      "on_url": "http://IP_ADDRESS/CODE-10176012/PULSE-172",
      "off_url": "http://IP_ADDRESS/CODE-10176009/PULSE-172",
      "http_method": "GET"
    },
        
    {
      "accessory": "Http",
      "name": "Light 2",
      "on_url": "http://IP_ADDRESS/CODE-10176019/PULSE-172",
      "off_url": "http://IP_ADDRESS/CODE-10176016/PULSE-172",
      "http_method": "GET"
    }
]
```
Simply change the `name` to your choosing and then change `IP_ADDRESS` to the IP address of the NodeMCU.

4. And that's it! You can add as many `accessories` as you want, making sure to change the appropriate values in each url

## Wiring

![Diagram](https://i.ibb.co/DMvP5cB/RF-Diagram.jpg)

## Usage

As shown in the example `config.json` file above, HTTP requests must follow this example format: 
```
http://IP_ADDRESS/CODE-10176012/PULSE-172
```

You can test whether it is working by using the Terminal and typing: `curl http://IP_ADDRESS/CODE-10176012/PULSE-172`.
This also means that you can integrate this with any command-based plugins by writing the command above.
