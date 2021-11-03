# Waterlezer

### HomeAssistant
Waterlezer integrates your water meter seamlessly into Home Assistant. Plug and play, no coding necessary. It comes pre-installed with calibration firmware. After joining it to your WiFi it will, you can calibrate the device easily.
The WaterLezer is designed to work with any home automation system but the current integration is for HomeAssistant only.

### ESPHome
WaterLezer is powered by ESPHome. The code is opensource and can be found on my GitHub page for waterlezer. Here you can find a default yaml file as it is used for the precompiled firmware.

### Installation
Connect the mcu to power, it will behave like a wifi access point. Join the network with SSID Waterlezer. You will be forwarded to a webpage (http://192.168.4.1).
On this page you can configure your home wifi settings. If configured correctly it will join your home network automatically. 
Now you can connect the sensor to the mcu using the short cable and mount the sensor on top of the watermeter.
Open a tap when you start calibrating. On the PCB there are two potentionmeters. Turn the left one all the way to the left and the right one to the right.
Now slowly turn the left one to the right until the led starts flashing slowly on and off (no small flashes in between).
Next slowly turn the right one to the left until the led starts alternating between off-half-on-half-off etc.

The red line in the graph below shows the reflection of the turning wheel of the meter. Calibration should result in the blue line. 
![reflection-graph](https://github.com/ajvdw/waterlezer/raw/main/media/reflection.png)

Finally you can configure the watermeter in homeassistant. The ESPHome addon should be installed. I have included a sample yaml file.
