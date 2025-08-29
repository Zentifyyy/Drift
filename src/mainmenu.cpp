#include <raylib.h>
#include <resource_dir.h>
#include <iostream>

class MainMenu{

public: // Constructer + Destructer

	MainMenu() { // Initialise Window

		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);

		InitWindow( m_WindowSize.x , m_WindowSize.y , "Drift");

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
		
		Vector2 rectPos{ (GetScreenWidth() - m_ButtonSize.x) / 2, (GetScreenHeight() / 2) - 12.5 };
		
		DrawRectangle( rectPos.x, rectPos.y, m_ButtonSize.x , m_ButtonSize.y, WHITE );
		DrawText("Play", (GetScreenWidth() - MeasureText("Play", 25)) / 2, (GetScreenHeight() / 2), 25, BLACK);
	
		if (IsMouseHoveringRect(rectPos, m_ButtonSize) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			IsMenuActive = false;
		}
	
	}

private: // Private Functions

	bool IsMouseHoveringRect(Vector2& rectPos, Vector2& rectSize) {

		float rectYmax = rectPos.y + (rectSize.y / 2);
		float rectYmin = rectPos.y - (rectSize.y / 2);

		float rectXmax = rectPos.x + (rectSize.x / 2);
		float rectXmin = rectPos.x - (rectSize.x / 2);

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

private: // Private Variables

	Texture m_Glider;

	Vector2 m_WindowSize{ 900 , 600 };

	Vector2 m_ButtonSize{ 200, 50 };
	
};