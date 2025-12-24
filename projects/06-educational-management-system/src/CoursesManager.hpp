/**
 * @file CoursesManager.hpp
 * @brief Manages the collection of courses in the Educational Management System.
 */

#pragma once
#include <map>
#include <unordered_map>
#include <vector>

#include "Course.hpp"
#include "Doctor.hpp"
#include "Student.hpp"

/**
 * @class CoursesManager
 * @brief Handles the creation, storage, retrieval, and management of Course objects.
 *
 * This class provides functionalities to add new courses, retrieve courses by their code,
 * and list courses based on various criteria.
 */
class CoursesManager {
    std::map<std::string, Course *>
        codeToCourseMap; /**< Maps course codes to Course objects for quick lookup. */

    /**
     * @brief Adds a course object to the internal map.
     * @param course A pointer to the Course object to be added.
     */
    void addCourse(Course *course);

   public:
    /**
     * @brief Lists a given set of courses.
     * @param courses A vector of constant pointers to Course objects to be listed.
     * @param tabs The number of tabs to indent the output.
     */
    void listCourses(const std::vector<const Course *> &courses, int tabs) const;

    /**
     * @brief Retrieves a list of courses available for a specific student to register in.
     * @param s A constant pointer to the Student.
     * @return A vector of constant pointers to available Course objects.
     */
    const std::vector<const Course *> getAvailableCoursesToStudent(const Student *s) const;

    /**
     * @brief Retrieves a course by its code.
     * @param code The code of the course to retrieve.
     * @return A pointer to the Course object if found, nullptr otherwise.
     */
    Course *getCourseByCode(const std::string &code) const;

    /**
     * @brief Creates a new course and adds it to the system.
     * @param doctor A pointer to the Doctor who will teach the course.
     * @param name The name of the course.
     * @param code The unique code for the course.
     * @return A pointer to the newly created Course object.
     */
    Course *createCourse(Doctor *doctor, const std::string &name, const std::string &code);

    /**
     * @brief Destructor for CoursesManager. Cleans up dynamically allocated Course objects.
     */
    ~CoursesManager();
};