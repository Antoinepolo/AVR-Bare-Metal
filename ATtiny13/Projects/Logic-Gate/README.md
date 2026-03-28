# ATtiny13 Logic Gate Emulator (Bare Metal C)

This project demonstrates how to use an **ATtiny13A** microcontroller to emulate a 3-input **AND Gate** using bare-metal C programming. It focuses on direct register manipulation and efficient bitwise operations.

## 🚀 Overview

The MCU monitors three input pins (PB0, PB1, PB2) and controls one output pin (PB3). 
Using internal pull-up resistors, the logic is as follows:
- **Buttons Pressed** = Logic `0` (GND)
- **Buttons Released** = Logic `1` (VCC via Pull-up)
- **Output (LED)** = High only when all three buttons are pressed simultaneously.

## 🛠️ Hardware Configuration

| Component | ATtiny13 Pin | Function |
| :--- | :--- | :--- |
| Button 1 | PB0 | Input (Pull-up) |
| Button 2 | PB1 | Input (Pull-up) |
| Button 3 | PB2 | Input (Pull-up) |
| LED | PB3 | Output (Active High) |

## 💻 Code Logic

Instead of using heavy abstraction layers, the code interacts directly with the AVR registers:
- `DDRB`: Data Direction Register (Configures Pins as Input/Output).
- `PORTB`: Port B Data Register (Activates Pull-ups / Sets Output State).
- `PINB`: Port B Input Pins Address (Reads current physical state).

### Key Snippet: Bitmasking
```c
// Check if all buttons are pressed (Logic 0)
if ((PINB & BTN_MASK) == 0) {
    PORTB |= (1 << PB3);  // Set LED HIGH
}
