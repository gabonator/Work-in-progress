This is a application for visualization of measured blood pressure values.
For collecting of bp data it uses BOSO Medicus prestige BT blood pressure meter,
a connector application connects to this bluetooth enabled device and downloads
all available measurements, then it uploads these measurements onto web based
simple management system.

See the /Man folder for some screenshots

Some release build of connector application (boso_bp.exe) is provided here,
but please do not use it. Build your own instead (use Visual Studio 2010)
and do not forget to set the correct virutal serial port number and
path/ip to the PHP script.

This project demonstrates the use of Corscience protocol, and should be useful
for someone who is trying to interface any Corscience device with PC connection.

I would like to thank to Harald Weigle from Boso who has kindly provided me the
protocol datashee which you can find in the /man folder.

Gabriel Valky, 2012

