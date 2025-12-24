#include "StudentSession.hpp"

#include "Helper.hpp"

StudentSession::StudentSession(CoursesManager& coursesManager, Student* currentStudent)
    : currentStudent(currentStudent),
      coursesManager(coursesManager),
      mainMenuHandler(std::vector<std::string>{"register in a course", "list my courses",
                                               "view a course", "grades report", "logout"},
                      "\nMain menu:\n", StudentMainMenuChoice::RegisterInCourse,
                      StudentMainMenuChoice::Logout),
      courseMenuHandler(
          std::vector<std::string>{"unregister from the course", "submit a solution", "back"},
          "\nCourse menu:\n", StudentViewCourseMenuChoice::Unregister,
          StudentViewCourseMenuChoice::Back) {}

void StudentSession::logout() {
    currentStudent = nullptr;
}
StudentMainMenuChoice StudentSession::showMainMenu() {
    return mainMenuHandler.showAndGetChoice("for Student " + currentStudent->getName());
}
StudentViewCourseMenuChoice StudentSession::viewCourseMenu(Course* course) {
    return courseMenuHandler.showAndGetChoice(course->getCourseName());
}

void StudentSession::submitAssignment(Course* course) {
    std::vector<const Assignment*> availableAssignments = course->getAvailableAssignments();
    course->printDetailed();
    int size = availableAssignments.size();
    if (!size) {
        std::cout << "There is no assignments to submit. Take rest\n";
        return;
    } else {
        std::cout << "Course has " << size << " assignments\n";
    }
    if (availableAssignments.empty()) {
        std::cout << "\tThere is no assignment for now!\n";
        return;
    }
    course->listStudentAssignments(currentStudent, availableAssignments, 1);
    const Assignment* assignmentToSubmit = selectFrom(availableAssignments, "assignment");
    assignmentToSubmit->printContent(1);
    std::string answer;
    std::cout << "Enter the solution: ";
    getline(std::cin, answer);
    bool success = course->submitAssignment(currentStudent, assignmentToSubmit, answer);
    if (success)
        std::cout << "\tSuccessful submission!\n";
    else
        std::cout << "\tSubmission failed!\n";
}
void StudentSession::registerInCourse() {
    std::vector<const Course*> availableToRegister =
        coursesManager.getAvailableCoursesToStudent(currentStudent);
    coursesManager.listCourses(availableToRegister, 1);
    const Course* chosen = selectFrom(availableToRegister, "course");
    if (!chosen) {
        return;
    }
    Course* courseToRegister = coursesManager.getCourseByCode(chosen->getCourseCode());
    courseToRegister->registerStudent(currentStudent);
    currentStudent->registerInCourse(courseToRegister);
}
void StudentSession::unregisterFromCourse(Course* course) {
    course->unregisterStudent(currentStudent);
    currentStudent->unregisterFromCourse(course);
}
void StudentSession::runViewCourseMenu() {
    auto& registeredCourses = currentStudent->getCourses();
    coursesManager.listCourses(registeredCourses, 1);
    const Course* chosen = selectFrom(registeredCourses, "course");
    if (!chosen) {
        return;
    }
    Course* courseToView = coursesManager.getCourseByCode(chosen->getCourseCode());
    auto& assignmentsToView = courseToView->getAllAssignments();
    if (assignmentsToView.empty()) {
        std::cout << "\tThere is no assignments for now!\n";
    } else {
        courseToView->listStudentAssignments(currentStudent, assignmentsToView, 1);
    }
    while (currentStudent) {
        auto choice = viewCourseMenu(courseToView);
        switch (choice) {
            case StudentViewCourseMenuChoice::Back:
                return;
            case StudentViewCourseMenuChoice::SubmitSolution:
                submitAssignment(courseToView);
                break;
            case StudentViewCourseMenuChoice::Unregister:
                unregisterFromCourse(courseToView);
                break;
            case StudentViewCourseMenuChoice::InvalidChoice:
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    }
}
void StudentSession::showGradesReport() {
    currentStudent->showTotalGradesReport(1);
}
void StudentSession::listRegisteredCourses() {
    auto coursesToList = currentStudent->getCourses();
    if (coursesToList.empty()) {
        std::cout << "\tThere is no courses to display!\n";
        return;
    }
    coursesManager.listCourses(coursesToList, 1);
}
void StudentSession::runMainMenu() {
    while (currentStudent) {
        auto choice = showMainMenu();
        switch (choice) {
            case StudentMainMenuChoice::Logout:
                logout();
                return;
            case StudentMainMenuChoice::GradesReport:
                showGradesReport();
                break;
            case StudentMainMenuChoice::ViewCourse:
                runViewCourseMenu();
                break;
            case StudentMainMenuChoice::ListMyCourses:
                listRegisteredCourses();
                break;
            case StudentMainMenuChoice::RegisterInCourse:
                registerInCourse();
                break;
            case StudentMainMenuChoice::InvalidChoice:
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    }
}