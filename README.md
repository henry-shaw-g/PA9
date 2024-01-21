## PA9 SUBMISSION README ##
### FOR ANDY: ##
- Team Members: Chase Larkin, Henry Shaw, Korbin Weiller
-  Video Link: https://drive.google.com/file/d/1foV6BJW-wQiNtOsHQ5fUhXywUWHvyUQY/view?usp=share_link

### GAME INFORMATION ###

- Co-op (2 hands on the keyboard) top down tank game! (inspired by the Wii Tanks minigame)
- features: static collisions between bodies and a tiled grid, keyboard tank driving, and a map

How to play:
- Player 1 (red) can move with WASD and fire with F.
- Player 2 (blue) can move with the arrow keys and fire with right control.
- If a bullet hits a tank, they will die and the other player's score will increase.

Future ideas:
- Menu screen
- More maps
- Sounds
- Graphical effects like animations, particles (obviously explosions)

### Building For Debug ###
Notes:
- You will need a recentish install of CMake
- If you get runtime errors related to missing DLLs / shared libraries refer to the SFML dependencies (linux users especially)
- In order to not mess up the CMake files / output directories I would recommend editing the code with an agnostic editor like VSCode, or maybe CLion
Steps:
1. Clone this project from github to a desired location. Then:
```
cd <Location of Cloned Directory>
```
2. Create a CMake build directory as specified:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Build -DTANK_GAME_DEBUG_BUILD=True
```
3. Use CMake's handy build shortcut (bypasses any platform specific build program):
```sh
cmake --build build
```
4. Pray:
```sh
./build/TankGame
```