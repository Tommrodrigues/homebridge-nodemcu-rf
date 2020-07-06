# homebridge-nodemcu-rf

This script interfaces with [homebridge](https://github.com/nfarina/homebridge) to expose an RF devices to Apple's [HomeKit](http://www.apple.com/ios/home/), allowing you to integrate numerous devices into your smart home.

## Requirements

* NodeMCU

* RF transmitter module

* Knowledge the RF codes (see [below](#notes))

* Pin Header Cables

* Micro-USB cable

## How-to

1. First, install the `rc-switch` and `ArduinoJson` libraries from the _Library manager_ in the Arduino IDE, then follow [this](https://gist.github.com/Tommrodrigues/8d9d3b886936ccea9c21f495755640dd) gist which walks you through how to flash a NodeMCU.

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
      "on_url": "http://rf.local/setState?code=10176012&pulse=172",
      "off_url": "http://rf.local/setState?code=10176009&pulse=172",
      "http_method": "GET"
    }
]
```

## Wiring

![Diagram](https://i.ibb.co/DMvP5cB/RF-Diagram.jpg)

## Notes

- To retrieve the RF codes, run [this](https://github.com/sui77/rc-switch/blob/master/examples/ReceiveDemo_Simple/ReceiveDemo_Simple.ino) script and with the reciever attached instead of the transmitter (follow same wiring as above). Then, simply press the outlet remote near the receiver and note down the codes.
