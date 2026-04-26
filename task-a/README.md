# Task A: Vulnerability discovery and remediation

This folder contains my Task A work for 7021SCN. I built a small C program with a deliberate memory corruption bug, showed how it can be triggered in a controlled lab setup, and then provided a safer fixed version.

The final files in this task are:

- `vulnerable.c` - intentionally unsafe example
- `secure.c` - fixed version using bounded handling
- `Makefile` - build targets for both versions
- `evidence/` - screenshots from build, runtime behaviour, and debugging

Evidence files used:

- `evidence/01-environment.png`
- `evidence/02-build-success.png`
- `evidence/03-short-input-both-ok.png`
- `evidence/04-vulnerable-segfault.png`
- `evidence/05-secure-rejected.png`
- `evidence/06-gdb-sigsegv-bt.png`

## What the brief asked for

Task A required three things:

- a custom C/C++ program with a memory corruption flaw
- explanation of how the flaw can be exploited in principle
- corrected code using secure coding practice

This task addresses all three in a small, reproducible example.

## Vulnerable program (`vulnerable.c`)

The vulnerable code copies user input into a fixed-size stack buffer:

- buffer size: `char buffer[10]`
- copy function: `strcpy(buffer, argv[1])`

`strcpy` does not know the size of `buffer`. If the input is longer than the destination, bytes are written past the end of the array. In stack memory this can overwrite adjacent control data and cause undefined behaviour.

## Secure program (`secure.c`)

The secure version keeps the same user-facing behaviour for valid input but prevents overflow:

- uses `snprintf(buffer, sizeof(buffer), "%s", argv[1])`
- checks return value
- rejects oversized input with a clear error and non-zero exit code

So the secure version fails safely instead of continuing with corrupted memory.

## Build instructions

From Kali/WSL:

```bash
cd "/mnt/c/Users/Nihaal/OneDrive/Desktop/Mod4pro/task-a"
make clean
make vulnerable
make secure
```

This creates `vulnerable` and `secure` binaries.

## Behaviour test

### 1) Normal input

```bash
./vulnerable Alice
./secure Alice
```

Expected: both print a normal greeting.

### 2) Oversized input

```bash
./vulnerable AAAAAAAAAAAAAAAAAAAAAA
```

Expected: unsafe binary may print a greeting first, then crash (observed `SIGSEGV` in my run/evidence).

```bash
./secure AAAAAAAAAAAAAAAAAAAAAA
echo $?
```

Expected: secure binary prints an error and exits non-zero.

## GDB check (supporting evidence)

```bash
gdb -q ./vulnerable
```

At the prompt:

```text
run AAAAAAAAAAAAAAAAAAAAAA
bt
```

In my debugging output, the crash pattern was consistent with overwritten stack data from the long input.

## Why this matters

This is a classic example of why unbounded string copy functions are dangerous in C. The bug is small, but it demonstrates an important secure coding lesson:

- insecure code can appear to work for normal input
- memory corruption still happens underneath
- failure may only become visible at function return or later execution

## Reflection

Doing this task made the difference between "works" and "safe" very obvious. The vulnerable code is only a few lines and compiles cleanly, but it still breaks memory safety when input size is not controlled.

The key improvement in the fixed version is not just switching one function call. The real improvement is adding an explicit boundary check and deciding what to do when input does not fit.

If this were production code, I would also treat this as one layer of defence, not the whole solution. I would combine safer code with compiler and runtime hardening, static analysis, code review, and repeatable tests for edge cases.

## Scope and ethics

All testing was done locally in my own lab setup (WSL/Kali) for coursework only. No unauthorised systems were targeted.

## References

- 7021SCN Week 4 lecture/lab material (buffer overflow)
- CWE-120: Buffer Copy without Checking Size of Input
- CERT C guidance on safer string handling
