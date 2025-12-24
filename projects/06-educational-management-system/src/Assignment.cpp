#include "Assignment.hpp"

#include "AssignmentSolution.hpp"
#include "Helper.hpp"

Assignment::Assignment(const Course *const course, const std::string &title,
                       const std::string &content, int fullMark)
    : content(content), title(title), fullMark(fullMark), course(course) {}
int Assignment::getFullMark() const {
    return fullMark;
}
void Assignment::printContent(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent << title << "\n";
    std::cout << indent << "Content: \n";
    std::cout << indent << "\t--> " << content << "\n";
}
const std::string &Assignment::getTitle() const {
    return title;
}
const Course *Assignment::getParentCourse() const {
    return course;
}
bool Assignment::canSubmit() const {
    return isAvailableToSubmit;
}
void Assignment::print(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent << title << "\n";
}
void Assignment::listSolutions(const std::vector<AssignmentSolution *> &solutions, int tabs,
                               bool numbered) const {
    if (solutions.empty()) {
        return;
    }
    int cnt = 1;
    std::string indent = indenter(tabs);
    std::cout << "\n*****************************************\n";
    for (auto &sol : solutions) {
        if (numbered) std::cout << indent << cnt++ << "- \n";
        sol->printContent(tabs);
        std::cout << "\n";
    }
    std::cout << "\n*****************************************\n\n";
}