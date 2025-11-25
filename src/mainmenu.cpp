#include "mainmenu.h"


MainMenu::MainMenu(Vector2 windowSize) {

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(windowSize.x, windowSize.y, "Drift");

	m_PlayRectPos = { (GetScreenWidth() - m_ButtonSize.x) / 2, (float)(GetScreenHeight() / 2) - 12.5f };

	m_PlayerPos =  { 0, 185 };
		
	LoadTextures();
};

MainMenu::~MainMenu() { // Close Window

	UnloadTextures();

	CloseWindow();
}

void MainMenu::Update() {

	ClearBackground(WHITE);
	DrawTexture(m_Background,0,0,WHITE);

	UpdateSine();
		
	DrawText("Drift", (GetScreenWidth() - MeasureText("Drift", 50)) / 2, 100, 50, WHITE);
	DrawPlayer();

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

void MainMenu::DrawPlayer() {

	m_PlayerRot += m_Sine / 2;
	m_PlayerPos.y += m_Sine / 4;

	m_PlayerPos.x += GetFrameTime() * 100;

	if (m_PlayerPos.x >= GetScreenWidth()) {
		m_PlayerPos.x = -m_Glider.width * m_PlayerScale;
	}

	DrawTextureEx( m_Glider , m_PlayerPos , m_PlayerRot , m_PlayerScale , WHITE);
}

void MainMenu::UpdateSine() {

	if (m_Sine >= 1) {
		m_SineUp = false;
	}
	else if (m_Sine <= -1) {
		m_SineUp = true;
	}

	if (m_SineUp) {
		m_Sine += GetFrameTime() * 3;
	}
	else {
		m_Sine -= GetFrameTime() * 3;
	}
}

bool MainMenu::IsMouseHoveringRect(Vector2& rectPos, Vector2& rectSize) {

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
	
void MainMenu::LoadTextures() {

	m_Glider = LoadTexture("resources/Glider.png");
		
	m_Background = LoadTexture("resources/Background.png");
}

void MainMenu::UnloadTextures() const {
	UnloadTexture(m_Glider);
	UnloadTexture(m_Background);
}