#include "DoctorSession.hpp"

#include <Sefn/InputUtils.hpp>

#include "Helper.hpp"

void DoctorSession::logout() {
    currentDoctor = nullptr;
}
DoctorMainMenuChoice DoctorSession::showMainMenu() {
    return mainMenuHandler.showAndGetChoice("for Doctor " + currentDoctor->getName());
}
DoctorViewCourseMenuChoice DoctorSession::viewCourseMenu(Course* course) {
    return courseMenuHandler.showAndGetChoice(course->getCourseName());
}
DoctorViewAssignmentMenuChoice DoctorSession::viewAssignmentMenu(const Assignment* assignment) {
    return assignmentMenuHandler.showAndGetChoice(assignment->getTitle());
}
DoctorViewSolutionMenuChoice DoctorSession::viewSolutionMenu(AssignmentSolution* sol) {
    return solutionMenuHandler.showAndGetChoice("of Student " + sol->getStudent()->getName());
}
void DoctorSession::listCourses() {
    auto& courses = currentDoctor->getCourses();
    if (courses.empty()) {
        std::cout << "\tThere is no courses to display!\n";
        return;
    }
    coursesManager.listCourses(courses, 1);
}
void DoctorSession::createCourse() {
    std::cout << "Enter course name: ";
    std::string courseName;
    getline(std::cin, courseName);
    std::string code = Sefn::readValidatedInput<std::string>("Enter course code (no spaces): ");
    while (coursesManager.getCourseByCode(code) != nullptr)
        code = Sefn::readValidatedInput<std::string>(
            "This code is already existed. Try another one (no spaces): ");
    Course* courseAdded = coursesManager.createCourse(currentDoctor, courseName, code);
    if (courseAdded) {
        currentDoctor->registerInCourse(courseAdded);
        std::cout << "\tCourse " << courseName << " created successfully!\n";
    } else {
        std::cout << "\tInvalid creation!\n";
    }
}

void DoctorSession::listAssignments(Course* course) {
    std::vector<const Assignment*> allAssignments = course->getAllAssignments();
    if (allAssignments.empty()) {
        std::cout << "\tThere is no assignment for now!\n";
    } else {
        course->listDoctorAssignments(allAssignments, 1, false);
    }
}
void DoctorSession::createAssignment(Course* course) {
    std::cout << "Enter assignment title: ";
    std::string title;
    getline(std::cin, title);
    std::cout << "Enter assignment content: ";
    std::string content;
    std::getline(std::cin, content);
    int fullMark = Sefn::readValidatedInput<int>("Enter the full mark grade: ");
    Assignment* assignmentAdded = course->createAssignment(title, content, fullMark);
    if (assignmentAdded) {
        std::cout << "\tAssignment " << title << " created successfully!\n";
    } else {
        std::cout << "\tInvalid creation!\n";
    }
}

