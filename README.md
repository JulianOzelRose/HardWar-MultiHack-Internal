# HardWar-MultiHack-Internal
This is an internal DLL-based hack for HardWar UIM 6. This program was not designed to function on multiplayer settings.
Rather, the purpose of this program is to better understand data structures and runtime modification. Features of this program include speedhack, instakill,
infinite cash, and auto negate stall. For educational purposes only.

To download this hack, navigate to the ```Release``` folder of this repo, then download ```HardWar-Hack-Internal.dll```. To enable the hack, use a DLL injection tool to inject the DLL onto the HardWar process. Once injected, a success message will be printed in-game. To toggle the speedhack, press ```VK_DELETE```. To use instakill, simply target a moth and press ```VK_INSERT```. Invincibility, infinite cash and auto-shield regeneration are enabled by default, but this can be changed by modifying the source. To un-inject the DLL, press ```VK_END```.

# In-Game Screenshots


###### Injection message being displayed


![Untitled-1](https://user-images.githubusercontent.com/95890436/199563029-f83fc664-7525-4404-b12c-a11a9975d286.png)


###### GUI being displayed


![Untitled-2](https://user-images.githubusercontent.com/95890436/199563045-9dfcf148-777f-42af-acaa-835b398c93fc.png)


###### Instakill being used




https://user-images.githubusercontent.com/95890436/208253686-3f4106a6-8814-40fa-93f1-7095b1d4e9d3.mp4





## ```PrintHUD()```
In order to print text to screen, the game's own print function was used. The game's print function is located on the
address at ```HardwarW.exe+0x7B950```. The function has several parameters, and is called using ```__stdcall```. The first
parameter tells the game the x-coordinate of where the message is displayed on screen, and the second parameter
tells the game the y-coordinate of the message to be displayed. The third parameter is the character string to be
displayed, and any subsequent parameter is used for format strings such as ```%d``` or ```%s```, much like the ```printf```
function.


###### Decompilation of ```HardwarW.exe+0x7B950```


![Capture](https://user-images.githubusercontent.com/95890436/199644060-09723649-525b-48e8-8f52-c8fec442006c.PNG)

# Data Structures
The player entity pointer is stored on offset
```0x11D9AC``` from the module's base address. The player's cash variable,
for example, would be stored on the address at ```moduleBase + 0x11D9AC + 0x03C```.
Memory mappings of the player, moth, hangar, and cargo data structures can be found
in the tables below.

## Player data structure ##
| **Offset**     | **Variable**    | **Type**       |
| :---           | :---            | :---           |
| 0x004          | name            | String[32]     |
| 0x02C          | status          | Integer        |
| 0x030          | location*       | Pointer        |
| 0x03C          | cash            | Integer        |

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


## Moth data structure ##
| **Offset**    | **Variable**    | **Type**      |
| :---          | :---            | :---          |
| 0x1D0         | hangar*         | Pointer       |
| 0x1D4         | status          | DWORD         |
| 0x1D8         | owner*          | Pointer       |
| 0x1F0         | target*         | Pointer       |
| 0x1F4         | droneType       | Integer       |
| 0x200         | engineNum       | Integer       |
| 0x204         | cellNum         | Integer       |
| 0x208         | podType         | Integer       |
| 0x20C         | currentWeapon   | Integer       |
| 0x248         | weapon1Ammo     | Integer       |
| 0x24C         | weapon2Ammo     | Integer       |
| 0x250         | weapon3Ammo     | Integer       |
| 0x254         | weapon4Ammo     | Integer       |
| 0x2DC         | pilot*          | Pointer       |
| 0x2E0         | passenger*      | Pointer       |
| 0x2E4         | autopilotStatus | BYTE          |
| 0x294         | shields         | DWORD         |
| 0x298         | engineDmg       | DWORD         |
| 0x29C         | structureDmg    | DWORD         |
| 0x2A0         | cpuDmg          | DWORD         |
| 0x2A4         | powerDmg        | DWORD         |
| 0x2A8         | weaponsDmg      | DWORD         |
| 0x368         | numFlares       | Integer       |
| 0x378         | numChaff        | Integer       |
| 0x37C         | numShells       | Integer       |
| 0x390         | stallWarningLvl | Integer       |
| 0x438         | thrust          | DWORD         |

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


## Hangar data structure ##
| **Offset**    | **Variable**     | **Type**      |
| :---          | :---             | :---          |
| 0x004         | terminalName     | String[32]    |
| 0x010         | displayName      | String[32]    |
| 0x034         | clearanceLvl     | Integer       |
| 0x03C         | enemiesList*     | Pointer       |
| 0x048         | owner*           | Pointer       |
| 0x8BC         | cashHeld         | Integer       |
| 0x8D8         | bay1*            | Pointer       |
| 0x8DC         | bay2*            | Pointer       |
| 0x8E0         | bay3*            | Pointer       |
| 0x8E4         | bay4*            | Pointer       |
| 0x8E8         | bay5*            | Pointer       |
| 0x8EC         | bay6*            | Pointer       |

The variable on offset ```0x004``` of the hangar data structure holds the name of the hangar,
as viewed from the game's perspective. The next variable on offset ```0x010``` holds the
display name that is viewed by the player. The clearance level variable
on offset ```0x034``` can either be set at 0 for unrestricted access, or 16
to be restricted from human pilots. The hangar bay pointers on offsets ```0x8D8```,
```0x8DC```, ```0x8E0```, ```0x8E4```, ```0x8E8```, and ```0x8EC``` point to the address
of the moth that is currently in that bay.


## Cargo data structure ##
| **Offset**      | **Variable**     | **Type**      |
| :---            | :---             | :---          |
| 0x004           | quantity         | Integer       |
| 0x008           | status           | Integer       |
| 0x00C           | location*        | Pointer       |

The status variable on offset ```0x008``` of the cargo structure is set to 0 if the cargo
is located outdoors, and gets set to 1 if the cargo is located in a cargo pod. The pointer
on offset ```0x00C``` points to the address of the moth of which it is stored in. The variable
stored on offset ```0x004``` simply holds the quantity of the item.

# Sources
I credit Guided Hacking for my knowledge of game hacking. They have very in-depth tutorials and guides
on how to create your own cheat tables and trainers from scratch. I highly reccommend purchasing a subscription
if you are interested in learning game hacking. Below are links to some of the guides I used to help me create this program.
* https://guidedhacking.com/threads/ghb1-start-here-beginner-guide-to-game-hacking.5911/
* https://guidedhacking.com/threads/ghb0-game-hacking-bible-introduction.14450/
* https://guidedhacking.com/threads/ghb2-beginners-guide-to-reverse-engineering.13446/
* https://guidedhacking.com/threads/how-to-hack-any-game-tutorial-c-trainer-3-first-internal.12142/
* https://guidedhacking.com/threads/ghb3-intermediate-guide-to-game-hacking.13495/
