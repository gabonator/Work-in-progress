Sygic websocket debugging api
==========

Sygic navigation app for iPhone contains hidden websocket server for debugging purposes. Unfortunatelly android builds do not have this feature. It can be used for controlling the app as well as for obtaining valuable information directly from the app during run time. For enabling the websocket service go to application settings -> info -> about -> tap three times at the list and hidden options will appear -> enable websocket server:
![](screenshots/ios_step_1.jpg)
![](screenshots/ios_step_2.jpg)
![](screenshots/ios_step_3.jpg)
![](screenshots/ios_step_4.jpg)

Then you need to know the IP address of your iphone.
![](screenshots/ios_ip.jpg)

On a computer running on the same network, open *hud/index.html* or *gpsemu/index.html* and have fun. GpsEmu serves ak gps coordinate emulator utilizing google maps api. To run the hud application you must manually set the IP address of your phone (see source code), gps emulator asks for the address automatically.

![](screenshots/app_gpsemu.jpg)
![](screenshots/app_hud.jpg)

If you want to take your experiments further, feel free to contact me at *gvalky at sygic dot com*.