/**
 * @file Course.hpp
 * @brief Defines the Course class for managing educational courses, assignments, and student progress.
 */

#pragma once
#include "Assignment.hpp"
#include "AssignmentSolution.hpp"
#include <deque>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Doctor;
class Student;

/**
 * @class Course
 * @brief Represents an educational course, managing its assignments, student enrollments, and assignment solutions.
 * 
 * This class handles the creation and management of assignments, tracks student submissions,
 * grades, and overall student performance within the context of a specific course.
 */
class Course{
    std::vector<const Assignment*> all_assignments; /**< List of all assignments for this course. */
    std::unordered_map<const Assignment*, std::vector<AssignmentSolution*>> all_assignment_solutions; /**< Maps assignments to all their submitted solutions. */
    std::unordered_map<const Assignment*, std::deque<AssignmentSolution*>> ungraded_assignments_queues; /**< Queues of ungraded solutions for each assignment. */
    std::unordered_map<const Student*, std::unordered_map<const Assignment*, AssignmentSolution*>> student_solutions_map; /**< Maps students to their solutions for each assignment. */
    std::unordered_map<const Student*, int> student_total_grade; /**< Maps students to their total grade in the course. */
    const Doctor* const doctor; /**< A constant pointer to the Doctor teaching this course. */
    std::string code; /**< Unique code for the course (e.g., CS101). */
    std::string name; /**< Name of the course (e.g., Programming 1). */
    int total_full_mark{}; /**< The sum of full marks of all assignments in the course. */

    /**
     * @brief Adds an assignment to the course.
     * @param assignment A pointer to the Assignment object to be added.
     */
    void push_assignment(const Assignment* assignment);

    /**
     * @brief Adds an assignment solution to the course's records.
     * @param sol A pointer to the AssignmentSolution object to be added.
     */
    void push_solution(AssignmentSolution* sol);

    /**
     * @brief Removes an assignment solution from the course's records.
     * @param sol A pointer to the AssignmentSolution object to be removed.
     */
    void remove_solution(const AssignmentSolution* sol);
public:
    /**
     * @brief Sets the grade for a specific assignment solution.
     * @param sol A pointer to the AssignmentSolution to be graded.
     * @param grade The grade to set.
     */
    void set_grade(AssignmentSolution* sol, int grade);

    /**
     * @brief Constructor for the Course class.
     * @param doctor A pointer to the Doctor teaching the course.
     * @param name The name of the course.
     * @param code The unique code of the course.
     */
    Course(const Doctor* doctor,const std::string &name, const std::string &code);

    /**
     * @brief Creates a new assignment for this course.
     * @param title The title of the assignment.
     * @param content The content of the assignment.
     * @param full_mark The full mark for the assignment.
     * @return A pointer to the newly created Assignment object.
     */
    Assignment* create_assignment(const std::string &title, const std::string &content, int full_mark);

    /**
     * @brief Gets the front solution from the ungraded queue for a specific assignment.
     * @param assignment A pointer to the Assignment.
     * @return A pointer to the AssignmentSolution at the front of the queue, or nullptr if the queue is empty.
     */
    AssignmentSolution* get_que_front(const Assignment* assignment)const;

    /**
     * @brief Removes the front solution from the ungraded queue for a specific assignment.
     * @param assignment A pointer to the Assignment.
     */
    void pop_que_front(const Assignment* assignment);

    /**
     * @brief Checks if a student has submitted a solution for a given assignment.
     * @param s A pointer to the Student.
     * @param assignment A pointer to the Assignment.
     * @return True if the student has submitted, false otherwise.
     */
    bool is_assignment_submitted(const Student* s,const Assignment* assignment)const;

    /**
     * @brief Handles a student submitting a solution for an assignment.
     * @param s A pointer to the Student submitting.
     * @param assignment A pointer to the Assignment.
     * @param answer The student's answer.
     * @return True if the submission was successful, false otherwise.
     */
    bool submit_assignment(const Student* s, const Assignment* assignment, const std::string &answer);

    /**
     * @brief Lists a student's assignments for this course.
     * @param s A pointer to the Student.
     * @param assignments A vector of assignments to list.
     * @param tabs The number of tabs to indent the output.
     */
    void list_student_assignments(const Student* s,const std::vector<const Assignment*> &assignments, int tabs)const;

    /**
     * @brief Handles a student unregistering from the course.
     * @param s A pointer to the Student.
     */
    void student_unregister(const Student* s);

    /**
     * @brief Handles a student registering for the course.
     * @param s A pointer to the Student.
     */
    void student_register(const Student* s);

    /**
     * @brief Shows a student's total grade in the course.
     * @param s A pointer to the Student.
     */
    void show_student_grade(const Student* s)const;

    /**
     * @brief Prints a summary of the course information.
     */
    void print()const;

    /**
     * @brief Prints detailed information about the course, including its assignments.
     */
    void print_detailed()const;

    /**
     * @brief Gets a list of assignments that are currently available for submission.
     * @return A vector of constant pointers to available Assignment objects.
     */
    std::vector<const Assignment*> get_available_assignments()const;

    /**
     * @brief Gets a list of all assignments for this course.
     * @return A constant reference to a vector of constant pointers to all Assignment objects.
     */
    const std::vector<const Assignment*> &get_all_assignments()const;
    
    /**
     * @brief Gets the name of the course.
     * @return The course name.
     */
    std::string get_course_name()const;

    /**
     * @brief Gets the code of the course.
     * @return The course code.
     */
    std::string get_course_code()const;

    /**
     * @brief Lists assignments for a doctor.
     * @param assignments A vector of assignments to list.
     * @param tabs The number of tabs to indent the output.
     * @param numbered If true, assignments are printed with numbers.
     */
    void list_doctor_assignments(const std::vector<const Assignment*> &assignments, int tabs, bool numbered)const;

    /**
     * @brief Lists the grades report for a specific assignment.
     * @param assignment A pointer to the Assignment.
     * @param tabs The number of tabs to indent the output.
     */
    void list_assignment_grades_report(const Assignment* assignment, int tabs)const;

    /**
     * @brief Gets all assignment solutions for a given assignment.
     * @param assignment A pointer to the Assignment.
     * @return A constant reference to a vector of AssignmentSolution pointers.
     */
    const std::vector<AssignmentSolution*> &get_all_assignment_solutions(const Assignment*)const;

    /**
     * @brief Destructor for the Course class. Cleans up dynamically allocated Assignment and AssignmentSolution objects.
     */
    ~Course();
};