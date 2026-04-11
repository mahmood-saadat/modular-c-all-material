# main-course

# Embedded C: A Modular Approach - Project Framework

This repository contains the official source code and reference materials for the **Embedded C: A Modular Approach** course. [cite_start]It is designed to demonstrate how to transition from "Code that just works" to "Code that scales" using a professional 4-layer architecture[cite: 7, 9].

## 📂 Repository Structure

[cite_start]The project follows a strict folder hierarchy to enforce the separation of concerns and ensure hardware portability[cite: 363, 365].

* **`/app`**: Contains the **Application Layer**. [cite_start]This is the "Hardware-Agnostic Brain" of the system, written in 100% portable C code[cite: 166, 315, 371].
* **`/interface`**: The **Interface Layer**. [cite_start]Acts as a "Universal API" or contract, hiding the lower-level hardware details from the application[cite: 196, 304, 371].
* **`/device`**: The **Device Layer**. [cite_start]Contains software drivers for external PCB components like sensors (e.g., ADS1115) and actuators[cite: 203, 277, 373].
* **`/hal`**: The **Hardware Abstraction Layer (HAL)**. [cite_start]The only layer allowed to contain MCU-specific register access and headers (e.g., STM32 or ESP32 specific files)[cite: 215, 219, 374].
* [cite_start]**`/common`**: Shared resources, including fixed-width type definitions and common macros[cite: 375].
* [cite_start]**`/docs`**: Contains the **PDF version of the course presentation** for offline study [cite: 1-414].

## 🚀 Examples & Features

### 1. The Multi-Platform Blinky
A practical demonstration of portability. The same application logic runs on both **STM32** and **ESP32** microcontrollers. [cite_start]To switch platforms, you only need to replace the files in the `/hal` folder; the application logic remains 100% untouched[cite: 155, 380, 382].

### 2. ESP32 Deep Dive
Complete code examples for all ESP32 modules covered in the course, demonstrating:
* [cite_start]**Layered Interaction:** How the Application calls the Interface to trigger hardware actions[cite: 181].
* [cite_start]**Callback Systems:** Managing asynchronous events like timers and interrupts[cite: 328, 348].
* [cite_start]**Modular Initialization:** Using a dedicated module to coordinate hardware-dependent startup[cite: 341].

## 🛠 Coding Standards
[cite_start]All code in this repository follows the **Barr Group Embedded C Coding Standards** to ensure safety and reliability[cite: 13, 73].
* [cite_start]**Ambiguity Elimination:** Use of `<stdint.h>` fixed-width types (e.g., `uint8_t`, `int32_t`)[cite: 84, 88].
* [cite_start]**Defensive Programming:** Implementation of **Yoda Conditions** (e.g., `if (CONSTANT == variable)`) to prevent assignment bugs[cite: 146, 147].
* [cite_start]**Naming Conventions:** Clear prefixes for scope and type (e.g., `g_` for globals, `p_` for pointers)[cite: 122, 140].
* [cite_start]**Self-Documenting Code:** Standardized comment blocks using `@brief`, `@param`, and `@return`[cite: 395, 396, 397].

## 📖 How to Use
1.  [cite_start]**Reference the Presentation:** Use the PDF in `/docs` to follow the architectural theory[cite: 42, 153].
2.  [cite_start]**Explore the HAL:** Compare the STM32 and ESP32 `/hal` implementations to see how silicon-specific code is isolated[cite: 236, 244].
3.  [cite_start]**Template:** Use this folder structure as a professional template for your own industrial firmware projects[cite: 15, 386].

---
**Instructor:** Mahmood Saadat  
[cite_start]**Organization:** [Cosmo Robotics](https://cosmorobotics.uk) [cite: 17]