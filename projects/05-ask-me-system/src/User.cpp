#include "User.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "Helper.hpp"

std::string User::getName() const {
    return userName;
}

void User::printHeader(int tabs) {
    std::string indent = indenter(tabs);

    int totalWidth = USERNAME_WIDTH + USERID_WIDTH + 7;  // +9 for separators and padding
    std::string decorator(totalWidth, '-');

    std::cout << indent << decorator << "\n";
    std::cout << indent << "| " << std::left << std::setw(USERNAME_WIDTH) << "Name" << " |" << " "
              << std::right << std::setw(USERID_WIDTH) << "ID" << " |\n";
    std::cout << indent << decorator << "\n";
}

void User::print(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent << "| " << std::left << std::setw(USERNAME_WIDTH) << userName << " |" << " "
              << std::right << std::setw(USERID_WIDTH) << id << " |\n";
}

bool User::verify(const std::string &userName, const std::string &password) const {
    return userName == this->userName && password == this->password;
}

int User::getId() const {
    return id;
}
bool User::isAllowingAnonymous() const {
    return allowAnonymous;
}
const std::vector<Question *> &User::getQuestionsSent() const {
    return sentQuestions;
}
const std::vector<Question *> &User::getQuestionsReceived() const {
    return receivedQuestions;
}
User::User(int id, const std::string &email, const std::string &userName,
           const std::string &password, bool allowAnonymous)
    : id(id),
      email(email),
      password(password),
      userName(userName),
      allowAnonymous(allowAnonymous) {}
void User::pushReceivedQuestion(Question *question) {
    receivedQuestions.push_back(question);
}
void User::pushSentQuestion(Question *question) {
    sentQuestions.push_back(question);
}
void User::popReceivedQuestion(Question *question) {
    auto it = std::find(receivedQuestions.begin(), receivedQuestions.end(), question);
    receivedQuestions.erase(it);
}
void User::popSentQuestion(Question *question) {
    auto it = std::find(sentQuestions.begin(), sentQuestions.end(), question);
    sentQuestions.erase(it);
}

std::string User::toString() const {
    std::ostringstream oss;
    oss << id << DELIM << email << DELIM << userName << DELIM << password << DELIM << allowAnonymous
        << DELIM;
    return oss.str();
}
User::User(const std::string &userStr) {
    std::istringstream iss(userStr);
    std::string tempInt;
    getline(iss, tempInt, DELIM);
    id = std::stoi(tempInt);
    getline(iss, email, DELIM);
    getline(iss, userName, DELIM);
    getline(iss, password, DELIM);
    getline(iss, tempInt, DELIM);
    allowAnonymous = std::stoi(tempInt);
}