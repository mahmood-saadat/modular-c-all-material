# ESP32 Debug Code Review Checklist

Use this checklist when comparing debug output to your code to identify potential bugs.

## Variable Initialization

- [ ] All global variables are initialized before first use
- [ ] No uninitialized local variables are being printed or used in calculations
- [ ] Array indices are within bounds (0 to size-1)
- [ ] Pointer variables are not NULL before dereferencing
- [ ] Enum values are valid for the expected range

## Memory and Buffers

- [ ] Buffer sizes match allocation: `char buffer[SIZE]` vs reads/writes
- [ ] No buffer overflows from string operations (strcpy, sprintf)
- [ ] String null-terminators are present where expected
- [ ] Array access doesn't exceed declared bounds
- [ ] Dynamic memory (malloc) is checked for NULL return
- [ ] No memory leaks: all malloc/new have corresponding free/delete

## Integer Arithmetic

- [ ] No integer overflow in addition/multiplication operations
- [ ] No integer underflow in subtraction operations
- [ ] Division by zero checks present where needed
- [ ] Modulo operations use non-zero divisor
- [ ] Type conversions don't lose precision (e.g., long to int)
- [ ] Signed/unsigned comparison is correct (mixed comparisons can cause issues)

## Control Flow

- [ ] Loop conditions are correct (off-by-one errors?)
- [ ] Loop exit conditions are reachable
- [ ] No infinite loops without escape conditions
- [ ] Conditional branches cover all expected cases
- [ ] Function return values are checked (especially error codes)
- [ ] All code paths have appropriate exit/return statements

## Function Logic

- [ ] Function parameters match expected types and values
- [ ] Input arguments follow naming convention (`t_` prefix)
- [ ] Global variable access follows convention (`g_` prefix)
- [ ] Function output/return values are used correctly by caller
- [ ] Function side effects are intentional and documented

## Timing and Sequencing

- [ ] Events occur in the expected order in debug output
- [ ] Timestamps or counters are monotonically increasing
- [ ] No race conditions between tasks/interrupts
- [ ] Semaphore/mutex operations are properly paired (acquire/release)
- [ ] Delays and timeouts use correct units (ms vs seconds)

## Multi-threading Issues

- [ ] Global variables accessed from multiple tasks are protected
- [ ] Mutex/semaphore held for minimum time
- [ ] No deadlock conditions (A waits for B, B waits for A)
- [ ] Queue/mailbox operations have timeouts
- [ ] Task priorities are appropriate for the workflow

## Hardware Interface

- [ ] Register reads/writes use correct addresses
- [ ] Pin configurations match intended function (input/output)
- [ ] ADC/DAC values are in expected range
- [ ] I2C/SPI timing meets device requirements
- [ ] Interrupts are enabled/disabled as needed

## Naming Convention Compliance

- [ ] Global variables start with `g_`
- [ ] Global booleans start with `g_b_`
- [ ] Global arrays start with `g_a_`
- [ ] Global pointers start with `g_p_`
- [ ] Global arrays of boolean pointers start with `g_a_b_p_`
- [ ] Function parameters start with `t_`
- [ ] All names use lower snake_case (no camelCase)
- [ ] Names are descriptive (avoid single letters except in loops)

## Debug Output Analysis

When reviewing debug output against code, check:

- [ ] All expected `printf` or logging statements appear in output
- [ ] Output values match calculated values in code
- [ ] Order of operations matches code structure
- [ ] Conditional branches executed as expected
- [ ] Loop iterations match expected count
- [ ] No unexpected error messages or warnings
- [ ] Function entry/exit points logged correctly

## Comparison Workflow

1. **Map Output to Code**: For each debug statement, locate it in the source file
2. **Verify Execution Path**: Trace the code path that produces this output
3. **Check Values**: Do printed values match expected calculations?
4. **Validate Sequence**: Are messages appearing in the correct order?
5. **Look for Missing Output**: Are there expected statements that don't appear?
6. **Identify Anomalies**: Any unexpected behavior or error messages?

---

**Last Updated**: 2026-09-21
