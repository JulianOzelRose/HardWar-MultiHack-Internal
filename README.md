# HardWar-Hack-Internal
This is an internal DLL-based hack for HardWar UIM 6. This hack was not designed to function on multiplayer settings -- it is not exactly practical.
Rather, the purpose of this program is to better understand data structures and runtime modification. Features of this program include speedhack, instakill,
infinite cash, and auto negate stall.

# Screenshots

![Untitled-1](https://user-images.githubusercontent.com/95890436/199563029-f83fc664-7525-4404-b12c-a11a9975d286.png)
###### Screenshot: Injection message being displayed


![Untitled-2](https://user-images.githubusercontent.com/95890436/199563045-9dfcf148-777f-42af-acaa-835b398c93fc.png)
###### Screenshot: In-game GUI being displayed


![Untitled-3](https://user-images.githubusercontent.com/95890436/199563052-2c2d43d2-bb58-43f4-b4ee-4394405f0917.png)
###### Screenshot: Instakill being used

## ```PrintHUD()```
In order to print text to screen, the game's own print function was used. The game's print function is located on the
address at ```HardwarW.exe+0x7B950```. The function has several parameters, and is called using __stdcall. The first
parameter tells the game the x-coordinate of where the message is displayed on screen, and the second parameter
tells the game the y-coordinate of the message to be displayed. The third parameter is the character string to be
displayed, and any subsequent parameter is used for format strings suchas ```%d``` or ```%s```, much like the ```printf```
function from C's cstdlib.


![decompile_Ghidra](https://user-images.githubusercontent.com/95890436/199567782-8e0e8a98-9f95-4939-8d2c-02d3c89db384.PNG)
###### Screenshot: Decompilation of ```HardwarW.exe+0x7B950``` from Ghidra.
