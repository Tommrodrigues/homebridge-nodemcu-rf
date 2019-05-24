# homebridge-nodemcu-rf

![GitHub last commit](https://img.shields.io/github/last-commit/Tommrodrigues/homebridge-nodemcu-rf.svg) ![GitHub issues](https://img.shields.io/github/issues/Tommrodrigues/homebridge-nodemcu-rf.svg)

## Description

This script interfaces with [homebridge](https://github.com/nfarina/homebridge) to expose an RF devices to Apple's [HomeKit](http://www.apple.com/ios/home/), allowing you to integrate numerous devices into your smart home.

## Requirements

* NodeMCU

* RF transmitter module

* Knowledge of the necessary RF codes & pulse-lengths

* Pin Header Cables

* Micro-USB cable

## How-to

1. First install the `rc-switch` library from the Library manager in the Arduino IDE then follow [this](https://gist.github.com/Tommrodrigues/8d9d3b886936ccea9c21f495755640dd) gist which walks you through how to flash a NodeMCU using the Arduino IDE. The `.ino` file reffered to is the `NodeMCU-RF.ino` file included in this repository.

2. Assuming that you already have [homebridge](https://github.com/nfarina/homebridge#installation) set up, the next thing you will have to do is install [homebridge-http](https://github.com/rudders/homebridge-http) using the command:
```
npm install -g homebridge-http
```

3. Finally, update your `config.json` file following the example below, making sure to adapt it accordingly:

```json
"accessories": [
    {
      "accessory": "Http",
      "name": "Outlet",
      "on_url": "rf.local/CODE-10176012/PULSE-172",
      "off_url": "rf.local/CODE-10176009/PULSE-172",
      "http_method": "GET"
    }
]
```

## Wiring

![Diagram](https://i.ibb.co/DMvP5cB/RF-Diagram.jpg)
