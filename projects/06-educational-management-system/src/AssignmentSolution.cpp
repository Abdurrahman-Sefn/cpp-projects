#include "AssignmentSolution.hpp"

#include <iomanip>

#include "Helper.hpp"
#include "Student.hpp"

AssignmentSolution::AssignmentSolution(const Assignment* assignment, const Student* student,
                                       std::string answer)
    : assignment(assignment), student(student), answer(answer) {}
bool AssignmentSolution::isGraded() const {
    return grade >= 0;
}
const std::string& AssignmentSolution::getComment() const {
    return comment;
}
int AssignmentSolution::getGrade() const {
    return grade;
}
int AssignmentSolution::getFullMark() const {
    return assignment->getFullMark();
}
void AssignmentSolution::updateAnswer(const std::string& newAnswer) {
    answer = newAnswer;
}
void AssignmentSolution::setGrade(int grade) {
    this->grade = grade;
}
void AssignmentSolution::setComment(std::string comment) {
    this->comment = comment;
}
void AssignmentSolution::printContent(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent << "Assignment : " << assignment->getTitle() << "\n";
    std::cout << indent << "Course     : " << assignment->getParentCourse()->getCourseName()
              << "\n";
    std::cout << indent << "Student    : " << student->getName() << "\n";
    std::cout << indent << "Answer     : " << answer << "\n";
    if (!comment.empty()) std::cout << indent << "Comment   : " << comment << "\n";
    std::cout << "\n";
}
void AssignmentSolution::printStudentGrade(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent << std::left << std::setw(30) << student->getName();
    std::cout << " | " << std::right << std::setw(3) << grade << "\n";
}
const Assignment* AssignmentSolution::getAssignment() const {
    return assignment;
}
const Student* AssignmentSolution::getStudent() const {
    return student;
}