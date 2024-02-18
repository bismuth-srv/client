#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>

int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL); // Initialize console on the bottom screen

	printf("Hello, world!\n");

	// Initialize grid variables
	const int GRID_SIZE = 5;
	const int CELL_SIZE = 20;
	const int GRID_OFFSET_X = 20;
	const int GRID_OFFSET_Y = 20;
	bool grid[GRID_SIZE][GRID_SIZE] = { false };

	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;

		// Clear top screen
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
		gfxSwapBuffers();

		// Draw grid on top screen
		for (int i = 0; i < GRID_SIZE; i++)
		{
			for (int j = 0; j < GRID_SIZE; j++)
			{
				u32 color = grid[i][j] ? RGB565(255, 255, 255) : RGB565(0, 0, 0);
				C2D_DrawRectSolid(GFX_TOP, GRID_OFFSET_X + i * CELL_SIZE, GRID_OFFSET_Y + j * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
			}
		}

		// Update grid based on user input
		hidScanInput();
		u32 kHeld = hidKeysHeld();
		touchPosition touch;
		hidTouchRead(&touch);
		int cellX = (touch.px - GRID_OFFSET_X) / CELL_SIZE;
		int cellY = (touch.py - GRID_OFFSET_Y) / CELL_SIZE;
		if (cellX >= 0 && cellX < GRID_SIZE && cellY >= 0 && cellY < GRID_SIZE)
		{
			if (kHeld & KEY_TOUCH)
				grid[cellX][cellY] = true;
			else if (kHeld & KEY_TOUCH)
				grid[cellX][cellY] = false;
		}
	}

	gfxExit();
	return 0;
}
