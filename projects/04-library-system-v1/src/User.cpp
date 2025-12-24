#include "User.hpp"

constexpr int USER_NAME_WIDTH = 40;
constexpr int USER_ID_WIDTH = 10;

void User::borrow(Book* book) {
    borrowedBooks[book]++;
}
bool User::returnBook(Book* book) {
    if (borrowedBooks.find(book) == borrowedBooks.end()) {
        return false;
    }
    if (--borrowedBooks[book] == 0) {
        borrowedBooks.erase(book);
    }
    return true;
}

User::User(int id, std::string name) : id(id), name(name) {}
std::string User::getName() const {
    return name;
}

void User::printHeader(int tabs) {
    std::string indent = indenter(tabs);

    int totalWidth = USER_NAME_WIDTH + USER_ID_WIDTH + 9;  // +9 for separators and padding
    std::string decorator(totalWidth, '-');

    std::cout << indent << decorator << "\n";
    std::cout << indent << "| " << std::left << std::setw(USER_NAME_WIDTH) << "Name" << " |" << " "
              << std::right << std::setw(USER_ID_WIDTH) << "ID" << " |\n";
    std::cout << indent << decorator << "\n";
}

void User::print(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent

              << "| " << std::left << std::setw(USER_NAME_WIDTH) << name << " |"

              << " " << std::right << std::setw(USER_ID_WIDTH) << id << " |\n";
}

void User::printBorrowedBooks(int tabs) const {
    std::string indent = indenter(tabs);

    if (borrowedBooks.empty()) {
        return;
    }

    std::cout << indent << "--> Borrowed Books:\n";
    for (auto const& [book, freq] : borrowedBooks) {
        std::cout << indent << "\t- " << freq << " book(s) of '" << book->getName() << "'\n";
    }
}
