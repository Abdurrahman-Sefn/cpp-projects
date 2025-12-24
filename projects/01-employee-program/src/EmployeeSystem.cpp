/**
 * @file EmployeeSystem.cpp
 * @brief A simple employee management system with file persistence.
 *
 * This program allows users to add, view, update, and delete employee records.
 * Data is persisted to a text file (employees.txt).
 *
 * @author Abdurrahman-sefn
 * @date 2025-12-24
 */

#include <Sefn/InputUtils.hpp>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

/**
 * @namespace Helper
 * @brief Utility functions for string manipulation and conversion.
 */
namespace Helper {
const std::string WHITESPACE = " \n\r\t\f\v";

/**
 * @brief Trims leading whitespace from a string.
 * @param s The string to trim.
 */
void lTrim(std::string& s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    if (start == std::string::npos) {
        s.clear();
    } else {
        s.erase(0, start);
    }
}

/**
 * @brief Trims trailing whitespace from a string.
 * @param s The string to trim.
 */
void rTrim(std::string& s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    if (end == std::string::npos) {
        s.clear();
    } else {
        s.erase(end + 1);
    }
}

/**
 * @brief Trims both leading and trailing whitespace from a string.
 * @param s The string to trim.
 */
void trim(std::string& s) {
    rTrim(s);
    lTrim(s);
}
}  // namespace Helper

/**
 * @class EmployeeSystem
 * @brief Manages a collection of employees with persistent storage.
 */
class EmployeeSystem {
    static constexpr int MIN_SALARY = 2000;
    static constexpr int MAX_SALARY = 100000;
    static constexpr int MIN_AGE = 16;
    static constexpr int MAX_AGE = 60;
    static constexpr const char* DATABASE_PATH = "employees.txt";

    /**
     * @struct Employee
     * @brief Represents a single employee record.
     */
    struct Employee {
        static constexpr char DELIM = '|';

        std::string name;
        int age{-1};
        int salary{-1};
        char gender{'N'};

        Employee() = default;

        /**
         * @brief Constructs an Employee with given details.
         * @param name The name of the employee.
         * @param age The age of the employee.
         * @param salary The salary of the employee.
         * @param gender The gender of the employee ('M' or 'F').
         */
        Employee(std::string name, int age, int salary, char gender)
            : name(std::move(name)), age(age), salary(salary), gender(gender) {}

        /**
         * @brief Constructs an Employee from a delimited string.
         * @param empStr The string containing employee data separated by delimiters.
         */
        explicit Employee(const std::string& empStr) {
            std::istringstream iss(empStr);
            std::getline(iss, name, DELIM);
            iss >> age;
            iss.ignore();
            iss >> salary;
            iss.ignore();
            iss >> gender;
        }

        /**
         * @brief Checks if a salary is within the valid range.
         * @param salary The salary to check.
         * @return True if valid, false otherwise.
         */
        static bool isValidSalary(int salary) {
            return salary >= MIN_SALARY && salary <= MAX_SALARY;
        }

        /**
         * @brief Checks if a name is valid.
         * @param name The name to check.
         * @return True if valid (not empty, starts with non-space, >2 chars, all lower or space),
         * false otherwise.
         */
        static bool isValidName(const std::string& name) {
            if (name.empty() || name[0] == ' ' || name.size() <= 2) {
                return false;
            }
            return std::all_of(name.begin(), name.end(), [](char c) {
                return std::islower(static_cast<unsigned char>(c)) || c == ' ';
            });
        }

        /**
         * @brief Checks if an age is within the valid range.
         * @param age The age to check.
         * @return True if valid, false otherwise.
         */
        static bool isValidAge(int age) { return age >= MIN_AGE && age <= MAX_AGE; }

        /**
         * @brief Checks if a gender is valid.
         * @param gender The gender to check ('M' or 'F').
         * @return True if valid, false otherwise.
         */
        static bool isValidGender(char gender) { return gender == 'M' || gender == 'F'; }

        /**
         * @brief Prints employee details to stdout.
         */
        void print() const {
            std::cout << "Name: " << name << "\n"
                      << "Age: " << age << "\n"
                      << "Salary: " << salary << "\n"
                      << "Gender: " << gender << "\n";
        }

        /**
         * @brief Converts employee data to a delimited string.
         * @return A string representation of the employee for storage.
         */
        std::string toString() const {
            std::ostringstream oss;
            oss << name << DELIM << age << DELIM << salary << DELIM << gender;
            return oss.str();
        }
    };

    std::map<std::string, Employee> employees;

    /**
     * @brief Reads an employee name from stdin.
     * @return The trimmed name.
     */
    std::string readEmployeeName() {
        std::string name;
        std::cout << "Enter employee name: ";
        std::getline(std::cin >> std::ws, name);
        Helper::trim(name);
        return name;
    }

