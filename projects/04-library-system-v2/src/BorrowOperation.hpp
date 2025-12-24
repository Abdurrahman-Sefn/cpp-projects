/**
 * @file BorrowOperation.hpp
 * @brief Defines the BorrowOperation class and related enumerations for managing book borrowing in
 * Library System V2.
 */

#pragma once
#include "Book.hpp"
#include "User.hpp"

/**
 * @enum BorrowResult
 * @brief Enumerates possible outcomes when attempting a book borrowing operation.
 */
enum class BorrowResult {
    SUCCESS,                         /**< The book was successfully borrowed. */
    BOOK_NOT_AVAILABLE,              /**< No copies of the book are currently available. */
    USER_REACHED_MAX_BORROWED_BOOKS, /**< The user has reached their limit for borrowed books. */
    USER_REACHED_MAX_REPETITIONS /**< The user has reached their limit for borrowing the same book.
                                  */
};

/**
 * @class BorrowOperation
 * @brief Represents a single instance of a user borrowing a book.
 *
 * This class stores immutable references to the User and Book involved in a borrowing event.
 * It also provides methods for serialization and deserialization for persistence.
 */
class BorrowOperation {
   public:
    friend class BorrowsManager;
    const User *const user; /**< Pointer to the User who performed the borrowing operation. */
    const Book *const book; /**< Pointer to the Book that was borrowed. */
   private:
    /**
     * @brief Deserializes a string representation of a borrow operation into user and book IDs.
     * @param borrowStr The string to deserialize.
     * @param userId Output parameter for the user's ID.
     * @param bookId Output parameter for the book's ID.
     */
    static void deserialize(const std::string &borrowStr, int &userId, int &bookId);
    const static char DELIM =
        '|'; /**< Delimiter used for serializing borrow operation data to string. */

    /**
     * @brief Constructor for BorrowOperation.
     * @param user A pointer to the User involved in the operation.
     * @param book A pointer to the Book involved in the operation.
     */
    BorrowOperation(const User *user, const Book *book);

    /**
     * @brief Converts the BorrowOperation object into a string representation for persistence.
     * @return A string representing the borrow operation's data.
     */
    std::string toString() const;
};
