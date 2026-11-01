*This project has been created as part of the 42 curriculum by rnauke.*

# so_long

## Description

A small 2D game written in C with [MLX42](https://github.com/codam-coding-college/MLX42).
The player collects every collectible on the map and then reaches the exit
in as few moves as possible. The map is read from a `.ber` file.

Features:
- Map parsing and validation (rectangular, walled, 1 player, 1 exit, >= 1 collectible)
- Flood-fill check that every collectible and the exit are reachable
- Move counter printed in the shell
- Clean exit on `ESC` and on the window close button

## Instructions

Requirements: `cc`, `cmake`, `glfw`. MLX42 is cloned and built by the Makefile.

```
make
./so_long maps/simple.ber
```

Controls: `W A S D` or the arrow keys to move, `ESC` to quit.

Map characters: `0` floor, `1` wall, `C` collectible, `E` exit, `P` player start.

Textures (PNG) are loaded from `textures/`:
`floor.png`, `wall.png`, `collectible.png`, `exit.png`, `player.png`.
They are scaled to 64x64 pixels at load time.

## Resources

- MLX42 documentation: https://github.com/codam-coding-college/MLX42/tree/master/docs
- Flood fill / BFS: https://en.wikipedia.org/wiki/Flood_fill

### Use of AI

- Debugging
- Optimizing
