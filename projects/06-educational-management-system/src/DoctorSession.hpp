/**
 * @file DoctorSession.hpp
 * @brief Defines the DoctorSession class and related enumerations for managing a doctor's
 * interaction with the Educational Management System.
 */

#pragma once
#include "CoursesManager.hpp"
#include "MenuHandler.hpp"

/**
 * @enum DoctorMainMenuChoice
 * @brief Enumerates the choices available in the doctor's main menu.
 */
enum class DoctorMainMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    ListCourses = 1, /**< Option to list courses taught by the doctor. */
    CreateCourse,    /**< Option to create a new course. */
    ViewCourse,      /**< Option to view details of a specific course. */
    Logout,          /**< Option to log out of the doctor's session. */

};

/**
 * @enum DoctorViewCourseMenuChoice
 * @brief Enumerates the choices available when viewing a specific course as a doctor.
 */
enum class DoctorViewCourseMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    ListAssignments = 1, /**< Option to list assignments for the current course. */
    CreateAssignment,    /**< Option to create a new assignment for the current course. */
    ViewAssignment,      /**< Option to view details of a specific assignment. */
    Back,                /**< Option to go back to the previous menu. */

};

/**
 * @enum DoctorViewAssignmentMenuChoice
 * @brief Enumerates the choices available when viewing a specific assignment as a doctor.
 */
enum class DoctorViewAssignmentMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    PrintContent = 1,      /**< Option to print the content of the assignment. */
    ListGradesReport,      /**< Option to list the grades report for the assignment. */
    ViewSolutionFromQueue, /**< Option to view an ungraded solution from the queue. */
    PopSolutionFromQueue,  /**< Option to pop (remove) a solution from the ungraded queue. */
    ListSolutions,         /**< Option to list all submitted solutions for the assignment. */
    ViewSolution,          /**< Option to view a specific submitted solution. */
    Back,                  /**< Option to go back to the previous menu. */

};

/**
 * @enum DoctorViewSolutionMenuChoice
 * @brief Enumerates the choices available when viewing a specific assignment solution as a doctor.
 */
enum class DoctorViewSolutionMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    PrintContent = 1, /**< Option to print the content of the solution. */
    SetGrade,         /**< Option to set the grade for the solution. */
    SetComment,       /**< Option to set a comment for the solution. */
    Back,             /**< Option to go back to the previous menu. */

};

/**
 * @class DoctorSession
 * @brief Manages the interactive session for a logged-in doctor.
 *
 * This class handles the display of menus, processing of doctor choices, and execution of actions
 * related to course management, assignment creation, and grading student solutions.
 */
class DoctorSession {
   private:
    Doctor* currentDoctor{}; /**< Pointer to the currently logged-in Doctor. */
    CoursesManager&
        coursesManager; /**< Reference to the CoursesManager for course-related operations. */

    // Menu handlers
    const MenuHandler<DoctorMainMenuChoice>
        mainMenuHandler; /**< Menu handler for the doctor's main menu. */
    const MenuHandler<DoctorViewCourseMenuChoice>
        courseMenuHandler; /**< Menu handler for the course view menu. */
    const MenuHandler<DoctorViewAssignmentMenuChoice>
        assignmentMenuHandler; /**< Menu handler for the assignment view menu. */
    const MenuHandler<DoctorViewSolutionMenuChoice>
        solutionMenuHandler; /**< Menu handler for the solution view menu. */

    /**
     * @brief Displays the doctor's main menu and gets the user's choice.
     * @return The chosen DoctorMainMenuChoice enum value.
     */
    DoctorMainMenuChoice showMainMenu();

    /**
     * @brief Displays the course view menu and gets the user's choice.
     * @param course A pointer to the current Course being viewed.
     * @return The chosen DoctorViewCourseMenuChoice enum value.
     */
    DoctorViewCourseMenuChoice viewCourseMenu(Course* course);

    /**
     * @brief Displays the assignment view menu and gets the user's choice.
     * @param assignment A constant pointer to the current Assignment being viewed.
     * @return The chosen DoctorViewAssignmentMenuChoice enum value.
     */
    DoctorViewAssignmentMenuChoice viewAssignmentMenu(const Assignment* assignment);

    /**
     * @brief Displays the solution view menu and gets the user's choice.
     * @param sol A pointer to the current AssignmentSolution being viewed.
     * @return The chosen DoctorViewSolutionMenuChoice enum value.
     */
    DoctorViewSolutionMenuChoice viewSolutionMenu(AssignmentSolution* sol);

    /**
     * @brief Handles the doctor logout process.
     */
    void logout();

    /**
     * @brief Lists all courses taught by the current doctor.
     */
    void listCourses();

    /**
     * @brief Handles the creation of a new course by the doctor.
     */
    void createCourse();

    /**
     * @brief Allows the doctor to set a grade for an assignment solution.
     * @param course A pointer to the Course the assignment belongs to.
     * @param sol A pointer to the AssignmentSolution to be graded.
     */
    void gradeSolution(Course* course, AssignmentSolution* sol);

    /**
     * @brief Allows the doctor to add a comment to an assignment solution.
     * @param sol A pointer to the AssignmentSolution to be commented on.
     */
    void addComment(AssignmentSolution* sol);

    /**
     * @brief Views an assignment solution from the ungraded queue.
     * @param curCourse A pointer to the current Course.
     * @param assignment A constant pointer to the Assignment.
     */
    void viewSolutionFromQueue(Course* curCourse, const Assignment* assignment);

    /**
     * @brief Lists all submitted solutions for a given assignment.
     * @param assignment A constant pointer to the Assignment.
     */
    void listSolutions(const Assignment* assignment);

    /**
     * @brief Lists all assignments for a given course.
     * @param course A pointer to the Course.
     */
    void listAssignments(Course* course);

    /**
     * @brief Handles the creation of a new assignment for a given course.
     * @param course A pointer to the Course.
     */
    void createAssignment(Course* course);

    /**
     * @brief Runs the course viewing menu loop.
     */
    void runViewCourseMenu();

    /**
     * @brief Runs the assignment viewing menu loop.
     * @param course A pointer to the current Course.
     */
    void runViewAssignmentMenu(Course* course);

    /**
     * @brief Runs the solution viewing menu loop.
     * @param curCourse A pointer to the current Course.
     * @param assignment A constant pointer to the current Assignment.
     * @param selectedBefore A pointer to an AssignmentSolution that might have been selected
     * previously.
     */
    void runViewSolutionMenu(Course* curCourse, const Assignment* assignment,
                             AssignmentSolution* selectedBefore = nullptr);

   public:
    /**
     * @brief Runs the main menu loop for the doctor's session.
     */
    void runMainMenu();

    /**
     * @brief Constructor for DoctorSession.
     * @param coursesManager A reference to the CoursesManager.
     * @param currentDoctor A pointer to the currently logged-in Doctor.
     */
    DoctorSession(CoursesManager& coursesManager, Doctor* currentDoctor);
};
