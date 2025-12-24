#include "AskMe.hpp"

#include <Sefn/InputUtils.hpp>

#include "Helper.hpp"

bool AskMe::enter() {
    const static std::vector<std::string> options{"Log in:", "Sign up", "Close system"};
    showMenu(options, "\nMenu: ", 0);
    int choice = Sefn::readValidatedInput<int>("\nEnter your choice[1 - 3]: ", 0);
    while (!isInRange(choice, 1, 3)) {
        std::cout << "\tWrong input!.\n";
        choice = Sefn::readValidatedInput<int>("Enter your choice[1 - 3]: ", 0);
    }
    if (choice == 3)
        return false;
    else if (choice == 1)
        login();
    else if (choice == 2)
        signUp();
    return true;
}
void AskMe::logout() {
    currentUserId = -1;
    currentUser = nullptr;
}
void AskMe::login() {
    std::string userName, password;
    std::cout << "Enter your username: ";
    readAndTrim(std::cin, userName);
    std::cout << "Enter your password: ";
    getline(std::cin, password);
    currentUser = usersManager.logIn(userName, password);
    if (currentUser) currentUserId = currentUser->getId();
    if (!currentUser) std::cout << "\tInvalid username or password!\n";
}

void AskMe::signUp() {
    std::string userName, password, email;
    std::cout << "Enter your email: ";
    readAndTrim(std::cin, email);
    std::cout << "Enter your username: ";
    readAndTrim(std::cin, userName);
    while (usersManager.getUserByUsername(userName)) {
        std::cout << "\tThis username is already taken. Try another one: \n";
        readAndTrim(std::cin, userName);
    }
    std::cout << "Enter your password: ";
    getline(std::cin, password);
    bool allowAnonymous =
        Sefn::readValidatedInput<bool>("Do you allow anonymous questions?(0 or 1): ");
    currentUser = usersManager.signUp(userName, password, email, allowAnonymous);
    if (currentUser) currentUserId = currentUser->getId();
}
void AskMe::askQuestion() {
    int userId = Sefn::readValidatedInput<int>("Enter user id or -1 to cancel: ");
    User* userToAsk = usersManager.getUserById(userId);
    if (!userToAsk) {
        std::cout << "\tThere is no user with such id...Try to list system users\n";
        return;
    }
    bool isAnonymous = false;
    if (userToAsk->isAllowingAnonymous()) {
        isAnonymous = Sefn::readValidatedInput<bool>("Ask as anonymous?(0 or 1): ");
    } else {
        std::cout << "Note: \'" << userToAsk->getName()
                  << "\' is not allowing anonymous questions\n";
    }
    int threadId = Sefn::readValidatedInput<int>(
        "for thread question, enter question id or -1 for a new one: ");
    Question* thread = questionsManager.getQuestionById(threadId);
    if (threadId != -1) {
        if (!thread || !thread->canSee(currentUser)) {
            std::cout << "\tThere is no question with such id...Try to list feed questions\n";
        }
    }
    std::string questionText;
    std::cout << "Enter question text: ";
    getline(std::cin, questionText);
    questionsManager.addQuestion(currentUser, userToAsk, questionText, isAnonymous, thread);
}
bool AskMe::readQuestion(Question*& question) {
    int questionId = Sefn::readValidatedInput<int>("Enter question id or -1 to cancel: ");
    if (questionId == -1) return false;
    question = questionsManager.getQuestionById(questionId);
    return true;
}
void AskMe::answerQuestion() {
    Question* question;
    bool status = readQuestion(question);
    if (!status) return;
    if (!question || !question->canEdit(currentUser)) {
        std::cout << "\tThere is no such an id in your questions' ids...Try print questions asked "
                     "to you\n";
        return;
    }
    questionsManager.printReceivedQuestions({question});
    if (question->isAnswered()) {
        std::cout << "\tWarning: already answered!-->answer will be updated\n";
    }
    std::string answerText;
    std::cout << "Enter answer text: ";
    getline(std::cin, answerText);
    question->setAnswerText(answerText);
}
void AskMe::deleteQuestion() {
    Question* question;
    bool status = readQuestion(question);
    if (!status) return;
    if (!question || !question->canEdit(currentUser)) {
        std::cout << "\tThere is no such an id in your questions' ids...Try print questions asked "
                     "to you\n";
        return;
    }
    questionsManager.printReceivedQuestions({question});
    bool isSure = Sefn::readValidatedInput<bool>("\tAre you sure to delete question?(0 or 1): ");
    if (!isSure) return;
    questionsManager.removeQuestion(question);
}

void AskMe::run() {
    const static std::vector<std::string> options{"print questions to me",
                                                  "print questions from me",
                                                  "answer question",
                                                  "delete question",
                                                  "ask question",
                                                  "list system users",
                                                  "feed",
                                                  "logout"};
    while (true) {
        if (!currentUser) {
            loadDatabase();
            bool state = enter();
            if (!state)
                break;
            else {
                updateDatabase();
                continue;
            }
        }
        showMenu(options, "\nMenu: ", 0);
        int choice = Sefn::readValidatedInput<int>("\nEnter your choice[1 - 8]: ", 0);
        if (!isInRange(choice, 1, 8)) {
            std::cout << "\tInvalid choice...Try again\n";
            continue;
        }
        switch (choice) {
            case 1: {
                loadDatabase();
                auto& questionsReceived = currentUser->getQuestionsReceived();
                questionsManager.printReceivedQuestions(questionsReceived);
                break;
            }
            case 2: {
                auto& questionsSent = currentUser->getQuestionsSent();
                questionsManager.printSentQuestions(questionsSent);
                break;
            }
            case 3:
                loadDatabase();
                answerQuestion();
                updateDatabase();
                break;
            case 4:
                loadDatabase();
                deleteQuestion();
                updateDatabase();
                break;
            case 5:
                loadDatabase();
                askQuestion();
                updateDatabase();
                break;
            case 6:
                loadDatabase();
                usersManager.listSystemUsers();
                break;
            case 7:
                loadDatabase();
                questionsManager.listFeed(currentUser);
                break;
            case 8:
                updateDatabase();
                logout();
                break;
        }
    }
}
void AskMe::linkObjects() {
    auto& usersIdMap = usersManager.getIdUsersMap();
    questionsManager.linkObjects(usersIdMap);
}
void AskMe::loadDatabase() {
    usersManager.loadDatabase();
    questionsManager.loadDatabase();
    linkObjects();
    currentUser = usersManager.getUserById(currentUserId);
}
void AskMe::updateDatabase() {
    usersManager.updateDatabase();
    questionsManager.updateDatabase();
}