# Cube3D
Cube3D is a challenging and engaging project from 42 School. It is a simplified implementation of the famous 3D game, inspired by the classic "Wolfenstein 3D" game, which is considered the forerunner of the first-person shooter genre.
## Prerequisites
To compile and run this project, you will need:

    A Unix operating system or Unix-like environment (such as Linux or MacOS)
    The GCC compiler
    The MiniLibX graphics library

## Compilation & Execution

To compile the project, clone the repository and run make:

```bash
git clone https://github.com/IAmVictorG/42_Cube3D.git
cd Cube3D
make
```
To run the game, use the following command:
```bash
./cube3d [file.cub]
```
`file.cub` is the game's map file. The format of the map is explained later in this document.
# Map Format
The game map is defined in a .cub file. The format of this file is as follows:
```bash
R 1920 1080       // resolution
NO ./path_to_north_texture // path to the north texture
SO ./path_to_south_texture // path to the south texture
WE ./path_to_west_texture  // path to the west texture
EA ./path_to_east_texture  // path to the east texture
S ./path_to_sprite_texture // path to the sprite texture

F 220,100,0       // floor color in RGB
C 70,70,70        // ceiling color in RGB

1111111111        // map layout, 1 represents a wall
1000000001        // 0 represents empty space
1011111101
1000000001
1111111111
```
Please note that the map must be completely surrounded by walls and it must be rectangular.
# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
