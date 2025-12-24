#include "BooksManager.hpp"

std::pair<const Book *, std::string> BooksManager::enterBook() const {
    std::string bookName;
    std::cout << "Enter book name: ";
    getline(std::cin, bookName);
    return {static_cast<const Book *>(booksByNameTrie.wordExists(bookName)), bookName};
}
bool BooksManager::addBook() {
    auto [existingBook, bookName] = enterBook();
    if (existingBook) {
        std::cout << "This name is already existed!\n";
        return false;
    }
    int id = Sefn::readValidatedInput<int>("Enter book id: ");
    if (booksByIdMap.find(id) != booksByIdMap.end()) {
        std::cout << "This id is already existed!\n";
        return false;
    }
    int quantity = Sefn::readValidatedInput<int>("Enter quantity: ");
    if (quantity <= 0) {
        std::cout << "Quantity must be greater than zero\n";
        return false;
    }
    Book *book = new Book(id, bookName, quantity);
    booksByIdMap[book->id] = book;
    booksByNameTrie.insert(book, book->getName());
    return true;
}
void BooksManager::searchBooksByPrefix() {
    std::cout << "Enter book prefix: ";
    std::string prefix;
    getline(std::cin, prefix);
    auto res = booksByNameTrie.autoComplete(prefix);
    if (res.empty()) {
        std::cout << "There is no book with such prefix.\n";
        return;
    }
    Book::printHeader(1);
    for (auto &book : res) {
        book->print(1);
    }
}
void BooksManager::printWhoBorrowedBookByName() const {
    auto [bookPtr, bookName] = enterBook();
    if (!bookPtr) {
        std::cout << "\tThere is no book with such name.\n";
    } else {
        bookPtr->printDetailed(1);
    }
}
void BooksManager::printLibraryById() const {
    if (booksByIdMap.empty()) return;
    std::cout << "Library sorted by ids: \n";
    Book::printHeader(1);
    for (auto &[id, book] : booksByIdMap) {
        book->print(1);
    }
}
void BooksManager::printLibraryByName() const {
    if (booksByIdMap.empty()) return;
    std::cout << "Library sorted by ids: \n";
    Book::printHeader(1);
    booksByNameTrie.traverse([](Book *book) { book->print(1); });
}
bool BooksManager::userBorrowBook(User *usr, Book *book) {
    return book->borrow(usr);
}
bool BooksManager::userReturnBook(User *usr, Book *book) {
    return book->returnCopy(usr);
}
BooksManager::~BooksManager() {
    for (auto &[id, book] : booksByIdMap) {
        delete book;
    }
}
