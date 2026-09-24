---
name: esp-debug
description: 'Debug ESP32 projects by selecting COM port, flashing with esptool, listening to debug messages, and comparing output to code behavior. Use when: troubleshooting firmware issues, verifying code execution, inspecting debug output, diagnosing unexpected behavior.'
argument-hint: 'Optionally specify COM port (e.g., COM3, /dev/ttyUSB0) or leave blank for selection'
user-invocable: true
---

# ESP32 Debug Workflow

## When to Use
- **Firmware troubleshooting**: Code not executing as expected
- **Debug output verification**: Compare actual behavior to intended logic
- **Port selection**: Multiple devices connected, need to identify correct COM port
- **Continuous debugging**: Flash, listen, and analyze in one workflow
- **Bug investigation**: Print statements or logging output analysis

## Procedure

### Agent Guardrails
- In VS Code agent workflows, flashing and monitoring are separate outcomes:
   - Flashing should complete in a normal command run.
   - Monitoring should run as a bounded, agent-capturable command so the output is returned directly, without asking the user to paste anything.
- Prefer running [debug-monitor script](./scripts/serial_monitor.py) with an explicit `--port` and a `--timeout` as a synchronous terminal command. A fixed timeout makes the process exit on its own once done, so the full captured transcript is returned inline in the tool result.
- Do not open an indefinite/persistent monitor terminal as the primary capture method when the goal is to analyze output programmatically — an unbounded session cannot be read back by the agent and forces a manual copy/paste step. Reserve the persistent ESP-IDF monitor terminal for when the user explicitly wants to watch live output themselves.
- Also pass `--output <file>` so a log file exists for later reference in addition to the inline capture.
- Only ask the user to inspect or paste terminal output when the automated capture command fails (e.g., port busy, pyserial missing, permissions) and cannot be retried.


### Step 1: COM Port Selection
1. List available COM ports on the system
   - Windows: Use PowerShell `Get-WmiObject Win32_SerialPort` or check Device Manager
   - Linux/macOS: `ls /dev/tty*`
2. Identify the ESP32 device (usually shows as `USB Serial` or similar)
3. Confirm the correct COM port (e.g., `COM3`, `/dev/ttyUSB0`)
4. Note any required baud rate (typically 115200 for ESP32)

### Step 2: Build the Project
1. Verify the project compiles successfully
2. Locate the binary output file (typically `build/esp32/project.bin` or similar)
3. Confirm all dependencies are built

### Step 3: Flash the Firmware
1. Use esptool.py to flash the project to the ESP32:
   ```bash
   esptool.py --chip esp32 --port <COM_PORT> --baud 460800 write_flash -z 0x1000 <PATH_TO_BINARY>
   ```
   - Replace `<COM_PORT>` with the identified port
   - Replace `<PATH_TO_BINARY>` with the actual binary path
2. Wait for flash completion confirmation
3. Device should automatically reset after flashing

### Step 4: Capture Debug Output Automatically
1. Run [debug-monitor script](./scripts/serial_monitor.py) as a synchronous terminal command right after flashing, with a bounded `--timeout` (long enough to capture the reset banner plus the behavior under test, e.g. 10-20 seconds) and an `--output` log file:
   ```bash
   python .github/skills/esp-debug/scripts/serial_monitor.py --port COM3 --baud 115200 --timeout 15 --output debug_capture.log
   ```
   - The `--timeout` flag is required for automated capture: it makes the process exit on its own so the command completes and its full stdout is returned directly to the agent.
   - Never omit `--port` for automated runs — without it the script prompts interactively and blocks.
2. If the firmware needs a trigger (reset button, input, scheduled task) that the agent can drive, do it before or during this capture window; otherwise size the timeout to cover the expected event.
3. Read the captured transcript directly from the command result. If the process needed to be moved to the background or the timeout elapsed without exiting, retrieve its output before proceeding.
4. Only fall back to a persistent monitor terminal (ESP-IDF monitor or a manual tool) when the user explicitly wants to watch live output themselves, or when automated capture repeatedly fails:
   - Manual tool options: Windows — PuTTY, TeraTerm, Serial Port Monitor; Linux/macOS — `screen`, `picocom`, `minicom`.
   ```bash
   screen /dev/ttyUSB0 115200
   # or on Windows with pyserial:
   python -m serial.tools.miniterm COM3 115200
   ```
5. If the automated capture command errors out (port busy, missing pyserial, permissions), report the exact error and ask the user how to proceed instead of guessing.

### Step 5: Compare Debug Output to Code
0. Use the transcript captured automatically in Step 4 as the primary evidence. Only ask the user to paste or summarize output when automated capture was not possible.
1. **Locate relevant code sections** in the codebase matching the debug output
   - Use function names, variable names, or log statements as search terms
   - Cross-reference with [code analysis template](./references/debug_checklist.md)
2. **Trace execution flow**:
   - Does output appear in expected order?
   - Are all expected log statements present?
   - Any missing or unexpected messages?
3. **Verify variable values**:
   - Print statements should match expected calculations
   - Check for off-by-one errors, overflow, or underflow
   - Verify array indices and buffer sizes
4. **Check timing and sequencing**:
   - Are timestamps/counts monotonically increasing?
   - Do events occur in the correct order?
   - Are delays and timeouts working as coded?
5. **Identify discrepancies**:
   - Missing output → code not reaching that point
   - Wrong values → calculation or logic error
   - Out-of-order messages → race condition or scheduler issue
6. **Review code for bugs** using [debug checklist](./references/debug_checklist.md):
   - Uninitialized variables
   - Buffer overflows
   - Null pointer dereferences
   - Memory leaks
   - Race conditions
   - Integer overflow/underflow

### Step 6: Report the results
Show the result with captured debug logs and analysis from the previous steps.

## Quick Reference: Common Debug Scenarios

| Symptom | Likely Cause | Investigation |
|---------|-------------|-----------------|
| No output at all | Baud rate mismatch, wrong COM port | Verify port and speed; check device manager |
| Garbled output | Baud rate incorrect | Try 115200, 230400, or 460800 |
| Output stops abruptly | Exception/crash, watchdog reset | Look for error messages before stop |
| Missing expected output | Code not executing | Add more logging; check conditionals |
| Wrong values in output | Logic error, uninitialized var, overflow | Review calculations; check initialization |
| Infinite loops | Missing break/return, wrong condition | Check loop conditions and exit logic |

## Scripts and Resources

- [Serial Monitor Script](./scripts/serial_monitor.py) — Automated capture and logging of debug output
- [Debug Checklist](./references/debug_checklist.md) — Common bugs to look for during code review
- [Coding Standards](../../instructions/c-coding-standards.instructions.md) — Follow BarrC standards and naming conventions when fixing bugs

## Tips

- **Keep logs**: Save debug output to files for later analysis
- **Capture automatically**: Prefer a bounded `--timeout` run of the debug-monitor script so output returns inline to the agent instead of requiring manual copy/paste
- **Add timestamps**: Include timing info in log statements for sequence verification
- **Use meaningful names**: Follow naming conventions for variables in print statements
- **Narrow scope**: Add logging strategically to isolate the issue area
- **Compare commits**: If behavior changed, compare code diff to find what changed
- **Test incrementally**: After each fix, re-flash and verify specific behavior

---

**Last Updated**: 2026-09-22  
**Skill Version**: 1.2
