# Employee Management System

## 🔗 Quick Links
*   [System Logic](src/EmployeeSystem.cpp)
*   [Database](data/employees.txt)

## 📖 System Specification

This program runs an infinite loop providing a menu for a factory manager to handle employee records.

*   **1) Add New Employee**:
    *   Prompts for **Name**, **Age**, **Salary**, and **Gender**.
    *   Validates input and adds the record to the database.
*   **2) Print All Employees**:
    *   Displays every employee in the system, one line per employee.
*   **3) Delete by Age**:
    *   Prompts for a `start_age` and `end_age`.
    *   **Logic**: Removes *all* employees where `start_age <= age <= end_age`.
*   **4) Update Salary by Name**:
    *   Prompts for an employee name and a new salary.
    *   Finds the matching employee and updates their record.

## ✨ Features
*   **Data Persistence**: Automatically saves to `employees.txt` to prevent data loss.
*   **Input Validation**: Ensures salaries are positive and names are valid strings.

## 🚀 Usage

1.  **Build the project** from the root directory (see root README).
2.  **Run the executable:**
    ```bash
    ./bin/employee_program
    ```
3.  **Follow the menu:**
    ```text
    1. Add new employee
    2. Print all employees
    3. Delete by age
    4. Update Salary by name
    5. Delete by name
    6. Exit
    ```

## 🔧 Target-Specific Build

To build *only* this project:

```bash
cmake --build . --target employee_program
```