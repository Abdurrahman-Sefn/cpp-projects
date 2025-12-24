#include "QuestionsManager.hpp"

#include <algorithm>
#include <fstream>

#include "User.hpp"

void QuestionsManager::printReceivedQuestions(
    const std::vector<Question *> &receivedQuestions) const {
    std::cout << "\n*****************************************************\n";
    for (auto &question : receivedQuestions) {
        printReceivedQuestions(question, 1);
    }
    std::cout << "\n*****************************************************\n";
}
void QuestionsManager::printSentQuestions(const std::vector<Question *> &sentQuestions) const {
    std::cout << "\n*****************************************************\n";
    for (auto &question : sentQuestions) {
        question->printToWhom(1);
        std::cout << "\n";
    }
    std::cout << "\n*****************************************************\n";
}
void QuestionsManager::printReceivedQuestions(Question *receivedQuestion, int indent) const {
    receivedQuestion->printFromWhom(indent);
    std::cout << "\n";
    auto it = parentToChildrenMap.find(receivedQuestion);
    if (it != parentToChildrenMap.end()) {
        for (auto &child : it->second) {
            printReceivedQuestions(child, indent + 1);
        }
    }
}

void QuestionsManager::listFeed(User *currentUser, int indent) const {
    std::cout << "\n*****************************************************\n";
    for (auto &[parent, children] : parentToChildrenMap) {
        if (parent->getParentQuestion() == nullptr && parent->canSee(currentUser) &&
            parent->isAnswered()) {
            listFeed(currentUser, parent, indent);
        }
    }
    std::cout << "\n*****************************************************\n";
}

void QuestionsManager::listFeed(User *currentUser, Question *question, int indent) const {
    question->printFeed(currentUser, indent);
    std::cout << "\n";
    indent++;
    auto it = parentToChildrenMap.find(question);
    if (it != parentToChildrenMap.cend()) {
        for (auto &child : it->second) {
            if (child->canSee(currentUser) && child->isAnswered())
                listFeed(currentUser, child, indent);
        }
    }
}
Question *QuestionsManager::addQuestion(User *sender, User *recipient,
                                        const std::string &questionText, bool isAnonymous,
                                        Question *parent) {
    int questionId = ++lastId;
    Question *question =
        new Question(sender, recipient, questionId, questionText, isAnonymous, parent);
    pushQuestion(question);
    if (!question->getParentQuestion()) {
        question->getRecipient()->pushReceivedQuestion(question);
    }
    question->getSender()->pushSentQuestion(question);
    return question;
}
void QuestionsManager::pushQuestion(Question *question) {
    idToQuestionMap[question->getId()] = question;
    if (question->getParentQuestion()) {
        parentToChildrenMap[question->getParentQuestion()].push_back(question);
    } else
        parentToChildrenMap[question];
}
void QuestionsManager::removeQuestion(Question *question) {
    if (!question->getParentQuestion()) {
        question->getRecipient()->popReceivedQuestion(question);
    } else {
        auto &v = parentToChildrenMap[question->getParentQuestion()];
        auto it = std::find(v.begin(), v.end(), question);
        v.erase(it);
    }
    removeQuestionThreaded(question);
}
void QuestionsManager::removeQuestionThreaded(Question *question) {
    question->getSender()->popSentQuestion(question);
    idToQuestionMap.erase(question->getId());
    if (parentToChildrenMap.count(question)) {
        for (auto &child : parentToChildrenMap[question]) {
            removeQuestionThreaded(child);
        }
        parentToChildrenMap.erase(question);
    }
    delete question;
}

void QuestionsManager::loadDatabase() {
    clear();
    std::ifstream questionsFile("Questions.txt");
    std::string questionStr;
    while (getline(questionsFile, questionStr)) {
        Question *question = new Question(questionStr);
        pushQuestion(question);
        lastId = std::max(lastId, question->getId());
    }
    questionsFile.close();
}

void QuestionsManager::updateDatabase() {
    std::ofstream questionsFile("Questions.txt");
    for (auto &[id, question] : idToQuestionMap) {
        questionsFile << question->toString() << "\n";
    }
    questionsFile.close();
}
void QuestionsManager::linkObjects(const std::map<int, User *> &usersIdMap) {
    for (auto &[id, question] : idToQuestionMap) {
        question->linkObjects(usersIdMap, idToQuestionMap);
    }
}
void QuestionsManager::clear() {
    for (auto &[id, question] : idToQuestionMap) {
        delete question;
    }
    idToQuestionMap.clear();
    parentToChildrenMap.clear();
    lastId = -1;
}
QuestionsManager::~QuestionsManager() {
    updateDatabase();
    clear();
}
Question *QuestionsManager::getQuestionById(int id) const {
    auto it = idToQuestionMap.find(id);
    if (it == idToQuestionMap.end()) return nullptr;
    return it->second;
}