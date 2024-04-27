# Data Structures and Algorithms Repository

This repository contains implementations of various data structures and algorithms in **x86 Linux Assembly and C and C++**. 

It is organized into two versions 
**Version 01**: This version was created in 2022 which contains the Data Structures and Algorithm in **C and C++**
**Version 02**: The newer version which contains codes in **X86 Linux Assembly, C and C++**. All codes have an updated format and have descriptions for each class & function.

## Version 01: C and C++ Data Structures

### Data Structures

1. **Doubly Circular Linked List**
   - Description: Implementation of a doubly circular linked list.

2. **Stack**
   - Description: Implementation of a stack data structure.

3. **Queue**
   - Description: Implementation of a queue data structure.

4. **Binary Search Tree**
   - Description: Implementation of a binary search tree.

5. **Graph**
   - Description: Implementation of a graph data structure.

### Sorting Algorithms

1. **Insertion Sort**
   - Description: Implementation of the insertion sort algorithm.

2. **Merge Sort**
   - Description: Implementation of the merge sort algorithm.

3. **Heap Sort**
   - Description: Implementation of the heap sort algorithm.

4. **Quick Sort**
   - Description: Implementation of the quick sort algorithm.

5. **Counting Sort**
   - Description: Implementation of the counting sort algorithm.

## Version 02: Assembly, C and C++ Data Structures

### Assembly

1. **Doubly Circular Linked List**
   - Description: Implementation of a doubly circular linked list in assembly language.

2. **Stack**
   - Description: Implementation of a stack data structure in assembly language.

3. **Queue**
   - Description: Implementation of a queue data structure in assembly language.

### C

1. **Doubly Circular Linked List**
   - Description: Implementation of a doubly circular linked list in C.

2. **Stack**
   - Description: Implementation of a stack data structure in C.

3. **Queue**
   - Description: Implementation of a queue data structure in C.

### C++

1. **Doubly Circular Linked List**
   - Description: Implementation of a doubly circular linked list in C++.

2. **Stack**
   - Description: Implementation of a stack data structure in C++.

3. **Queue**
   - Description: Implementation of a queue data structure in C++.

4. **Binary Search Tree**
   - Description: Implementation of a binary search tree in C++.

## How to Use

### For x86 Linux Assembly:

Each assembly directory contains assembly source files and a driver file. You can assemble and run the programs using GNU Assembler (as) and GNU Linker (ld).

To assemble and run assembly programs:
```bash
as -o output_file.o source_file.s
ld -o output_file -lc -dynamic-linker /lib/ld-linux.so.2 output_file.o driver.o -e entry_point_function
./output_file
```

### For C:

Each C directory contains C source files and a driver file. You can compile and run the programs using GCC (GNU Compiler Collection).
To compile and run C programs:

```bash
gcc -o output_file source_file.c
./output_file
```

### For C++:

Each C++ directory contains C++ source files and a driver file. You can compile and run the programs using G++ (GNU Compiler Collection).

To compile and run C++ programs:
```bash
g++ -o output_file source_file.cpp
./output_file
```
