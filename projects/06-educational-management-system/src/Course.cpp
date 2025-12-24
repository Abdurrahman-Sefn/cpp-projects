#include "Course.hpp"

#include <algorithm>
#include <iomanip>

#include "Doctor.hpp"
#include "Helper.hpp"

Course::Course(const Doctor* doctor, const std::string& name, const std::string& code)
    : doctor(doctor), code(code), name(name) {}
Assignment* Course::createAssignment(const std::string& title, const std::string& content,
                                     int fullMark) {
    Assignment* added = new Assignment(this, title, content, fullMark);
    addAssignment(added);
    return added;
}
AssignmentSolution* Course::getQueueFront(const Assignment* assignment) const {
    auto& que = ungradedAssignmentsQueues.at(assignment);
    AssignmentSolution* front{};
    if (!que.empty()) {
        front = que.front();
    }
    return front;
}
void Course::popQueueFront(const Assignment* assignment) {
    auto& que = ungradedAssignmentsQueues.at(assignment);
    if (!que.empty()) {
        que.pop_front();
    }
}
void Course::setGrade(AssignmentSolution* sol, int grade) {
    sol->setGrade(grade);
    const Student* s = sol->getStudent();
    studentTotalGrade.at(s) += grade;
}

void Course::addAssignment(const Assignment* assignment) {
    allAssignments.push_back(assignment);
    allAssignmentSolutions[assignment];
    ungradedAssignmentsQueues[assignment];
    totalFullMark += assignment->getFullMark();
}
void Course::addSolution(AssignmentSolution* sol) {
    const Assignment* assignment = sol->getAssignment();
    auto student = sol->getStudent();
    auto& mp = studentSolutionsMap.at(student);
    mp[assignment] = sol;
    allAssignmentSolutions[assignment].push_back(sol);
    ungradedAssignmentsQueues[assignment].push_back(sol);
}
void Course::removeSolution(const AssignmentSolution* sol) {
    const Assignment* assignment = sol->getAssignment();
    if (sol->isGraded()) {
        auto& v = allAssignmentSolutions.at(assignment);
        auto it = std::find(v.begin(), v.end(), sol);
        v.erase(it);
    } else {
        auto& que = ungradedAssignmentsQueues.at(assignment);
        auto it = std::find(que.begin(), que.end(), sol);
        que.erase(it);
    }
    delete sol;
}

bool Course::isAssignmentSubmitted(const Student* s, const Assignment* assignment) const {
    return studentSolutionsMap.at(s).find(assignment) != studentSolutionsMap.at(s).end();
}
bool Course::submitAssignment(const Student* s, const Assignment* assignment,
                              const std::string& answer) {
    if (!assignment->canSubmit()) {
        return false;
    }
    bool isSubmittedBefore = isAssignmentSubmitted(s, assignment);
    auto& mp = studentSolutionsMap.at(s);
    if (isSubmittedBefore) {
        mp.at(assignment)->updateAnswer(answer);
    } else {
        AssignmentSolution* solutionToAdd = new AssignmentSolution(assignment, s, answer);
        addSolution(solutionToAdd);
    }
    return true;
}
void Course::listStudentAssignments(const Student* s,
                                    const std::vector<const Assignment*>& assignments,
                                    int tabs) const {
    if (assignments.empty()) {
        return;
    }
    std::cout << "\n*****************************************\n";
    std::string indent = indenter(tabs);
    auto& solutionsMp = studentSolutionsMap.at(s);
    for (size_t i = 0; i < assignments.size(); ++i) {
        const Assignment* assignment = assignments[i];
        AssignmentSolution* sol{};
        std::cout << indent << "Assignment " << std::right << std::setw(2) << i + 1 << "- ";
        std::cout << std::left << std::setw(20) << assignment->getTitle();
        if (solutionsMp.count(assignment)) {
            std::cout << std::left << std::setw(17) << " submitted";
            if (solutionsMp.at(assignment)->isGraded()) {
                sol = solutionsMp.at(assignment);
            }
        } else {
            std::cout << std::left << std::setw(17) << " NOT submitted";
        }
        std::cout << " - " << std::right << std::setw(2) << (sol ? toString(sol->getGrade()) : "NA")
                  << " / " << std::right << std::setw(2) << assignment->getFullMark() << "\n";
        if (sol && !sol->getComment().empty())
            std::cout << indent << "\t-->" << sol->getComment() << "\n";
    }
    std::cout << "\n*****************************************\n\n";
}
void Course::unregisterStudent(const Student* s) {
    for (auto& [assignmet, sol] : studentSolutionsMap.at(s)) {
        removeSolution(sol);
    }
    studentSolutionsMap.erase(s);
    studentTotalGrade.erase(s);
}
void Course::registerStudent(const Student* s) {
    studentTotalGrade[s];
    studentSolutionsMap[s];
}
void Course::showStudentGrade(const Student* s) const {
    std::cout << "Course code " << std::left << std::setw(10) << code << "| Total submitted "
              << std::right << std::setw(2) << studentSolutionsMap.at(s).size()
              << " assignment(s) | Grade " << std::right << std::setw(3) << studentTotalGrade.at(s)
              << " / " << std::right << std::setw(3) << totalFullMark << "\n";
}
void Course::print() const {
    std::cout << "Course " << std::left << std::setw(20) << name << " | Code " << code << "\n";
}
void Course::printDetailed() const {
    std::cout << "Course " << name << " with Code " << code << " taught by Dr " << doctor->getName()
              << "\n";
}
std::vector<const Assignment*> Course::getAvailableAssignments() const {
    std::vector<const Assignment*> availableToSubmit;
    for (auto assignment : allAssignments) {
        if (assignment->canSubmit()) {
            availableToSubmit.push_back(assignment);
        }
    }
    return availableToSubmit;
}
const std::vector<const Assignment*>& Course::getAllAssignments() const {
    return allAssignments;
}

std::string Course::getCourseName() const {
    return name;
}
std::string Course::getCourseCode() const {
    return code;
}
void Course::listDoctorAssignments(const std::vector<const Assignment*>& assignments, int tabs,
                                   bool numbered) const {
    if (assignments.empty()) {
        return;
    }
    std::cout << "\n*****************************************\n";
    int cnt = 1;
    std::string indent = indenter(tabs);
    for (auto& assignment : assignments) {
        if (numbered) std::cout << indent << cnt++ << "- \n";
        assignment->print(tabs);
        std::cout << "\n";
    }
    std::cout << "\n*****************************************\n\n";
}
void Course::listAssignmentGradesReport(const Assignment* assignment, int tabs) const {
    for (auto& sol : allAssignmentSolutions.at(assignment)) {
        sol->printStudentGrade(tabs);
    }
}
const std::vector<AssignmentSolution*>& Course::getAllAssignmentSolutions(
    const Assignment* assignment) const {
    return allAssignmentSolutions.at(assignment);
}
Course::~Course() {
    for (auto& [assignment, sols] : allAssignmentSolutions) {
        for (auto& sol : sols) {
            delete sol;
        }
        delete assignment;
    }
}