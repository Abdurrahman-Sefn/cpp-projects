# Hospital System

## 🔗 Quick Links
*   [Triage Logic](src/HospitalSystem.cpp)
*   [Database](data/patients.txt)

## 📖 System Rules & Logic

The system is designed to manage a busy hospital triage environment with strict constraints:

*   **Structure**:
    *   **20 Specializations**: The hospital has exactly 20 departments (e.g., Children, Surgery).
    *   **Capacity Limit**: Each specialization queue can hold a maximum of **5 patients**. If full, new patients are rejected.
*   **Patient Intake (Priority Logic)**:
    *   **Regular (Status 0)**: Added to the **end** of the queue (FIFO).
    *   **Urgent (Status 1)**: Added to the **front** of the queue (Priority Override).
*   **Doctor Workflow**:
    *   Doctors pick up patients from a specific specialization.
    *   The system removes the patient from the front of the queue (highest priority first).

## ✨ Features
*   **Queue Management**: Efficiently handles 20 parallel queues.
*   **Data Persistence**: Patient data is automatically saved to `patients.txt`.
*   **Robust Input**: Validates names and menu choices.

## 🚀 Usage

1.  **Build the project** from the root directory (see root README).
2.  **Run the executable:**
    ```bash
    ./bin/hospital_system
    ```
3.  **Follow the menu:**
    ```text
    1. Add new patient (Regular/Urgent)
    2. Print all patients
    3. Get next patient
    4. Exit
    ```

## 🔧 Target-Specific Build

To build *only* this project:

```bash
cmake --build . --target hospital_system
```