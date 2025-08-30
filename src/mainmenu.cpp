#include <raylib.h>
#include <resource_dir.h>
#include <iostream>

class MainMenu{

public: // Constructer + Destructer

	MainMenu() { // Initialise Window

		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

		InitWindow( m_WindowSize.x , m_WindowSize.y , "Drift");

		m_PlayRectPos = { (GetScreenWidth() - m_ButtonSize.x) / 2, (float)(GetScreenHeight() / 2) - 12.5f };

		m_ExitRectPos = { (GetScreenWidth() - m_ButtonSize.x) / 2, (float)(GetScreenHeight() / 2) + 25 + m_ButtonSize.y };

		LoadTextures();
	};

	~MainMenu() { // Close Window

		UnloadTextures();

		CloseWindow();
	}

public: // Public Functions

	void Update() {

		ClearBackground(SKYBLUE);
		
		DrawText("Drift", (GetScreenWidth() - MeasureText("Drift", 50)) / 2, 100, 50, WHITE);
		DrawTextureEx(m_Glider, { (float)GetScreenWidth() / 2 + MeasureText("Drift", 50) - 50, 100}, 0, 0.2f, WHITE);
		
		DrawRectangle(m_ExitRectPos.x, m_ExitRectPos.y, m_ButtonSize.x, m_ButtonSize.y, m_ExitButtonCol);
		DrawText("Exit", (GetScreenWidth() - MeasureText("Exit", 25)) / 2, (GetScreenHeight() / 2) + 90, 25, BLACK);

		if (IsMouseHoveringRect(m_ExitRectPos, m_ButtonSize)) {
			
			m_ExitButtonCol = LIGHTGRAY;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				m_ExitButtonCol = GRAY;
				CloseGame = true;
			}
		}
		else {
			m_ExitButtonCol = WHITE;
		}

		DrawRectangle( m_PlayRectPos.x, m_PlayRectPos.y, m_ButtonSize.x , m_ButtonSize.y, m_PlayButtonCol );
		DrawText("Play", (GetScreenWidth() - MeasureText("Play", 25)) / 2, (GetScreenHeight() / 2), 25, BLACK);
	
		if (IsMouseHoveringRect(m_PlayRectPos, m_ButtonSize)) {

			m_PlayButtonCol = LIGHTGRAY;
			
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				m_PlayButtonCol = GRAY;
				IsMenuActive = false;
			}
		}
		else {
			m_PlayButtonCol = WHITE;
		}
	
	}

private: // Private Functions

	bool IsMouseHoveringRect(Vector2& rectPos, Vector2& rectSize) {

		float rectYmax = rectPos.y + rectSize.y;
		float rectYmin = rectPos.y;

		float rectXmax = rectPos.x + rectSize.x;
		float rectXmin = rectPos.x;

		Vector2 mousePos = GetMousePosition();
		
		if (mousePos.y > rectYmin && mousePos.y < rectYmax) {

			if (mousePos.x > rectXmin && mousePos.x < rectXmax ) {
				return true;
			}
			else {
				return false;
			}
		}
		else
		{
			return false;
		}
		
	}
	
	void LoadTextures() {

		SearchAndSetResourceDir("resources");

		m_Glider = LoadTexture("Glider.png");
	}

	void UnloadTextures() {
		UnloadTexture(m_Glider);
	}

public:

	bool IsMenuActive = true;
	bool CloseGame = false;

private: // Private Variables

	Texture m_Glider;

	Vector2 m_WindowSize{ 900 , 600 };

	Vector2 m_ButtonSize{ 200, 50 };

	Vector2 m_ExitRectPos{};
	Vector2 m_PlayRectPos{};

	Color m_ExitButtonCol = WHITE;
	Color m_PlayButtonCol = WHITE;
};