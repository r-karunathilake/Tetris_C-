# Tetris C++

---

Welcome!

This repository contains the source code for my Tetris remake in C++ using the SFML software development library. I mainly created this project to practice my C++ coding. If you wish, you can use, modify, and distribute this code according to the terms of the license provided. 

## Features 
- Standard Tetris rules 
- Random block generation
- Game music and action audio 
- Score board 
- Next Tetris block board 

## Controls
- Rotate Tetris Block:     Up-Arrow (&uarr)
- Move Tetris Block Left:  Left-Arrow (&larr)
- Move Tetris Block Right: Right-Arrow (&rarr)
- Move Tetris Block Down:  Down-Arrow(&darr)

## Dependencies 
- C++20
- C++ Compiler(e.g. GCC or Clang)
- SFML library 
- CMake (if using Makefile)

## Building and Running 
### Linux
1. Clone this repository to local storage
2. If using clang C++ compiler and on Linux OS, simply execute `make run` on the command line from the root directroy of the repository. 
3. If using another compiler (e.g. GCC), update the `Makefile` CXX to your compiler command and then run `make run`. 
4. Game should launch automatically

### Other Operating Systems 
1. You will have to manually compile the project based on your chosen compiler.

## License 

This project is licensed under the [MIT License](https://opensource.org/license/mit/).

## References 

1. [Game Over Music](https://opengameart.org/content/game-over-soundold-school) by den_yes under [CC0 1.0 Universal license](https://creativecommons.org/publicdomain/zero/1.0/).
2. [Block Rotation Sound]() by qubodup under [CC0 1.0 Universal license](https://creativecommons.org/publicdomain/zero/1.0/).
3. [Game Played Font](https://www.fontspace.com/game-played-font-f31380) by Chequered Ink.
4. [Clear Row Sound](https://opengameart.org/content/beep-tone-sound-sfx) by Brandon Morris under [CC0 1.0 Universal license](https://creativecommons.org/publicdomain/zero/1.0/).
5. [Game Icons](https://opengameart.org/content/2g1) by qubodup under [CC BY 3.0 DEED license](https://creativecommons.org/licenses/by/3.0/).
