/**
 * @file Student.hpp
 * @brief Defines the Student class for representing students in the Educational Management System.
 */

#pragma once
#include "Course.hpp"
#include <unordered_set>


/**
 * @class Student
 * @brief Represents a student in the educational system.
 * 
 * This class stores a student's personal and account information, and manages the courses they are registered in.
 * It provides functionalities for authentication, course registration/unregistration, and viewing grades.
 */
class Student{
    std::string name; /**< The full name of the student. */
    std::string email; /**< The email address of the student. */
    std::string username; /**< The unique username for the student's account. */
    std::string password; /**< The password for the student's account. */
    std::unordered_set<const Course*> courses_set; /**< A set of courses the student is registered in for quick lookup. */
    std::vector<const Course*> registered_courses; /**< A vector of courses the student is registered in. */

    /**
     * @brief Adds a course to the student's list of registered courses.
     * @param course A constant pointer to the Course object to be added.
     */
    void push_course(const Course* course);

    /**
     * @brief Removes a course from the student's list of registered courses.
     * @param course A constant pointer to the Course object to be removed.
     */
    void remove_course(const Course* course);
public:
    /**
     * @brief Constructor for the Student class.
     * @param usrname The username for the student's account.
     * @param password The password for the student's account.
     * @param name The full name of the student.
     * @param email The email address of the student.
     */
    Student(std::string usrname, std::string password, std::string name, std::string email);

    /**
     * @brief Verifies the provided username and password against the student's credentials.
     * @param usrname The username to verify.
     * @param password The password to verify.
     * @return True if the credentials match, false otherwise.
     */
    bool verify(const std::string &usrname, const std::string &password)const;

    /**
     * @brief Gets the full name of the student.
     * @return The student's full name.
     */
    const std::string &get_name()const;

    /**
     * @brief Gets the username of the student.
     * @return The student's username.
     */
    const std::string &get_usrname()const;

    /**
     * @brief Checks if the student is registered in a specific course.
     * @param course A constant pointer to the Course object to check.
     * @return True if the student is registered in the course, false otherwise.
     */
    bool is_registered_in_course(const Course* course)const;

    /**
     * @brief Gets a constant reference to the vector of courses the student is registered in.
     * @return A constant reference to `registered_courses`.
     */
    const std::vector<const Course*> &get_courses()const;

    /**
     * @brief Registers the student in a specific course.
     * @param course A constant pointer to the Course object to register in.
     */
    void register_in_course(const Course* course);

    /**
     * @brief Unregisters the student from a specific course.
     * @param course A constant pointer to the Course object to unregister from.
     */
    void unregister_from_course(const Course* course);

    /**
     * @brief Shows the student's total grades report for all registered courses.
     * @param tabs The number of tabs to indent the output.
     */
    void show_total_grades_report(int tabs)const;
};