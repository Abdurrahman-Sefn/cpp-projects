#include "Student.hpp"

#include <algorithm>

Student::Student(std::string username, std::string password, std::string name, std::string email)
    : name(name), email(email), username(username), password(password) {}

bool Student::verify(const std::string &username, const std::string &password) const {
    return this->username == username && this->password == password;
}

const std::vector<const Course *> &Student::getCourses() const {
    return registeredCourses;
}
bool Student::isRegisteredInCourse(const Course *course) const {
    return coursesSet.find(course) != coursesSet.end();
}
void Student::addCourse(const Course *course) {
    coursesSet.insert(course);
    registeredCourses.push_back(course);
}
void Student::removeCourse(const Course *course) {
    coursesSet.erase(course);
    auto it = std::find(registeredCourses.begin(), registeredCourses.end(), course);
    if (it != registeredCourses.end()) {
        registeredCourses.erase(it);
    }
}
void Student::registerInCourse(const Course *course) {
    if (!isRegisteredInCourse(course)) addCourse(course);
}
void Student::unregisterFromCourse(const Course *course) {
    if (isRegisteredInCourse(course)) removeCourse(course);
}
void Student::showTotalGradesReport(int /*tabs*/) const {
    std::cout << "\n";
    for (auto &course : registeredCourses) {
        course->showStudentGrade(this);
    }
}
const std::string &Student::getName() const {
    return name;
}
const std::string &Student::getUsername() const {
    return username;
}