/**
 * @file User.hpp
 * @brief Defines the User class for managing user information and interactions in the AskMe system.
 */

#pragma once
#include <iostream>
#include <vector>

#include "Question.hpp"

/**
 * @class User
 * @brief Represents a user in the AskMe system, handling authentication, question
 * sending/receiving, and anonymity settings.
 *
 * This class stores user details such as ID, email, password, and username. It also manages
 * lists of questions sent by and received by the user, and their preference for anonymous
 * questions.
 */
class User {
    static constexpr int USERNAME_WIDTH = 40; /**< Width for displaying user name. */
    static constexpr int USERID_WIDTH = 10;   /**< Width for displaying user ID. */
    static const char DELIM = '|'; /**< Delimiter used for serializing user data to string. */
    int id{-1};                    /**< Unique identifier for the user. */
    std::string email;             /**< User's email address. */
    std::string password;          /**< User's password. */
    std::string userName;          /**< User's chosen username. */
    bool allowAnonymous = false;   /**< Flag indicating if the user allows anonymous questions. */
    std::vector<Question *> sentQuestions;     /**< List of questions sent by this user. */
    std::vector<Question *> receivedQuestions; /**< List of questions received by this user. */
   public:
    /**
     * @brief Converts the User object into a string representation for persistence.
     * @return A string representing the user's data.
     */
    std::string toString() const;

    /**
     * @brief Constructs a User object from a serialized string.
     * @param userStr The string representation of a user.
     */
    User(const std::string &userStr);

    /**
     * @brief Adds a question to the list of questions received by this user.
     * @param question A pointer to the Question object received.
     */
    void pushReceivedQuestion(Question *question);

    /**
     * @brief Adds a question to the list of questions sent by this user.
     * @param question A pointer to the Question object sent.
     */
    void pushSentQuestion(Question *question);

    /**
     * @brief Removes a question from the list of questions received by this user.
     * @param question A pointer to the Question object to be removed.
     */
    void popReceivedQuestion(Question *question);

    /**
     * @brief Removes a question from the list of questions sent by this user.
     * @param question A pointer to the Question object to be removed.
     */
    void popSentQuestion(Question *question);

    /**
     * @brief Constructor for the User class.
     * @param id The unique ID of the user.
     * @param email The user's email address.
     * @param userName The user's chosen username.
     * @param password The user's password.
     * @param allowAnonymous True if the user allows anonymous questions, false otherwise.
     */
    User(int id, const std::string &email, const std::string &userName, const std::string &password,
         bool allowAnonymous);

    /**
     * @brief Verifies the provided username and password against the user's credentials.
     * @param userName The username to verify.
     * @param password The password to verify.
     * @return True if the credentials match, false otherwise.
     */
    bool verify(const std::string &userName, const std::string &password) const;

    /**
     * @brief Prints the header for user information.
     * @param tabs The number of tabs to indent the output.
     */
    static void printHeader(int tabs = 0);

    /**
     * @brief Prints a summary of the user's information.
     * @param tabs The number of tabs to indent the output.
     */
    void print(int tabs = 0) const;

    /**
     * @brief Gets the username of the user.
     * @return The username of the user.
     */
    std::string getName() const;

    /**
     * @brief Checks if the user allows anonymous questions.
     * @return True if anonymous questions are allowed, false otherwise.
     */
    bool isAllowingAnonymous() const;

    /**
     * @brief Gets the ID of the user.
     * @return The ID of the user.
     */
    int getId() const;

    /**
     * @brief Gets a constant reference to the vector of questions sent by this user.
     * @return A constant reference to `sentQuestions`.
     */
    const std::vector<Question *> &getQuestionsSent() const;

    /**
     * @brief Gets a constant reference to the vector of questions received by this user.
     * @return A constant reference to `receivedQuestions`.
     */
    const std::vector<Question *> &getQuestionsReceived() const;
};