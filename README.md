# ESP32_PROJECTS

## ESP32 Add-on in Arduino IDE
To install the ESP32 board in your Arduino IDE, follow these next instructions:

1. In your Arduino IDE, go to `File > Preferences`  
2. Enter the following into the “Additional Board Manager URLs” field: Then, click the “OK” button:   
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
3. Open the Boards Manager. Go to `Tools > Board > Boards Manager…`   
4. Search for `ESP32` and press install button for the “ESP32 by Espressif Systems“:  

## Testing the Installation
Plug the ESP32 board to your computer. With your Arduino IDE open, follow these steps:  

1. Select your Board in `Tools > Board menu` (ESP32 Dev Module)  
2. Select the Port (if you don’t see the COM Port in your Arduino IDE, you need to install the CP210x or CH340 USB to UART Bridge VCP Drivers):  
3. Open the following example under `File > Examples > WiFi (ESP32) > WiFiScan`  
4. A new sketch opens in your Arduino IDE:  
5. Press the Upload button in the Arduino IDE. you should see a “Done uploading.” message.  

## Installing the ESPAsyncWebServer library

1. Open the Library Manager.
2. Search for `espasyncwebserver` and Enter.
3. Install `ESPAsyncWebSrv` by dvarrel (The ESPAsyncWebServer library requires the AsyncTCP library to work.)
