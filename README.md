# AI-Based Urine Test Record Management System

**Use Case ID:** KJS-HC-03

## 1. Project Overview
This project is a C-based academic simulation of a urine test record management system. It demonstrates how Data Structures can be used to store, search, sort and process patient test records.

The system uses sample data for demonstration purposes.

## 2. Functionalities Implemented
- Store patient test records.
- Search patient records using Patient ID.
- Sort patient records according to test time.
- Search records using Binary Search.
- Add and process records using a Circular Queue.

## 3. Data Structures Used

### Hash Table
- Used for searching patient records using Patient ID.
- Uses a hash function and Linear Probing for collision handling.
- Average search complexity: O(1).

### Sorted Array
- Uses Insertion Sort to arrange records by test time.
- Uses Binary Search to find records by time.
- Insertion Sort: O(n²) worst case.
- Binary Search: O(log n).

### Circular Queue
- Uses FIFO (First In, First Out) to process patient records.
- Supports Enqueue, Dequeue and Display operations.
- Enqueue and Dequeue: O(1).

## 4. Technologies Used
- C Programming
- Code::Blocks IDE
- GitHub
