/**
 * @file StudentSession.hpp
 * @brief Defines the StudentSession class and related enumerations for managing a student's
 * interaction with the Educational Management System.
 */

#pragma once
#include "CoursesManager.hpp"
#include "MenuHandler.hpp"

/**
 * @enum StudentMainMenuChoice
 * @brief Enumerates the choices available in the student's main menu.
 */
enum class StudentMainMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    RegisterInCourse = 1, /**< Option to register in a new course. */
    ListMyCourses,        /**< Option to list courses the student is registered in. */
    ViewCourse,           /**< Option to view details of a specific course. */
    GradesReport,         /**< Option to view the student's grades report. */
    Logout,               /**< Option to log out of the student's session. */

};

/**
 * @enum StudentViewCourseMenuChoice
 * @brief Enumerates the choices available when viewing a specific course as a student.
 */
enum class StudentViewCourseMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    Unregister = 1, /**< Option to unregister from the current course. */
    SubmitSolution, /**< Option to submit a solution for an assignment in the current course. */
    Back,           /**< Option to go back to the previous menu. */

};

/**
 * @class StudentSession
 * @brief Manages the interactive session for a logged-in student.
 *
 * This class handles the display of menus, processing of student choices, and execution of actions
 * related to course registration, assignment submission, and viewing grades.
 */
class StudentSession {
   private:
    Student* currentStudent{}; /**< Pointer to the currently logged-in Student. */
    const CoursesManager&
        coursesManager; /**< Reference to the CoursesManager for course-related operations. */

    // Menu handlers
    const MenuHandler<StudentMainMenuChoice>
        mainMenuHandler; /**< Menu handler for the student's main menu. */
    const MenuHandler<StudentViewCourseMenuChoice>
        courseMenuHandler; /**< Menu handler for the course view menu. */

    /**
     * @brief Lists all courses the current student is registered in.
     */
    void listRegisteredCourses();

    /**
     * @brief Displays the student's grades report.
     */
    void showGradesReport();

    /**
     * @brief Displays the student's main menu and gets the user's choice.
     * @return The chosen StudentMainMenuChoice enum value.
     */
    StudentMainMenuChoice showMainMenu();

    /**
     * @brief Handles the student logout process.
     */
    void logout();

    /**
     * @brief Handles the process of a student registering in a course.
     */
    void registerInCourse();

    /**
     * @brief Handles the process of a student unregistering from a course.
     * @param course A pointer to the Course to unregister from.
     */
    void unregisterFromCourse(Course* course);

    /**
     * @brief Handles the process of a student submitting an assignment.
     * @param course A pointer to the Course the assignment belongs to.
     */
    void submitAssignment(Course* course);

    /**
     * @brief Displays the course view menu and gets the user's choice.
     * @param course A pointer to the current Course being viewed.
     * @return The chosen StudentViewCourseMenuChoice enum value.
     */
    StudentViewCourseMenuChoice viewCourseMenu(Course* course);

    /**
     * @brief Runs the course viewing menu loop for the student.
     */
    void runViewCourseMenu();

   public:
    /**
     * @brief Constructor for StudentSession.
     * @param coursesManager A reference to the CoursesManager.
     * @param currentStudent A pointer to the currently logged-in Student.
     */
    StudentSession(CoursesManager& coursesManager, Student* currentStudent);

    /**
     * @brief Runs the main menu loop for the student's session.
     */
    void runMainMenu();
};
