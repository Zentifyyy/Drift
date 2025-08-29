#include "mainmenu.cpp"
#include "driftgame.cpp"

int main ()
{
	MainMenu menu;
	DriftGame game;
	
	while (!WindowShouldClose())
	{
		BeginDrawing();

		if (!menu.IsMenuActive)
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
