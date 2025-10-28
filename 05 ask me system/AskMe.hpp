/**
 * @file AskMe.hpp
 * @brief Defines the main AskMe class that orchestrates the question and answer system.
 */

#pragma once
#include "UsersManager.hpp"
#include "QuestionsManager.hpp"

/**
 * @class AskMe
 * @brief The core class for the AskMe question and answer system.
 * 
 * This class integrates `UsersManager` and `QuestionsManager` to provide a complete
 * system for user authentication, asking questions, answering questions, and managing data.
 */
class AskMe{
    UsersManager users_manager; /**< Manages all user-related operations. */
    QuestionsManager questions_manager; /**< Manages all question-related operations. */
    int cur_user_id{-1}; /**< The ID of the currently logged-in user. */
    User *cur_user{}; /**< Pointer to the currently logged-in user. */

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
    bool read_question(Question* &question);

    /**
     * @brief Handles the user login process.
     */
    void login();

    /**
     * @brief Handles the user signup process.
     */
    void signup();

    /**
     * @brief Logs out the current user.
     */
    void logout();

    /**
     * @brief Links related objects after loading from persistence (e.g., questions to users).
     */
    void link_objects();

    /**
     * @brief Loads all data from persistent storage.
     */
    void load_database();

    /**
     * @brief Updates all data to persistent storage.
     */
    void update_database();

    /**
     * @brief Handles the process of a user asking a new question.
     */
    void ask_question();

    /**
     * @brief Handles the process of a user answering an existing question.
     */
    void answer_question();

    /**
     * @brief Handles the process of a user deleting a question.
     */
    void delete_question();
public:
    /**
     * @brief Runs the main loop of the AskMe system, presenting the main menu to the user.
     */
    void run();
};