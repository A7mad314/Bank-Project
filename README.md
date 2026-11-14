# Bank Management System (CLI)

A comprehensive console-based application built entirely in C++ to manage bank clients, system users, and financial transactions. This project was developed to build a deep, ground-up understanding of core programming logic, memory management, and data persistence without relying on external libraries or frameworks.

## System Features

### 1. Robust Authentication & Security
- **Login Tracking:** The system monitors login attempts. If a user enters incorrect credentials 5 consecutive times, the system triggers a permanent lock state to prevent brute-force attacks.
- **System Safeguards:** Built-in logic prevents critical administrative errors, such as users deleting their own active session accounts or standard users modifying/deleting Admin profiles.

### 2. Advanced Role-Based Access Control (RBAC)
- **Bitwise Permissions:** Instead of standard boolean flags, the system utilizes Bitwise Operations (| , &) to assign and verify precise user permissions. System admins can grant specific access to individual modules (e.g., viewing clients, adding clients, processing transactions, or managing other users) highly efficiently.

### 3. Custom File-Based Database (CRUD)
- **Data Persistence:** All client records and user credentials are saved in flat text files (.txt).
- **Data Parsing:** Developed a custom string parser that converts struct records into a single string line using a unique delimiter (#//#) before saving, and reverses the process (Splitting) when loading data back into the system's memory.

### 4. Client & Transaction Management
- **Full Client Management:** Functionality to add, update, delete, search, and list clients.
- **Financial Logic:** A dedicated transactions menu for deposits and withdrawals, including validation checks to ensure users cannot withdraw more than their available account balance.

## Methodologies & Core Concepts Used
- **Procedural & Modular Programming:** The codebase is heavily modular, breaking down complex operations into small, reusable, and single-purpose functions.
- **Memory & Data Structures:** Utilizing C++ structs to group related data, and std::vector for dynamic array management to handle data in memory during runtime.
- **String Manipulation:** Extensive use of standard string libraries and custom algorithms to slice, find, and manipulate data streams.

## Developer's Note: Evolution & Hindsight
This project represents Version 1 of my logic-building phase. Looking back with more experience, I am well aware that there are much easier, safer, and more modern ways to implement many of these features today. 

For instance:
- Databases (SQL/NoSQL) are far superior and more efficient than parsing .txt files for data persistence.
- Password Hashing is a mandatory security standard compared to storing plaintext passwords.
- Object-Oriented Programming (OOP) would provide better encapsulation and structure than purely procedural structs and global passing.
- Pass-by-Reference & Pointers could be utilized more effectively to optimize memory usage instead of passing by value in certain functions.

However, building this system the hard way from absolute scratch was an intentional and invaluable experience. It forced me to manually solve the exact problems that modern databases and frameworks abstract away, providing me with a rock-solid foundation in problem-solving and software logic.
