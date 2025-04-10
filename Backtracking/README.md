# N-Queens Problem Solver

This project solves the **N-Queens problem** using multiple recursive algorithms.  
It allows the user to select the number of queens and the algorithm to be used for solving.

## 🧠 Problem Overview

The **N-Queens Problem** consists of placing `n` queens on an `n x n` chessboard such that no two queens threaten each other. This means no two queens can be in the same row, column, or diagonal.

## 📌 Solution Workflow

1. The user is prompted to enter the number of queens (`n`).
2. The user selects which algorithm to use for solving the problem.
3. All available algorithms are implemented **recursively**.

---

## 🔍 Algorithms

### 1. Brute Force

- Tries **every possible configuration** of placing queens.
- Ensures a correct solution but is the **slowest** method due to its exhaustive nature.

### 2. Optimized_1

- Places the i-th queen starting from the i-th **row**, attempting all positions in that row.
- Guarantees **exactly one queen per row**, reducing the solution space.

### 3. Optimized_2

- Inherits the row condition from `Optimized_1`.
- Adds a **column check** using the `checkColumn` function to prevent column conflicts.
- Further reduces the number of invalid placements.

### 4. Backtracking

- The most efficient and intelligent algorithm in the set.
- For each attempted placement:
  - Checks column validity with `checkColumn`
  - Checks diagonal validity with `checkDiagonal`
- Uses **pruning** to eliminate invalid branches early, significantly improving performance.

---

## ✅ Features

- Multiple algorithms to compare performance and effectiveness
- User input for number of queens and algorithm choice
- Modular and recursive implementation
- Debug-friendly structure
