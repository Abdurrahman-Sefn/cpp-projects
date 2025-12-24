/**
 * @file BooksManager.hpp
 * @brief Manages the collection of books in Library System V2, including persistence.
 */

#pragma once
#include <Sefn.hpp>

#include "Book.hpp"
#include "BorrowOperation.hpp"
#include "User.hpp"

/**
 * @class BooksManager
 * @brief Handles the creation, storage, retrieval, and management of Book objects with data
 * persistence.
 *
 * This class extends the functionalities of V1 by adding data loading and saving mechanisms
 * to and from a file (`Books.txt`). It manages books by ID and name, and supports operations
 * like adding, searching, and printing book lists.
 */
class BooksManager {
    std::map<int, Book *> idsDictionary; /**< Maps book IDs to Book objects for quick lookup. */
    Sefn::Trie<Book> namesDictionary; /**< Manages books by name, facilitating prefix searches. */

    /**
     * @brief Loads book data from the `Books.txt` file into memory.
     */
    void loadDatabase();

    /**
     * @brief Saves current book data from memory to the `Books.txt` file.
     */
    void updateDatabase() const;

    /**
     * @brief Adds a book object to both internal dictionaries.
     * @param book A pointer to the Book object to be added.
     */
    void pushBook(Book *book);

    /**
     * @brief Clears all book data from memory.
     */
    void clear();

   public:
    /**
     * @brief Constructor for BooksManager. Initializes by loading data from the database.
     */
    BooksManager();

    /**
     * @brief Deleted copy constructor to prevent unintended copying.
     */
    BooksManager(const BooksManager &) = delete;

    /**
     * @brief Deleted assignment operator to prevent unintended assignment.
     */
    BooksManager &operator=(const BooksManager &) = delete;

    /**
     * @brief Prompts the user to enter book details and returns a pair of Book pointer and error
     * message.
     * @return A pair containing a pointer to the entered Book (or nullptr if invalid) and an error
     * string.
     */
    std::pair<Book *, std::string> enterBook();

    /**
     * @brief Adds a new book to the library.
     * @param bookNameFormatted The formatted name of the book to be added.
     * @return An AddBookResult enum indicating the success or type of failure.
     */
    AddBookResult addBook(std::string &bookNameFormatted);

    /**
     * @brief Searches for books by a given prefix in their names and prints the results.
     */
    void searchBooksByPrefix();

    /**
     * @brief Increments the borrowed count for a specific book.
     * @param book A pointer to the Book whose borrowed count is to be incremented.
     */
    void incrementBook(Book *book);

    /**
     * @brief Decrements the borrowed count for a specific book.
     * @param book A pointer to the Book whose borrowed count is to be decremented.
     */
    void decrementBook(Book *book);

    /**
     * @brief Prints a list of books that are currently borrowed, based on provided borrow
     * operations.
     * @param operations A vector of BorrowOperation pointers representing current borrowings.
     */
    void printBorrowedBooks(const std::vector<BorrowOperation *> &operations) const;

    /**
     * @brief Prints all books in the library, sorted by ID.
     */
    void printLibraryById() const;

    /**
     * @brief Prints all books in the library, sorted by name.
     */
    void printLibraryByName() const;

    /**
     * @brief Retrieves a book by its ID.
     * @param id The ID of the book to retrieve.
     * @return A const pointer to the Book object if found, nullptr otherwise.
     */
    const Book *getBookById(int id) const;

    /**
     * @brief Destructor for BooksManager. Saves data to the database and cleans up dynamically
     * allocated Book objects.
     */
    ~BooksManager();
};
