#include "Doctor.hpp"

Doctor::Doctor(std::string username, std::string password, std::string name, std::string email)
    : name(name), email(email), username(username), password(password) {}

bool Doctor::verify(const std::string &username, const std::string &password) const {
    return this->username == username && this->password == password;
}

const std::string &Doctor::getName() const {
    return name;
}
const std::string &Doctor::getUsername() const {
    return username;
}
const std::vector<const Course *> &Doctor::getCourses() const {
    return registeredCourses;
}
void Doctor::addCourse(const Course *course) {
    coursesSet.insert(course);
    registeredCourses.push_back(course);
}
void Doctor::registerInCourse(const Course *course) {
    if (!isRegisteredInCourse(course)) addCourse(course);
}
bool Doctor::isRegisteredInCourse(const Course *course) const {
    return coursesSet.find(course) != coursesSet.end();
}