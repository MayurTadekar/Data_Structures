# Data Structures and Algorithms Repository

This repository contains implementations of various data structures and algorithms in **x86 Linux Assembly and C and C++**. 

It is organized into two versions:

**Version 01**: This version was created in 2022 which contains the Data Structures and Algorithm in **C and C++**

**Version 02**: The newer version which contains codes in **X86 Linux Assembly, C and C++**. All codes have an updated format and have descriptions for each class & function.

## Version 01: C and C++ Data Structures

### Data Structures

1. [**Doubly Circular Linked List**](Version_01/01_C_Data_Structures_And_Algorithm/01_Data_Structures/02_Doubly_Circular_Linked_List)
   - Implementation: `dcll.c`, `dcll.h`, `main.c`
   - Description: Implementation of a doubly circular linked list.

2. [**Stack**](Version_01/01_C_Data_Structures_And_Algorithm/01_Data_Structures/03_Stack)
   - Implementation: `stack.c`, `stack.h`, `main.c`
   - Description: Implementation of a stack data structure.

3. [**Queue**](Version_01/01_C_Data_Structures_And_Algorithm/01_Data_Structures/04_Queue)
   - Implementation: `queue.c`, `queue.h`, `main.c`
   - Description: Implementation of a queue data structure.

4. [**Binary Search Tree**](Version_01/01_C_Data_Structures_And_Algorithm/01_Data_Structures/04_Binary_Search_Tree)
   - Implementation: `tree.c`, `tree.h`, `main.c`
   - Description: Implementation of a binary search tree.

5. [**Graph**](Version_01/01_C_Data_Structures_And_Algorithm/01_Data_Structures/05_Graph)
   - Implementation: `graph.c`, `graph.h`, `main.c`
   - Description: Implementation of a graph data structure.

### Sorting Algorithms

1. [**Insertion Sort**](Version_01/01_C_Data_Structures_And_Algorithm/02_Sorting/01_Insertion_Sort)
   - Implementation: `insert_sort.c`, `insert_sort.h`, `main.c`
   - Description: Implementation of the insertion sort algorithm.

2. [**Merge Sort**](Version_01/01_C_Data_Structures_And_Algorithm/02_Sorting/02_Merge_Sort)
   - Implementation: `merge_sort.c`, `merge_sort.h`, `main.c`
   - Description: Implementation of the merge sort algorithm.

3. [**Heap Sort**](Version_01/01_C_Data_Structures_And_Algorithm/02_Sorting/03_Heap_Sort)
   - Implementation: `heap_sort.c`, `heap_sort.h`, `main.c`
   - Description: Implementation of the heap sort algorithm.

4. [**Quick Sort**](Version_01/01_C_Data_Structures_And_Algorithm/02_Sorting/04_Quick_Sort)
   - Implementation: `quick_sort.c`, `quick_sort.h`, `main.c`
   - Description: Implementation of the quick sort algorithm.

5. [**Counting Sort**](Version_01/01_C_Data_Structures_And_Algorithm/02_Sorting/05_Counting_Sort)
   - Implementation: `counting_sort.c`, `counting_sort.h`, `main.c`
   - Description: Implementation of the counting sort algorithm.

## Version 02: x86 Linux Assembly, C, and C++ Data Structures

### x86 Linux Assembly

1. [**Doubly Circular Linked List**](Version_02/00_Assembly/01_DCLL)
   - Implementation: `dcll.s`, `driver.s`
   - Description: Implementation of a doubly circular linked list in assembly language.

2. [**Stack**](Version_02/00_Assembly/02_Stack)
   - Implementation: `stack.s`, `driver.s`
   - Description: Implementation of a stack data structure in assembly language.

3. [**Queue**](Version_02/00_Assembly/03_Queue)
   - Implementation: `queue.s`, `driver.s`
   - Description: Implementation of a queue data structure in assembly language.

### C

1. [**Doubly Circular Linked List**](Version_02/01_C/01_DoublyCircularLinkedList)
   - Implementation: `dcll.c`, `dcll.h`, `driver.c`
   - Description: Implementation of a doubly circular linked list in C.

2. [**Stack**](Version_02/01_C/02_Stack)
   - Implementation: `stack.c`, `stack.h`, `driver.c`
   - Description: Implementation of a stack data structure in C.

3. [**Queue**](Version_02/01_C/03_Queue)
   - Implementation: `queue.c`, `queue.h`, `driver.c`
   - Description: Implementation of a queue data structure in C.

### C++

1. [**Doubly Circular Linked List**](Version_02/02_CPP/01_DoublyCircularLinkedList)
   - Implementation: `dcll.hpp`, `Driver.cpp`
   - Description: Implementation of a doubly circular linked list in C++.

2. [**Stack**](Version_02/02_CPP/02_Stack)
   - Implementation: `stack.hpp`, `driver.cpp`
   - Description: Implementation of a stack data structure in C++.

3. [**Queue**](Version_02/02_CPP/03_Queue)
   - Implementation: `queue.hpp`, `Driver.cpp`
   - Description: Implementation of a queue data structure in C++.

4. [**Binary Search Tree**](Version_02/02_CPP/04_Binary_Search_Tree)
   - Implementation: `bst.hpp`, `binarytree.hpp`, `tree.hpp`, `DataNotFoundException.hpp`, `TreeEmptyException.hpp`, `Driver.cpp`
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
