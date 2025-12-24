/**
 * @file LibrarySystem.hpp
 * @brief Defines the main LibrarySystem class that orchestrates library operations in V2.
 */

#pragma once
#include "BooksManager.hpp"
#include "BorrowsManager.hpp"
#include "UsersManager.hpp"

/**
 * @class LibrarySystem
 * @brief The core class for Library System V2, integrating user, book, and borrowing management.
 *
 * This class orchestrates the interactions between `UsersManager`, `BooksManager`, and
 * `BorrowsManager` to provide a comprehensive library system with features like user and book
 * management, borrowing, returning books, and data persistence.
 */
class LibrarySystem {
    UsersManager usersManager;     /**< Manages all user-related operations. */
    BooksManager booksManager;     /**< Manages all book-related operations. */
    BorrowsManager borrowsManager; /**< Manages all borrowing and returning operations. */

    /**
     * @brief Structure to hold the result of a verification process, typically for
     * borrowing/returning.
     */
    struct VerificationResult {
        bool success = false; /**< Indicates if the verification was successful. */
        User* user = nullptr; /**< Pointer to the User involved in the operation. */
        Book* book = nullptr; /**< Pointer to the Book involved in the operation. */
    };

    /**
     * @brief Verifies user and book existence for borrowing/returning operations.
     * @return A VerificationResult object containing the success status and pointers to the user
     * and book.
     */
    VerificationResult verify();

    /**
     * @brief Handles the process of a user borrowing a book.
     */
    void borrowBook();

    /**
     * @brief Handles the process of a user returning a book.
     */
    void returnBook();

    /**
     * @brief Prints a list of users who have borrowed a specific book, identified by its name.
     */
    void printWhoBorrowedBookByName();

    /**
     * @brief Prints a list of books currently borrowed by a specific user.
     */
    void printUserBorrowedBooks();

    /**
     * @brief Handles the process of adding a new user to the system.
     */
    void addUser();

    /**
     * @brief Handles the process of adding a new book to the system.
     */
    void addBook();

    /**
     * @brief Loads borrowing operations data from the database.
     */
    void loadBorrowsDatabase();

   public:
    /**
     * @brief Constructor for LibrarySystem. Initializes managers and loads data.
     */
    LibrarySystem();

    /**
     * @brief Runs the main loop of the library system, presenting the main menu to the user.
     */
    void run();
};
