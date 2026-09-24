---
description: "Use when writing, generating, reviewing, or modifying C code (.c/.h) in this ESP32 project (app/, hal/, library/, main/, templates/). Enforces the BarrC coding standard, the App->Interfaces->Devices->HAL layered architecture with strict per-layer include rules, and lower_snake_case naming conventions (g_, b_, a_, p_, t_ prefixes)."
applyTo: "**/*.c,**/*.h"
---

# Code Development Standards for ESP32 AI Project

## Overview
This document defines the coding standards and conventions for this ESP32 project. All code generation and modifications must adhere to these standards before submission.

**Scope**: Applies to all first-party code under `app/`, `hal/`, `library/`, `main/`, and `templates/`. Does **not** apply to `managed_components/` or `build/` — these contain vendored/third-party and auto-generated files that are outside our control and must not be hand-edited to satisfy these rules.

## 0. Mandatory Self-Review Before Responding
- Before presenting any generated or modified code as your final result, re-read this entire instructions file from top to bottom.
- Verify the result reflects every rule below: coding standard, architecture/layering, include rules, naming conventions, and the bug-review pass in Section 5.
- Fix any violation you find before showing the result to the user. Do not skip this check even for small changes.

## 1. Coding Standard
- Follow **BarrC (BARR C Coding Standards)** for all C code development
- Emphasize safety, reliability, and maintainability
- Refer to BARR-C standard rules for code style, commenting, and structure

## 2. Architecture Pattern
All code organization must follow one of these two architecture patterns:

```
Pattern 1 (Complex devices):
App → Interfaces → Devices → HAL (Hardware Abstraction Layer)

Pattern 2 (Simple interfaces):
App → Interfaces → HAL (Hardware Abstraction Layer)
```

**Guidelines:**
- **App Layer**: Application-specific logic and tasks (`app/task/`)
- **Interfaces Layer**: Device-agnostic abstractions (`library/interfaces/`)
- **Devices Layer**: Specific device drivers (`library/devices/`)
- **HAL Layer**: Low-level hardware abstractions (`hal/`)

## 3. Architectural Dependency Rules (CRITICAL)

**These rules enforce strict layering and must be followed strictly:**

### HAL Layer (`hal/`)
- **Header files** can ONLY include:
  - Standard C library headers (stdio.h, stdint.h, stdbool.h, etc.)
  - Other HAL library headers
  - **NO platform-specific headers, NO OS headers, NO peripherals**
- **Source files** (.c) are free to include any required header (FreeRTOS, ESP-IDF, etc.)

### Device Layer (`library/devices/`)
- **Can ONLY include** headers from HAL layer
- **Cannot include** Interface or App layer headers
- **Cannot include** platform-specific headers

### Interface Layer (`library/interfaces/`)
- **Can include** HAL layer headers
- **Can include** Device layer headers
- **Cannot include** App layer headers
- **Cannot include** platform-specific headers

### App Layer (`app/`)
- **Can ONLY include** Interface layer headers
- **Cannot include** Device, HAL, or platform-specific headers directly
- Must access hardware through Interfaces only

### Header vs Source Files
- **Header files (.h)**: Must follow the inclusion rules strictly
- **Source files (.c)**: Free to include any required headers for implementation, but public API (headers) must still respect the rules

## 4. Naming Conventions

### Golden Rule: ALL NAMES MUST BE LOWER SNAKE_CASE
All variable names, function names, and identifiers must use lowercase with underscores separating words. No camelCase, no PascalCase.

### Global Variables
- **Prefix**: `g_`
- **Example**: `g_adc_value`, `g_sensor_data`, `g_current_state`

### Global Booleans
- **Prefix**: `g_b_`
- **Example**: `g_b_is_initialized`, `g_b_enable_logging`, `g_b_device_ready`

### Global Arrays
- **Prefix**: `g_a_`
- **Example**: `g_a_sensor_readings`, `g_a_gpio_states`, `g_a_buffer`

### Global Pointers
- **Prefix**: `g_p_`
- **Example**: `g_p_queue_handle`, `g_p_mutex`, `g_p_device_config`

### Global Array of Boolean Pointers
- **Prefix**: `g_a_b_p_`
- **Example**: `g_a_b_p_device_flags`, `g_a_b_p_channel_enabled`

### Function Input Arguments
- **Prefix**: `t_` (not `g_`)
- **Follow same naming rules as globals for suffixes**
- **Always use lower snake_case**
- **Examples**:
  - `t_adc_value` (simple input)
  - `t_b_enable_flag` (boolean input)
  - `t_a_data` (array input)
  - `t_p_queue_handle` (pointer input)

### Function Names
- Use **descriptive, clear names** in **lower snake_case**
- Examples: `initialize_adc()`, `read_sensor_value()`, `calculate_average()`

### Local Variables
- Use descriptive names without special prefixes
- Always use **lower snake_case**
- Examples: `sensor_value`, `calibration_factor`, `read_count`

### Braces
- Opening braces `{` must be on the next line of the control statement or function definition
- Closing braces `}` must be on their own line
- Example:
  ```c
  void example_function(void)
  {
      if (condition)
      {
          // code
      }
  }
  ```
