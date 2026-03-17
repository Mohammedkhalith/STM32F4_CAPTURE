# STM32F401 TIM9 Input Capture with 16x2 LCD

This project demonstrates **Timer Input Capture** using **TIM9 Channel 2 (PA3)** on an STM32F401 microcontroller. The captured timer value is displayed on a **16x2 LCD** using direct **GPIO register programming (Bare-Metal C)**.

The program continuously reads the **CCR2 register** of Timer 9 and prints the captured value on the LCD screen.

---

## 📌 Features

- Bare-metal register level programming
- Timer Input Capture using TIM9
- LCD interface using GPIO
- Continuous captured value display
- No HAL / Cube libraries used

---

## 🧠 Concepts Covered

This project demonstrates:

- Timer input capture mode
- GPIO alternate function configuration
- LCD interfacing (8-bit mode)
- Register-level peripheral programming
- Real-time data display on LCD

---

## 🛠 Hardware Requirements

- STM32F401 Development Board
- 16x2 LCD Display (HD44780 compatible)
- External signal source (PWM / square wave)
- Breadboard and jumper wires
- 10K potentiometer (for LCD contrast)

---

## 🔌 Pin Configuration

### Timer Input Capture

| Pin | Function |
|----|----|
| PA3 | TIM9_CH2 Input Capture |

External signal should be connected to **PA3**.

---

### LCD Connections (8-bit mode)

| LCD Pin | STM32 Pin |
|------|------|
| D0-D7 | PA0 - PA7 |
| RS | PA8 |
| RW | PA9 |
| EN | PA10 |

---

## ⚙️ Timer Configuration

| Parameter | Value |
|------|------|
| Timer | TIM9 |
| Channel | Channel 2 |
| Prescaler | 16000 - 1 |
| ARR | 4000 |
| Mode | Input Capture |

----------------------------
