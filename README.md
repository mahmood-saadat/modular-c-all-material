# main-course

# Embedded C: A Modular Approach - Project Framework

This repository contains the official source code and reference materials for the **Embedded C: A Modular Approach** course. It is designed to demonstrate how to transition from "Code that just works" to "Code that scales" using a professional 4-layer architecture.

## 📂 Repository Structure

The project follows a strict folder hierarchy to enforce the separation of concerns and ensure hardware portability.

* **`/app`**: Contains the **Application Layer**. This is the "Hardware-Agnostic Brain" of the system, written in 100% portable C code.
* **`/interface`**: The **Interface Layer**. Acts as a "Universal API" or contract, hiding the lower-level hardware details from the application.
* **`/device`**: The **Device Layer**. Contains software drivers for external PCB components like sensors (e.g., ADS1115) and actuators.
* **`/hal`**: The **Hardware Abstraction Layer (HAL)**. The only layer allowed to contain MCU-specific register access and headers (e.g., STM32 or ESP32 specific files).
* **`/common`**: Shared resources, including fixed-width type definitions and common macros.
* **`/docs`**: Contains the **PDF version of the course presentation** for offline study.

## 🚀 Examples & Features

### 1. The Multi-Platform Blinky
A practical demonstration of portability. The same application logic runs on both **STM32** and **ESP32** microcontrollers. To switch platforms, you only need to replace the files in the `/hal` folder; the application logic remains 100% untouched.

### 2. ESP32 Deep Dive
Complete code examples for all ESP32 modules covered in the course, demonstrating:
* **Layered Interaction:** How the Application calls the Interface to trigger hardware actions.
* **Callback Systems:** Managing asynchronous events like timers and interrupts.
* **Modular Initialization:** Using a dedicated module to coordinate hardware-dependent startup.

## 🛠 Coding Standards
All code in this repository follows the **Barr Group Embedded C Coding Standards** to ensure safety and reliability.
* **Ambiguity Elimination:** Use of `<stdint.h>` fixed-width types (e.g., `uint8_t`, `int32_t`)[cite: 84, 88].
* **Defensive Programming:** Implementation of **Yoda Conditions** (e.g., `if (CONSTANT == variable)`) to prevent assignment bugs.
* **Naming Conventions:** Clear prefixes for scope and type (e.g., `g_` for globals, `p_` for pointers).
* **Self-Documenting Code:** Standardized comment blocks using `@brief`, `@param`, and `@return`.

## 📖 How to Use
1.  **Reference the Presentation:** Use the PDF in `/docs` to follow the architectural theory.
2.  **Explore the HAL:** Compare the STM32 and ESP32 `/hal` implementations to see how silicon-specific code is isolated.
3.  **Template:** Use this folder structure as a professional template for your own industrial firmware projects.

---
**Instructor:** Mahmood Saadat  
**Organization:** [Cosmo Robotics](https://cosmorobotics.uk) [cite: 17]