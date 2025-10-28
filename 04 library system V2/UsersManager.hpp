/**
 * @file UsersManager.hpp
 * @brief Manages the collection of users in Library System V2, including persistence.
 */

#pragma once
#include <Dictionary.hpp>
#include "User.hpp"
#include "Book.hpp"
#include "BorrowOperation.hpp"
#include <input_utils.hpp>

/**
 * @class UsersManager
 * @brief Handles the creation, storage, retrieval, and management of User objects with data persistence.
 * 
 * This class extends the functionalities of V1 by adding data loading and saving mechanisms
 * to and from a file (`Users.txt`). It manages users by ID and name, and supports operations
 * like adding and printing user lists.
 */
class UsersManager{
    std::map<int, User*> ids_dictionary; /**< Maps user IDs to User objects for quick lookup. */
    Dictionary <User> names_dictionary; /**< Manages users by name, facilitating searching. */

    /**
     * @brief Loads user data from the `Users.txt` file into memory.
     */
    void load_database();

    /**
     * @brief Updates the persistent storage with the current user data.
     */
    void update_database();

    /**
     * @brief Adds a user object to both internal dictionaries.
     * @param user A pointer to the User object to be added.
     */
    void push_user(User *user);

    /**
     * @brief Clears all user data from memory.
     */
    void clear();
public:
    /**
     * @brief Constructor for UsersManager. Initializes by loading data from the database.
     */
    UsersManager();

    /**
     * @brief Deleted copy constructor to prevent unintended copying.
     */
    UsersManager(const UsersManager&) = delete;

    /**
     * @brief Deleted assignment operator to prevent unintended assignment.
     */
    UsersManager& operator=(const UsersManager&) = delete;

    /**
     * @brief Prompts the user to enter user details and returns a pair of User pointer and error message.
     * @return A pair containing a pointer to the entered User (or nullptr if invalid) and an error string.
     */
    std::pair<User*, std::string> enter_user();

    /**
     * @brief Adds a new user to the system.
     * @param name_added_formatted The formatted name of the user to be added.
     * @return An AddUserResult enum indicating the success or type of failure.
     */
    AddUserResult add_user(std::string &name_added_formatted);

    /**
     * @brief Retrieves a user by their ID.
     * @param id The ID of the user to retrieve.
     * @return A const pointer to the User object if found, nullptr otherwise.
     */
    const User* get_user_by_id(int id) const;

    /**
     * @brief Prints all users in the system, sorted by name.
     */
    void print_users_by_name()const;

    /**
     * @brief Prints all users in the system, sorted by ID.
     */
    void print_users_by_id()const;

    /**
     * @brief Prints a list of users who have borrowed books, based on provided borrow operations.
     * @param operations A vector of BorrowOperation pointers representing current borrowings.
     */
    void print_borrowers(const std::vector<BorrowOperation*> &operations)const;

    /**
     * @brief Destructor for UsersManager. Saves data to the database and cleans up dynamically allocated User objects.
     */
    ~UsersManager();
};