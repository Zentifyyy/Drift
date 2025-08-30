#include "mainmenu.cpp"
#include "driftgame.cpp"

int main()
{
	MainMenu menu;
	DriftGame game;

	bool closeGame = false;

	while (!closeGame)
	{
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
}