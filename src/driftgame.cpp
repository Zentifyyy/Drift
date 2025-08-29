#include <raylib.h>
#include <resource_dir.h>
#include <iostream>

class DriftGame {
public:
	
	DriftGame() {
		LoadTextures();

		m_ScissorsPos = { (float)GetScreenWidth(), (float)GetScreenHeight() / 2 - ( m_Scissors.height / 2) * .6f };
	}

	~DriftGame() {
		UnloadTextures();
	}

public:

	void Update() {
		
		ClearBackground(SKYBLUE);

		UpdateSine();

		DrawPlayer();

		DrawScissors();
	}

private:

	void DrawScissors() {

		m_ScissorsPos.x -= GetFrameTime() * m_ScissorsScrollSpeed;

		DrawTextureEx(m_Scissors, m_ScissorsPos , 0 , .6f ,WHITE);
	}

	void DrawPlayer() {

		m_PlayerRot += sine / 2;
		m_PlayerPos.y += sine / 4;

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
	}

	void UnloadTextures() {
		UnloadTexture(m_PlayerCharacter);
		UnloadTexture(m_Scissors);
	}

private:

	Texture m_PlayerCharacter;
	Texture m_Scissors;

	Vector2 m_PlayerPos{ 100 , (float)GetScreenHeight() / 2};
	float m_PlayerRot = -10;

	float sine = 0;
	bool m_SineUp = true;

	Vector2 m_ScissorsPos{};
	const int m_ScissorsScrollSpeed = 300;
};