#include <iostream>
#include <vector>
#include <conio.h>  // For real-time input handling
#include <windows.h> // For Sleep function
#include <ctime>
#include <sstream>  // Fix for to_string() issue

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;
char grid[HEIGHT][WIDTH];
int score = 0;

// Tetromino shapes
vector<vector<vector<int>>> tetrominoes = {
    {{1, 1, 1, 1}}, // I shape
    {{1, 1}, {1, 1}}, // O shape
    {{0, 1, 0}, {1, 1, 1}}, // T shape
    {{0, 1, 1}, {1, 1, 0}}, // S shape
    {{1, 1, 0}, {0, 1, 1}}, // Z shape
    {{1, 0, 0}, {1, 1, 1}}, // J shape
    {{0, 0, 1}, {1, 1, 1}}  // L shape
};

struct Tetromino {
    vector<vector<int>> shape;
    int x, y;
};    

Tetromino currentTetromino;

// Initialize grid
void initializeGrid() {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            grid[i][j] = '.';
}

// Print grid without flickering
void printGrid() {
    char tempGrid[HEIGHT][WIDTH];

    // Copy grid to temp
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            tempGrid[i][j] = grid[i][j];

    // Place the active tetromino on tempGrid
    for (int i = 0; i < currentTetromino.shape.size(); i++)
        for (int j = 0; j < currentTetromino.shape[i].size(); j++)
            if (currentTetromino.shape[i][j])
                tempGrid[currentTetromino.y + i][currentTetromino.x + j] = '#';

    // Print buffer (fixes flickering)
    stringstream buffer;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            buffer << tempGrid[i][j] << " ";
        buffer << "\n";
    }
    buffer << "Score: " << score << "\n";

    cout << "\x1B[H" << buffer.str(); // Fix for `to_string()` issue
}

// Check if movement is valid
bool canMove(int dx, int dy, vector<vector<int>> shape) {
    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j]) {
                int newX = currentTetromino.x + j + dx;
                int newY = currentTetromino.y + i + dy;
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || grid[newY][newX] != '.')
                    return false;
            }
        }
    }
    return true;
}

// **Fixed Rotate Function (Supports Any Rectangular Tetromino)**
void rotateTetromino() {
    int rows = currentTetromino.shape.size();
    int cols = currentTetromino.shape[0].size();
    vector<vector<int>> rotated(cols, vector<int>(rows, 0));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            rotated[j][rows - 1 - i] = currentTetromino.shape[i][j];

    if (canMove(0, 0, rotated))
        currentTetromino.shape = rotated;
}

// Place tetromino on grid
void placeTetromino() {
    for (int i = 0; i < currentTetromino.shape.size(); i++)
        for (int j = 0; j < currentTetromino.shape[i].size(); j++)
            if (currentTetromino.shape[i][j])
                grid[currentTetromino.y + i][currentTetromino.x + j] = '#';
}

// Clear full lines & update score
void clearLines() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < WIDTH; j++)
            if (grid[i][j] == '.')
                full = false;

        if (full) {
            for (int k = i; k > 0; k--)
                for (int j = 0; j < WIDTH; j++)
                    grid[k][j] = grid[k - 1][j];

            for (int j = 0; j < WIDTH; j++)
                grid[0][j] = '.';

            score += 100;
            i++; // Check same row after shifting
        }
    }
}

// Handle user input
void handleInput() {
    while (_kbhit()) {
        char ch = _getch();
        if (ch == 75 && canMove(-1, 0, currentTetromino.shape)) // Left Arrow
            currentTetromino.x--;
        else if (ch == 77 && canMove(1, 0, currentTetromino.shape)) // Right Arrow
            currentTetromino.x++;
        else if (ch == 80 && canMove(0, 1, currentTetromino.shape)) // Down Arrow
            currentTetromino.y++;
        else if (ch == 72) // Up Arrow (Rotate)
            rotateTetromino();
        else if (ch == 32) // Spacebar (Hard Drop)
            while (canMove(0, 1, currentTetromino.shape)) currentTetromino.y++;
    }
    Sleep(50);
}

// Spawn a new tetromino
void spawnTetromino() {
    currentTetromino.shape = tetrominoes[rand() % tetrominoes.size()];
    currentTetromino.x = WIDTH / 2 - 1;
    currentTetromino.y = 0;

    while (_kbhit()) _getch(); // Flush input buffer

    if (!canMove(0, 0, currentTetromino.shape)) { // Game Over
        printGrid();
        cout << "Game Over! Final Score: " << score << endl;
        exit(0);
    }
}

// Main game loop
int main() {
    srand(time(0));
    initializeGrid();
    spawnTetromino();
    cout << "\x1B[2J\x1B[H"; // Clear screen once before loop

    while (true) {
        printGrid();
        handleInput();

        if (canMove(0, 1, currentTetromino.shape))
            currentTetromino.y++;
        else {
            placeTetromino();
            clearLines();
            spawnTetromino();
        }

        Sleep(1000);
    }

    
    return 0;
}