    /**
     * @brief Reads a unique and valid employee name.
     * @return A valid, unique name.
     */
    std::string readNewUniqueName() {
        while (true) {
            std::string name = readEmployeeName();
            if (name.empty()) continue;

            if (employees.find(name) != employees.end()) {
                std::cout << "\n This name already exists, try another one\n";
            } else if (!Employee::isValidName(name)) {
                std::cout << "\nInvalid name. Try again\n";
            } else {
                return name;
            }
        }
    }

    /**
     * @brief Reads and validates salary input.
     * @return A valid salary.
     */
    int readSalary() {
        return Sefn::readValidatedInput<int>("Enter employee salary: ", 0, Employee::isValidSalary,
                                             "\nInvalid salary. Try again\n");
    }

    /**
     * @brief Reads and validates age input.
     * @return A valid age.
     */
    int readAge() {
        return Sefn::readValidatedInput<int>("Enter employee age: ", 0, Employee::isValidAge,
                                             "\nInvalid age. Try again\n");
    }

    /**
     * @brief Reads and validates gender input.
     * @return A valid gender char.
     */
    char readGender() {
        return Sefn::readValidatedInput<char>("Enter employee gender: ", 0, Employee::isValidGender,
                                              "\nInvalid gender. Try again\n");
    }

    /**
     * @brief Adds a new employee to the system.
     */
    void addEmployee() {
        std::string name = readNewUniqueName();
        employees[name] = Employee(name, readAge(), readSalary(), readGender());
    }

    /**
     * @brief Prints all employees in the system.
     */
    void printEmployees() {
        std::cout << "\n******************\n";
        for (const auto& [name, emp] : employees) {
            emp.print();
            std::cout << "\n";
        }
        std::cout << "******************\n";
    }

    /**
     * @brief Deletes an employee by name.
     * @param name The name of the employee to delete.
     */
    void deleteEmployeeByName(const std::string& name) {
        auto it = employees.find(name);
        if (it == employees.end()) {
            std::cout << "\nThis name does not exist!\n";
            return;
        }
        employees.erase(it);
    }

    /**
     * @brief Deletes employees within a specified age range.
     */
    void deleteEmployeesByAgeRange() {
        int start = Sefn::readValidatedInput<int>("Enter lower limit: ");
        int end = Sefn::readValidatedInput<int>("Enter upper limit: ");
        if (end < start) std::swap(start, end);

        std::vector<std::string> keysToRemove;
        for (const auto& [name, emp] : employees) {
            if (emp.age >= start && emp.age <= end) {
                keysToRemove.push_back(name);
            }
        }

        for (const auto& key : keysToRemove) {
            employees.erase(key);
        }
        std::cout << keysToRemove.size() << " employee(s) removed\n";
    }

    /**
     * @brief Updates the salary of an existing employee.
     * @param name The name of the employee to update.
     */
    void updateSalary(const std::string& name) {
        auto it = employees.find(name);
        if (it == employees.end()) {
            std::cout << "\nThis name does not exist!\n";
            return;
        }
        it->second.salary = readSalary();
    }

    /**
     * @brief Loads employee data from the database file.
     */
    void loadDatabase() {
        std::ifstream data(DATABASE_PATH);
        if (data.fail()) return;

        std::string empStr;
        employees.clear();
        while (std::getline(data, empStr) && !empStr.empty()) {
            Employee emp(empStr);
            employees[emp.name] = emp;
        }
        data.close();
    }

    /**
     * @brief Saves employee data to the database file.
     */
    void updateDatabase() {
        std::ofstream data(DATABASE_PATH);
        if (data.fail()) {
            std::cerr << "\nCould not open " << DATABASE_PATH << " for writing!\n";
            return;
        }
        for (const auto& [name, emp] : employees) {
            data << emp.toString() << "\n";
        }
        data.close();
    }

   public:
    /**
     * @brief Constructs the EmployeeSystem.
     */
    EmployeeSystem() { std::cout << "\n*******Welcome!*******\n"; }

    /**
     * @brief Starts the employee system application loop.
     *
     * Displays the menu and processes user input until exit is chosen.
     */
    void run() {
        loadDatabase();
        while (true) {
            std::cout << "\n\nEnter Your choice: \n"
                      << "\t1) Add new employee\n"
                      << "\t2) Print all employees\n"
                      << "\t3) Delete by age range\n"
                      << "\t4) Update salary by name\n"
                      << "\t5) Delete an employee by name\n"
                      << "\t6) Exit\n";

            int choice = Sefn::readValidatedInput<int>("Enter your choice: ");
            if (choice == 1) {
                addEmployee();
            } else if (choice == 2) {
                printEmployees();
            } else if (choice == 3) {
                deleteEmployeesByAgeRange();
            } else if (choice == 4) {
                updateSalary(readEmployeeName());
            } else if (choice == 5) {
                deleteEmployeeByName(readEmployeeName());
            } else if (choice == 6) {
                std::cout << "\n*******Bye!*******\n";
                break;
            } else {
                std::cout << "Invalid choice. Please try again.\n";
            }
            updateDatabase();
        }
    }
};

int main() {
    EmployeeSystem system;
    system.run();
    return 0;
}
