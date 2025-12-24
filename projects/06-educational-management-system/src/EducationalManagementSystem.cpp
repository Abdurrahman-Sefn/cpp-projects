#include "EducationalManagementSystem.hpp"

#include "Helper.hpp"

SystemMainMenuChoice EducationalManagemenentSystem::showSystemMenu() {
    return mainMenuHandler.showAndGetChoice();
}
bool EducationalManagemenentSystem::enter() {
    auto choice = showSystemMenu();
    switch (choice) {
        case SystemMainMenuChoice::Exit:
            return false;
        case SystemMainMenuChoice::SignUp:
            signup();
            break;
        case SystemMainMenuChoice::Login:
            login();
            break;
        case SystemMainMenuChoice::InvalidChoice:
        default:
            std::cout << "\nInvalid choice!\n";
            break;
    }
    return true;
}
void EducationalManagemenentSystem::login() {
    std::string username = Sefn::readValidatedInput<std::string>("Enter username: ");
    std::string password = Sefn::readValidatedInput<std::string>("Enter password: ");
    currentDoctor = usersManager.doctorLogin(username, password);
    if (currentDoctor) {
        std::cout << "\n\tWelcome Dr " << currentDoctor->getName() << " !\n";
        return;
    }
    currentStudent = usersManager.studentLogin(username, password);
    if (currentStudent) {
        std::cout << "\n\tWelcome " << currentStudent->getName() << " !\n";
        return;
    } else {
        std::cout << "\n\tInvalid username or password!\n";
    }
}
void EducationalManagemenentSystem::signup() {
    auto type = enterMenuHandler.showAndGetChoice();
    if (type == EnterMenuChoice::Back || type == EnterMenuChoice::InvalidChoice) {
        return;
    }
    std::string name;
    std::cout << "Enter your name: ";
    getline(std::cin, name);
    std::string email = Sefn::readValidatedInput<std::string>("Enter your email: ");
    std::string username = Sefn::readValidatedInput<std::string>("Enter username: ");
    while (usersManager.isUsernameTaken(username)) {
        username = Sefn::readValidatedInput<std::string>(
            "\tThis username is already existed. Enter another username: ");
    }
    std::string password = Sefn::readValidatedInput<std::string>("Enter password: ");
    if (type == EnterMenuChoice::Student) {
        currentStudent = usersManager.studentSignUp(username, password, name, email);
        if (currentStudent) std::cout << "\n\tWelcome " << currentStudent->getName() << " !\n";
    } else if (type == EnterMenuChoice::Doctor) {
        currentDoctor = usersManager.doctorSignUp(username, password, name, email);
        if (currentDoctor) std::cout << "\n\tWelcome Dr " << currentDoctor->getName() << " !\n";
    }
}

void EducationalManagemenentSystem::run() {
    while (true) {
        bool state = enter();
        if (!state) {
            return;
        }
        if (currentDoctor) {
            DoctorSession session(coursesManager, currentDoctor);
            session.runMainMenu();
        } else if (currentStudent) {
            StudentSession session(coursesManager, currentStudent);
            session.runMainMenu();
        }
        currentDoctor = nullptr;
        currentStudent = nullptr;
    }
}

