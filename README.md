# HardWar-MultiHack-Internal
This is an internal DLL-based hack for HardWar UIM 6. This program was not designed to function on multiplayer settings.
Rather, the purpose of this program is to better understand data structures and runtime modification. Features of this program include speedhack, instakill,
infinite cash, and auto negate stall. For educational purposes only.

To download this hack, navigate to the [Release](https://github.com/JulianOzelRose/HardWar-MultiHack-Internal/tree/master/Release) folder of this repo,
then download ```HardWar-MultiHack-Internal.dll```. To enable the hack, use a DLL injection tool to inject the DLL onto the HardWar process. I recommend using
[this one](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/). Once injected, a success message will be displayed in-game. To toggle the speedhack, press
```VK_DELETE```. To use instakill, simply target a moth and press ```VK_INSERT```. Invincibility, infinite cash and auto-shield
regeneration are enabled by default, but this can be changed by modifying the source code. To un-inject the DLL, press ```VK_END```.

## Screenshots
###### Injection message being displayed
![Injection-Success-3](https://user-images.githubusercontent.com/95890436/229284726-97fb4f86-6548-469b-891d-eda0c439c209.png)

###### Multihack GUI being displayed
![Untitled-2](https://user-images.githubusercontent.com/95890436/199563045-9dfcf148-777f-42af-acaa-835b398c93fc.png)

###### Instakill being used
https://user-images.githubusercontent.com/95890436/208253686-3f4106a6-8814-40fa-93f1-7095b1d4e9d3.mp4

## Hooking the print function
In order to print text to screen, this hack hooks the game's print function. The game's print function is located on the
address at ```0x7B950```. The function has several parameters, and is called by this hack using ```__stdcall```. The first
parameter tells the game the x-coordinate of where the message is displayed on screen, and the second parameter
tells the game the y-coordinate of the message to be displayed. The third parameter is the character string to be
displayed, and any subsequent parameter is used for format strings such as ```%d``` or ```%s```.


###### Decompilation of print function shown in Ghidra
![Capture](https://user-images.githubusercontent.com/95890436/199644060-09723649-525b-48e8-8f52-c8fec442006c.PNG)

## Data structures
The player entity pointer is stored on offset
```0x11D9AC``` from the module's base address. The player's cash variable,
for example, would be stored on the address at ```moduleBase + 0x11D9AC + 0x03C```.
Memory mappings of the player, moth, hangar, and cargo data structures can be found
in the tables below.

#### Player ####
| **Offset** | **Type** | **Variable** |
| :---       | :---     | :---         |
| 0x004      | String   | Name         |
| 0x02C      | Integer  | Status       |
| 0x030      | Pointer  | Location     |
| 0x03C      | Integer  | Cash         |

The location pointer on offset ```0x030``` of the player data structure
points to the address of the moth or hangar that the player
is currently located. If the player is in a moth located in a hangar,
then the moth's address will be pointed to. If the player is on foot
in a hangar, then the hangar's address will be pointed to. Dead players
are teleported to the Limbo! hangar, where they remain on foot. For the
player status variable on offset ```0x02C```, a value of 1 indicates the
player is in a moth, a value of 2 means the player is on foot in a hangar,
a value of 3 means the player is in a monorail car, a value of 4 means the
player is awaiting a monorail car, and a value of 5 means the player is in a walkway.

#### Moth ####
| **Offset** | **Type**  | **Variable**       |
| :---       | :---      | :---               |
| 0x1D0      | Pointer   | Hangar             |
| 0x1D4      | DWORD     | Status             |
| 0x1D8      | Pointer   | Owner              |
| 0x1EC      | Integer   | Target Type        |
| 0x1F0      | Pointer   | Target             |
| 0x1F4      | Integer   | Drone Type         |
| 0x200      | Integer   | Engine Number      |
| 0x204      | Integer   | Cell Number        |
| 0x208      | Integer   | Pod Type           |
| 0x20C      | Integer   | Current Weapon     |
| 0x248      | Integer   | Weapon 1 Ammo      |
| 0x24C      | Integer   | Weapon 2 Ammo      |
| 0x250      | Integer   | Weapon 3 Ammo      |
| 0x254      | Integer   | Weapon 4 Ammo      |
| 0x2DC      | Pointer   | Pilot              |
| 0x2E0      | Pointer   | Passenger          |
| 0x2E4      | BYTE      | Autopilot Status   |
| 0x294      | DWORD     | Shields            |
| 0x298      | DWORD     | Engine Damage      |
| 0x29C      | DWORD     | Structure Damage   |
| 0x2A0      | DWORD     | CPU Damage         |
| 0x2A4      | DWORD     | Power Damage       |
| 0x2A8      | DWORD     | Weapons Damage     |
| 0x368      | Integer   | Flares             |
| 0x378      | Integer   | Chaff              |
| 0x37C      | Integer   | Shells             |
| 0x390      | Integer   | Stall Level        |
| 0x438      | DWORD     | Thrust             |

The hangar pointer on offset ```0x1D0``` of the moth data structure
points to the address of the hangar that the moth is currently parked
in, if applicable. The pilot pointer on offset ```0x2DC``` points to
the address of the pilot. The target pointer on offset ```0x1F0```
points to the address of the moth's current target -- which can be either
a hangar address or a moth address. The health and shield values on
```0x294```, ```0x298```, ```0x29C```, ```0x2A0```, ```0x2A4```, and ```0x2A8```
all have maximum values of 0x4000 (or 16384 in decimal). The hex value on
```0x0B8``` stores the autopilot, flight, power, and shield system versions.
The hex value on ```0x0BC``` stores the navigation, radar, target, and
infrared system versions.

#### Hangar ####
| **Offset** | **Type**  | **Variable**     |
| :---       | :---      | :---             |
| 0x004      | String    | Terminal Name    |
| 0x010      | String    | Display Name     |
| 0x034      | Integer   | Clearance Level  |
| 0x03C      | Pointer   | Enemies List     |
| 0x048      | Pointer   | Owner            |
| 0x8BC      | Integer   | Cash Held        |
| 0x8D8      | Pointer   | Bay 1            |
| 0x8DC      | Pointer   | Bay 2            |
| 0x8E0      | Pointer   | Bay 3            |
| 0x8E4      | Pointer   | Bay 4            |
| 0x8E8      | Pointer   | Bay 5            |
| 0x8EC      | Pointer   | Bay 6            |

The variable on offset ```0x004``` of the hangar data structure holds the name of the hangar,
as viewed from the game's perspective. The next variable on offset ```0x010``` holds the
display name that is viewed by the player. The clearance level variable
on offset ```0x034``` can either be set at 0 for unrestricted access, or 16
to be restricted from human pilots. The hangar bay pointers on offsets ```0x8D8```,
```0x8DC```, ```0x8E0```, ```0x8E4```, ```0x8E8```, and ```0x8EC``` point to the address
of the moth that is currently in that bay.

#### Cargo ####
| **Offset** | **Type**  | **Variable** |
| :---       | :---      | :---         |
| 0x004      | Integer   | Quantity     |
| 0x008      | Integer   | Status       |
| 0x00C      | Pointer   | Location     |

The status variable on offset ```0x008``` of the cargo structure is set to 0 if the cargo
is located outdoors, and gets set to 1 if the cargo is located in a cargo pod. The pointer
on offset ```0x00C``` points to the address of the moth of which it is stored in. The variable
stored on offset ```0x004``` simply holds the quantity of the item.

## Sources
I credit Guided Hacking for my knowledge of game hacking. They have very in-depth tutorials and guides
on how to create your own cheat tables and trainers from scratch. I highly reccommend purchasing a subscription
if you are interested in learning game hacking. Below are links to some of the guides I used to help me create this program.
* [Guided Hacking - Guide - GHB0 - Game Hacking Bible Introduction](https://guidedhacking.com/threads/ghb0-game-hacking-bible-introduction.14450/)
* [Guided Hacking - GHB1 - Start Here Beginner Guide to Game Hacking](https://guidedhacking.com/threads/ghb1-start-here-beginner-guide-to-game-hacking.5911/)
* [Guided Hacking - GHB2 - Beginners Guide To Reverse Engineering](https://guidedhacking.com/threads/ghb2-beginners-guide-to-reverse-engineering.13446/)
* [Guided Hacking - GHB3 - Intermediate Guide to Game Hacking](https://guidedhacking.com/threads/ghb3-intermediate-guide-to-game-hacking.13495/)
* [Guided Hacking - How to Hack Any Game Tutorial C++ Trainer #3](https://guidedhacking.com/threads/how-to-hack-any-game-tutorial-c-trainer-3-first-internal.12142/)
