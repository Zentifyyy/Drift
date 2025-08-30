#include <raylib.h>
#include <resource_dir.h>
#include <iostream>
#include <string>


class DriftGame {
public:
	
	DriftGame() {
		LoadTextures();

		m_ScissorsPos = { (float)GetScreenWidth(), (float)GetScreenHeight() / 2 - ( m_Scissors.height / 2) * .75f };
		
		m_ScissorsPosTwo = { m_ScissorsPos.x + GetScreenWidth() / 3 + (m_Scissors.width * 0.75f) , m_ScissorsPos.y };
	
		m_ScissorsPosThree = { m_ScissorsPos.x + ((GetScreenWidth() / 3) + (m_Scissors.width * 0.75f)) * 2 , m_ScissorsPos.y };
		
		m_ScissorsPos.y += GetRandomValue(-m_ScissorMaxDist , m_ScissorMaxDist);
		
		m_ScissorsPosTwo.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
		
		m_ScissorsPosThree.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
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

		DrawScissors(m_ScissorsPos);

		DrawScissors(m_ScissorsPosTwo);

		DrawScissors(m_ScissorsPosThree);

		Score();
	}

private:

	void Died() {

		m_ScissorsPos = { (float)GetScreenWidth(), (float)GetScreenHeight() / 2 - (m_Scissors.height / 2) * .75f };

		m_ScissorsPosTwo = { m_ScissorsPos.x + GetScreenWidth() / 3 + (m_Scissors.width * 0.75f) , m_ScissorsPos.y };

		m_ScissorsPosThree = { m_ScissorsPos.x + ((GetScreenWidth() / 3) + (m_Scissors.width * 0.75f)) * 2 , m_ScissorsPos.y };

		m_ScissorsPos.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);

		m_ScissorsPosTwo.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);

		m_ScissorsPosThree.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);

		m_PlayerPos = { 100 , (float)GetScreenHeight() / 2 };
		
		m_Score = 0;
	}

	void Score(){

		DrawText(std::to_string(m_Score).c_str(), GetScreenWidth() / 2 + MeasureText(std::to_string(m_Score).c_str(), 50) / 2, 100, 50, WHITE);

		// If player Out of bounds
		if (m_PlayerPos.y <= 0 || m_PlayerPos.y >= GetScreenHeight()) {
			Died();
		}

		// Collision for Scissors

		if (m_ScissorsPos.x - m_PlayerPos.x < 100 && m_ScissorsPos.x - m_PlayerPos.x + m_Scissors.width > 0) {
			m_ClosestScissorPos = m_ScissorsPos;
		}
		else if (m_ScissorsPosTwo.x - m_PlayerPos.x < 100 && m_ScissorsPosTwo.x - m_PlayerPos.x + m_Scissors.width > 0) {
			m_ClosestScissorPos = m_ScissorsPosTwo;
		}
		else if (m_ScissorsPosThree.x - m_PlayerPos.x < 100 && m_ScissorsPosThree.x - m_PlayerPos.x + m_Scissors.width > 0) {
			m_ClosestScissorPos = m_ScissorsPosThree;
		}
		else {
			return;
		}

		if (RectCollisionCheck(m_PlayerPos, { (float)m_PlayerCharacter.width * 0.1f, (float)m_PlayerCharacter.height * 0.1f }, m_ClosestScissorPos, { (float)m_Scissors.width * 0.85f , ((m_Scissors.height * 0.85f) / 2) - 160 })
			|| RectCollisionCheck(m_PlayerPos, { (float)m_PlayerCharacter.width * 0.1f, (float)m_PlayerCharacter.height * 0.1f }, { m_ClosestScissorPos.x, m_ClosestScissorPos.y + m_Scissors.height / 2 - 30 }, { (float)m_Scissors.width * 0.85f , ((m_Scissors.height * 0.85f) / 2) }))
		{
			Died();
		}

		if (RectCollisionCheck({m_PlayerPos}, { (float)m_PlayerCharacter.width * 0.1f, (float)m_PlayerCharacter.height * 0.1f }, { m_ClosestScissorPos.x - 100 + m_Scissors.width *0.85f, m_ClosestScissorPos.y + (m_Scissors.height / 2) - 260 }, { m_PlayerCharacter.width * 0.1f + 4, 260 })) {
			m_Score++;
			std::cout << m_Score << "\n";
		}
	}

	bool RectCollisionCheck(Vector2 Rect1Pos, Vector2 Rect1Size, Vector2 Rect2Pos, Vector2 Rect2Size) {

		//DrawRectangle(Rect1Pos.x,Rect1Pos.y,Rect1Size.x,Rect1Size.y, ColorAlpha(GREEN, 0.5f));

		//DrawRectangle(Rect2Pos.x, Rect2Pos.y, Rect2Size.x, Rect2Size.y, ColorAlpha(VIOLET,0.5f));

		if (Rect1Pos.x > Rect2Pos.x && Rect1Pos.x + Rect1Size.x < Rect2Pos.x + Rect2Size.x) {
			
			if (Rect1Pos.y > Rect2Pos.y && Rect1Pos.y + Rect1Size.y < Rect2Pos.y + Rect2Size.y) {
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	}

	void DrawBackground() {

		m_BackgroundX -= GetFrameTime() * 100;

		if (m_BackgroundX <= -m_Background.width) {
			m_BackgroundX = 0;
		}

		DrawTexture(m_Background , m_BackgroundX , 0 , WHITE);

		DrawTexture(m_Background, m_BackgroundX + m_Background.width, 0, WHITE);
	}

	void DrawScissors(Vector2& pos) {

		pos.x -= GetFrameTime() * m_ScissorsScrollSpeed;

		if (pos.x + (m_Scissors.width * 0.85f) <= 0) {
			pos.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
			pos.x += GetScreenWidth() * 1.5f;
		}


		DrawTextureEx(m_Scissors, pos,
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

	const int m_ScissorMaxDist = 30;

	const int m_ScissorsScrollSpeed = 200;

	Vector2 m_ClosestScissorPos{};

	float m_Gravity = 4.5f;

	int m_Score = 0;
};