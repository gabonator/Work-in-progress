Panstamp swap
-----------------

Panstamp is a small arduino based wireless enabled module. It uses CC1101 configurable radio frontend. SWAP (Simple wireless abstract protocol) provides abstraction layer for communication with CC1101 radio. I tried to improve this protocol to support following features:
- Packet delivery information - Receiver notifies sender about successfull reception of packet, in case of transmission problems, it tries to resend the packet
- Mediator - this allow forming effective MESH netwoks or for accessing distant nodes
- Inquiry - scanning for modules in RX mode
- Modem mode - attach your panstamp module to PC and use SWAP network monitor for analysing or configuring your network 


SWAP monitor
-----------------
This utility communicates through virtual serial port with panstamp module which is running modem firmware. Monitor can be used for sniffing network traffic, configuring your devices... It is programmed as HTML webpage, you can open it in any webbrowser with websocket support. For accessing serial ports of your PC from javascript running in your browser, a server application was designed. For running this server application 'server.js' you will need NodeJs. It uses following libraries which you need to install by running 'npm install ...' command:
- serialport: for enumerating available serial pors and for communicating with them
- websocket: for creating local websocket server

![Image 1](Readme/monitor1.jpg)
![Image 2](Readme/monitor2.jpg)

Hw configuration
-----------------
For attaching CC1101 module to your arduino, you will need to wire up 7 signals:
- VCC: CC1101 pin 1 - Arduino 3.3V 
- SI (spi): CC1101 pin 3 - Arduino pin 11
- SCK (spi): CC1101 pin 4 - Arduino pin 13
- SO (spi): CC1101 pin 5 - Arduino pin 12
- CSn (chip select): CC1101 pin 7 - Arduino pin 10
- GDO0 (interrupt on packet receive): CC1101 pin 8 - Arduino pin 2 
- GND: CC1101 pin 9 - Arduino GND

![Image 2](Readme/monitor2.jpg)

Module pinout:
![Image 2](Readme/cc1101_pinout.jpg)

Links:
-----------------
- http://www.panstamp.com/ - panstamp modules
- https://github.com/panStamp/panstamp/wiki - panstamp homepage
- https://github.com/panStamp/panstamp/wiki/SWAP-API - SWAP library documentation
- https://github.com/panStamp/swap - SWAP library code