### Initilisation
- All the variables must be properly initialized at declaration. Default to 0 or NULL as appropriate.
- Example:
  ```c
  static uint16_t g_a_adc_raw_values[ADC_CHANNELS] = {0};
  static bool g_b_is_initialized = false;
  static void* g_p_device_config = NULL;
  ```

## 5. Code Quality Requirements

### After Code Generation
1. **Review for potential bugs**:
   - Buffer overflows
   - Off-by-one errors
   - Memory leaks
   - Null pointer dereferences
   - Integer overflow/underflow
   - Uninitialized variables
   - Race conditions in multi-threaded code

2. **Verify naming conventions**:
   - All globals follow prefix rules (`g_`, `g_b_`, `g_a_`, `g_p_`, `g_a_b_p_`)
   - All function arguments use `t_` prefix with appropriate suffixes
   - ALL names are in **lower snake_case** (no camelCase)
   - All names are descriptive and meaningful

3. **Verify architecture and dependencies**:
   - Code placement matches App→Interfaces→Devices→HAL pattern
   - HAL headers only include standard C or other HAL headers
   - Device headers only include HAL headers
   - Interface headers only include HAL or Device headers
   - App code only includes Interface headers
   - No circular dependencies
   - Proper abstraction boundaries maintained

## 6. File Organization

```
app/           → Application logic and tasks
├── callbacks/  → Event callbacks
├── globals/    → Global variables and data
├── initialise/ → Initialization code
└── task/       → Task implementations

hal/           → Hardware Abstraction Layer
├── adc/        → ADC driver
├── gpio/       → GPIO driver
├── i2c/        → I2C driver
├── pwm/        → PWM driver
└── os/         → OS abstractions (tasks, semaphores, delays)

library/       → Reusable libraries
├── devices/    → Device drivers (ADS1115, etc.)
└── interfaces/ → Generic interfaces
```

## 7. Code Review Checklist

Before committing or submitting code, verify:
- [ ] Re-read this instructions file in full (Section 0) and confirmed the result reflects all of it
- [ ] All names use **lower snake_case** (including functions and local variables)
- [ ] All global variables follow `g_`, `g_b_`, `g_a_`, `g_p_` prefixes
- [ ] All global arrays of booleans use `g_a_b_p_` prefix
- [ ] All function arguments use `t_` prefix with appropriate suffixes
- [ ] Function names are descriptive and use lower snake_case
- [ ] Local variables use descriptive lower snake_case names
- [ ] Code follows architecture pattern (App→Interfaces→Devices→HAL)
- [ ] **HAL headers only include standard C or other HAL headers**
- [ ] **Device headers only include HAL headers**
- [ ] **Interface headers only include HAL or Device headers**
- [ ] **App code only includes Interface headers**
- [ ] No circular dependencies
- [ ] No buffer overflows, null pointers, memory leaks, or uninitialized variables
- [ ] No race conditions in multi-threaded code
- [ ] Comments explain complex logic using BarrC standards

## 8. Example Code Snippet

```c
// File: hal/adc/inc/hal_adc.h
// HAL headers can ONLY include standard C or other HAL headers
#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdint.h>
#include <stdbool.h>
// OK: Standard C headers

// NOT OK: No platform-specific headers like esp_adc.h, driver/adc.h
// NOT OK: No OS headers like FreeRTOS.h

typedef struct
{
    uint8_t channel_count;
    uint16_t sampling_rate;
} hal_adc_config_t;

void hal_initialize_adc(hal_adc_config_t t_p_config);
uint16_t hal_read_adc_channel(uint8_t t_channel);

#endif
```

```c
// File: hal/adc/src/hal_adc.c
// Source files CAN include any necessary headers for implementation
#include "hal_adc.h"
#include "esp_adc.h"           // OK in .c file
#include "freertos/FreeRTOS.h" // OK in .c file

static uint16_t g_a_adc_raw_values[ADC_CHANNELS] = {0};
static bool g_b_adc_initialized = false;

void hal_initialize_adc(hal_adc_config_t t_p_config)
{
    uint16_t local_read_value;
    
    for (uint8_t channel_index = 0; channel_index < t_p_config->channel_count; channel_index++)
    {
        g_a_adc_raw_values[channel_index] = 0;
    }
    
    g_b_adc_initialized = true;
}
```

```c
// File: library/interfaces/analog_input/inc/if_analog_input.h
// Interface can include HAL headers
#ifndef IF_ANALOG_INPUT_H
#define IF_ANALOG_INPUT_H

#include "hal_adc.h"  // OK: HAL header

typedef struct
{
    uint8_t input_id;
    uint16_t calibration_offset;
} analog_input_config_t;

uint16_t if_get_analog_input(uint8_t t_input_id);

#endif
```

```c
// File: app/task/src/app.c
// App can only include Interface headers
#include "if_analog_input.h"  // OK: Interface header

// NOT OK: Cannot include HAL headers like hal_adc.h
// NOT OK: Cannot include Device headers

void app_read_sensors(void)
{
    uint16_t sensor_value = if_get_analog_input(0);
}
```

---

**Last Updated**: 2026-09-22  
**Version**: 4.0 (Fixed file naming to `.instructions.md` for auto-discovery; added mandatory self-review step)
