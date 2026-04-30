# Student Study Time Optimizer
## Algorithm: 0/1 Knapsack (Dynamic Programming)

---

## Problem Statement

A student has a limited number of hours before an exam.
There are multiple subjects to study — each requiring different time
and offering different marks weightage.

**Goal:** Select the best combination of subjects to maximize total marks
within the available study time.

This is a classic **0/1 Knapsack Problem**:
- Each subject is either fully studied (1) or skipped (0)
- You cannot partially study a subject

---

## Real-World Analogy

| Knapsack Concept | Study Optimizer Equivalent |
|---|---|
| Knapsack capacity | Total available study time (hours) |
| Item | Subject |
| Item weight | Time required to study the subject |
| Item value | Marks weightage of the subject |
| Goal | Maximize total marks within time limit |

---

## Project Structure

```
StudyOptimizer/
├── main.cpp        → Entry point, menu, user input, display
├── subject.h       → Subject class declaration
├── subject.cpp     → Subject class implementation
├── optimizer.h     → Optimizer class declaration
├── optimizer.cpp   → 0/1 Knapsack DP algorithm
└── README.md       → This file
```

### File Responsibilities

| File | Role |
|---|---|
| `subject.h / .cpp` | Subject class: name, time, marks |
| `optimizer.h / .cpp` | Core DP algorithm + traceback |
| `main.cpp` | Input handling, menus, output display |

---

## Algorithm Explanation

### 0/1 Knapsack — Dynamic Programming

**Step 1: Build the DP Table**

Create a 2D table `dp[i][t]` where:
- `i` = number of subjects considered (0 to n)
- `t` = time available (0 to totalTime)
- `dp[i][t]` = maximum marks using first `i` subjects within `t` hours

```
For each subject i (1 to n):
    For each time t (0 to totalTime):

        Option A - Skip subject i:
            dp[i][t] = dp[i-1][t]

        Option B - Include subject i (only if time[i] <= t):
            dp[i][t] = dp[i-1][t - time[i]] + marks[i]

        Take the maximum of Option A and Option B
```

**Step 2: Read the Answer**

`dp[n][totalTime]` gives the maximum marks achievable.

**Step 3: Traceback — Find Selected Subjects**

```
Start at dp[n][totalTime]
For i from n down to 1:
    If dp[i][t] != dp[i-1][t]:
        → Subject i was INCLUDED
        → Subtract its time: t = t - time[i]
    Else:
        → Subject i was SKIPPED
```

### DP Table Example (8 subjects, 10 hours)

```
        0   1   2   3   4   5   6   7   8   9  10
Base    0   0   0   0   0   0   0   0   0   0   0
Math    0   0   0  10  10  10  10  10  10  10  10
Physic  0   0   0  10  12  12  12  22  22  22  22
Chemis  0   0   7  10  12  17  19  22  22  29  29
Comput  0   0   7  10  12  17  19  22  25  29  32
Englis  0   5   7  12  15  17  22  24  27  30  34
Biolog  0   5   7  12  15  17  22  24  27  31  34
Econom  0   5   8  13  15  20  23  25  30  32  35
Histor  0   5   9  13  17  20  24  27  30  34  36
```

Answer: **36 marks** using 10 hours.

### Time and Space Complexity

| Metric | Value |
|---|---|
| Time Complexity | O(n × W) |
| Space Complexity | O(n × W) |

Where `n` = number of subjects, `W` = total study time.

---

## How to Compile and Run

### Requirements
- g++ compiler with C++17 support
- VS Code or any terminal

### Compile (all files together)

```bash
g++ -std=c++17 -Wall -o optimizer main.cpp subject.cpp optimizer.cpp
```

### Run

```bash
.\optimizer.exe        # Windows
./optimizer            # Linux / macOS
```

---

## Sample Input / Output

### Input

```
Select mode:
  [1] Use preset subjects (8 subjects)
  [2] Enter your own subjects
Choice: 1

Enter total available study time (in hours): 10
Show DP table step-by-step? (y/n): n
```

### Output

```
============================================================
               STUDY TIME OPTIMIZER - RESULTS
============================================================

  Total Study Time Available : 10 hours
  Total Subjects Considered  : 8

------------------------------------------------------------
  Maximum Marks Achievable   : 36
------------------------------------------------------------

  Selected Subjects (5):

  Physics             Time = 4   hrs   Marks = 12
  Chemistry           Time = 2   hrs   Marks = 7
  English             Time = 1   hrs   Marks = 5
  Economics           Time = 2   hrs   Marks = 8
  History             Time = 1   hrs   Marks = 4

------------------------------------------------------------
  Total Time Used  : 10 / 10 hours
  Total Marks      : 36
============================================================
```

### Custom Input Example

```
Select mode: 2
How many subjects? 3

Subject 1:
  Name       : Math
  Time (hrs) : 3
  Marks      : 10

Subject 2:
  Name       : Physics
  Time (hrs) : 4
  Marks      : 12

Subject 3:
  Name       : English
  Time (hrs) : 1
  Marks      : 5

Enter total available study time: 7

--- RESULTS ---
Maximum Marks Achievable : 22
Selected Subjects:
  Math     Time = 3  Marks = 10
  Physics  Time = 4  Marks = 12
Total Time Used : 7 / 7 hours
```

---

## Preset Subjects

| Subject | Time (hrs) | Marks |
|---|---|---|
| Mathematics | 3 | 10 |
| Physics | 4 | 12 |
| Chemistry | 2 | 7 |
| Computer Science | 5 | 15 |
| English | 1 | 5 |
| Biology | 3 | 9 |
| Economics | 2 | 8 |
| History | 1 | 4 |

---

## STL Usage

| Container | Used In | Purpose |
|---|---|---|
| `vector<Subject>` | main, optimizer | Store list of subjects |
| `vector<vector<int>>` | optimizer.cpp | 2D DP table |
| `string` | subject.h | Subject name |

---

## VS Code — Quick Compile Task

Create `.vscode/tasks.json`:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build Optimizer",
      "type": "shell",
      "command": "g++",
      "args": [
        "-std=c++17", "-Wall",
        "-o", "optimizer",
        "main.cpp", "subject.cpp", "optimizer.cpp"
      ],
      "group": { "kind": "build", "isDefault": true }
    }
  ]
}
```

Press **Ctrl+Shift+B** to build, then run `.\optimizer.exe` in the terminal.

---

## Why 0/1 Knapsack?

- **Greedy doesn't work** here — picking the highest marks-per-hour subject 
  first does not always give the optimal result.
- **DP guarantees** the globally optimal solution by considering every 
  possible combination without redundant recalculations.
- This makes it suitable for real exam planning where you need the 
  mathematically best schedule.
