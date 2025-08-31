#include "mainmenu.cpp"
#include "driftgame.cpp"

int main()
{
	MainMenu menu;
	DriftGame game;

	bool closeGame = false;

	SearchAndSetResourceDir("resources");
	
	Sound BackgroundMusic = LoadSound("BackgroundMusic.wav");

	while (!closeGame)
	{
		if (menu.CloseGame || WindowShouldClose()) {
			closeGame = true;
		}

		if (!IsSoundPlaying(BackgroundMusic)) {
			PlaySound(BackgroundMusic);
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

	UnloadSound(BackgroundMusic);
}