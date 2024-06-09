# Pixel Prank

This project creates a prank program that displays randomly colored rectangles on an overlay window on your screen. The rectangles are shown for a specified duration. Then the screen is cleared before repeating the process several times.

## Files

### main.cpp

This file contains the main C++ program that creates the overlay window and performs the prank.

### runW.bat

A batch file to compile and run the C++ program on Windows using `g++`.

### run.sh

A shell script to compile and run the C++ program on Unix-based systems using `g++`.

## Project Setup and Usage

### Prerequisites

- `g++` (GCC) compiler
- Windows OS (for `runW.bat`) or Unix-based OS (for `run.sh`)

### Compilation and Execution on Windows

1. Open a command prompt.
2. Navigate to the project directory.
3. Run the batch file:
   ```bat
   runW.bat
   ```

### Compilation and Execution on Unix-based Systems

1. Open a terminal.
2. Navigate to the project directory.
3. Make the shell script executable (if not already):
   ```sh
   chmod +x run.sh
   ```
4. Run the shell script:
   ```sh
   ./run.sh
   ```

## Notes

- The prank duration and the number of repetitions can be adjusted by modifying the `performPrankForDuration` and `nbRep` variables.
- The program currently supports drawing rectangles. Additional features, like displaying images, can be added by uncommenting and completing the `displayImage` function. (yet to be fixed the problem. :) )