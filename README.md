
# Parallel Numerical Integration of π using POSIX Threads

This project demonstrates how to approximate the value of π using **numerical integration** and how to accelerate the computation using **POSIX threads (pthreads)**.

The program evaluates the integral:

π = 4 ∫₀¹ √(1 − x²) dx

The function √(1 − x²) represents the upper half of a unit circle.  
The integral from 0 to 1 corresponds to the **area of one quarter of the unit circle**, and multiplying by 4 gives the value of **π**.

The integral is approximated using the **Midpoint Riemann Sum (rectangular decomposition method)**.

---

# Repository Structure

```

pthread-parallel-pi-integration
│
├── src
│   ├── 2integral_serial.c
│   ├── 2integral_serial_timer.c
│   └── 3integral_parallel.c
│
├── report
│   └── POSIX_Threads_Report.pdf
│
├── README.md
├── LICENSE
└── .gitignore

```

---

# Programs Included

## 1. Serial Numerical Integration

`2integral_serial.c`

Computes π using the midpoint Riemann sum method in a **single-threaded implementation**.

Input:
```

<number_of_intervals>

```

Example:
```

./serial 1000000

```

---

## 2. Serial Version with Timing

`2integral_serial_timer.c`

This program performs the same numerical integration as the basic serial
implementation, but also measures the **execution time** of the computation
using `gettimeofday()`.

To improve numerical precision, this version uses **`long double` arithmetic**
for the integration variables and accumulation of the summation.

Input:
```

<number_of_intervals>

```

Example:
```

./serial_timer 1000000

```

Output includes:

- computed value of π
- execution time

---

## 3. Parallel Numerical Integration using POSIX Threads

`3integral_parallel.c`

This version divides the integration work across **multiple threads**.

Each thread computes the partial sum for a portion of the intervals, and the results are combined using a **mutex-protected global sum**.

Input:
```

<number_of_intervals> <number_of_threads>

```

Example:
```

./parallel 1000000 4

```

Output includes:

- computed value of π
- number of threads used
- execution time

---

# Compilation

Use **gcc** with math and pthread libraries.

Compile the serial program:

```

gcc src/2integral_serial.c -o serial -lm

```

Compile the serial timer program:

```

gcc src/2integral_serial_timer.c -o serial_timer -lm

```

Compile the pthread parallel program:

```

gcc src/3integral_parallel.c -o parallel -lm -lpthread

```

---

# Running the Programs

Example serial run:

```

./serial 1000000

```

Example serial run with timing:

```

./serial_timer 1000000

```

Example parallel run:

```

./parallel 1000000 4

```

Where:

```

1000000  → number of integration intervals
4        → number of threads

```

---

# Performance Experiments

The report evaluates two experiments:

### 1️⃣ Serial vs Parallel (2 Threads)

Intervals tested:

```

1,000
10,000
100,000
1,000,000

```

### 2️⃣ Thread Scaling

Threads tested:

```

1
2
4
8
16

```

Performance metrics measured:

- execution time
- speedup
- parallel efficiency

---

# Key Concepts Demonstrated

- Numerical integration
- Midpoint Riemann sum
- POSIX threads
- Parallel workload partitioning
- Mutex synchronization
- Parallel performance analysis

---

# Author

Nabin Kumar Singh  
M.S. Electrical and Computer Engineering  
University of Alabama in Huntsville
```
