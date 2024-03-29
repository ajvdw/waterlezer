# Waterlezer

### HomeAssistant
Waterlezer integrates your water meter seamlessly into Home Assistant. Plug and play, no coding necessary. It comes pre-installed with calibration firmware. After joining it to your WiFi it will, you can calibrate the device easily.
The WaterLezer is designed to work with any home automation system but the current integration is for HomeAssistant only.

### ESPHome
WaterLezer is powered by ESPHome. The code is opensource and can be found on my GitHub page for waterlezer. Here you can find a default yaml file as it is used for the precompiled firmware.

### How does it work
The waterlezer hardware is designed for detecting reflection from a metalic surface of a rotating wheel that is used for counting the number of liters of water flowing through the meter. It has an IR emitting LED and an IR sensitive phototransistor. It can output two digital signals to a microcontroller. Each signal can be set to a certain amount of reflection.  

### Installation
Push the sensor on the watermeter. Connect the waterlezer with the mcu. Connect the mcu to power (using a micro usb cable and phone charger).
Once powered-on it will behave like a wifi access point. Join the network with SSID Waterlezer. You will be forwarded to a webpage (http://192.168.4.1).
On this page you can configure your home wifi settings. If configured correctly it will join your home network automatically. 
Now you can connect the sensor to the mcu using the short cable and mount the sensor on top of the watermeter.

### Calibration
Open a tap and keep the water running when you are calibrating. 
On the PCB there are two potentiometers (blue boxes). Turn the left one all the way to the left and the right one all the way to the right.
Now slowly turn the left one to the right until the led starts flashing slowly on and off (no small flashes in between).
Next slowly turn the right one to the left until the led starts alternating between off-medium-on-medium-off etc.

The blue line in the graph below shows the reflection of the turning wheel of the meter. Calibration should result in the red line. 
![reflection-graph](https://github.com/ajvdw/waterlezer/raw/main/media/reflection.png)

The calibrated points are represented by an intersection between the vertical red lines and the blue curve (Horizontal lines through the yellow stars).

### Configuration
Now you can configure the watermeter in homeassistant. The ESPHome addon should be installed. 
I have included a sample yaml file (https://github.com/ajvdw/waterlezer/blob/main/esphome/waterlezer.yaml).
The easies way to start, is by adding a device (using the +). Don't copy the content of the yaml yet. Configure it by adding the name and wifi parameters of your home wifi. Select ESP8266 from the menu. A configuration yaml is generated. Edit the configuration to make sure that your device has a static IP address (https://esphome.io/components/wifi.html). Then create a binary file to upload to the waterlezer by selecting install and download the file.

The generated bin-file has to be uploaded the the waterlezer mcu manually by accessing the waterlezer-wifi and visit the 192.168.4.1 homepage. This page has an upload button to send the generated firmware to the device. If everything went well you can access the log of the device via homeassistant.
Finally you can modify the waterlezer.yaml and configuration.yaml with the yaml settings from the sample files. The current watermeter value can be entered using the utility_meter.calibration service under developer tools. The utility_meter integration takes care of retaining the values even when the waterlezer is rebooted or power cycled.
