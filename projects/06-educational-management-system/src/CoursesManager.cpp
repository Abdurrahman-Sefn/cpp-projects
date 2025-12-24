#include "CoursesManager.hpp"

#include "Helper.hpp"

const std::vector<const Course*> CoursesManager::getAvailableCoursesToStudent(
    const Student* s) const {
    std::vector<const Course*> ret;
    for (auto& [code, course] : codeToCourseMap) {
        if (!s->isRegisteredInCourse(course)) {
            ret.push_back(course);
        }
    }
    return ret;
}
void CoursesManager::listCourses(const std::vector<const Course*>& courses, int tabs) const {
    if (courses.empty()) {
        return;
    }
    std::cout << "\n*****************************************\n";
    std::string indent = indenter(tabs);
    int cnt = 1;
    for (auto& course : courses) {
        std::cout << indent << cnt++ << "- ";
        course->print();
    }
    std::cout << "\n*****************************************\n\n";
}

Course* CoursesManager::getCourseByCode(const std::string& code) const {
    if (codeToCourseMap.find(code) != codeToCourseMap.end())
        return codeToCourseMap.at(code);
    else
        return nullptr;
}
Course* CoursesManager::createCourse(Doctor* doctor, const std::string& name,
                                     const std::string& code) {
    if (getCourseByCode(code)) {
        return nullptr;
    }
    Course* added = new Course(doctor, name, code);
    addCourse(added);
    return added;
}
void CoursesManager::addCourse(Course* course) {
    codeToCourseMap[course->getCourseCode()] = course;
}
CoursesManager::~CoursesManager() {
    for (auto& [code, course] : codeToCourseMap) {
        delete course;
    }
}