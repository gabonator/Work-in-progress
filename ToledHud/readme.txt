Toled hud (or Let'sHUD) is another HUD device for your car. What makes this product different from others is the fact, that this HUD does not project the image on the car's front window. Instead, it displays the instructions directly on the transparent glass display using OLED technology. This approach provides ultimately high light intensity during daylight. In comparison with Garmin hud which uses Vacuum fluorescent display technology with high power consumption and heat dissipitation, Toled hud is very lightweight, small and consumes less than  100mA at 5V. Communication with smartphone is done via bluetooth link. Unfortunatelly, the manufacturer have  used cheap bluetooth module without BLE support, so it is possible to pair it only with Android devices. After  desoldering the bluetooth module and swapping it with BLE compatible module it should be possible to extend the compatibility with iOs devices.

The android application transfers driving instructions from Sygic Truck (or Sygic Taxi) navigation to the paired toled hud display. Inteprocess communication is done through Android Intents (consumer navigation from Google Play store does not support this). The application is simple single screen Activity, without any background process. Sometimes the OS will terminate the application, but it will probably happen only when the device is running on battery power. 

If you want to try it, you will need special license for activating HUD intents from Sygic navigation. Contact me and I will give you some evaluation activation codes.

Folders:
 - *Documentation*: Specification of communication protocol
 - *MsvcTest*: Test application for MS Visual Studio
 - *SygicMfdReceiver*: Demo java code for obtaining HUD information from Sygic navigation
 - *AndroidApp*: Final application
 
Useful links:
  - Manufacturer Won motors: http://www.wonmotors.com/sub1/let's_hud.html
  - Hardware specification: http://www.headupdisplay.co.kr/transparent-hud/
  - Video: https://www.youtube.com/watch?v=uCkIvQwFa_A
  - Video: https://www.youtube.com/watch?v=D5IVaCYuuvs

Credits:
  - Miodrag Relic (for providing the hud device to me, which I broke after two days :)
  - Lukas Apalovic (sygic multifunction display sample code)
