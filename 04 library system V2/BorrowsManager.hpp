/**
 * @file BorrowsManager.hpp
 * @brief Manages all borrowing and returning operations in Library System V2.
 */

#pragma once
#include "User.hpp"
#include "Book.hpp"
#include "BorrowOperation.hpp"

class LibrarySystem;

/**
 * @class BorrowsManager
 * @brief Handles the logic for users borrowing and returning books, including limits and history tracking.
 * 
 * This class maintains records of all borrowing operations, linking users to the books they have borrowed.
 * It enforces borrowing limits and provides history for both users and books.
 */
class BorrowsManager
{
private:
    static const int MAX_BORROWS_PER_USER = 5; /**< Maximum number of books a single user can borrow. */
    static const int MAX_BORROWS_REPETITION = 1; /**< Maximum number of times a user can borrow the same book. */
    static const std::vector<BorrowOperation*> NA; /**< Placeholder for empty borrow history. */
    std::unordered_map<const User*, std::vector<BorrowOperation*>> borrows_by_user; /**< Maps users to their borrowing history. */
    std::unordered_map<const Book*, std::vector<BorrowOperation*>> borrows_by_book; /**< Maps books to their borrowing history. */

    /**
     * @brief Creates a new borrow link between a user and a book.
     * @param user A pointer to the User.
     * @param book A pointer to the Book.
     */
    void create_borrow_link(const User *user,const Book *book);

    /**
     * @brief Updates the persistent storage with the current borrowing operations.
     */
    void update_database();

    /**
     * @brief Deserializes a string representation of a borrow operation.
     * @param borrow_str The string to deserialize.
     * @param user_id Output parameter for the user's ID.
     * @param book_id Output parameter for the book's ID.
     */
    static void deserialize(const std::string &borrow_str, int &user_id, int &book_id);

    friend LibrarySystem;
public:
    /**
     * @brief Deleted copy constructor to prevent unintended copying.
     */
    BorrowsManager(const BorrowsManager&) = delete;

    /**
     * @brief Deleted assignment operator to prevent unintended assignment.
     */
    BorrowsManager &operator=(const BorrowsManager&) = delete;

    /**
     * @brief Default constructor for BorrowsManager.
     */
    BorrowsManager() = default;

    /**
     * @brief Handles the process of a user returning a book.
     * @param user A pointer to the User returning the book.
     * @param book A pointer to the Book being returned.
     * @return True if the book was successfully returned, false otherwise.
     */
    bool return_book(User* user, Book* book);

    /**
     * @brief Handles the process of a user borrowing a book.
     * @param user A pointer to the User borrowing the book.
     * @param book A pointer to the Book being borrowed.
     * @return A BorrowResult enum indicating the success or type of failure.
     */
    BorrowResult borrow_book(User* user, Book* book);

    /**
     * @brief Retrieves the borrowing history for a specific book.
     * @param book A pointer to the Book.
     * @return A constant reference to a vector of BorrowOperation pointers related to the book.
     */
    const std::vector<BorrowOperation*> &get_book_history(Book *book) const;

    /**
     * @brief Retrieves the borrowing history for a specific user.
     * @param user A pointer to the User.
     * @return A constant reference to a vector of BorrowOperation pointers related to the user.
     */
    const std::vector<BorrowOperation*> &get_user_history(User *user) const;

    /**
     * @brief Destructor for BorrowsManager. Cleans up dynamically allocated BorrowOperation objects.
     */
    ~BorrowsManager();
};