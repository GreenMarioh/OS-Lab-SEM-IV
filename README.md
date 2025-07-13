# 🧠 OS Lab Programs (Scheduling & IPC) — C Language

This repository contains C implementations of key **Operating System concepts**, focusing on **CPU scheduling algorithms** and **inter-process communication (IPC)** mechanisms using `fork()` and `pipe()`. These programs are ideal for academic lab work, revision, or experimentation.

---

## 📋 Table of Contents

- [📁 Source Files Descriptions](#-source-files-descriptions)
- [⚙️ Compilation & Usage](#️-compilation--usage)
- [📌 Requirements](#-requirements)
- [📄 License](#-license)

---

## 📁 Source Files Descriptions

### 🔄 Scheduling Algorithms

- **`fcfs.c`**  
  Implements the **First-Come, First-Serve (FCFS)** scheduling algorithm. It takes arrival and burst times of processes, schedules them in arrival order, and calculates waiting, turnaround, and completion times.

- **`sjf.c`**  
  Implements **Shortest Job First (SJF)** scheduling (non-preemptive). Chooses the shortest available job at each step and calculates relevant metrics.

- **`RoundRobin.c`**  
  Simulates the **Round Robin** scheduling algorithm. Uses a queue to cycle through processes with a fixed time quantum. Includes a Gantt chart for process execution visualization.

- **`SRTF.c`**  
  Implements **Shortest Remaining Time First (SRTF)** scheduling — a preemptive variant of SJF. Selects the process with the least remaining time at every time unit. Includes Gantt chart visualization.

- **`srtfOneLine.c`**  
  A **condensed one-liner version of SRTF**, retaining full functionality but written in a compressed code style for faster reading and minimalism.

---

### 🔁 Process Management & IPC

- **`fork3.c`**  
  Demonstrates **process creation** using `fork()`. Outputs a message from both the parent and child processes, showing their execution context.

- **`pipe.c`**  
  Implements **inter-process communication** using **unnamed pipes**. Demonstrates writing and reading messages in the same process using pipe file descriptors.

- **`pipe2.c`**  
  Illustrates **parent-child communication** through a pipe. The parent writes two messages, which the child process reads after a `fork()`.

---

## ⚙️ Compilation & Usage

Use `gcc` to compile the C files. Here’s an example for each:

```bash
gcc fcfs.c -o fcfs && ./fcfs
gcc sjf.c -o sjf && ./sjf
gcc RoundRobin.c -o rr && ./rr
gcc SRTF.c -o srtf && ./srtf
gcc srtfOneLine.c -o srtf1 && ./srtf1
gcc fork3.c -o fork3 && ./fork3
gcc pipe.c -o pipe && ./pipe
gcc pipe2.c -o pipe2 && ./pipe2
```

> ⚠️ Make sure you're using a UNIX-like environment for `fork()` and `pipe()` functionality to work properly (Linux or WSL recommended).

---

## 📌 Requirements

- GCC Compiler (Linux or Windows WSL)
- Basic understanding of:
  - CPU scheduling strategies
  - Process creation with `fork()`
  - Piping mechanisms (`pipe()` system call)

---
