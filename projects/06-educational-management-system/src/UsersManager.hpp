/**
 * @file UsersManager.hpp
 * @brief Manages user accounts (students and doctors) for the Educational Management System.
 */

#pragma once
#include "Course.hpp"
#include "Doctor.hpp"
#include "Student.hpp"

/**
 * @class UsersManager
 * @brief Handles the creation, storage, retrieval, and management of both Student and Doctor
 * accounts.
 *
 * This class provides functionalities for user registration, login, and managing user data
 * for both student and doctor roles within the educational system.
 */
class UsersManager {
   private:
    std::unordered_map<std::string, Student*>
        usernameToStudentMap; /**< Maps usernames to Student objects. */
    std::unordered_map<std::string, Doctor*>
        usernameToDoctorMap; /**< Maps usernames to Doctor objects. */

    /**
     * @brief Adds a student object to the internal map.
     * @param student A pointer to the Student object to be added.
     */
    void addStudent(Student* student);

    /**
     * @brief Adds a doctor object to the internal map.
     * @param doctor A pointer to the Doctor object to be added.
     */
    void addDoctor(Doctor* doctor);

   public:
    /**
     * @brief Retrieves a student by their username.
     * @param username The username of the student to retrieve.
     * @return A pointer to the Student object if found, nullptr otherwise.
     */
    Student* getStudentByUsername(std::string username) const;

    /**
     * @brief Retrieves a doctor by their username.
     * @param username The username of the doctor to retrieve.
     * @return A pointer to the Doctor object if found, nullptr otherwise.
     */
    Doctor* getDoctorByUsername(std::string username) const;

    /**
     * @brief Checks if a given username already exists in the system (for either student or
     * doctor).
     * @param username The username to check.
     * @return True if the username exists, false otherwise.
     */
    bool isUsernameTaken(std::string username) const;

    /**
     * @brief Attempts to log in a student with the given username and password.
     * @param username The username for student login.
     * @param password The password for student login.
     * @return A pointer to the logged-in Student object if successful, nullptr otherwise.
     */
    Student* studentLogin(std::string username, std::string password) const;

    /**
     * @brief Attempts to log in a doctor with the given username and password.
     * @param username The username for doctor login.
     * @param password The password for doctor login.
     * @return A pointer to the logged-in Doctor object if successful, nullptr otherwise.
     */
    Doctor* doctorLogin(std::string username, std::string password) const;

    /**
     * @brief Registers a new student with the provided details.
     * @param username The desired username for the student.
     * @param password The desired password for the student.
     * @param name The full name of the student.
     * @param email The email address of the student.
     * @return A pointer to the newly created Student object if successful, nullptr otherwise.
     */
    Student* studentSignUp(std::string username, std::string password, std::string name,
                           std::string email);

    /**
     * @brief Registers a new doctor with the provided details.
     * @param username The desired username for the doctor.
     * @param password The desired password for the doctor.
     * @param name The full name of the doctor.
     * @param email The email address of the doctor.
     * @return A pointer to the newly created Doctor object if successful, nullptr otherwise.
     */
    Doctor* doctorSignUp(std::string username, std::string password, std::string name,
                         std::string email);

    /**
     * @brief Destructor for UsersManager. Cleans up dynamically allocated Student and Doctor
     * objects.
     */
    ~UsersManager();
};
