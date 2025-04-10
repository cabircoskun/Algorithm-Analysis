# C Code Variable Analyzer with Double Hashing

This project analyzes a C code file provided by the user and detects variable declarations and usages. It uses a **double hashing** technique to store declared variables and checks for improper or undeclared usage.

## Problem Solution Overview

- The program starts by prompting the user to provide a `.txt` file containing C code.
- The file is read **line by line**, and each line is processed individually.

### Step-by-Step Process

1. **Declaration Detection**:  
   Each line is checked to see if it contains a variable declaration. If a declaration is found, the variable's **type** and **name** are extracted.

2. **Usage Detection**:  
   For lines that do **not** contain a declaration, the program checks for any **variable usage**. If usage is detected, the variable names are stored in a separate array.

3. **Hash Table Creation**:  
   Based on the number of declared variables, a suitable size for the hash table is determined.

4. **Double Hashing Insertion**:  
   All declared variable names and their types are inserted into the hash table using **double hashing**, with two hash functions `hash1` and `hash2`.

   - If a variable with the **same name** is declared more than once, an **error** is raised.

5. **Validation of Usage**:  
   After building the hash table, the program checks all used variables.  
   If a variable is used without being declared (i.e., not found in the hash table), an **error** is reported.

6. **Debug Mode Option**:  
   At the start of the program, the user is asked whether to enable **debug mode**.  
   If enabled, the program provides detailed outputs for each processing step.

## Features

- Detects variable declarations and usages in C code
- Uses a hash table with **double hashing** for efficient lookup
- Reports errors for:
  - Duplicate declarations
  - Undeclared variable usage
- Optional **debug mode** for step-by-step diagnostics
