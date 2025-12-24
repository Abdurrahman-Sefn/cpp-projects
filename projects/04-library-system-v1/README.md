# Library System V1

A console-based Library Management System designed for efficient book and user management, featuring optimized data structures for high-performance searching.

## 🔗 Quick Links
*   [System Controller](src/LibrarySystem.hpp)
*   [Book Model](src/Book.hpp)

## ✨ Features

### 📚 Book Management
*   **Add Books**: Register books with unique IDs, Names, and quantities.
*   **Prefix Search (Trie)**: Optimized **O(L)** lookup using a Trie data structure to find books by prefix (e.g., searching "Cpp" instantly finds "CppHowToProgram").
*   **Sorted Listings**: View the entire collection sorted by **ID** or **Name**.
*   **Borrower Tracking**: Query exactly which users have borrowed a specific book by name.

### 👤 User & Transaction Management
*   **User Registration**: Manage a registry of library members.
*   **Borrowing Logic**: Validates stock availability (must be > 0) before processing and automatically handles inventory decrements.
*   **Returning Logic**: Processes returns by updating user records and restoring book stock.

## 🖥️ Interactive Menu
The system provides a 10-option administrative interface:

1.  **Add Book**: Insert new titles into the system.
2.  **Search Books**: Find books using prefix auto-completion (**Instant O(L) lookup via Trie**).
3.  **Print Who Borrowed**: List all users currently holding a specific book.
4.  **Print Library (ID)**: List all books sorted by their unique ID.
5.  **Print Library (Name)**: List all books alphabetically.
6.  **Add User**: Register new members.
7.  **User Borrow**: Process a new borrowing transaction.
8.  **User Return**: Process a book return.
9.  **Print Users**: List all registered members.
10. **Exit**: Shut down the system.

## 🚀 Usage

1.  **Build the project** from the root directory.
2.  **Run the executable:**
    ```bash
    ./bin/library_system_v1
    ```

## 🔧 Target-Specific Build
```bash
cmake --build . --target library_system_v1
```
