---
description: "Review a module's .c/.h files against the project's C coding standards using the Embedded C Expert agent, listing bugs, standard violations, and best-practice suggestions"
agent: "Embedded C Expert"
argument-hint: "<module name, or select/open a .c or .h file, e.g. gpio, analog_output>"
---

Review the module indicated by the user for bugs, coding-standard violations, and best-practice improvements, from the point of view of the `Embedded C Expert` persona.

## 1. Identify the module

Determine which module to review, in this order of priority:
1. If a `.c` or `.h` file is currently selected or open in the editor, use the folder that contains it (its parent `inc/`/`src/` folder) as the module.
2. Otherwise, treat the text following this command as the module name (e.g. `gpio`, `analog_output`) and search the layered folders for a match:
   - `hal/<module>`
   - `library/interfaces/<module>`
   - `library/devices/<module>`
   - `app/<module>`

A module folder typically contains an `inc/` (header) and `src/` (implementation) subfolder. If the name matches more than one layer (e.g. a device and an interface share a name), ask the user which one to review. If no match is found, list the closest candidate folder names and ask the user to confirm before continuing.

## 2. Read the module

Read every `.c` and `.h` file under the module's `inc/` and `src/` folders (both the header and the source side of the module).

## 3. Review against the coding standards

Follow the rules defined in [c-coding-standards.instructions.md](../instructions/c-coding-standards.instructions.md) — BarrC naming conventions, the App → Interfaces → Devices → HAL layered architecture, and per-layer include rules.

For each file, evaluate:
- **Potential bugs**: null/uninitialized pointer use, missing bounds checks, unchecked return/error codes, integer overflow, resource leaks, incorrect `const`/`volatile` usage, off-by-one errors
- **Instruction violations**: naming convention mismatches (`g_`, `b_`, `a_`, `p_`, `t_` prefixes, lower_snake_case), incorrect layering or forbidden includes, missing/incorrect header guards, anything else that conflicts with `c-coding-standards.instructions.md`
- **Best practices**: encapsulation, fixed-width types for hardware interfaces, defensive programming, function/module cohesion, readability

## 4. Present findings as a list

Present the review as a single flat list, grouped under three headings: `Potential Bugs`, `Instruction Violations`, `Best Practice Suggestions`. Each entry must include the file name, the relevant line number(s) if known, a short description of the issue, and a suggested fix. If a category has no findings, state "None found" under that heading.

## 5. Ask before modifying

After presenting the list, ask the user whether they want you to proceed and apply fixes for the listed entries (all of them, or a subset). Do not modify any file until the user confirms.
