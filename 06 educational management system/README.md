# Educational Management System

This is a comprehensive console-based educational management system.

## Description

This program provides a platform for managing courses, students, and doctors in an educational setting. It allows for user registration and login for both students and doctors, each with their own set of functionalities.

### Doctor Features
- Log in and manage their courses.
- Create, view, and manage assignments for their courses.
- View and grade student solutions for assignments.

### Student Features
- Log in and register for courses.
- View their registered courses and course assignments.
- Submit solutions for assignments.
- View their grades.

## Building and Running

To build the project, you can use the following command:

```bash
g++ main.cpp EducationalManageMentSystem.cpp UsersManager.cpp CoursesManager.cpp DoctorSession.cpp StudentSession.cpp Doctor.cpp Student.cpp Course.cpp Assignment.cpp AssignmentSolution.cpp Helper.cpp -o program.out
```

To run the project, execute the following command:

```bash
./program.out
```

## Usage

The system starts with a login/signup prompt. Users can register as either a student or a doctor and then log in to access their respective dashboards.
