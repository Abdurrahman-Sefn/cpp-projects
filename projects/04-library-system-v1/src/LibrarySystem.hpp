/**
 * @file LibrarySystem.hpp
 * @brief Defines the main LibrarySystem class that orchestrates library operations.
 */

#pragma once
#include "BooksManager.hpp"
#include "UsersManager.hpp"

/**
 * @class LibrarySystem
 * @brief The core class for the library management system.
 *
 * This class integrates UsersManager and BooksManager to provide a complete
 * library system functionality, including user and book management, borrowing,
 * and returning books.
 */
class LibrarySystem {
    UsersManager usersManager; /**< Manages all user-related operations. */
    BooksManager booksManager; /**< Manages all book-related operations. */

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
     * @brief Loads initial data into the library system (e.g., from files).
     */
    void loadDatabase();

    /**
     * @brief Updates the persistent data storage with current library system state.
     */
    void updateDatabase();

   public:
    /**
     * @brief Runs the main loop of the library system, presenting the main menu to the user.
     */
    void run();
};
