/**
 * @file User.hpp
 * @brief Defines the User class for managing user information in the library system.
 */

#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Helper.hpp"
#include "Book.hpp"

/**
 * @class User
 * @brief Represents a user in the library system, managing their details and borrowed books.
 * 
 * This class stores information about a user, including their ID, name, and a list of
 * books they have currently borrowed.
 */
class User{
    static constexpr int USER_NAME_WIDTH = 40; /**< Width for displaying user name. */
    static constexpr int USER_ID_WIDTH = 10; /**< Width for displaying user ID. */
    int id; /**< Unique identifier for the user. */
    std::string name; /**< Name of the user. */
    std::unordered_map<Book*, int>borrowed_books; /**< Map of books borrowed by the user and the number of copies. */

    /**
     * @brief Records that the user has borrowed a specific book.
     * @param book A pointer to the Book that was borrowed.
     */
    void borrow(Book* book);

    /**
     * @brief Records that the user has returned a specific book.
     * @param book A pointer to the Book that was returned.
     * @return True if the book was successfully returned, false otherwise.
     */
    bool return_(Book* book);

    /**
     * @brief Constructor for the User class.
     * @param id The unique ID of the user.
     * @param name The name of the user.
     */
    User(int id, std::string name);

    friend class UsersManager;
public:
    /**
     * @brief Gets the name of the user.
     * @return The name of the user.
     */
    std::string get_name() const;

    /**
     * @brief Prints a list of books currently borrowed by the user.
     * @param tabs The number of tabs to indent the output.
     */
    void print_borrowed_books(int tabs = 0)const;

    /**
     * @brief Prints the header for user information.
     * @param tabs The number of tabs to indent the output.
     */
    static void print_header(int tabs = 0);

    /**
     * @brief Prints a summary of the user's information.
     * @param tabs The number of tabs to indent the output.
     */
    void print(int tabs = 0) const;
};
