#include "BorrowsManager.hpp"

#include <algorithm>
#include <fstream>

const std::vector<BorrowOperation *> BorrowsManager::NA;

void BorrowsManager::createBorrowLink(const User *user, const Book *book) {
    BorrowOperation *operation = new BorrowOperation(user, book);
    borrowsByBook[book].push_back(operation);
    borrowsByUser[user].push_back(operation);
}

BorrowResult BorrowsManager::borrowBook(User *user, Book *book) {
    if (!book->isAvailable()) {
        return BorrowResult::BOOK_NOT_AVAILABLE;
    }
    const auto &it = borrowsByUser.find(user);
    if (it != borrowsByUser.cend()) {
        if (it->second.size() >= MAX_BORROWS_PER_USER) {
            return BorrowResult::USER_REACHED_MAX_BORROWED_BOOKS;
        }
        int freq = 0;
        for (const auto &operation : it->second) {
            if (operation->book == book) freq++;
        }
        if (freq >= MAX_BORROWS_REPETITION) return BorrowResult::USER_REACHED_MAX_REPETITIONS;
    }
    createBorrowLink(user, book);
    return BorrowResult::SUCCESS;
}
bool BorrowsManager::returnBook(User *user, Book *book) {
    auto itUser = borrowsByUser.find(user);
    if (itUser == borrowsByUser.end()) {
        return false;
    }

    auto &operations = itUser->second;
    auto operationIt = std::find_if(operations.begin(), operations.end(),
                                    [book](const BorrowOperation *op) { return op->book == book; });

    if (operationIt == operations.end()) {
        return false;
    }

    BorrowOperation *operation = *operationIt;
    operations.erase(operationIt);

    auto &bookOperations = borrowsByBook[book];
    auto bookOperationIt = std::find(bookOperations.begin(), bookOperations.end(), operation);

    if (bookOperationIt == bookOperations.end()) {
        throw std::invalid_argument("Incompatible Data");
    }

    bookOperations.erase(bookOperationIt);
    delete operation;
    return true;
}
const std::vector<BorrowOperation *> &BorrowsManager::getBookHistory(Book *book) const {
    auto it = borrowsByBook.find(book);
    return it != borrowsByBook.cend() ? it->second : NA;
}
const std::vector<BorrowOperation *> &BorrowsManager::getUserHistory(User *user) const {
    auto it = borrowsByUser.find(user);
    return it != borrowsByUser.cend() ? it->second : NA;
}
BorrowsManager::~BorrowsManager() {
    updateDatabase();
    for (auto &[key, v] : borrowsByBook) {
        for (auto &operation : v) {
            delete operation;
        }
    }
}
void BorrowsManager::updateDatabase() {
    std::ofstream data("BorrowOperations.txt");
    if (data.fail()) {
        std::cerr << "CAN't open database of borrow operations --> \"BorrowOperations.txt\"";
        return;
    }
    for (auto &[book, operations] : borrowsByBook) {
        for (auto &operation : operations) {
            data << operation->toString() << "\n";
        }
    }
    data.close();
}

void BorrowsManager::deserialize(const std::string &borrowStr, int &userId, int &bookId) {
    BorrowOperation::deserialize(borrowStr, userId, bookId);
}
