# Library System V2

An enterprise-grade evolution of the Library System, featuring a **decoupled architecture**, strict business rules, and full data persistence.

## 🔗 Quick Links
*   [System Controller](src/LibrarySystem.hpp)
*   [Borrowing Manager](src/BorrowsManager.hpp)
*   [Borrowing Entity](src/BorrowOperation.hpp)
*   [Books Database](data/Books.txt)
*   [Users Database](data/Users.txt)
*   [Transactions DB](data/BorrowOperations.txt)

## 🏛️ Architectural Overhaul
Unlike V1, this version separates concerns by introducing a dedicated **Borrowing Layer**:
*   **`BorrowsManager`**: Centralizes all transaction logic, decoupling `User` and `Book` classes.
*   **`BorrowOperation`**: Represents the association class between a User and a Book, allowing for scalable tracking.

## ✨ Features
*   **Strict Business Rules**:
    *   **Max Limit**: Users cannot borrow more than **5 books** at once.
    *   **Repetition Limit**: Users cannot borrow the same book twice simultaneously.
*   **Full Data Persistence**:
    *   `Users.txt` & `Books.txt`: Entity storage.
    *   `BorrowOperations.txt`: Transactional storage (who has what).
*   **Advanced Reporting**:
    *   **User History (Option 4)**: View all books currently held by a specific user.
    *   **Book Tracking (Option 10)**: View all users currently holding a specific book.

## 🖥️ Interactive Menu
The expanded 12-option menu provides comprehensive control over the library's state:

1.  **Add Book**: Insert new titles into the system.
2.  **Search Books (Prefix)**: Find books using **Instant O(L) Trie lookups**.
3.  **Print Who Borrowed Book**: List all users currently holding a specific book.
4.  **Print Books Borrowed by User**: View the borrowing history/active books for a specific user.
5.  **Print Library (by ID)**: List all books sorted by their unique ID.
6.  **Print Library (by Name)**: List all books alphabetically.
7.  **Add User**: Register new members to the system.
8.  **User Borrow Book**: Process a new borrowing transaction (enforces business limits).
9.  **User Return Book**: Process a book return.
10. **Print Users (by Name)**: List all members alphabetically.
11. **Print Users (by ID)**: List all members by their unique ID.
12. **Exit**: Securely save all data to files and shut down.

## 🚀 Usage

1.  **Build the project**:
    ```bash
    cmake --build . --target library_system_v2
    ```
2.  **Run the executable:**
    ```bash
    ./bin/library_system_v2
    ```

## 🔧 Target-Specific Build
```bash
cmake --build . --target library_system_v2
```