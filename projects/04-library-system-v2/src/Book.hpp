/**
 * @file Book.hpp
 * @brief Defines the Book class and related enumerations for managing book information in Library
 * System V2.
 */

#pragma once
#include <iomanip>
#include <iostream>
#include <unordered_map>

#include "Helper.hpp"
class User;

/**
 * @enum AddBookResult
 * @brief Enumerates possible outcomes when attempting to add a new book to the system.
 */
enum class AddBookResult {
    SUCCESS,                /**< Book was added successfully. */
    ID_IS_EXISTED_BEFORE,   /**< A book with the same ID already exists. */
    NAME_IS_EXISTED_BEFORE, /**< A book with the same name already exists. */
    INVALID_QUANTITY,       /**< The specified quantity for the book is invalid. */
};

/**
 * @class Book
 * @brief Represents a book in Library System V2, managing its details, quantity, and borrowing
 * status.
 *
 * This class stores information about a book, including its ID, name, total quantity,
 * and the number of copies currently borrowed. It also provides methods for serialization
 * and checking availability.
 */
class Book {
    friend class BooksManager;
    static constexpr int BOOK_NAME_WIDTH = 40; /**< Width for displaying book name. */
    static constexpr int ID_WIDTH = 10;        /**< Width for displaying book ID. */
    static constexpr int QTY_WIDTH = 15;       /**< Width for displaying book quantity. */
    static constexpr int BORROWED_WIDTH = 15;  /**< Width for displaying borrowed count. */
    static const char DELIM = '|'; /**< Delimiter used for serializing book data to string. */
    int id;                        /**< Unique identifier for the book. */
    std::string name;              /**< Name or title of the book. */
    std::string formattedName;     /**< Formatted name of the book for display/search. */
    int quantity;                  /**< Total number of copies of the book available. */
    int borrowed = 0;              /**< Number of copies currently borrowed. */

    /**
     * @brief Constructor for the Book class.
     * @param id The unique ID of the book.
     * @param name The name or title of the book.
     * @param quantity The total number of copies of the book.
     */
    Book(int id, std::string name, int quantity);

    /**
     * @brief Constructs a Book object from a serialized string.
     * @param book_str The string representation of a book.
     */
    Book(const std::string &book_str);

    /**
     * @brief Converts the Book object into a string representation for persistence.
     * @return A string representing the book's data.
     */
    std::string toString() const;

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
     * @brief Gets the name of the book.
     * @return The name of the book.
     */
    std::string getName() const;

    /**
     * @brief Gets the ID of the book.
     * @return The ID of the book.
     */
    int getId() const;

    /**
     * @brief Checks if there are available copies of the book.
     * @return True if at least one copy is available, false otherwise.
     */
    bool isAvailable() const;

    /**
     * @brief Gets the formatted name of the book.
     * @return The formatted name of the book.
     */
    const std::string &getNameFormatted() const;
};
