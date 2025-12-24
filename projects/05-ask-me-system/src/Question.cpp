#include "Question.hpp"

#include <iomanip>
#include <sstream>

#include "Helper.hpp"
#include "Question.hpp"
#include "User.hpp"

Question::Question(User* sender, User* recipient, int id, const std::string& questionText,
                   bool isAnonymous, Question* parent)
    : id(id),
      questionText(questionText),
      parent(parent),
      sender(sender),
      recipient(recipient),
      isAnonymous(isAnonymous) {}
Question::~Question() {
    if (answer) delete answer;
}
Answer::Answer(const std::string& answerText) : answerText(answerText) {}
const std::string& Answer::getAnswerText() const {
    return answerText;
}
void Answer::update(const std::string& newAnswerText) {
    answerText = newAnswerText;
}

int Question::getId() const {
    return id;
}
void Question::printToWhom(int indent) const {
    std::string tabs = indenter(indent);
    std::cout << tabs << "Question id   :  " << id << "\n";
    if (parent) std::cout << tabs << "\t-->From thread question id: " << parent->getId() << "\n";
    std::cout << tabs << "Is anonymous? : " << isAnonymous << "\n";
    std::cout << tabs << "To User       : " << recipient->getName() << "\n";
    std::cout << tabs << "\tQuestion text : " << questionText << "\n";
    if (answer)
        std::cout << tabs << "\tAnswer text   : " << answer->getAnswerText() << "\n";
    else
        std::cout << tabs << "\tNot Answered Yet!\n";
}
void Question::printFromWhom(int indent) const {
    std::string tabs = indenter(indent);
    std::cout << tabs << "Question id : " << id << "\n";
    if (isAnonymous)
        std::cout << tabs << "From an anonymous user!\n";
    else
        std::cout << tabs << "From User   : " << sender->getName() << "\n";
    std::cout << tabs << "\tQuestion text : " << questionText << "\n";
    if (answer)
        std::cout << tabs << "\tAnswer text   : " << answer->getAnswerText() << "\n";
    else
        std::cout << tabs << "\tNot Answered Yet!\n";
}

void Question::printFeed(const User* const currentUser, int indent) const {
    std::string tabs = indenter(indent);
    std::cout << tabs << "Question id : " << id << "\n";
    if (isAnonymous)
        std::cout << tabs << "From an anonymous user!\n";
    else {
        std::cout << tabs << "From User   : " << sender->getName();
        if (currentUser == sender) std::cout << "(You)";
        std::cout << "\n";
    }
    std::cout << tabs << "To User     : " << recipient->getName();
    if (currentUser == recipient) std::cout << "(You)";
    std::cout << "\n";
    std::cout << tabs << "\tQuestion text : " << questionText << "\n";
    if (answer) std::cout << tabs << "\tAnswer text   : " << answer->getAnswerText() << "\n";
}

bool Question::canEdit(User* user) const {
    return recipient == user;
}

bool Question::canSee(User* user) const {
    bool res = (user == recipient || user == sender);
    if (!res && answer && (!parent || parent->canSee(user))) {
        return true;
    }
    return res;
}

void Question::setAnswerText(const std::string& answerText) {
    if (!answer)
        answer = new Answer(answerText);
    else
        answer->update(answerText);
}

std::string Question::toString() const {
    std::ostringstream oss;
    oss << id << DELIM << questionText << DELIM << (answer ? answer->getAnswerText() : "") << DELIM
        << isAnonymous << DELIM << (parent ? parent->getId() : -1) << DELIM << sender->getId()
        << DELIM << recipient->getId() << DELIM;
    return oss.str();
}
Question::Question(const std::string& questionStr) {
    std::string temp;
    std::istringstream iss(questionStr);

    getline(iss, temp, DELIM);
    id = stoi(temp);
    getline(iss, questionText, DELIM);
    getline(iss, temp, DELIM);
    if (!temp.empty()) answer = new Answer(temp);
    getline(iss, temp, DELIM);
    isAnonymous = stoi(temp);
    getline(iss, temp, DELIM);
    tempParentId = stoi(temp);
    getline(iss, temp, DELIM);
    tempSenderId = stoi(temp);
    getline(iss, temp, DELIM);
    tempRecipientId = stoi(temp);
}
User* Question::getSender() const {
    return sender;
}
User* Question::getRecipient() const {
    return recipient;
}
bool Question::isAnswered() const {
    return answer != nullptr;
}
Question* Question::getParentQuestion() const {
    return parent;
}
void Question::linkObjects(const std::map<int, User*>& usersIdMap,
                           const std::map<int, Question*>& questionsIdMap) {
    if (tempParentId != -1) parent = questionsIdMap.at(tempParentId);
    sender = usersIdMap.at(tempSenderId);
    recipient = usersIdMap.at(tempRecipientId);

    sender->pushSentQuestion(this);
    if (parent == nullptr) recipient->pushReceivedQuestion(this);
}