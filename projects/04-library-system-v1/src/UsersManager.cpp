#include "UsersManager.hpp"

std::pair<const User *, std::string> UsersManager::enterUser() const {
    std::string userName;
    std::cout << "Enter user name: ";
    getline(std::cin, userName);
    return {usersByNameTrie.wordExists(userName), userName};
}
bool UsersManager::addUser() {
    auto [existingUser, userName] = enterUser();
    if (existingUser) {
        std::cout << "This name is already existed!\n";
        return false;
    }
    int id = Sefn::readValidatedInput<int>("Enter user id: ");
    if (usersByIdMap.find(id) != usersByIdMap.end()) {
        std::cout << "This id is already existed!\n";
        return false;
    }
    User *user = new User(id, userName);
    usersByIdMap[id] = user;
    usersByNameTrie.insert(user, userName);
    return true;
}
void UsersManager::userBorrowBook(User *usr, Book *book) {
    return usr->borrow(book);
}
bool UsersManager::userReturnBook(User *usr, Book *book) {
    return usr->returnBook(book);
}
void UsersManager::printUsers() const {
    std::cout << "Users sorted by ids: \n";
    User::printHeader(1);
    for (auto &[id, usr] : usersByIdMap) {
        usr->print(1);
        usr->printBorrowedBooks(2);
    }
}
UsersManager::~UsersManager() {
    for (auto &[id, user] : usersByIdMap) {
        delete user;
    }
}
