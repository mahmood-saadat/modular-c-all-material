# Embedded C: A Modular Approach - Project Framework

This repository contains the official source code and reference materials for the **Embedded C: A Modular Approach** course. It is designed to demonstrate how to transition from "Code that just works" to "Code that scales" using a professional 4-layer architecture.

Stop writing firmware that only works on one chip. Most electronic engineers can make a microcontroller "work," but few can design firmware that is professional, safe, and truly portable. If your main.c is hundreds of lines long, or if switching from an STM32 to an AVR requires a total rewrite, this course is for you.

This course is a deep dive into Firmware Architecture. We move beyond simple "bare-metal" coding and teach you how to think like a Software Architect. You will learn to build a robust, 4-layer stack that separates your high-level logic from the low-level silicon.

# The 4-Layer Framework You Will Master:

* The HAL (Hardware Abstraction Layer): Hiding the silicon and register complexity.

* The Device Layer: Building reusable drivers for external components like sensors and LCDs.

* The Interface Layer: Creating a "contract" between your hardware and your brain.

* The Application Layer: Writing pure, hardware-agnostic business logic.

# Why This Course Is Different:

* Architectural Focus: We don't teach C syntax; we teach C strategy.

* Standards: Every line of code follows standards, including "Yoda Conditions" and strict naming conventions.

* Hardware Agnostic: The principles you learn here apply to any MCU, STM32, PIC, AVR, ESP32, or ARM Cortex.

# What You Will Learn

* Design a modular 4-layer firmware project from scratch.

* Implement the code according to an Embedded C Coding Standard.

* Decouple application logic from hardware using the Interface Pattern.

* Create a "Professional Starter Kit" template to jumpstart any future project.

* Structure the Application Layer with dedicated Init, Callback, and Global modules.

* Apply defensive programming techniques to eliminate "Magic Numbers" and assignment bugs.

# Are there any course requirements or prerequisites?

* Understanding of the C programming language (loops, pointers, structs).

* Familiarity with any Microcontroller (MCU) and basic electronics.

* A desire to move from "Hobbyist" to "Professional" firmware habits.

# Who this course is for:

* Electronic Engineers who want to write better, more structured software.

* Embedded Developers struggling with code portability and unmanageable projects.

* Students & Hobbyists looking to enter the professional embedded systems industry.

* Firmware Managers who need a standard architectural framework for their team.



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
* **Ambiguity Elimination:** Use of `<stdint.h>` fixed-width types (e.g., `uint8_t`, `int32_t`).
* **Defensive Programming:** Implementation of **Yoda Conditions** (e.g., `if (CONSTANT == variable)`) to prevent assignment bugs.
* **Naming Conventions:** Clear prefixes for scope and type (e.g., `g_` for globals, `p_` for pointers).
* **Self-Documenting Code:** Standardized comment blocks using `@brief`, `@param`, and `@return`.

## 📖 How to Use
1.  **Reference the Presentation:** Use the PDF in `/docs` to follow the architectural theory.
2.  **Explore the HAL:** Compare the STM32 and ESP32 `/hal` implementations to see how silicon-specific code is isolated.
3.  **Template:** Use this folder structure as a professional template for your own industrial firmware projects.

---
**Instructor:** Mahmood Saadat  
**Organization:** [Cosmo Robotics](https://cosmorobotics.uk/learning/)
**Udemy:** [Embedded C Firmware Architecture - A Modular Approach](https://www.udemy.com/course/embedded-c-firmware-architecture-a-modular-approach/?referralCode=EFD12AF0DDA09E696CC2)
**Youtube:** [Cosmo Robotics](https://youtube.com/@mahmoodsaadat8537?si=8Nq0eulE_7zd1bM-)
