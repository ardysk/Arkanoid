# Arkanoid Game for FRDM-KL05Z

## Overview
This project implements a classic Arkanoid game on the FRDM-KL05Z microcontroller platform. The game utilizes:
- An **OLED screen** for display,
- A **touch slider** for paddle control,
- A **matrix keyboard** for menu navigation.

## Features
- **Dynamic Gameplay**: Real-time collision detection with interactive paddle and ball control.
- **Menu Options**: Adjust brightness, enable night mode, and configure the refresh rate.
- **Scoring System**: Real-time score updates with a leaderboard display.
- **Game Over Screen**: Displays the final score and provides an option to restart.
- **Power-ups**: Includes multiball, paddle expansion, and extra lives.

## Hardware Components
- **FRDM-KL05Z Microcontroller Board**
- **OLED Display (SSD1306)**: SPI-connected, displays game graphics.
- **Touch Slider (TSI)**: Enables paddle control with precise touch detection.
- **Matrix Keyboard**: Used for menu navigation.

## Software Structure
The project is modular, divided into the following components:

### Core Files
- **`main.c`**: Initializes peripherals and manages the main game loop.
- **`arkanoid.c` / `arkanoid.h`**: Handles game logic, including ball movement, paddle control, block collision, and power-ups.
- **`oled.c` / `oled.h`**: Manages the OLED display, including drawing text, shapes, and refreshing the screen.
- **`tsi.c` / `tsi.h`**: Handles the touch slider, providing paddle position data.
- **`spi.c` / `spi.h`**: Configures the SPI interface for OLED communication.
- **`gpio.c` / `gpio.h`**: Provides GPIO utilities for controlling hardware components.

### Additional Resources
- **`Fonts.c` / `Fonts.h`**: Bitmap fonts and graphics for blocks and text.
- **`LIB_Config.h`**: Pin definitions and configuration macros.
- **`frdm_bsp.h`**: Board-specific definitions and macros.

## Gameplay Mechanics

### Initialization
- Peripherals (SPI, OLED, TSI) are initialized.
- The game starts with the paddle and ball in their default positions.

### Menu Navigation
- Use the **matrix keyboard** to select options like starting the game or viewing scores.

### Game Loop
1. Control the paddle using the **touch slider**.
2. The ball interacts with blocks and the paddle, scoring points for block destruction.
3. Lose a life if the ball falls below the paddle.

### Game Over
- When all lives are lost, the game displays the final score and waits for a restart.

## Controls
- **Touch Slider**: Moves the paddle horizontally.
- **Matrix Keyboard**:
  - Navigate through the menu.
  - Input player nickname.

## Build and Deployment

### Requirements
- **IDE**: MCUXpresso IDE (recommended).
- **SDK**: NXP SDK for FRDM-KL05Z.
- **Programming Tool**: OpenSDA or a compatible flash loader.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/arkanoid.git
2. Open the project in **MCUXpresso IDE**:
   - Launch **MCUXpresso IDE**.
   - Navigate to **File > Import > Existing Projects into Workspace**.
   - Select the project directory and click **Finish**.

3. Compile the project:
   ```bash
   make all
4. Flash the binary to the FRDM-KL05Z board using OpenSDA or other supported tools:
    ```bash
    make flash
5. Connect the hardware components as per the schematics.
6. Power on the board to start the game.

## File Descriptions
| File            | Description                                                                 |
|-----------------|-----------------------------------------------------------------------------|
| `main.c`        | Main game loop and system initialization.                                   |
| `arkanoid.c`    | Implements game logic like ball movement, collisions, scoring, and levels. |
| `arkanoid.h`    | Header file defining structures, constants, and prototypes for the game.    |
| `oled.c`        | Handles OLED graphics rendering, including text, shapes, and screen refresh.|
| `oled.h`        | Header file for OLED screen configurations and prototypes.                 |
| `tsi.c`         | Manages touch slider input for precise paddle control.                     |
| `tsi.h`         | Header file for touch slider configurations and prototypes.                |
| `spi.c`         | Implements SPI communication for the OLED display.                         |
| `spi.h`         | Header file defining SPI settings and communication functions.             |
| `gpio.c`        | Provides GPIO utility functions for controlling hardware components.       |
| `gpio.h`        | Header file defining GPIO configurations and functions.                    |
| `Fonts.c`       | Contains bitmap fonts and graphical assets used in the game.               |
| `Fonts.h`       | Header file declaring font and bitmap assets for display rendering.        |
| `LIB_Config.h`  | Defines pin configurations and macros specific to the FRDM-KL05Z board.    |
| `frdm_bsp.h`    | Board-specific definitions and helper macros for the FRDM-KL05Z.           |

## Schematics

### System Diagram
- **FRDM-KL05Z** connected to:
  - **OLED display**
  - **Matrix keyboard**
  - **Touch slider**

### Pin Configuration
- **OLED Display**:
  - **CS**: PTB6
  - **DC**: PTB7
  - **RES**: PTB8
  - **SPI Interface** for communication
- **Touch Slider**:
  - **PTA12**
  - **PTA13**
- **Matrix Keyboard**:
  - Connected to **GPIO** pins.

## Known Issues
- Touch slider calibration may require adjustments based on the operating environment.
- Limited RAM on the FRDM-KL05Z board may restrict:
  - The number of levels
  - Complex animations

## Future Enhancements
- Introduce additional power-ups and game levels.
- Implement persistent score storage using non-volatile memory.
- Enhance the graphics and animations for improved user experience.

## Acknowledgments
This project was developed as part of the **"Microprocessor Systems 2"** course, under the supervision of **mgr inż. Sebastian Koryciak**.


