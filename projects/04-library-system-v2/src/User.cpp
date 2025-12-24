#include "User.hpp"

#include <sstream>

User::User(int id, std::string name) : id(id), name((trim(name), name)) {
    std::ostringstream oss;
    oss << "'" << std::left << std::setw(USER_NAME_WIDTH) << name << "'";
    formattedName = oss.str();
}
std::string User::getName() const {
    return name;
}
const std::string &User::getNameFormatted() const {
    return formattedName;
}
void User::printHeader(int tabs) {
    std::string indent = getIndentation(tabs);

    int total_width = USER_NAME_WIDTH + USER_ID_WIDTH + 7;  // +9 for separators and padding
    std::string decorator(total_width, '-');

    std::cout << indent << decorator << "\n";
    std::cout << indent << "| " << std::left << std::setw(USER_NAME_WIDTH) << "Name" << " |" << " "
              << std::right << std::setw(USER_ID_WIDTH) << "ID" << " |\n";
    std::cout << indent << decorator << "\n";
}

void User::print(int tabs) const {
    std::string indent = getIndentation(tabs);
    std::cout << indent << "| " << std::left << std::setw(USER_NAME_WIDTH) << name << " |" << " "
              << std::right << std::setw(USER_ID_WIDTH) << id << " |\n";
}

User::User(const std::string &user_str) {
    std::istringstream iss(user_str);
    getline(iss, name, DELIM);
    iss >> id;
}

std::string User::toString() const {
    std::ostringstream oss;
    oss << name << DELIM << id << DELIM;
    return oss.str();
}
int User::getId() const {
    return id;
}
