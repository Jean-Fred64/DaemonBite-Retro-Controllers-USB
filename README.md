# DaemonBite Retro Controllers To USB Adapters
## Introduction
This is a collection of easy to build adapters for connecting SNES, NES, Mega Drive/Genesis (3/6-button), Master System, Atari, Commodore, Amiga (incl. CD32), Amstrad GX4000 controllers to USB. Support for more controllers is on the way (Sega Saturn, NeoGeo etc.).

The input lag for these adapters is minimal. Here is the result of the Sega controller adapter from a test with a 1ms polling rate on a MiSTer:

| Controller | Samples | Average | Max | Min | Std Dev |
| ------ | ------ | ------ | ------ | ------ | ------ | 
| Original 3-Button Mega Drive Controller | 2342 | 0.75ms | 1.28ms | 0.24ms | 0.29ms |
| 8bitdo M30 Wireless 2.4G | 2348 | 4.54ms | 8.05ms | 2.22ms | 1.31ms |

## How to assemble the adapters
See the README files in the subfolders for build instructions. All the adapters are build around the Arduino Pro Micro.

## How to test controllers
[https://greggman.github.io/html5-gamepad-test/](https://greggman.github.io/html5-gamepad-test/)

## Building the projects
You will need the [Arduino IDE](https://www.arduino.cc/en/Main/Software) to build the projects. Download the whole repository via the "Clone or download" button, open the project you want to build in the IDE and select "Arduino Leonardo" in Tools / Board. Connect the Arduino to a USB port and build/upload from Scetch / Upload.

## Useful links :wink:
[Pinout joystick chart of compatible systems](https://en.wikipedia.org/wiki/Atari_joystick_port#Chart_of_compatible_systems)
<img width="1127" height="808" alt="image" src="https://github.com/user-attachments/assets/d5ddb8d7-fa64-4eae-bf17-4d774ad6f153" />


[DE-9 Joystick](https://wiki.icomp.de/wiki/DE-9_Joystick)
<img width="1562" height="658" alt="image" src="https://github.com/user-attachments/assets/89a423b2-8699-4096-80a3-c7082165e9c6" />


## License
This project is licensed under the GNU General Public License v3.0. The name "daemonbite" is registered to my company in Finland and should not be used by others.

## Credits
The Mega Drive gamepad interface is based on this repository : https://github.com/jonthysell/SegaController but almost entirely rewritten and a lot of optimisations have been made.
