** PA9 SUBMISSION README **
FOR ANDY:
> Team Members: Chase Larkin, Henry Shaw, Korbin Weiller
> Video Link: https://drive.google.com/file/d/1foV6BJW-wQiNtOsHQ5fUhXywUWHvyUQY/view?usp=share_link

GAME INFORMATION

> Co-op (2 hands on the keyboard) top down tank game! (inspired by the Wii Tanks minigame)
    * features: static collisions between bodies and a tiled grid, keyboard tank driving, and a map
> How to play:
    - Player 1 (red) can move with WASD and fire with F.
    - Player 2 (blue) can move with the arrow keys and fire with right control.
    - If a bullet hits a tank, they will die and the other player's score will increase.
> Future ideas:
    - Menu screen
    - More maps
    - Sounds
    - Graphical effects like animations, particles (obviously explosions)

BUILDING FOR DEBUG (VS Community 2022, Windows):
1. Select the project you want to run (PA9Main for now).
2. Go to project>properties>Properties
3. In the properties editor, set the Configuration dropdown to Debug and set the Platform to Win32.
4. Keeping those configuration options set, go to ConfigurationProperties>Debugging and in the Environment field, enter the field below. This is so the DLLS get loaded when debugging without having to copy them everytime:
```
PATH=$(SolutionDir)SFML-2.5.1\bin;%PATH%
```
5. All the other configurations should already be set and tracked in the repo, so you should be able to run the project in the local debugger and use all the SFML libraries dynamically.
6. When running with the debugger, make sure the local debugger mode is set to Debug, and the archictecture is set to x86 (the two dropdowns to the left of the green start debugging button).

BUILDING FOR RELEASE:
TODO
