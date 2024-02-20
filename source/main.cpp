#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <chrono>
#include <thread>
#include <citro2d.h>
#include <curl/curl.h>
#include <input.h>
#include <curl.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define numColumns 8
#define numRows 4
#define GRID_SIZE 50

void drawUI() {
	C2D_DrawRectSolid(0, 0, 2, SCREEN_WIDTH, SCREEN_HEIGHT, C2D_Color32(91, 91, 91, 1));
	C2D_DrawRectSolid(0, 0, 1, SCREEN_WIDTH, 40, C2D_Color32(57, 57, 57, 1));
	drawSelectedSquare();
}

int main() {
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);
	printf("Starting Sulfur UI...\n");
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	link3dsStdio();
	while (aptMainLoop()) {
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;

		hidScanInput();

		C2D_TargetClear(top, C2D_Color32(57, 57, 57, 1));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);

		circlePadInput();
		drawUI();
		C3D_FrameEnd(0);
	}
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}