# Waterlezer

### HomeAssistant
Waterlezer integrates your water meter seamlessly into Home Assistant. Plug and play, no coding necessary. It comes pre-installed with calibration firmware. After joining it to your WiFi it will, you can calibrate the device easily.
The WaterLezer is designed to work with any home automation system but the current integration is for HomeAssistant only.

### ESPHome
WaterLezer is powered by ESPHome. The code is opensource and can be found on my GitHub page for waterlezer. Here you can find a default yaml file as it is used for the precompiled firmware.

### Calibration
Connect the mcu to power, it will behave like a wifi access point. Join the network with SSID Waterlezer. You will be forwarded to a webpage (http://192.168.4.1).
On this page you can configure your home wifi settings. If configured correctly it will join your home network automatically. 
Now you can connect the sensor to the mcu using the short cable and mount the sensor on top of the watermeter.
Open a tap to let the water running when you start calibrating. 
On the PCB there are two potentionmeters (blue). Turn the left one all the way to the left and the right one to the right.
Now slowly turn the left one to the right until the led starts flashing slowly on and off (no small flashes in between).
Next slowly turn the right one to the left until the led starts alternating between off-medium-on-medium-off etc.

The blue line in the graph below shows the reflection of the turning wheel of the meter. Calibration should result in the red line. 
![reflection-graph](https://github.com/ajvdw/waterlezer/raw/main/media/reflection.png)

### Configuration
Now you can configure the watermeter in homeassistant. The ESPHome addon should be installed. I have included a sample yaml file (https://github.com/ajvdw/waterlezer/blob/main/esphome/waterlezer.yaml).
The easies way to start, is by adding a device (using the +). Don't copy the content of the yaml yet. Configur it by adding the name and wifi parameters of your home wifi. Select ESP8266 from the menu. A configuration yaml is generated. Edit the configuration to make sure that your device has a static IP address (https://esphome.io/components/wifi.html). Then create a binary file to upload to the waterlezer by selecting install and download the file.
This file has to be uploaded the the waterlezer mcu manually by accessing the waterlezer-wifi and visit the 192.168.4.1 homepage. This page has an upload button to send the generated firmware to the device. If everything went well you can access the log of the device via homeassistant.
Finally you can modify the configuration with the watermeter specific yaml settings from the sample. The offset parameter represents the current watermeter value or startvalue in liters.





