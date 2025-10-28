/**
 * @file AssignmentSolution.hpp
 * @brief Defines the AssignmentSolution class for managing student submissions to assignments.
 */

#pragma once
#include "Assignment.hpp"

class Student;

/**
 * @class AssignmentSolution
 * @brief Represents a student's submitted solution to an assignment, including their answer, grade, and comments.
 * 
 * This class links a specific student to their submission for a particular assignment.
 * It allows for setting grades and comments, and provides methods to access submission details.
 */
class AssignmentSolution{
    const Assignment* const assignment; /**< A constant pointer to the Assignment this solution is for. */
    const Student* const student; /**< A constant pointer to the Student who submitted this solution. */
    std::string answer; /**< The student's answer or content of the submission. */
    std::string comment; /**< Comments provided by the grader (e.g., doctor). */
    int grade{-1}; /**< The grade received for the assignment. -1 indicates not yet graded. */
public:
    /**
     * @brief Sets the grade for the assignment solution.
     * @param grade The grade to be set.
     */
    void set_grade(int grade);

    /**
     * @brief Sets the comment for the assignment solution.
     * @param comment The comment string to be set.
     */
    void set_comment(std::string comment);

    /**
     * @brief Prints the content of the assignment solution (the student's answer).
     * @param tabs The number of tabs to indent the output.
     */
    void print_content(int tabs)const;

    /**
     * @brief Prints the student's grade for this assignment solution.
     * @param tabs The number of tabs to indent the output.
     */
    void print_student_grade(int tabs)const;

    /**
     * @brief Gets a pointer to the assignment associated with this solution.
     * @return A constant pointer to the Assignment object.
     */
    const Assignment* get_assignment()const;

    /**
     * @brief Gets a pointer to the student who submitted this solution.
     * @return A constant pointer to the Student object.
     */
    const Student* get_student()const;

    /**
     * @brief Constructor for the AssignmentSolution class.
     * @param assignment A pointer to the Assignment.
     * @param student A pointer to the Student.
     * @param answer The student's submitted answer.
     */
    AssignmentSolution(const Assignment* assignment, const Student* student, std::string answer);

    /**
     * @brief Checks if the assignment solution has been graded.
     * @return True if a grade has been set, false otherwise.
     */
    bool is_graded()const;

    /**
     * @brief Gets the comment associated with the solution.
     * @return A constant reference to the comment string.
     */
    const std::string &get_comment()const;

    /**
     * @brief Gets the grade received for the solution.
     * @return The integer grade.
     */
    int get_grade()const;

    /**
     * @brief Gets the full mark of the associated assignment.
     * @return The full mark.
     */
    int get_full_mark()const;

    /**
     * @brief Updates the student's answer for the assignment solution.
     * @param new_answer The new answer string.
     */
    void update_answer(const std::string &new_answer);
};