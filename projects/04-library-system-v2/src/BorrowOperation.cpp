#include "BorrowOperation.hpp"

#include <sstream>

BorrowOperation::BorrowOperation(const User *user, const Book *book) : user(user), book(book) {}

std::string BorrowOperation::toString() const {
    std::ostringstream oss;
    oss << user->getId() << DELIM << book->getId() << DELIM;
    return oss.str();
}

void BorrowOperation::deserialize(const std::string &borrowStr, int &userId, int &bookId) {
    std::istringstream iss(borrowStr);
    iss >> userId;
    iss.ignore();
    iss >> bookId;
}
