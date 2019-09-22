# Laser projector reverse engineering

- Product name: AUCD 1W DMX ILDA Bluetooth RGB Animation Laser Projector DJ Party Stage Lighting  
- Bluetooth ID: DQF6 xxxx
- Bluetooth operation video: https://www.youtube.com/watch?v=8_6Ns_fSROs
- Application download link: https://drive.google.com/file/d/129DjttSHxKn2GGRaxmZ0fhHCZRFtb_Tl/view
- Decompiled using jadx decompiler (brew install jadx)
- Protocol implementation code: LaserLightProtocol.java

Android application does not contain any animations, but they are downloaded them from website of manufacturer instead. App requests aspx directory lister api running on url "http://www.gz-huoyue.cn/api/UpDownLoadFiles", folder attribute is not protected. Example urls:

- http://www.gz-huoyue.cn/api/UpDownLoadFiles?startIndex=0&endIndex=100&proDirName=JGDFiles&selDirName=Programs&suffName=.BNC
- http://www.gz-huoyue.cn/api/UpDownLoadFiles?startIndex=0&endIndex=100&proDirName=JGDFiles&selDirName=TF1&suffName=.tf1
- http://www.gz-huoyue.cn/api/UpDownLoadFiles?startIndex=0&endIndex=100&proDirName=JGDFiles&selDirName=TF2&suffName=.tf2
- http://www.gz-huoyue.cn/api/UpDownLoadFiles?startIndex=0&endIndex=100&proDirName=JGDFiles&selDirName=TF1/../../..&suffName=.aspx
- http://www.gz-huoyue.cn/UpDownLoadFiles/JGDFiles/TF1/purplemantra.tf1
- http://www.gz-huoyue.cn/UpDownLoadFiles/JGDFiles/TF2/1234.tf2

Bluetooth protocol allows full DMX control of the device, preview of geometry and also upload of new animation (TF1 format). Unfortunately the projector shows blank image for one second after receiving of new geometry and this behavior prevents using bluetooth for realtime streaming.
Projector does support only 7 colours (only R, G, B and combinations), the coordinates are in polar system, radius is in range 0..4095 and angle 0..1023 and maximum number of points the memory can handle is 750. Static geometry can be animated using various DMX modifiers (scrolling, zooming, rotating effects...) It seems, the projector can show two different geometries with two different modifiers.
Protocol was reverse engineered by analysing LaserLightProtocol.java and verified by enabling Bluetooth HCI snoop log on android device, produced log was analysed with Wireshark.
- conn_preview.js - generates various geometries and transfers them into projector, geometry is shown instantly
- conn_upload.js - uploads TF1 file into projector, switch to animation number 0 to display uploaded file
- load_tf1.js - reverse engineering of TF1 file and conversion into json
