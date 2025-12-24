# Tic-Tac-Toe Game

## 🔗 Quick Links
*   [Game Logic](src/TicTacToe.cpp)

## 📖 Game Rules & Logic

*   **Dynamic Grid (N x N)**: Unlike standard implementations, this game supports any grid size from **3x3** up to **9x9**. The user defines `N` at the start.
*   **Win Condition**: A player wins by completing a full row, column, or diagonal of their symbol (`X` or `O`).
*   **Draw Condition**: The game ends in a tie if the board fills up with no winner.

## ✨ Features
*   **Two Player Mode**: Hot-seat multiplayer.
*   **Real-time Visualization**:
    *   Console output after every move.
    *   **Live File View**: The board state is continuously written to `board.txt`, allowing for external visualization or debugging.
*   **Input Validation**: Prevents overwriting existing moves or choosing invalid coordinates.

## 🚀 Usage

1.  **Build the project** from the root directory (see root README).
2.  **Run the executable:**
    ```bash
    ./bin/tic_tac_toe
    ```
3.  **Play the game:**
    *   The game will prompt for coordinates (Row Column).
    *   Open `board.txt` in a text editor (or use `tail -f board.txt` in a separate terminal) to view the board updates in real-time.

## 🔧 Target-Specific Build

To build *only* this project:

```bash
cmake --build . --target tic_tac_toe
```
