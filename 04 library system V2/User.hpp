/**
 * @file User.hpp
 * @brief Defines the User class and related enumerations for managing user information in Library System V2.
 */

#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Helper.hpp"
#include "Book.hpp"

/**
 * @enum AddUserResult
 * @brief Enumerates possible outcomes when attempting to add a new user to the system.
 */
enum class AddUserResult{
    SUCCESS, /**< User was added successfully. */
    ID_IS_EXISTED_BEFORE, /**< A user with the same ID already exists. */
    NAME_IS_EXISTED_BEFORE /**< A user with the same name already exists. */
};

/**
 * @class User
 * @brief Represents a user in Library System V2, managing their details.
 * 
 * This class stores information about a user, including their ID and name.
 * It also provides methods for serialization and formatted name retrieval.
 */
class User{
    static constexpr int USER_NAME_WIDTH = 40; /**< Width for displaying user name. */
    static constexpr int USER_ID_WIDTH = 10; /**< Width for displaying user ID. */
    static const char DELIM = '|'; /**< Delimiter used for serializing user data to string. */
    int id; /**< Unique identifier for the user. */
    std::string name; /**< Name of the user. */
    std::string formatted_name; /**< Formatted name of the user for display/search. */

    /**
     * @brief Constructor for the User class.
     * @param id The unique ID of the user.
     * @param name The name of the user.
     */
    User(int id, std::string name);

    /**
     * @brief Constructs a User object from a serialized string.
     * @param user_str The string representation of a user.
     */
    User(const std::string &user_str);

    /**
     * @brief Converts the User object into a string representation for persistence.
     * @return A string representing the user's data.
     */
    std::string to_string()const;

    friend class UsersManager;
public:
    /**
     * @brief Gets the name of the user.
     * @return The name of the user.
     */
    std::string get_name() const;

    /**
     * @brief Gets the formatted name of the user.
     * @return The formatted name of the user.
     */
    const std::string &get_name_formatted() const;

    /**
     * @brief Gets the ID of the user.
     * @return The ID of the user.
     */
    int get_id() const;

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
};
