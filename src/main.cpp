#include "mainmenu.h"
#include "driftgame.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame();

MainMenu menu({900,600});
DriftGame game;

bool closeGame = false;

int main()
{
	#if defined(PLATFORM_WEB)
		emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
	#else

		SetTargetFPS(60);

		while (!closeGame)
		{
			UpdateDrawFrame();
		}

	#endif

	CloseWindow();
}


void UpdateDrawFrame(void)
{
	BeginDrawing();

	if (menu.CloseGame || WindowShouldClose()) {
		closeGame = true;
	}

	BeginDrawing();

	if (menu.IsMenuActive)
	{
		menu.Update();
	}
	else
	{
		game.Update();
	}

	EndDrawing();
}