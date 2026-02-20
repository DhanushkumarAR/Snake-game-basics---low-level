#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h> 

int width = 20, height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int gameOver;
int flag; 

void Setup() {
    gameOver = 0;
    flag = 0; 
    
    // Start head in the center
    x = width / 2;
    y = height / 2;
    
    // Spawn first fruit
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls"); // Clear screen buffer
    
    // Top wall
    for (int i = 0; i < width + 2; i++) printf("#");
    printf("\n");

    // Map rendering
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            if (j == 0) printf("#"); // Left wall
            
            if (i == y && j == x) printf("O"); // Head
            else if (i == fruitY && j == fruitX) printf("F"); // Fruit
            else {
                int printTail = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); // Tail segment
                        printTail = 1;
                    }
                }
                if (printTail == 0) printf(" "); // Blank space
            }
            
            if (j == width - 1) printf("#"); // Right wall
        }
        printf("\n"); 
    }

    // Bottom wall
    for (int i = 0; i < width + 2; i++) printf("#");
    printf("\n");
    
    printf("Score: %d\n", score);
    printf("Controls: WASD. Press 'x' to quit.\n");
}

void Input() {
    // Read input without pausing execution
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': flag = 1; break; 
            case 'd': flag = 2; break; 
            case 'w': flag = 3; break; 
            case 's': flag = 4; break; 
            case 'x': gameOver = 1; break; 
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    
    // Shift tail logic
    tailX[0] = x;
    tailY[0] = y;
    
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    // Apply movement
    switch (flag) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
        default: break;
    }
    
    // Boundary collision
    if (x < 0 || x >= width || y < 0 || y >= height) gameOver = 1;
    
    // Self collision
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = 1;
    }
    
    // Food consumption
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; 
    }
}

int main() {
    Setup(); 
    
    while (!gameOver) {
        Draw();  
        Input(); 
        Logic(); 
        Sleep(50); // Framerate cap
    }
    
    printf("\nGame Over! Final Score: %d\n", score);
    return 0;
}
