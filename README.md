# MyCPP_Portfolio

A comprehensive collection of C++ projects ranging from simple console games to complex management systems. This repository demonstrates professional software engineering practices including **Object-Oriented Programming (OOP)**, **Data Structures (Tries, Queues)**, **System Architecture**, and **Modern Build Systems**.

## 📂 Repository Structure

| Project | Description | Key Tech |
| :--- | :--- | :--- |
| **[01-employee-program](projects/01-employee-program)** | Factory management system with CRUD operations and age-range filtering. | `File I/O`, `CRUD` |
| **[02-tic-tac-toe-game](projects/02-tic-tac-toe-game)** | Configurable **N x N** game with real-time file-based board visualization. | `Game Logic`, `N*N Grid` |
| **[03-hospital-system](projects/03-hospital-system)** | Triage system managing 20 specializations with **Priority Queue** logic for urgent cases. | `Priority Queue`, `FIFO/LIFO` |
| **[04-library-system-v1](projects/04-library-system-v1)** | Book management system utilizing **Trie Data Structures** for O(L) prefix search. | `Trie`, `Algorithms` |
| **[04-library-system-v2](projects/04-library-system-v2)** | Enterprise evolution of V1 with **decoupled architecture**, persistence, and advanced reporting. | `Architecture`, `Decoupling` |
| **[05-ask-me-system](projects/05-ask-me-system)** | Full **Ask.fm Clone** supporting threaded questions, anonymous users, and public feeds. | `Graph/Tree`, `Social Logic` |
| **[06-educational-management-system](projects/06-educational-management-system)** | Complex LMS with Role-Based Access Control (**RBAC**) for Doctors and Students. | `RBAC`, `System Design` |

## 🛠️ Prerequisites

*   **C++ Compiler**: Must support **C++17** or later (e.g., GCC, Clang, MSVC).
*   **CMake**: Version **3.20** or later.

## 💪 Shared Utilities & Robustness

This portfolio relies on my custom utility library, **[SefnUtils](https://github.com/Abdurrahman-Sefn/sefn-utils)**, which is automatically fetched via CMake.

*   **Crash-Proof Input**: All projects use `Sefn::readValidatedInput`. This generic template function handles input stream errors (e.g., user entering "abc" when an `int` is expected) and re-prompts the user, ensuring the applications never crash due to bad input.
*   **Data Structures**: Custom implementations of structures like **Trie** are pulled from this library to optimize search operations.

## 🚀 Build Instructions

This project is designed to be **portable**. External dependencies (like `SefnUtils`) are automatically managed via CMake's `FetchContent`.

1.  **Clone the repository:**
    ```bash
    git clone <repository_url>
    cd <repository_name>
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Generate build files:**
    ```bash
    cmake ..
    ```

4.  **Build all projects:**
    ```bash
    cmake --build .
    ```

## 🏗️ Running Specific Projects

After a successful build, the executables will be located in the `bin/` directory.

To run a specific project:
```bash
./bin/hospital_system
```

> **Note**: Usage instructions and menu options are available in the README within each project folder. The **Educational Management System** includes a detailed terminal walkthrough.

## 🔮 Future Improvements

*   **Refactor Common Utilities**: Currently, helper functions (menu display, string trimming, etc.) are included within each project to keep them self-contained. A future enhancement is to centralize these into a shared static library or integrate them into the `SefnUtils` library to strictly adhere to the DRY (Don't Repeat Yourself) principle.
*   **Unit Testing**: Implement automated testing using Google Test (gtest) to cover core business logic in the management systems.

## 📜 License

This repository is open-source and available for educational purposes.