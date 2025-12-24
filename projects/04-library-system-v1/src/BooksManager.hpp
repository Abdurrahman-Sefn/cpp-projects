/**
 * @file BooksManager.hpp
 * @brief Manages the collection of books in the library system.
 */

#pragma once
#include "Book.hpp"
#include "Sefn.hpp"
#include "User.hpp"

/**
 * @class BooksManager
 * @brief Handles the creation, storage, retrieval, and management of Book objects.
 *
 * This class provides functionalities to add new books, search for books, print book lists,
 * and manage the borrowing and returning of books by users.
 */
class BooksManager {
    std::map<int, Book *> booksByIdMap; /**< Maps book IDs to Book objects for quick lookup. */
    Sefn::Trie<Book>
        booksByNameTrie; /**< Manages books by name, potentially for prefix searches. */
   public:
    /**
     * @brief Prompts the user to enter book details and returns a pair of Book pointer and error
     * message.
     * @return A pair containing a pointer to the entered Book (or nullptr if invalid) and an error
     * string.
     */
    std::pair<const Book *, std::string> enterBook() const;

    /**
     * @brief Adds a new book to the library based on user input.
     * @return True if the book was successfully added, false otherwise.
     */
    bool addBook();

    /**
     * @brief Searches for books by a given prefix in their names and prints the results.
     */
    void searchBooksByPrefix();

    /**
     * @brief Prints a list of users who have borrowed a specific book, identified by its name.
     */
    void printWhoBorrowedBookByName() const;

    /**
     * @brief Prints all books in the library, sorted by ID.
     */
    void printLibraryById() const;

    /**
     * @brief Prints all books in the library, sorted by name.
     */
    void printLibraryByName() const;

    /**
     * @brief Handles a user borrowing a book.
     * @param usr A pointer to the User borrowing the book.
     * @param book A pointer to the Book being borrowed.
     * @return True if the book was successfully borrowed, false otherwise.
     */
    bool userBorrowBook(User *usr, Book *book);

    /**
     * @brief Handles a user returning a book.
     * @param usr A pointer to the User returning the book.
     * @param book A pointer to the Book being returned.
     * @return True if the book was successfully returned, false otherwise.
     */
    bool userReturnBook(User *usr, Book *book);

    /**
     * @brief Destructor for BooksManager, responsible for cleaning up dynamically allocated Book
     * objects.
     */
    ~BooksManager();
};
