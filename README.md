# Parallel Prime Generator

## Overview

This project computes prime numbers in a given range [start, end] using multiple child processes to utilize multiple CPU cores. It also measures how execution time changes with the number of processes and visualizes the results using Python.

## OS Concepts Used

- Process creation (fork()): The parent creates n child processes to run computations in parallel.
- Work partitioning: The range [start, end] is split into n chunks; each child handles one chunk.
- Synchronization (wait()): The parent waits for all children to finish before merging outputs.
- Parallelism & overhead: Demonstrates speedup up to core limits and diminishing returns due to scheduling and context switching.

## How It Works

1. Input: start, end, and n (number of child processes).
2. Each child checks primes in its assigned subrange and writes to a separate file.
3. The parent waits for all child processes, merges results into prime.txt, and appends execution time to time.txt.

## Python Automation & Plotting

- tester.py runs the C program repeatedly for different ranges and values of n.
- Each run appends a line to time.txt in the format:

  start end n execution_time

- plot.ipynb reads time.txt and plots n vs execution time to analyze scalability.

## Files

- prime_gen.c – Parallel prime generator written in C using fork()
- prime_generated_ai.c – AI-assisted reference implementation
- plot.ipynb – Python notebook for plotting n vs execution time
- tester.py – Automates performance experiments
- time.txt – Generated timing data (ignored by git)
- prime.txt – Merged prime numbers output (ignored by git)
- .gitignore – Ignores generated output files

## Build & Run

Compile:

gcc prime_gen.c -o primes -lm

Run manually:

./primes 1 1000000 4

Run automated tests:

python3 tester.py

## Key Observations

- Execution time decreases initially as n increases due to parallel execution.
- Performance gains diminish after reaching the number of logical CPU cores.
- Too many processes increase overhead due to context switching and scheduling.

## AI Assistance Disclosure

Some parts of this project were developed with the assistance of AI-generated code for learning and productivity purposes.

- File: prime_generated_ai.c
- Usage: Used as a reference and starting point for implementing parallel prime generation using fork() and process synchronization.
- Verification: The code was reviewed, tested, and modified  to ensure correctness, performance, and alignment with operating system concepts.

All final design decisions, integration, testing, and documentation were done manually.

## Author

RUPDEEP RAY(24CS8023)

NAKUL RAMTEKE(24CS8026)

NIJAMPUDI RAM CHARAN(24CS8024)
