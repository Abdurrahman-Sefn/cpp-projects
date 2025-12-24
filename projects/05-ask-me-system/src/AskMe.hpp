/**
 * @file AskMe.hpp
 * @brief Defines the main AskMe class that orchestrates the question and answer system.
 */

#pragma once
#include "QuestionsManager.hpp"
#include "UsersManager.hpp"

/**
 * @class AskMe
 * @brief The core class for the AskMe question and answer system.
 *
 * This class integrates `UsersManager` and `QuestionsManager` to provide a complete
 * system for user authentication, asking questions, answering questions, and managing data.
 */
class AskMe {
    UsersManager usersManager;         /**< Manages all user-related operations. */
    QuestionsManager questionsManager; /**< Manages all question-related operations. */
    int currentUserId{-1};             /**< The ID of the currently logged-in user. */
    User *currentUser{};               /**< Pointer to the currently logged-in user. */

    /**
     * @brief Handles the login/signup process.
     * @return True if a user successfully logs in or signs up, false otherwise.
     */
    bool enter();

    /**
     * @brief Reads question details from the user.
     * @param question A reference to a Question pointer to store the new question.
     * @return True if the question was successfully read, false otherwise.
     */
    bool readQuestion(Question *&question);

    /**
     * @brief Handles the user login process.
     */
    void login();

    /**
     * @brief Handles the user signup process.
     */
    void signUp();

    /**
     * @brief Logs out the current user.
     */
    void logout();

    /**
     * @brief Links related objects after loading from persistence (e.g., questions to users).
     */
    void linkObjects();

    /**
     * @brief Loads all data from persistent storage.
     */
    void loadDatabase();

    /**
     * @brief Updates all data to persistent storage.
     */
    void updateDatabase();

    /**
     * @brief Handles the process of a user asking a new question.
     */
    void askQuestion();

    /**
     * @brief Handles the process of a user answering an existing question.
     */
    void answerQuestion();

    /**
     * @brief Handles the process of a user deleting a question.
     */
    void deleteQuestion();

   public:
    /**
     * @brief Runs the main loop of the AskMe system, presenting the main menu to the user.
     */
    void run();
};