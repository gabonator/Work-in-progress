Single file websocket server in C++ compatible with current versions of web browsers. 

Use it on your own risk, the code is not very tidy and the multithread synchronization is not properly done, but for websocket experiments it should be perfectly sufficient. If you need to interface your hardware with web browser, use "serwebproxy" instesad. Pull requests are welcome!

License: do whatever you want with it, you do not need my permission to use or modify this code

This code was based on work by trevor.n.webster, Micael Hildenborg (SHA1) and Rene Nyffenegger (Base64)
  - http://winsockwebsocket.codeplex.com/
  - http://www.codeproject.com/Articles/222487/Deadlocks-and-race-condition-scenarios-with-a-WebS
  - http://code.google.com/p/smallsha1/source/browse/trunk/sha1.cpp
  - http://www.adp-gmbh.ch/cpp/common/base64.html
