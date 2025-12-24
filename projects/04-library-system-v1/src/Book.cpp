#include "Book.hpp"

#include "User.hpp"

bool Book::borrow(User* user) {
    if (borrowed == quantity) {
        return false;
    }
    borrowed++;
    borrowers[user]++;
    return true;
}
bool Book::returnCopy(User* user) {
    if (borrowers.find(user) == borrowers.end()) {
        return false;
    }
    if (--borrowers[user] == 0) {
        borrowers.erase(user);
    }
    borrowed--;
    return true;
}
Book::Book(int id, std::string name, int quantity) : id(id), name(name), quantity(quantity) {}

void Book::printHeader(int tabs) {
    std::string indent = indenter(tabs);

    int totalWidth =
        NAME_WIDTH + ID_WIDTH + QTY_WIDTH + BORROWED_WIDTH + 13;  // +13 for separators and padding
    std::string decorator(totalWidth, '-');

    std::cout << indent << decorator << "\n";
    std::cout << indent << "| " << std::left << std::setw(NAME_WIDTH) << "Name" << " |" << " "
              << std::right << std::setw(ID_WIDTH) << "ID" << " |" << " " << std::right
              << std::setw(QTY_WIDTH) << "Total Quantity" << " |" << " " << std::right
              << std::setw(BORROWED_WIDTH) << "Total Borrowed" << " |\n";
    std::cout << indent << decorator << "\n";
}

void Book::print(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent

              << "| " << std::left << std::setw(NAME_WIDTH) << name << " |"

              << " " << std::right << std::setw(ID_WIDTH) << id << " |"

              << " " << std::right << std::setw(QTY_WIDTH) << quantity << " |"

              << " " << std::right << std::setw(BORROWED_WIDTH) << borrowed << " |\n";
}

void Book::printDetailed(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent << "Book '" << getName() << "' is borrowed by: \n";
    if (borrowers.empty()) {
        std::cout << indent << "\tNot borrowed by anyone currently.\n";
        return;
    }
    indent.push_back('\t');
    for (auto const& [usr, freq] : borrowers) {
        std::cout << indent << std::left << std::setw(20) << usr->getName();
        std::cout << " (" << freq << ") book(s)\n";
    }
}

std::string Book::getName() const {
    return name;
}
