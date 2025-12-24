#include "UsersManager.hpp"

#include <fstream>
User *UsersManager::getUserById(int id) const {
    auto it = idToUserMap.find(id);
    if (it == idToUserMap.end()) return nullptr;
    return it->second;
}
User *UsersManager::getUserByUsername(const std::string &username) const {
    auto it = usernameToUserMap.find(username);
    if (it == usernameToUserMap.end()) return nullptr;
    return it->second;
}
User *UsersManager::logIn(const std::string &userName, const std::string &password) const {
    auto it = usernameToUserMap.find(userName);
    if (it == usernameToUserMap.end()) return nullptr;
    if (it->second->verify(userName, password)) {
        return it->second;
    }
    return nullptr;
}
User *UsersManager::signUp(const std::string &userName, const std::string &password,
                           const std::string &email, bool allowAnonymous) {
    int id = ++lastId;
    User *user = new User(id, email, userName, password, allowAnonymous);
    pushUser(user);
    return user;
}
void UsersManager::listSystemUsers() const {
    User::printHeader(1);
    for (auto &[id, user] : idToUserMap) {
        user->print(1);
    }
    std::cout << "\n";
}
void UsersManager::pushUser(User *user) {
    usernameToUserMap[user->getName()] = user;
    idToUserMap[user->getId()] = user;
}

void UsersManager::loadDatabase() {
    clear();
    std::ifstream usersFile("Users.txt");
    std::string userStr;
    while (getline(usersFile, userStr)) {
        User *user = new User(userStr);
        pushUser(user);
        lastId = std::max(lastId, user->getId());
    }
    usersFile.close();
}
void UsersManager::clear() {
    for (auto &[id, user] : idToUserMap) {
        delete user;
    }
    usernameToUserMap.clear();
    idToUserMap.clear();
    lastId = -1;
}
void UsersManager::updateDatabase() {
    std::ofstream usersFile("Users.txt");
    for (auto &[id, user] : idToUserMap) {
        usersFile << user->toString() << "\n";
    }
    usersFile.close();
}
const std::map<int, User *> &UsersManager::getIdUsersMap() const {
    return idToUserMap;
}
UsersManager::~UsersManager() {
    updateDatabase();
    clear();
}