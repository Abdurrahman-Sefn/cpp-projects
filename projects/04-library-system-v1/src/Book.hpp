/**
 * @file Book.hpp
 * @brief Defines the Book class for managing book information in the library system.
 */

#pragma once
#include <iomanip>
#include <iostream>
#include <unordered_map>

#include "Helper.hpp"

class User;

/**
 * @class Book
 * @brief Represents a book in the library system, managing its details, quantity, and borrowing
 * status.
 *
 * This class stores information about a book, including its ID, name, total quantity,
 * and the number of copies currently borrowed. It also tracks which users have borrowed
 * specific copies of the book.
 */
class Book {
    friend class BooksManager;
    static constexpr int NAME_WIDTH = 40;     /**< Width for displaying book name. */
    static constexpr int ID_WIDTH = 10;       /**< Width for displaying book ID. */
    static constexpr int QTY_WIDTH = 15;      /**< Width for displaying book quantity. */
    static constexpr int BORROWED_WIDTH = 15; /**< Width for displaying borrowed count. */
    int id;                                   /**< Unique identifier for the book. */
    std::string name;                         /**< Name or title of the book. */
    int quantity;                             /**< Total number of copies of the book available. */
    int borrowed = 0;                         /**< Number of copies currently borrowed. */
    std::unordered_map<User*, int> borrowers; /**< Map of users who borrowed the book and the number
                                                 of copies they borrowed. */

    /**
     * @brief Attempts to borrow a copy of the book for a given user.
     * @param user A pointer to the User attempting to borrow the book.
     * @return True if the book was successfully borrowed, false otherwise.
     */
    bool borrow(User* user);

    /**
     * @brief Attempts to return a copy of the book from a given user.
     * @param user A pointer to the User attempting to return the book.
     * @return True if the book was successfully returned, false otherwise.
     */
    bool returnCopy(User* user);

    /**
     * @brief Constructor for the Book class.
     * @param id The unique ID of the book.
     * @param name The name or title of the book.
     * @param quantity The total number of copies of the book.
     */
    Book(int id, std::string name, int quantity);

   public:
    /**
     * @brief Prints the header for book information.
     * @param tabs The number of tabs to indent the output.
     */
    static void printHeader(int tabs = 0);

    /**
     * @brief Prints a summary of the book's information.
     * @param tabs The number of tabs to indent the output.
     */
    void print(int tabs = 0) const;

    /**
     * @brief Prints detailed information about the book, including its borrowers.
     * @param tabs The number of tabs to indent the output.
     */
    void printDetailed(int tabs = 0) const;

    /**
     * @brief Gets the name of the book.
     * @return The name of the book.
     */
    std::string getName() const;
};
