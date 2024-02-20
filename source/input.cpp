#include <3ds.h>
#include <chrono>
#include <thread>
#include <citro2d.h>
#include <cstdio>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define numColumns 8
#define numRows 4
#define GRID_SIZE 50

int selectedSquareX = 0;
int selectedSquareY = 40;
int selected = 0;

int maxpos = 100;

void circlePadInput() {
    circlePosition pos;
    hidCircleRead(&pos);

    if (pos.dx > maxpos) {
        selectedSquareX += GRID_SIZE;
        if (selectedSquareX >= SCREEN_WIDTH)
            selectedSquareX = 40;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (pos.dx < -maxpos) {
        selectedSquareX -= GRID_SIZE;
        if (selectedSquareX < 40)
            selectedSquareX = 40;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (pos.dy < maxpos) {
        selectedSquareY += GRID_SIZE;
        if (selectedSquareY >= SCREEN_HEIGHT)
            selectedSquareY = 40;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (pos.dy > -maxpos) {
        selectedSquareY -= GRID_SIZE;
        if (selectedSquareY < 40)
            selectedSquareY = 200;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void drawSelectedSquare() {
	C2D_DrawLine(selectedSquareX, selectedSquareY, C2D_Color32(64, 64, 64, 1) , selectedSquareX + SCREEN_WIDTH, selectedSquareY, C2D_Color32(64, 64, 64, 1), 1, 0);
    printf("selectedSquareX: %d\n", selectedSquareX);
    printf("selectedSquareY: %d\n", selectedSquareY);
}