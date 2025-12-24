#include "BooksManager.hpp"

#include <algorithm>
#include <fstream>

std::pair<Book *, std::string> BooksManager::enterBook() {
    std::string bookName;
    std::cout << "Enter book name: ";
    readAndTrim(std::cin, bookName);
    return {namesDictionary.wordExists(bookName), bookName};
}
void BooksManager::pushBook(Book *book) {
    idsDictionary[book->id] = book;
    namesDictionary.insert(book, book->getName());
}
void BooksManager::clear() {
    idsDictionary.clear();
    namesDictionary.clear();
}

AddBookResult BooksManager::addBook(std::string &bookNameFormatted) {
    auto [isExisted, bookName] = enterBook();
    if (isExisted) {
        return AddBookResult::NAME_IS_EXISTED_BEFORE;
    }
    int id = Sefn::readValidatedInput<int>("Enter book id: ");
    if (idsDictionary.find(id) != idsDictionary.end()) {
        return AddBookResult::ID_IS_EXISTED_BEFORE;
    }
    int quantity = Sefn::readValidatedInput<int>("Enter quantity: ");
    if (quantity <= 0) {
        return AddBookResult::INVALID_QUANTITY;
    }
    Book *book = new Book(id, bookName, quantity);
    pushBook(book);
    bookNameFormatted = book->getNameFormatted();
    return AddBookResult::SUCCESS;
}
void BooksManager::searchBooksByPrefix() {
    std::cout << "Enter book prefix: ";
    std::string prefix;
    readAndTrim(std::cin, prefix);
    auto res = namesDictionary.autoComplete(prefix);
    if (res.empty()) {
        std::cout << "\tThere is no book with such prefix.\n";
        return;
    }
    Book::printHeader(1);
    for (auto &book : res) {
        book->print(1);
    }
}

void BooksManager::printLibraryById() const {
    if (idsDictionary.empty()) return;
    std::cout << "\tBooks sorted by id: \n";
    Book::printHeader(2);
    for (auto &[id, book] : idsDictionary) {
        book->print(2);
    }
}
void BooksManager::printLibraryByName() const {
    if (idsDictionary.empty()) return;
    std::cout << "\tBooks sorted by name: \n";
    Book::printHeader(2);
    namesDictionary.traverse([](Book *book) { book->print(2); });
}

void BooksManager::incrementBook(Book *book) {
    book->borrowed--;
    if (book->borrowed < 0) {
        throw std::invalid_argument("Incompatible borrowing or returning!");
    }
}
void BooksManager::decrementBook(Book *book) {
    if (!book->isAvailable()) {
        throw std::invalid_argument("Incompatible borrowing or returning!");
    }
    book->borrowed++;
}

void BooksManager::printBorrowedBooks(const std::vector<BorrowOperation *> &operations) const {
    std::vector<std::string> booksNames;
    for (auto &operation : operations) {
        booksNames.push_back(operation->book->getNameFormatted());
    }
    std::sort(booksNames.begin(), booksNames.end());
    for (size_t i = 0; i < booksNames.size(); ++i) {
        std::string curName = booksNames[i];
        int freq = 1;
        while (i + 1 < booksNames.size() && curName == booksNames[i + 1]) {
            ++i;
            ++freq;
        }
        if (freq > 1) --i;
        std::cout << "\t" << std::setw(2) << std::right << freq << " item(s) of Book " << curName
                  << " borrowed by this user.\n";
    }
}

const Book *BooksManager::getBookById(int id) const {
    auto it = idsDictionary.find(id);
    if (it == idsDictionary.cend()) {
        return nullptr;
    }
    return it->second;
}

BooksManager::BooksManager() {
    loadDatabase();
}

BooksManager::~BooksManager() {
    updateDatabase();
    for (auto &[id, book] : idsDictionary) {
        delete book;
    }
}

void BooksManager::loadDatabase() {
    std::ifstream data("Books.txt");
    if (data.fail()) {
        data.close();
        throw std::invalid_argument("CAN't open database of books --> \"Books.txt\"");
    }
    clear();
    std::string bookStr;
    while (readAndTrim(data, bookStr)) {
        Book *book = new Book(bookStr);
        pushBook(book);
    }
    data.close();
}

void BooksManager::updateDatabase() const {
    std::ofstream data("Books.txt");
    if (data.fail()) {
        std::cerr << "CAN't open database of books --> \"Books.txt\"";
        return;
    }
    for (auto &[id, book] : idsDictionary) {
        data << book->toString() << "\n";
    }
    data.close();
}
