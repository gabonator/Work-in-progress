Sarien with audio support
======================

This is a small extension to a wonderful project http://sarien.net/ by Martin Kool. He made a utility that converts AGI adventure games by Sierra into Javascript. At the time he was working on it, there was no way how to play the AGI tunes through web browser. When I found his project I decided to give it a try to add sound support to his interpreter. What is in this repository is actually a javascript version of King's Quest 2 game. I converted the in-game tunes and sounds into javascript. The raw Sound files are possible to export from AGI games using the WinAGI GDS utility. These binary files actually represent 3 channel midi recording, and are converted to javascript by my utility snd2midi.cpp (modified code from ScummVM). I tried to write a cross-browser sound playing module, it is still not perfect, but it works reliably in Chrome and Safari, Firefox is causing some problems, it plays the music with some delay.

The tunes are stored as two dimensional array - it contains 3 arrays containing notes for each channel. 
Every note is represented by pair of two numbers - The first number is the note number (same as MIDI note) and the second is duration.

My extension is placed in gplay.js file. This file decodes the recording and passes noteon/noteoff commands to sound generator in gaudio.js

This game is playable here: http://pub.valky.eu/sarien/