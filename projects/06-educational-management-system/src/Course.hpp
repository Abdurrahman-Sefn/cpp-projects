/**
 * @file Course.hpp
 * @brief Defines the Course class for managing educational courses, assignments, and student
 * progress.
 */

#pragma once
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Assignment.hpp"
#include "AssignmentSolution.hpp"

class Doctor;
class Student;

/**
 * @class Course
 * @brief Represents an educational course, managing its assignments, student enrollments, and
 * assignment solutions.
 *
 * This class handles the creation and management of assignments, tracks student submissions,
 * grades, and overall student performance within the context of a specific course.
 */
class Course {
    std::vector<const Assignment*> allAssignments; /**< List of all assignments for this course. */
    std::unordered_map<const Assignment*, std::vector<AssignmentSolution*>>
        allAssignmentSolutions; /**< Maps assignments to all their submitted solutions. */
    std::unordered_map<const Assignment*, std::deque<AssignmentSolution*>>
        ungradedAssignmentsQueues; /**< Queues of ungraded solutions for each assignment. */
    std::unordered_map<const Student*, std::unordered_map<const Assignment*, AssignmentSolution*>>
        studentSolutionsMap; /**< Maps students to their solutions for each assignment. */
    std::unordered_map<const Student*, int>
        studentTotalGrade;      /**< Maps students to their total grade in the course. */
    const Doctor* const doctor; /**< A constant pointer to the Doctor teaching this course. */
    std::string code;           /**< Unique code for the course (e.g., CS101). */
    std::string name;           /**< Name of the course (e.g., Programming 1). */
    int totalFullMark{};        /**< The sum of full marks of all assignments in the course. */

    /**
     * @brief Adds an assignment to the course.
     * @param assignment A pointer to the Assignment object to be added.
     */
    void addAssignment(const Assignment* assignment);

    /**
     * @brief Adds an assignment solution to the course's records.
     * @param sol A pointer to the AssignmentSolution object to be added.
     */
    void addSolution(AssignmentSolution* sol);

    /**
     * @brief Removes an assignment solution from the course's records.
     * @param sol A pointer to the AssignmentSolution object to be removed.
     */
    void removeSolution(const AssignmentSolution* sol);

   public:
    /**
     * @brief Sets the grade for a specific assignment solution.
     * @param sol A pointer to the AssignmentSolution to be graded.
     * @param grade The grade to set.
     */
    void setGrade(AssignmentSolution* sol, int grade);

    /**
     * @brief Constructor for the Course class.
     * @param doctor A pointer to the Doctor teaching the course.
     * @param name The name of the course.
     * @param code The unique code of the course.
     */
    Course(const Doctor* doctor, const std::string& name, const std::string& code);

    /**
     * @brief Creates a new assignment for this course.
     * @param title The title of the assignment.
     * @param content The content of the assignment.
     * @param fullMark The full mark for the assignment.
     * @return A pointer to the newly created Assignment object.
     */
    Assignment* createAssignment(const std::string& title, const std::string& content,
                                 int fullMark);

    /**
     * @brief Gets the front solution from the ungraded queue for a specific assignment.
     * @param assignment A pointer to the Assignment.
     * @return A pointer to the AssignmentSolution at the front of the queue, or nullptr if the
     * queue is empty.
     */
    AssignmentSolution* getQueueFront(const Assignment* assignment) const;

    /**
     * @brief Removes the front solution from the ungraded queue for a specific assignment.
     * @param assignment A pointer to the Assignment.
     */
    void popQueueFront(const Assignment* assignment);

    /**
     * @brief Checks if a student has submitted a solution for a given assignment.
     * @param s A pointer to the Student.
     * @param assignment A pointer to the Assignment.
     * @return True if the student has submitted, false otherwise.
     */
    bool isAssignmentSubmitted(const Student* s, const Assignment* assignment) const;

    /**
     * @brief Handles a student submitting a solution for an assignment.
     * @param s A pointer to the Student submitting.
     * @param assignment A pointer to the Assignment.
     * @param answer The student's answer.
     * @return True if the submission was successful, false otherwise.
     */
    bool submitAssignment(const Student* s, const Assignment* assignment,
                          const std::string& answer);

    /**
     * @brief Lists a student's assignments for this course.
     * @param s A pointer to the Student.
     * @param assignments A vector of assignments to list.
     * @param tabs The number of tabs to indent the output.
     */
    void listStudentAssignments(const Student* s, const std::vector<const Assignment*>& assignments,
                                int tabs) const;

    /**
     * @brief Handles a student unregistering from the course.
     * @param s A pointer to the Student.
     */
    void unregisterStudent(const Student* s);

    /**
     * @brief Handles a student registering for the course.
     * @param s A pointer to the Student.
     */
    void registerStudent(const Student* s);

    /**
     * @brief Shows a student's total grade in the course.
     * @param s A pointer to the Student.
     */
    void showStudentGrade(const Student* s) const;

    /**
     * @brief Prints a summary of the course information.
     */
    void print() const;

    /**
     * @brief Prints detailed information about the course, including its assignments.
     */
    void printDetailed() const;

    /**
     * @brief Gets a list of assignments that are currently available for submission.
     * @return A vector of constant pointers to available Assignment objects.
     */
    std::vector<const Assignment*> getAvailableAssignments() const;

    /**
     * @brief Gets a list of all assignments for this course.
     * @return A constant reference to a vector of constant pointers to all Assignment objects.
     */
    const std::vector<const Assignment*>& getAllAssignments() const;

    /**
     * @brief Gets the name of the course.
     * @return The course name.
     */
    std::string getCourseName() const;

    /**
     * @brief Gets the code of the course.
     * @return The course code.
     */
    std::string getCourseCode() const;

    /**
     * @brief Lists assignments for a doctor.
     * @param assignments A vector of assignments to list.
     * @param tabs The number of tabs to indent the output.
     * @param numbered If true, assignments are printed with numbers.
     */
    void listDoctorAssignments(const std::vector<const Assignment*>& assignments, int tabs,
                               bool numbered) const;

    /**
     * @brief Lists the grades report for a specific assignment.
     * @param assignment A pointer to the Assignment.
     * @param tabs The number of tabs to indent the output.
     */
    void listAssignmentGradesReport(const Assignment* assignment, int tabs) const;

    /**
     * @brief Gets all assignment solutions for a given assignment.
     * @param assignment A pointer to the Assignment.
     * @return A constant reference to a vector of AssignmentSolution pointers.
     */
    const std::vector<AssignmentSolution*>& getAllAssignmentSolutions(const Assignment*) const;

    /**
     * @brief Destructor for the Course class. Cleans up dynamically allocated Assignment and
     * AssignmentSolution objects.
     */
    ~Course();
};