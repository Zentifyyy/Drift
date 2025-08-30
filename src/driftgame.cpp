#include <raylib.h>
#include <resource_dir.h>
#include <iostream>

class DriftGame {
public:
	
	DriftGame() {
		LoadTextures();

		m_ScissorsPos = { (float)GetScreenWidth(), (float)GetScreenHeight() / 2 - ( m_Scissors.height / 2) * .75f };
		
		m_ScissorsPosTwo = { m_ScissorsPos.x + GetScreenWidth() / 3 + (m_Scissors.width * 0.75f) , m_ScissorsPos.y };
	
		m_ScissorsPosThree = { m_ScissorsPos.x + ((GetScreenWidth() / 3) + (m_Scissors.width * 0.75f)) * 2 , m_ScissorsPos.y };
		
		m_ScissorYOffset = GetRandomValue(-m_ScissorMaxDist , m_ScissorMaxDist);
		
		m_ScissorYOffsetTwo = GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
		
		m_ScissorYOffsetThree = GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
	}

	~DriftGame() {
		UnloadTextures();
	}

public:

	void Update() {
		
		ClearBackground(SKYBLUE);

		DrawBackground();

		UpdateSine();

		DrawPlayer();

		DrawScissors(m_ScissorsPos, m_ScissorYOffset );

		DrawScissors(m_ScissorsPosTwo, m_ScissorYOffsetTwo );

		DrawScissors(m_ScissorsPosThree, m_ScissorYOffsetThree );
	}

private:

	void DrawBackground() {

		m_BackgroundX -= GetFrameTime() * 100;

		if (m_BackgroundX <= -m_Background.width) {
			m_BackgroundX = 0;
		}

		DrawTexture(m_Background , m_BackgroundX , 0 , WHITE);

		DrawTexture(m_Background, m_BackgroundX + m_Background.width, 0, WHITE);
	}

	void DrawScissors(Vector2& pos, float& yOffset) {

		pos.x -= GetFrameTime() * m_ScissorsScrollSpeed;

		if (pos.x + (m_Scissors.width * 0.85f) <= 0) {
			yOffset = GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
			pos.x += GetScreenWidth() * 1.5f;
		}

		DrawTextureEx(m_Scissors, { pos.x,pos.y + yOffset },
			0, 0.75f, WHITE);
	}

	void DrawPlayer() {

		// Swaying
		m_PlayerRot += sine / 2;
		m_PlayerPos.y += sine / 4;

		// Gravity
		dy += m_Gravity * GetFrameTime();

		// Jump
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE)) {
			dy = -m_Gravity + 1.5f;
		}
		
		m_PlayerPos.y += dy;

		// Draw Player
		DrawTextureEx (m_PlayerCharacter , m_PlayerPos , m_PlayerRot , .1f , WHITE);
	}

	void UpdateSine() {

		if (sine >= 1) {
			m_SineUp = false;
		}
		else if (sine <= -1) {
			m_SineUp = true;
		}

		if (m_SineUp) {
			sine += GetFrameTime() * 3;
		}
		else {
			sine -= GetFrameTime() * 3;
		}
	}

	void LoadTextures() {
		SearchAndSetResourceDir("resources");

		m_PlayerCharacter = LoadTexture("Glider.png");
		m_Scissors = LoadTexture("Scissors.png");
		m_Background = LoadTexture("Background.png");
	}

	void UnloadTextures() {
		UnloadTexture(m_PlayerCharacter);
		UnloadTexture(m_Scissors);
		UnloadTexture(m_Background);
	}

private:

	Texture m_PlayerCharacter;
	Texture m_Scissors;
	Texture m_Background;

	float m_BackgroundX = 0;

	Vector2 m_PlayerPos{ 100 , (float)GetScreenHeight() / 2};
	float m_PlayerRot = -10;

	float dy = 0;

	float sine = 0;
	bool m_SineUp = true;

	Vector2 m_ScissorsPos{};
	Vector2 m_ScissorsPosTwo{};
	Vector2 m_ScissorsPosThree{};

	float m_ScissorYOffset = 0;
	float m_ScissorYOffsetTwo = 0;
	float m_ScissorYOffsetThree = 0;

	const int m_ScissorMaxDist = 75;

	const int m_ScissorsScrollSpeed = 200;

	float m_Gravity = 4.5f;
};