Garmin HUD interface in C++
======================

Because I was unable to disassemble the Navigon application for locating the code implementing the communication with Garmin HUD, I decided to open the gadget, identify the internal connection between ST32F100 microcomputer and bluetooth module. Then attaching the oscilloscope to proper pins and they were damn small, so I had to use needle, I sniffed some packets. The internal UART decoder in oscilloscope gave some nonsense characters while I was expecting some ASCII commands in human readable format. I took snapshots of the signals (Waveform\*.SVG) and analysed them manually (Waveform\decoder.html). The communication between bluetooth module and microcomputer is regular UART with 10 bit frames (1 startbit, 8 data bits, 1 stopbit). Then I realized that the oscilloscope gave exactly the same results as manual decoding. After enabling logging the frames into text file (Logs\*.txt) I tried sending each of these frames to the bluetooth serial port through FAR manager and noted what was displayed on the hud. Then I was able to identify various commands and their description is in PacketDesc.txt. Code in C++ implementing this protocol is in HudInterface.h. If you don't know how to connect to bluetooth device, maybe the bluetooth library (Bluetooth.h, Main.cpp) will came in handy. I tried to convert the library also for WindowsCE, but without success :(


Description of garmin protocol, stuffing and crc can be found here: http://www8.garmin.com/support/commProtocol.html

And here is a video of Sygic Navigation working with Garmin HUD, I am proud to say that all this took about 24 hours:
http://www.youtube.com/watch?v=WK9IV0syupE

