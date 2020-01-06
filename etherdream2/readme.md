# Etherdream2 websocket bridge

For realtime control of ILDA laser projector from web.
  - bridge - source code files of the bridge and project for XCode
  - test - some useful test tools (discovery of etherdream adapters, nodejs controller for etherdream, simple websocket test)
  - example_circle - draws simple pattern using etherdream2 to websocket bridge
  - example_maze - realtime 3d maze

Based on following projects:
  - [ofxEtherdream](https://github.com/memo/ofxEtherdream), originally written by Jacob Potter, with some light improvements (direct connection by IP address)
  - [libwebsock](https://github.com/payden/libwebsock), with some fixes for osx
