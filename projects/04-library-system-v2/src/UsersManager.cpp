#include "UsersManager.hpp"

#include <algorithm>
#include <fstream>

std::pair<User *, std::string> UsersManager::enterUser() {
    std::string userName;
    std::cout << "Enter user name: ";
    readAndTrim(std::cin, userName);
    return {namesDictionary.wordExists(userName), userName};
}

void UsersManager::pushUser(User *user) {
    idsDictionary[user->getId()] = user;
    namesDictionary.insert(user, user->getName());
}

void UsersManager::clear() {
    idsDictionary.clear();
    namesDictionary.clear();
}

AddUserResult UsersManager::addUser(std::string &nameAddedFormatted) {
    auto [usrPtr, usrName] = enterUser();
    if (usrPtr) {
        return AddUserResult::NAME_IS_EXISTED_BEFORE;
    }
    int id = Sefn::readValidatedInput<int>("Enter user id: ");
    if (idsDictionary.find(id) != idsDictionary.end()) {
        return AddUserResult::ID_IS_EXISTED_BEFORE;
    }
    User *user = new User(id, usrName);
    pushUser(user);
    nameAddedFormatted = user->getNameFormatted();
    return AddUserResult::SUCCESS;
}

void UsersManager::printUsersById() const {
    std::cout << "\tUsers sorted by id: \n";
    User::printHeader(2);
    for (auto &[id, user] : idsDictionary) {
        user->print(2);
    }
}

void UsersManager::printUsersByName() const {
    std::cout << "\tUsers sorted by name: \n";
    User::printHeader(2);
    namesDictionary.traverse([](User *user) { user->print(2); });
}

void UsersManager::printBorrowers(const std::vector<BorrowOperation *> &operations) const {
    std::vector<std::string> borrowersNames;
    for (auto &operation : operations) {
        borrowersNames.push_back(operation->user->getNameFormatted());
    }
    std::sort(borrowersNames.begin(), borrowersNames.end());
    for (size_t i = 0; i < borrowersNames.size(); ++i) {
        std::string curName = borrowersNames[i];
        int freq = 1;
        while (i + 1 < borrowersNames.size() && curName == borrowersNames[i + 1]) {
            ++i;
            ++freq;
        }
        if (freq > 1) --i;
        std::cout << "\tUser " << curName << " borrowed " << std::setw(2) << std::right << freq
                  << " item(s) of this book\n";
    }
}

const User *UsersManager::getUserById(int id) const {
    auto it = idsDictionary.find(id);
    if (it == idsDictionary.cend()) {
        return nullptr;
    }
    return it->second;
}

UsersManager::~UsersManager() {
    updateDatabase();
    for (auto &[id, user] : idsDictionary) {
        delete user;
    }
}
UsersManager::UsersManager() {
    loadDatabase();
}

void UsersManager::loadDatabase() {
    std::ifstream data("Users.txt");
    if (data.fail()) {
        data.close();
        throw std::invalid_argument("CAN't open database of users --> \"Users.txt\"");
    }
    clear();
    std::string userStr;
    while (readAndTrim(data, userStr)) {
        User *user = new User(userStr);
        pushUser(user);
    }
    data.close();
}
void UsersManager::updateDatabase() {
    std::ofstream data("Users.txt");
    if (data.fail()) {
        std::cerr << "CAN't open database of users --> \"Users.txt\"";
        return;
    }
    for (auto &[id, user] : idsDictionary) {
        data << user->toString() << "\n";
    }
    data.close();
}