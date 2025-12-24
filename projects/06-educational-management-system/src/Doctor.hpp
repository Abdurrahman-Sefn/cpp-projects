/**
 * @file Doctor.hpp
 * @brief Defines the Doctor class for representing instructors in the Educational Management
 * System.
 */

#pragma once
#include <unordered_set>

#include "Course.hpp"

/**
 * @class Doctor
 * @brief Represents a doctor (instructor) in the educational system.
 *
 * This class stores a doctor's personal and account information, and manages the courses they
 * teach. It provides functionalities for authentication, course registration, and retrieving course
 * lists.
 */
class Doctor {
    std::string name;     /**< The full name of the doctor. */
    std::string email;    /**< The email address of the doctor. */
    std::string username; /**< The unique username for the doctor's account. */
    std::string password; /**< The password for the doctor's account. */
    std::unordered_set<const Course *>
        coursesSet; /**< A set of courses taught by this doctor for quick lookup. */
    std::vector<const Course *>
        registeredCourses; /**< A vector of courses taught by this doctor. */

    /**
     * @brief Adds a course to the doctor's list of taught courses.
     * @param course A constant pointer to the Course object to be added.
     */
    void addCourse(const Course *course);

   public:
    /**
     * @brief Constructor for the Doctor class.
     * @param username The username for the doctor's account.
     * @param password The password for the doctor's account.
     * @param name The full name of the doctor.
     * @param email The email address of the doctor.
     */
    Doctor(std::string username, std::string password, std::string name, std::string email);

    /**
     * @brief Verifies the provided username and password against the doctor's credentials.
     * @param username The username to verify.
     * @param password The password to verify.
     * @return True if the credentials match, false otherwise.
     */
    bool verify(const std::string &username, const std::string &password) const;

    /**
     * @brief Gets the full name of the doctor.
     * @return The doctor's full name.
     */
    const std::string &getName() const;

    /**
     * @brief Gets the username of the doctor.
     * @return The doctor's username.
     */
    const std::string &getUsername() const;

    /**
     * @brief Gets a constant reference to the vector of courses taught by this doctor.
     * @return A constant reference to `registered_courses`.
     */
    const std::vector<const Course *> &getCourses() const;

    /**
     * @brief Registers the doctor to teach a specific course.
     * @param course A constant pointer to the Course object to register for.
     */
    void registerInCourse(const Course *course);

    /**
     * @brief Checks if the doctor is registered to teach a specific course.
     * @param course A constant pointer to the Course object to check.
     * @return True if the doctor teaches the course, false otherwise.
     */
    bool isRegisteredInCourse(const Course *course) const;
};