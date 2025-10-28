# Library System V2

This is an enhanced version of the console-based library management system.

## Description

This program allows you to manage books, users, and borrowing operations in a library. It includes features such as adding books and users, borrowing and returning books, and persisting data to files.

## New Features in V2

This version of the library system includes several improvements over V1, most notably:

*   **Data Persistence:** The system now saves and loads data from the following files:
    *   `Books.txt`: Stores book information.
    *   `Users.txt`: Stores user information.
    *   `BorrowOperations.txt`: Stores information about borrowed books.
*   **Borrowing System:** A more robust system for managing borrowing operations.

## Building and Running

To build the project, you can use the following command:

```bash
g++ main.cpp LibrarySystem.cpp BooksManager.cpp UsersManager.cpp BorrowsManager.cpp Book.cpp User.cpp BorrowOperation.cpp Helper.cpp -o program.out
```

To run the project, execute the following command:

```bash
./program.out
```

## Usage

Upon running the program, you will be presented with a menu of options to manage the library. The system will load data from the `.txt` files on startup and save data to them on shutdown.
