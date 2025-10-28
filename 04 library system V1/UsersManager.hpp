/**
 * @file UsersManager.hpp
 * @brief Manages the collection of users in the library system.
 */

#pragma once
#include "Dictionary.hpp"
#include "User.hpp"
#include "Book.hpp"
#include <input_utils.hpp>

/**
 * @class UsersManager
 * @brief Handles the creation, storage, retrieval, and management of User objects.
 * 
 * This class provides functionalities to add new users, print user lists,
 * and facilitate user-book interactions like borrowing and returning.
 */
class UsersManager{
    std::map<int, User*> ids_dictionary; /**< Maps user IDs to User objects for quick lookup. */
    Dictionary <User> names_dictionary; /**< Manages users by name, potentially for searching. */
public:
    /**
     * @brief Prompts the user to enter user details and returns a pair of User pointer and error message.
     * @return A pair containing a pointer to the entered User (or nullptr if invalid) and an error string.
     */
    std::pair<const User*, std::string> enter_user()const;

    /**
     * @brief Adds a new user to the system based on user input.
     * @return True if the user was successfully added, false otherwise.
     */
    bool add_user();

    /**
     * @brief Records that a user has borrowed a book.
     * @param usr A pointer to the User who borrowed the book.
     * @param book A pointer to the Book that was borrowed.
     */
    void user_borrow_book(User *usr, Book *book);

    /**
     * @brief Records that a user has returned a book.
     * @param usr A pointer to the User who returned the book.
     * @param book A pointer to the Book that was returned.
     * @return True if the book was successfully returned, false otherwise.
     */
    bool user_return_book(User *usr, Book *book);

    /**
     * @brief Prints a list of all registered users.
     */
    void print_users()const;

    /**
     * @brief Destructor for UsersManager, responsible for cleaning up dynamically allocated User objects.
     */
    ~UsersManager();
};