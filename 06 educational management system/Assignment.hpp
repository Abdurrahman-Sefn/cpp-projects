/**
 * @file Assignment.hpp
 * @brief Defines the Assignment class for managing course assignments in the Educational Management System.
 */

#pragma once
#include <iostream>
#include <vector>
class Course;
class AssignmentSolution;

/**
 * @class Assignment
 * @brief Represents an assignment within a course, including its content, title, full mark, and submission status.
 * 
 * This class stores details about an assignment and provides methods for printing its content,
 * listing submitted solutions, and checking if it's available for submission.
 */
class Assignment{
    std::string content; /**< The detailed content or description of the assignment. */
    std::string title; /**< The title of the assignment. */
    int full_mark; /**< The maximum possible score for the assignment. */
    bool is_available_to_submit = true; /**< Flag indicating if the assignment is currently open for submissions. */
    const Course* const course; /**< A constant pointer to the parent Course this assignment belongs to. */
public:
    /**
     * @brief Prints the content of the assignment.
     * @param tabs The number of tabs to indent the output.
     */
    void print_content(int tabs)const;

    /**
     * @brief Prints a summary of the assignment's details.
     * @param tabs The number of tabs to indent the output.
     */
    void print(int tabs)const;

    /**
     * @brief Lists the solutions submitted for this assignment.
     * @param solutions A vector of pointers to AssignmentSolution objects.
     * @param tabs The number of tabs to indent the output.
     * @param numbered If true, solutions are printed with numbers.
     */
    void list_solutions(const std::vector<AssignmentSolution*> &solutions, int tabs, bool numbered)const;

    /**
     * @brief Checks if the assignment is currently available for submission.
     * @return True if submissions are allowed, false otherwise.
     */
    bool can_submit()const;

    /**
     * @brief Constructor for the Assignment class.
     * @param course A pointer to the parent Course.
     * @param title The title of the assignment.
     * @param content The content of the assignment.
     * @param full_mark The full mark for the assignment.
     */
    Assignment(const Course* course, const std::string &title, const std::string &content, int full_mark);

    /**
     * @brief Gets the full mark for the assignment.
     * @return The full mark.
     */
    int get_full_mark()const;

    /**
     * @brief Gets the title of the assignment.
     * @return The title of the assignment.
     */
    const std::string &get_title()const;

    /**
     * @brief Gets a pointer to the parent course.
     * @return A constant pointer to the Course object.
     */
    const Course* get_parent_course()const;
};