Arkanoid Game for FRDM-KL05Z

Overview

This project implements a classic Arkanoid game on the FRDM-KL05Z microcontroller platform. The game utilizes an OLED screen for display, a touch slider for paddle control, and a matrix keyboard for menu navigation.

Features

Dynamic Gameplay: Interactive paddle and ball control with real-time collision detection.

Menu Options: Adjust brightness, night mode, and refresh rate.

Scoring System: Real-time score updates and leaderboard display.

Game Over Screen: Displays the final score and allows restarting the game.

Power-ups: Include multiball, paddle expansion, and extra life.

Hardware Components

FRDM-KL05Z Microcontroller Board

OLED Display (SSD1306): Connected via SPI, displays game graphics.

Touch Slider (TSI): Enables paddle control with precise touch detection.

Matrix Keyboard: Used for menu navigation.

Software Structure

The software is modularized into the following components:

Core Files

main.c: Initializes peripherals and manages the main game loop.

arkanoid.c / arkanoid.h: Handles game logic, including ball movement, paddle control, block collision, and power-ups.

oled.c / oled.h: Manages the OLED display, including drawing text, shapes, and refreshing the screen.

tsi.c / tsi.h: Handles the touch slider, providing paddle position data.

spi.c / spi.h: Configures the SPI interface for OLED communication.

gpio.c / gpio.h: Provides GPIO utilities for controlling hardware components.

Additional Resources

Fonts.c / Fonts.h: Bitmap fonts and graphics used for display elements like blocks and text.

LIB_Config.h: Contains pin definitions and configuration macros.

frdm_bsp.h: Board-specific definitions and macros.

Gameplay Mechanics

Initialization:

Peripherals (SPI, OLED, TSI) are initialized.

The game starts with the paddle and ball positioned at their default locations.

Menu Navigation:

Use the matrix keyboard to select options such as starting the game or viewing scores.

Game Loop:

Control the paddle using the touch slider.

The ball interacts with blocks and the paddle, updating the score upon block destruction.

Lose a life if the ball falls below the paddle.

Game Over:

When all lives are lost, the game displays the final score.

Controls

Touch Slider: Moves the paddle horizontally.

Matrix Keyboard:

Navigate through the menu.

Input player nickname.

Build and Deployment

Requirements

IDE: MCUXpresso IDE (recommended).

SDK: NXP SDK for FRDM-KL05Z.

Programming Tool: OpenSDA or compatible flash loader.

Steps

Clone the repository:

git clone https://github.com/your-repo/arkanoid.git

Open the project in MCUXpresso IDE.

Compile the project.

Flash the binary to the FRDM-KL05Z board.

Connect the hardware components as per the schematics.

Power on the board to start the game.

File Descriptions

main.c: Contains the main game loop and initializes the system.

arkanoid.c: Implements gameplay logic such as collisions, scoring, and level progression.

oled.c: Handles drawing on the OLED display.

tsi.c: Reads touch slider input for paddle control.

spi.c: Manages SPI communication with the OLED display.

gpio.c: Provides utility functions for GPIO control.

Fonts.c: Contains bitmap fonts and graphics for the game.

LIB_Config.h: Defines hardware configurations and macros.

frdm_bsp.h: Provides board-specific constants and helper functions.

Schematics

System Diagram: Connects FRDM-KL05Z, OLED, matrix keyboard, and touch slider.

Pin Configuration:

OLED:

CS: PTB6

DC: PTB7

RES: PTB8

SPI Interface

Touch Slider: PTA12, PTA13.

Matrix Keyboard: Connected to GPIO.

Known Issues

Touch slider calibration may require adjustment depending on environmental factors.

Limited RAM may restrict the number of levels or complex animations.

Future Enhancements

Add more power-ups and game levels.

Implement persistent score storage using non-volatile memory.

Enhance graphics and animations.

Acknowledgments

This project was developed as part of the "Microprocessor Systems 2" course under the supervision of mgr inż. Sebastian Koryciak.
