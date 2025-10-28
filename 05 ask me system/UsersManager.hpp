/**
 * @file UsersManager.hpp
 * @brief Manages user accounts and authentication for the AskMe system.
 */

#pragma once
#include "User.hpp"
#include <unordered_map>
#include <map>
#include <vector>

/**
 * @class UsersManager
 * @brief Handles the creation, storage, retrieval, and management of User accounts.
 * 
 * This class provides functionalities for user registration, login, and persistence
 * of user data to a file (`Users.txt`). It manages users by username and ID.
 */
class UsersManager{
    std::unordered_map<std::string, User*> username_to_user_map; /**< Maps usernames to User objects for quick lookup. */
    std::map<int, User*> id_to_user_map; /**< Maps user IDs to User objects for quick lookup. */
    int last_id; /**< The last assigned user ID, used for generating new unique IDs. */

    /**
     * @brief Adds a user object to the internal maps.
     * @param user A pointer to the User object to be added.
     */
    void push_user(User* user);

    /**
     * @brief Clears all user data from memory.
     */
    void clear();
public:
    /**
     * @brief Gets a constant reference to the map of user IDs to User objects.
     * @return A constant reference to `id_to_user_map`.
     */
    const std::map<int, User*> &get_id_users_map()const;

    /**
     * @brief Retrieves a user by their ID.
     * @param id The ID of the user to retrieve.
     * @return A pointer to the User object if found, nullptr otherwise.
     */
    User* get_user_by_id(int id)const;

    /**
     * @brief Retrieves a user by their username.
     * @param username The username of the user to retrieve.
     * @return A pointer to the User object if found, nullptr otherwise.
     */
    User* get_user_by_username(const std::string &username)const;

    /**
     * @brief Attempts to log in a user with the given username and password.
     * @param user_name The username for login.
     * @param password The password for login.
     * @return A pointer to the logged-in User object if successful, nullptr otherwise.
     */
    User* log_in(const std::string &user_name, const std::string &password)const;

    /**
     * @brief Registers a new user with the provided details.
     * @param user_name The desired username.
     * @param password The desired password.
     * @param email The user's email address.
     * @param allow_anonymous True if the user allows anonymous questions, false otherwise.
     * @return A pointer to the newly created User object if successful, nullptr otherwise.
     */
    User* sign_up(const std::string &user_name, const std::string &password, const std::string &email, bool allow_anonymous);

    /**
     * @brief Lists all registered users in the system.
     */
    void list_system_users()const;

    /**
     * @brief Loads all user data from persistent storage (`Users.txt`).
     */
    void load_database();

    /**
     * @brief Updates all user data to persistent storage (`Users.txt`).
     */
    void update_database();

    /**
     * @brief Destructor for UsersManager. Cleans up dynamically allocated User objects.
     */
    ~UsersManager();
};