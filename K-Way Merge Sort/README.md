# K-Way Merge Sort Algorithm

This project implements a variation of the classical merge sort algorithm, called **K-Way Merge Sort**. The algorithm is executed for various `k` values ranging from 2 to 10 to observe the sorting behavior.

## Problem Solution Overview

- Initially, a loop is created to generate random arrays with unique values, depending on the value of `N`.
- Each generated array is then shuffled using the `shuffle` function to ensure randomness.
- For each array, another loop iterates over different values of `k` (from 2 to 10) and sends the array to the custom `merge_sort` function.

## K-Way Merge Sort Implementation

- The `merge_sort` function is implemented recursively.
- In each recursive step, the array is divided into `k` sub-arrays.
- The base case for recursion is when the size of the array becomes smaller than `k`.
- At this point, the recursive calls stop, and each sub-array is sent to the `merge` function.

## Merge Function Details

- Inside the `merge` function, each sub-array is first sorted using the **insertion sort** algorithm.
- Then, the sorted sub-arrays are merged together to form a single sorted array.
- This process is repeated until the entire array is fully sorted.

## Features

- Random generation of unique arrays
- Support for varying `k` values (2 through 10)
- Recursive k-way division and sorting
- Combination of insertion sort and merge strategy