void DoctorSession::runViewSolutionMenu(Course* curCourse, const Assignment* assignment,
                                        AssignmentSolution* selectedBefore) {
    AssignmentSolution* solToView = selectedBefore;
    if (!selectedBefore) {
        const Course* course = assignment->getParentCourse();
        const std::vector<AssignmentSolution*>& allSolutions =
            course->getAllAssignmentSolutions(assignment);
        assignment->listSolutions(allSolutions, 1, true);
        solToView = selectFrom(allSolutions, "Solution");
    }
    while (currentDoctor && assignment && solToView) {
        auto choice = viewSolutionMenu(solToView);
        switch (choice) {
            case DoctorViewSolutionMenuChoice::Back:
                return;
            case DoctorViewSolutionMenuChoice::SetComment:
                addComment(solToView);
                break;
            case DoctorViewSolutionMenuChoice::SetGrade:
                gradeSolution(curCourse, solToView);
                break;
            case DoctorViewSolutionMenuChoice::PrintContent:
                solToView->printContent(1);
                break;
            case DoctorViewSolutionMenuChoice::InvalidChoice:
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
        if (selectedBefore) {
            return;
        }
    }
}
void DoctorSession::runViewAssignmentMenu(Course* course) {
    std::vector<const Assignment*> allAssignments = course->getAllAssignments();
    course->listDoctorAssignments(allAssignments, 1, true);
    const Assignment* assignmentToView = selectFrom(allAssignments, "Assignment");
    while (currentDoctor && course && assignmentToView) {
        auto choice = viewAssignmentMenu(assignmentToView);
        switch (choice) {
            case DoctorViewAssignmentMenuChoice::Back:
                return;
            case DoctorViewAssignmentMenuChoice::ViewSolution:
                runViewSolutionMenu(course, assignmentToView);
                break;
            case DoctorViewAssignmentMenuChoice::ListSolutions:
                listSolutions(assignmentToView);
                break;
            case DoctorViewAssignmentMenuChoice::PopSolutionFromQueue:
                course->popQueueFront(assignmentToView);
                break;
            case DoctorViewAssignmentMenuChoice::ViewSolutionFromQueue:
                viewSolutionFromQueue(course, assignmentToView);
                break;
            case DoctorViewAssignmentMenuChoice::ListGradesReport:
                course->listAssignmentGradesReport(assignmentToView, 1);
                break;
            case DoctorViewAssignmentMenuChoice::PrintContent:
                assignmentToView->printContent(1);
                break;
            case DoctorViewAssignmentMenuChoice::InvalidChoice:
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    }
}
void DoctorSession::runViewCourseMenu() {
    auto& registeredCourses = currentDoctor->getCourses();
    coursesManager.listCourses(registeredCourses, 1);
    const Course* chosen = selectFrom(registeredCourses, "course");
    while (currentDoctor && chosen) {
        Course* courseToView = coursesManager.getCourseByCode(chosen->getCourseCode());
        auto choice = viewCourseMenu(courseToView);
        switch (choice) {
            case DoctorViewCourseMenuChoice::Back:
                return;
            case DoctorViewCourseMenuChoice::ViewAssignment:
                runViewAssignmentMenu(courseToView);
                break;
            case DoctorViewCourseMenuChoice::CreateAssignment:
                createAssignment(courseToView);
                break;
            case DoctorViewCourseMenuChoice::ListAssignments:
                listAssignments(courseToView);
                break;
            case DoctorViewCourseMenuChoice::InvalidChoice:
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    }
}
void DoctorSession::runMainMenu() {
    while (currentDoctor) {
        auto choice = showMainMenu();
        switch (choice) {
            case DoctorMainMenuChoice::Logout:
                logout();
                return;
            case DoctorMainMenuChoice::ViewCourse:
                runViewCourseMenu();
                break;
            case DoctorMainMenuChoice::CreateCourse:
                createCourse();
                break;
            case DoctorMainMenuChoice::ListCourses:
                listCourses();
                break;
            case DoctorMainMenuChoice::InvalidChoice:
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    }
}
DoctorSession::DoctorSession(CoursesManager& coursesManager, Doctor* currentDoctor)
    : currentDoctor(currentDoctor),
      coursesManager(coursesManager),
      mainMenuHandler(
          std::vector<std::string>{"list my courses", "create a course", "view a course", "logout"},
          "\nMain menu:\n", DoctorMainMenuChoice::ListCourses, DoctorMainMenuChoice::Logout),
      courseMenuHandler(std::vector<std::string>{"list assignments", "create an assignment",
                                                 "view an assignment", "back"},
                        "\nCourse menu:\n", DoctorViewCourseMenuChoice::ListAssignments,
                        DoctorViewCourseMenuChoice::Back),
      assignmentMenuHandler(std::vector<std::string>{"print content", "list grades report",
                                                     "view a solution from the queue",
                                                     "pop a solution from the queue",
                                                     "list solutions", "view a solution", "back"},
                            "\nAssignment menu:\n", DoctorViewAssignmentMenuChoice::PrintContent,
                            DoctorViewAssignmentMenuChoice::Back),
      solutionMenuHandler(
          std::vector<std::string>{"print content", "set grade", "set comment", "back"},
          "\nSolution menu:\n", DoctorViewSolutionMenuChoice::PrintContent,
          DoctorViewSolutionMenuChoice::Back) {}

void DoctorSession::gradeSolution(Course* course, AssignmentSolution* sol) {
    int grade = Sefn::readValidatedInput<int>("Enter the grade: ");
    course->setGrade(sol, grade);
}
void DoctorSession::addComment(AssignmentSolution* sol) {
    std::cout << "Enter your comment: ";
    std::string comment;
    getline(std::cin, comment);
    sol->setComment(comment);
}
void DoctorSession::viewSolutionFromQueue(Course* curCourse, const Assignment* assignment) {
    auto sol = curCourse->getQueueFront(assignment);
    if (!sol) {
        std::cout << "\tThis queue is empty!\n";
        return;
    }
    runViewSolutionMenu(curCourse, assignment, sol);
    if (sol->isGraded()) {
        curCourse->popQueueFront(assignment);
    }
}
void DoctorSession::listSolutions(const Assignment* assignment) {
    auto course = assignment->getParentCourse();
    auto& allSolutions = course->getAllAssignmentSolutions(assignment);
    if (allSolutions.empty()) {
        std::cout << "\tThere is no solutions submitted for now!\n";
    }
    assignment->listSolutions(allSolutions, 1, false);
}