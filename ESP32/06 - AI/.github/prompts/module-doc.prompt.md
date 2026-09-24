---
description: "Generate overview and detailed Mermaid diagram documentation for a project module (HAL, Interface, Device, or App layer) into the Docs folder"
agent: "agent"
argument-hint: "<module name, e.g. gpio, analog_output, task>"
---

Generate Mermaid-diagram documentation for the module specified by the user (the text following this command, e.g. `gpio`, `analog_output`, `task`).

## 1. Locate the module

Search the project's layered folders for a folder matching the given module name:
- `hal/<module>`
- `library/interfaces/<module>`
- `library/devices/<module>`
- `app/<module>`

A module folder typically contains `inc/` (headers) and `src/` (implementation) subfolders. If the name matches more than one layer (e.g. a device and an interface share a name), document each match separately. If no match is found, list the closest candidate folder names and ask the user to confirm before continuing.

Follow the architecture and layering rules defined in [c-coding-standards.instructions.md](../instructions/c-coding-standards.instructions.md) when describing dependencies (App → Interfaces → Devices → HAL).

## 2. Read the module

Read every file under the module's `inc/` and `src/` folders. For each file, note:
- Public types, structs, enums, and macros declared in headers
- Public function signatures declared in headers
- Static/internal functions and global variables defined in source files
- Which other-layer headers are included (e.g. an interface including a HAL header)

## 3. Prepare the Docs folder

Ensure a `Docs/` folder exists at the workspace root. Create it if it does not already exist.

## 4. Generate two Markdown files

Before writing, check whether `Docs/<module>.md` or `Docs/<module>-detailed.md` already exist. If either does, warn the user that it will be overwritten and ask for confirmation before proceeding. Only proceed with writing after the user confirms.

Write both files into `Docs/`:

### `Docs/<module>.md` — Overview

A short description of the module (what it does, which architecture layer it belongs to) followed by **one** Mermaid `flowchart` diagram showing:
- The module as a labeled box/subgraph containing its `inc/` and `src/` file names (no function-level detail)
- The architecture layer the module belongs to (App / Interfaces / Devices / HAL)
- One-level dependency arrows to/from the layers or modules it directly includes or is included by

### `Docs/<module>-detailed.md` — Detailed structure

A short description followed by **one or more** Mermaid diagrams (use `classDiagram` for per-file types/functions, and `flowchart` for call/include relationships) showing:
- Each header file as a class/node listing its public types, macros, and function signatures
- Each source file as a class/node listing its static functions and global variables
- Include relationships between this module's files and other-layer headers it depends on
- Any notable call relationships between the module's own functions

## 5. Confirm

After writing both files, summarize what was created and list the file paths.
