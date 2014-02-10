Alley cat
==========

This game was created in 1984 and now, after 20 years I am trying to convert it to modern computer platforms. My idea was porting this game at first into C++ and then to javascript, so that it could be played in any web browser without using a DOS emulator.
For obtaining the assembler source code I used IDA disassembler. The utility "AsmToC" converts 16 bit assembler instructions line by line into C code, about 95% of the conversion is done by this utility, however some conditional jumps need to be fixed manually. The converter puts a breakpoint in every point of code where it wasn't sure what to do. Main code of game is placed in Game folder. This programs is designed to be compiled in Visual Studio and emulates the CGA graphic adapter, sound card, timers and keyboard. This project is still not finished and the game is not playable, but the cat can be moved by arrow keys :)

![Image 1](Screenshots/splash.png)

![Image 2](Screenshots/game.png)
