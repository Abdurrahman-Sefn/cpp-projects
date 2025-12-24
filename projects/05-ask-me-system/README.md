# Ask Me System (Ask.fm Clone)

## 🔗 Quick Links
*   [System Controller](src/AskMe.hpp)
*   [Questions Manager](src/QuestionsManager.hpp)
*   [Users Manager](src/UsersManager.hpp)
*   [Questions Database](data/Questions.txt)
*   [Users Database](data/Users.txt)

## 📖 Big Picture & Design
A file-based Q&A system designed to simulate a real-world social platform.
*   **Simulated Concurrency**: The system is designed so that multiple users can run the program simultaneously (in separate terminals). The application automatically reloads the database before every action, allowing users to see questions and answers from others in near real-time without restarting.
*   **Threaded Architecture**: Questions can be "Parent" or "Child" (Threaded).
    *   If a question is answered, others can ask follow-up questions in that thread.
    *   **Cascading Deletion**: If a parent question is deleted, the entire thread (all child questions) is automatically removed.
*   **Correctness & Security**:
    *   **Access Control**: Users can only see, answer, or delete questions directed to **themselves**. It is impossible to modify or remove a question asked to someone else.
    *   **Data Integrity**: Strict validation ensures that every operation (ask/answer/delete) refers to valid, existing IDs.

## ✨ Features
*   **User Authentication**: Login, Signup, and Logout.
*   **Privacy Settings**: Users can choose to allow or block anonymous questions.
*   **Question Management**:
    *   **Ask**: Send questions to users (with optional anonymity).
    *   **Answer**: Reply to questions sent to you.
    *   **Delete**: Remove questions (triggers cascading delete for threads).
*   **Feed System**: A public feed displaying **only answered questions**, showing the full conversation thread.
*   **Data Persistence**: All state is saved to `Users.txt` and `Questions.txt`.

## 🚀 Usage

1.  **Build the project**:
    ```bash
    cmake --build . --target ask_me_system
    ```
2.  **Run (Simulate 2 Users)**:
    *   Open **Terminal A**: Run `./bin/ask_me_system` -> Login as User A.
    *   Open **Terminal B**: Run `./bin/ask_me_system` -> Login as User B.
    *   *User A asks User B a question. User B selects "Print questions to me" and sees it immediately.*

3.  **Menu Options**:
    *   `Print questions to me`
    *   `Print questions from me`
    *   `Answer question`
    *   `Delete question`
    *   `Ask question`
    *   `List system users`
    *   `Feed`
    *   `Logout`

## 🔧 Target-Specific Build
```bash
cmake --build . --target ask_me_system
```
