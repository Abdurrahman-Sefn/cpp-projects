/**
 * @file EducationalManageMentSystem.hpp
 * @brief Defines the main EducationalManagemenentSystem class and related enumerations.
 */

#pragma once
#include "DoctorSession.hpp"
#include "MenuHandler.hpp"
#include "StudentSession.hpp"
#include "UsersManager.hpp"

/**
 * @enum SystemMainMenuChoice
 * @brief Enumerates the choices available in the system's main menu.
 */
enum class SystemMainMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    Login = 1, /**< Option to log in to the system. */
    SignUp,    /**< Option to sign up for a new account. */
    Exit,      /**< Option to shut down the system. */

};

/**
 * @enum EnterMenuChoice
 * @brief Enumerates the choices available when selecting user type for login/signup.
 */
enum class EnterMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    Student = 1, /**< Option to proceed as a student. */
    Doctor,      /**< Option to proceed as a doctor. */
    Back,        /**< Option to go back to the previous menu. */

};

/**
 * @class EducationalManagemenentSystem
 * @brief The main class for the Educational Management System.
 *
 * This class orchestrates the entire system, managing user authentication (login/signup),
 * user sessions (student/doctor), and the overall flow of the application.
 */
class EducationalManagemenentSystem {
    UsersManager usersManager;     /**< Manages all user accounts (students and doctors). */
    CoursesManager coursesManager; /**< Manages all courses in the system. */
    Student* currentStudent{};     /**< Pointer to the currently logged-in Student. */
    Doctor* currentDoctor{};       /**< Pointer to the currently logged-in Doctor. */

    // Menu handlers
    const MenuHandler<SystemMainMenuChoice>
        mainMenuHandler; /**< Menu handler for the system's main menu. */
    const MenuHandler<EnterMenuChoice>
        enterMenuHandler; /**< Menu handler for the user type selection menu. */

    /**
     * @brief Displays the system's main menu and gets the user's choice.
     * @return The chosen SystemMainMenuChoice enum value.
     */
    SystemMainMenuChoice showSystemMenu();

    /**
     * @brief Handles the login/signup process, allowing users to choose their role.
     * @return True if a user successfully logs in or signs up, false otherwise.
     */
    bool enter();

    /**
     * @brief Handles the user login process.
     */
    void login();

    /**
     * @brief Handles the user signup process.
     */
    void signup();

    /**
     * @brief Loads dummy data into the system for testing or initial setup.
     */
    void loadDummyData();

   public:
    /**
     * @brief Constructor for EducationalManagemenentSystem. Initializes managers and loads dummy
     * data.
     */
    EducationalManagemenentSystem();

    /**
     * @brief Runs the main loop of the educational management system.
     */
    void run();
};