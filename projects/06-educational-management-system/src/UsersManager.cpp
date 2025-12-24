#include "UsersManager.hpp"

void UsersManager::addDoctor(Doctor* doctor) {
    usernameToDoctorMap[doctor->getUsername()] = doctor;
}
void UsersManager::addStudent(Student* student) {
    usernameToStudentMap[student->getUsername()] = student;
}

Student* UsersManager::getStudentByUsername(std::string username) const {
    if (usernameToStudentMap.count(username)) {
        return usernameToStudentMap.at(username);
    }
    return nullptr;
}
Doctor* UsersManager::getDoctorByUsername(std::string username) const {
    if (usernameToDoctorMap.count(username)) {
        return usernameToDoctorMap.at(username);
    }
    return nullptr;
}
bool UsersManager::isUsernameTaken(std::string username) const {
    return getDoctorByUsername(username) || getStudentByUsername(username);
}
Student* UsersManager::studentLogin(std::string username, std::string password) const {
    Student* s = getStudentByUsername(username);
    if (s && s->verify(username, password)) {
        return s;
    }
    return nullptr;
}
Doctor* UsersManager::doctorLogin(std::string username, std::string password) const {
    Doctor* d = getDoctorByUsername(username);
    if (d && d->verify(username, password)) {
        return d;
    }
    return nullptr;
}
Student* UsersManager::studentSignUp(std::string username, std::string password, std::string name,
                                     std::string email) {
    if (isUsernameTaken(username)) return nullptr;
    Student* s = new Student(username, password, name, email);
    addStudent(s);
    return s;
}
Doctor* UsersManager::doctorSignUp(std::string username, std::string password, std::string name,
                                   std::string email) {
    if (isUsernameTaken(username)) return nullptr;
    Doctor* d = new Doctor(username, password, name, email);
    addDoctor(d);
    return d;
}
UsersManager::~UsersManager() {
    for (auto& [username, doctor] : usernameToDoctorMap) delete doctor;
    for (auto& [username, student] : usernameToStudentMap) delete student;
}