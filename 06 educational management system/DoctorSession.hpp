/**
 * @file DoctorSession.hpp
 * @brief Defines the DoctorSession class and related enumerations for managing a doctor's interaction with the Educational Management System.
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
    CreateCourse, /**< Option to create a new course. */
    ViewCourse, /**< Option to view details of a specific course. */
    Logout, /**< Option to log out of the doctor's session. */

};

/**
 * @enum DoctorViewCourseMenuChoice
 * @brief Enumerates the choices available when viewing a specific course as a doctor.
 */
enum class DoctorViewCourseMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    ListAssignments = 1, /**< Option to list assignments for the current course. */
    CreateAssignment, /**< Option to create a new assignment for the current course. */
    ViewAssignment, /**< Option to view details of a specific assignment. */
    Back, /**< Option to go back to the previous menu. */

};

/**
 * @enum DoctorViewAssignmentMenuChoice
 * @brief Enumerates the choices available when viewing a specific assignment as a doctor.
 */
enum class DoctorViewAssignmentMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    PrintContent = 1, /**< Option to print the content of the assignment. */
    ListGradesReport, /**< Option to list the grades report for the assignment. */
    ViewSolutionFromQueue, /**< Option to view an ungraded solution from the queue. */
    PopSolutionFromQueue, /**< Option to pop (remove) a solution from the ungraded queue. */
    ListSolutions, /**< Option to list all submitted solutions for the assignment. */
    ViewSolution, /**< Option to view a specific submitted solution. */
    Back, /**< Option to go back to the previous menu. */

};

/**
 * @enum DoctorViewSolutionMenuChoice
 * @brief Enumerates the choices available when viewing a specific assignment solution as a doctor.
 */
enum class DoctorViewSolutionMenuChoice {
    InvalidChoice = 0, /**< Represents an invalid menu choice. */

    PrintContent = 1, /**< Option to print the content of the solution. */
    SetGrade, /**< Option to set the grade for the solution. */
    SetComment, /**< Option to set a comment for the solution. */
    Back, /**< Option to go back to the previous menu. */

};

/**
 * @class DoctorSession
 * @brief Manages the interactive session for a logged-in doctor.
 * 
 * This class handles the display of menus, processing of doctor choices, and execution of actions
 * related to course management, assignment creation, and grading student solutions.
 */
class DoctorSession
{

private:
    Doctor* cur_doctor{}; /**< Pointer to the currently logged-in Doctor. */
    CoursesManager &courses_manager; /**< Reference to the CoursesManager for course-related operations. */

    // Menu handlers
    const MenuHandler<DoctorMainMenuChoice> main_menu_handler; /**< Menu handler for the doctor's main menu. */
    const MenuHandler<DoctorViewCourseMenuChoice> course_menu_handler; /**< Menu handler for the course view menu. */
    const MenuHandler<DoctorViewAssignmentMenuChoice> assignment_menu_handler; /**< Menu handler for the assignment view menu. */
    const MenuHandler<DoctorViewSolutionMenuChoice> solution_menu_handler; /**< Menu handler for the solution view menu. */

    /**
     * @brief Displays the doctor's main menu and gets the user's choice.
     * @return The chosen DoctorMainMenuChoice enum value.
     */
    DoctorMainMenuChoice main_menu();

    /**
     * @brief Displays the course view menu and gets the user's choice.
     * @param course A pointer to the current Course being viewed.
     * @return The chosen DoctorViewCourseMenuChoice enum value.
     */
    DoctorViewCourseMenuChoice view_course_menu(Course* course);

    /**
     * @brief Displays the assignment view menu and gets the user's choice.
     * @param assignment A constant pointer to the current Assignment being viewed.
     * @return The chosen DoctorViewAssignmentMenuChoice enum value.
     */
    DoctorViewAssignmentMenuChoice view_assignment_menu(const Assignment* assignment);

    /**
     * @brief Displays the solution view menu and gets the user's choice.
     * @param sol A pointer to the current AssignmentSolution being viewed.
     * @return The chosen DoctorViewSolutionMenuChoice enum value.
     */
    DoctorViewSolutionMenuChoice view_solution_menu(AssignmentSolution* sol);

    /**
     * @brief Handles the doctor logout process.
     */
    void logout();

    /**
     * @brief Lists all courses taught by the current doctor.
     */
    void list_courses();

    /**
     * @brief Handles the creation of a new course by the doctor.
     */
    void create_course();

    /**
     * @brief Allows the doctor to set a grade for an assignment solution.
     * @param course A pointer to the Course the assignment belongs to.
     * @param sol A pointer to the AssignmentSolution to be graded.
     */
    void make_grade(Course* course, AssignmentSolution* sol);

    /**
     * @brief Allows the doctor to add a comment to an assignment solution.
     * @param sol A pointer to the AssignmentSolution to be commented on.
     */
    void make_comment(AssignmentSolution* sol);

    /**
     * @brief Views an assignment solution from the ungraded queue.
     * @param cur_course A pointer to the current Course.
     * @param assignment A constant pointer to the Assignment.
     */
    void view_a_solution_from_queue(Course* cur_course, const Assignment* assignment);

    /**
     * @brief Lists all submitted solutions for a given assignment.
     * @param assignment A constant pointer to the Assignment.
     */
    void list_solutions(const Assignment* assignment);

    /**
     * @brief Lists all assignments for a given course.
     * @param course A pointer to the Course.
     */
    void list_assignments(Course* course);

    /**
     * @brief Handles the creation of a new assignment for a given course.
     * @param course A pointer to the Course.
     */
    void create_assignment(Course* course);

    /**
     * @brief Runs the course viewing menu loop.
     */
    void run_view_course_menu();

    /**
     * @brief Runs the assignment viewing menu loop.
     * @param course A pointer to the current Course.
     */
    void run_view_assignment_menu(Course* course);

    /**
     * @brief Runs the solution viewing menu loop.
     * @param cur_course A pointer to the current Course.
     * @param assignment A constant pointer to the current Assignment.
     * @param selected_before A pointer to an AssignmentSolution that might have been selected previously.
     */
    void run_view_solution_menu(Course* cur_course, const Assignment* assignment,  AssignmentSolution* selected_before = nullptr);
public:
    /**
     * @brief Runs the main menu loop for the doctor's session.
     */
    void run_main_menu();

    /**
     * @brief Constructor for DoctorSession.
     * @param courses_manager A reference to the CoursesManager.
     * @param cur_doctor A pointer to the currently logged-in Doctor.
     */
    DoctorSession(CoursesManager &courses_manager, Doctor* cur_doctor);
};