EducationalManagemenentSystem::EducationalManagemenentSystem()
    : mainMenuHandler(std::vector<std::string>{"Login", "Sign up", "Shutdown system"},
                      "\nEducational Management System:\n", SystemMainMenuChoice::Login,
                      SystemMainMenuChoice::Exit),
      enterMenuHandler(std::vector<std::string>{"Student", "Doctor", "Back"},
                       "\nSelect user type:\n", EnterMenuChoice::Student, EnterMenuChoice::Back) {
    loadDummyData();
}
void EducationalManagemenentSystem::loadDummyData() {
    std::cout << "Loading dummy data...\n";

    // =================================================================
    // ١. إنشاء الأطباء والطلاب (Creating Doctors & Students)
    // =================================================================
    Doctor* doc1 = usersManager.doctorSignUp("mostafa", "111", "Mostafa Saad", "mostafa@gmail.com");
    Doctor* doc2 = usersManager.doctorSignUp("hany", "222", "Hany Mohamed", "hany@yahoo.com");

    Student* s1 = usersManager.studentSignUp("ahmed", "123", "Ahmed Ali", "ahmed@gmail.com");
    Student* s2 = usersManager.studentSignUp("ali", "123", "Ali Hassan", "ali@gmail.com");
    Student* s3 = usersManager.studentSignUp("salma", "123", "Salma Ibrahim", "salma@gmail.com");
    Student* s4 = usersManager.studentSignUp("mona", "123", "Mona Youssef", "mona@gmail.com");
    usersManager.studentSignUp("omar", "123", "Omar Khaled",
                               "omar@gmail.com");  // طالب لن يسجل في أي كورس

    // =================================================================
    // ٢. إنشاء المساقات الدراسية (Creating Courses)
    // =================================================================
    Course* course1 = coursesManager.createCourse(doc1, "Programming 1", "CS101");
    doc1->registerInCourse(course1);
    Course* course2 = coursesManager.createCourse(doc1, "Data Structures", "CS213");
    doc1->registerInCourse(course2);
    Course* course3 = coursesManager.createCourse(doc2, "Calculus 1", "MATH101");
    doc2->registerInCourse(course3);
    Course* course4 =
        coursesManager.createCourse(doc2, "Physics 1", "PHY101");  // كورس لن يسجل فيه أي طالب
    doc2->registerInCourse(course4);

    // =================================================================
    // ٣. تسجيل الطلاب في المساقات (Registering Students in Courses)
    // لاحظ أن التسجيل يتم في كلا الاتجاهين (الطالب يسجل، والكورس يسجل الطالب)
    // =================================================================
    // Ahmed -> CS101, MATH101
    s1->registerInCourse(course1);
    course1->registerStudent(s1);
    s1->registerInCourse(course3);
    course3->registerStudent(s1);

    // Ali -> CS101
    s2->registerInCourse(course1);
    course1->registerStudent(s2);

    // Salma -> CS213, MATH101
    s3->registerInCourse(course2);
    course2->registerStudent(s3);
    s3->registerInCourse(course3);
    course3->registerStudent(s3);

    // Mona -> CS101, CS213
    s4->registerInCourse(course1);
    course1->registerStudent(s4);
    s4->registerInCourse(course2);
    course2->registerStudent(s4);

    // =================================================================
    // ٤. إنشاء الواجبات (Creating Assignments)
    // =================================================================
    Assignment* as1_c1 =
        course1->createAssignment("Assignment 1", "Implement a simple calculator.", 10);
    Assignment* as2_c1 = course1->createAssignment("Assignment 2", "Explain loops in C++.", 8);

    Assignment* as1_c2 = course2->createAssignment("Assignment 1", "Implement a linked list.", 15);

    Assignment* as1_c3 =
        course3->createAssignment("Homework 1", "Solve differentiation problems.", 12);

    // =================================================================
    // ٥. تسليم حلول الواجبات (Submitting Solutions)
    // =================================================================
    // CS101 Submissions
    course1->submitAssignment(s1, as1_c1, "Ahmed's answer for assignment 1.");
    course1->submitAssignment(s2, as1_c1, "Ali's answer for assignment 1.");
    course1->submitAssignment(s4, as1_c1, "Mona's answer for assignment 1.");
    course1->submitAssignment(s2, as2_c1, "Ali's answer for assignment 2.");  // Ali submitted both

    // CS213 Submissions
    course2->submitAssignment(s3, as1_c2, "Salma's implementation of a linked list.");
    course2->submitAssignment(s4, as1_c2, "Mona's implementation of a linked list.");

    // MATH101 Submissions
    course3->submitAssignment(s1, as1_c3, "Ahmed's solutions for calculus homework.");

    // =================================================================
    // ٦. تقييم بعض الحلول (Grading some solutions)
    // هذه الخطوة تحاكي قيام الطبيب بتقييم الحلول الموجودة في قائمة الانتظار
    // =================================================================

    // Doctor Mostafa grades CS101, Assignment 1
    // Grade Ahmed's solution
    AssignmentSolution* sol1 = course1->getQueueFront(as1_c1);
    course1->setGrade(sol1, 8);  // Ahmed gets 8/10
    course1->popQueueFront(as1_c1);

    // Grade Ali's solution
    AssignmentSolution* sol2 = course1->getQueueFront(as1_c1);
    course1->setGrade(sol2, 9);  // Ali gets 9/10
    course1->popQueueFront(as1_c1);

    // Mona's solution for CS101-As1 remains ungraded.
    // Ali's solution for CS101-As2 remains ungraded.

    // Doctor Mostafa grades CS213, Assignment 1
    // Grade Salma's solution
    AssignmentSolution* sol3 = course2->getQueueFront(as1_c2);
    course2->setGrade(sol3, 13);  // Salma gets 13/15
    course2->popQueueFront(as1_c2);

    // Mona's solution for CS213-As1 remains ungraded.

    std::cout << "Dummy data loaded successfully.\n\n";
}