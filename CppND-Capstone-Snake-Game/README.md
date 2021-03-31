# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Code 
The Snake game code consists of four main classes: Game, Snake, Controller, and Renderer. The image above shows how the code functions:

To begin, main creates a Controller, a Game, and a Renderer object. Game stores a Snake object as part of the state.
main calls Game::Run to start the game loop.
The next videos walk through each of the files in the Snake game repository in more detail.

## Code Structure

<img src="code_structure.png"/>

The main classes of the program as are `Game`, `Snake`, `Controller` and `Renderer`. 

**Game** is composed of objects of `Snake`, `Controller` and `Renderer`. This class run the main Game Loop where all the action takes palce.

**Snake** class describes the our hero, the snake. It contains information and beavior of the snake.

**Controller** handles the input and makes the snake move. 

**Renderer** renders the game by creating SDL window, loading assets and drawing all the UI elements. 




### Loops, Functions, I/O

The project demonstrates an understanding of C++ functions and control structures. Refer to `game.cpp` for example.
The project reads data from a file and process the data, or the program writes data to a file. Files are read in `tilemap.cpp`
The project accepts user input and processes the input. User input handled in `handler.cpp`

### Object Oriented Programming

The project uses Object Oriented Programming techniques. The `Game` class followes OOP techniques of composition. 
Classes use appropriate access specifiers for class members.| Appropriate access specifiers in all classes to keep some members private and some public.
Class constructors utilize member initialization lists. Initialization lists are used in `Snake` class (`snake.cpp`) and `Text` class (`text.cpp`) constructors. 

### Memory Management

The project makes use of references in function declarations. Several methods use pass-by-reference throughout the application 
The project uses destructors appropriately. Destructors are used to destroy the window an quit SDL in `Rederer` class (`renderer.cpp`) 
The project uses smart pointers instead of raw pointers. `unique_ptr` is used in `Renderer` class constructor to point to an object of the `Text` class

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
