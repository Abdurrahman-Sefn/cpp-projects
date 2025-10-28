/**
 * @file User.hpp
 * @brief Defines the User class for managing user information and interactions in the AskMe system.
 */

#pragma once
#include "Question.hpp"
#include <iostream>
#include <vector>

/**
 * @class User
 * @brief Represents a user in the AskMe system, handling authentication, question sending/receiving, and anonymity settings.
 * 
 * This class stores user details such as ID, email, password, and username. It also manages
 * lists of questions sent by and received by the user, and their preference for anonymous questions.
 */
class User{
    static constexpr int USER_NAME_WIDTH = 40; /**< Width for displaying user name. */
    static constexpr int USER_ID_WIDTH = 10; /**< Width for displaying user ID. */
    static const char DELIM = '|'; /**< Delimiter used for serializing user data to string. */
    int id{-1}; /**< Unique identifier for the user. */
    std::string email; /**< User's email address. */
    std::string password; /**< User's password. */
    std::string user_name; /**< User's chosen username. */
    bool allow_anonymous = false; /**< Flag indicating if the user allows anonymous questions. */
    std::vector<Question*> questions_from_user; /**< List of questions sent by this user. */
    std::vector<Question*> questions_to_user; /**< List of questions received by this user. */
public:
    /**
     * @brief Converts the User object into a string representation for persistence.
     * @return A string representing the user's data.
     */
    std::string to_string()const;

    /**
     * @brief Constructs a User object from a serialized string.
     * @param user_str The string representation of a user.
     */
    User(const std::string &user_str);

    /**
     * @brief Adds a question to the list of questions received by this user.
     * @param question A pointer to the Question object received.
     */
    void push_received_question(Question* question);

    /**
     * @brief Adds a question to the list of questions sent by this user.
     * @param question A pointer to the Question object sent.
     */
    void push_sent_question(Question* question);

    /**
     * @brief Removes a question from the list of questions received by this user.
     * @param question A pointer to the Question object to be removed.
     */
    void pop_received_question(Question* question);

    /**
     * @brief Removes a question from the list of questions sent by this user.
     * @param question A pointer to the Question object to be removed.
     */
    void pop_sent_question(Question* question);

    /**
     * @brief Constructor for the User class.
     * @param id The unique ID of the user.
     * @param email The user's email address.
     * @param user_name The user's chosen username.
     * @param password The user's password.
     * @param allow_anonymous True if the user allows anonymous questions, false otherwise.
     */
    User(int id, const std::string &email, const std::string &user_name, const std::string &password, bool allow_anonymous);

    /**
     * @brief Verifies the provided username and password against the user's credentials.
     * @param user_name The username to verify.
     * @param password The password to verify.
     * @return True if the credentials match, false otherwise.
     */
    bool verify(const std::string &user_name, const std::string &password)const;

    /**
     * @brief Prints the header for user information.
     * @param tabs The number of tabs to indent the output.
     */
    static void print_header(int tabs = 0);

    /**
     * @brief Prints a summary of the user's information.
     * @param tabs The number of tabs to indent the output.
     */
    void print(int tabs = 0) const;

    /**
     * @brief Gets the username of the user.
     * @return The username of the user.
     */
    std::string get_name()const;

    /**
     * @brief Checks if the user allows anonymous questions.
     * @return True if anonymous questions are allowed, false otherwise.
     */
    bool is_allowing_anonymous()const;

    /**
     * @brief Gets the ID of the user.
     * @return The ID of the user.
     */
    int get_id()const;

    /**
     * @brief Gets a constant reference to the vector of questions sent by this user.
     * @return A constant reference to `questions_from_user`.
     */
    const std::vector<Question*> &get_questions_sent()const;

    /**
     * @brief Gets a constant reference to the vector of questions received by this user.
     * @return A constant reference to `questions_to_user`.
     */
    const std::vector<Question*> &get_questions_received()const;
};