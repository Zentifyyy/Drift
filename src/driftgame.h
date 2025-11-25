#pragma once
#include <raylib.h>
#include <string>

class DriftGame {
public:

	DriftGame();

	~DriftGame();

public:

	void Update();

private:
	
	void DrawDeadUI();

	void Died();

	void Score();

	bool RectCollisionCheck(Vector2 Rect1Pos, Vector2 Rect1Size, Vector2 Rect2Pos, Vector2 Rect2Size);

	void DrawBackground();

	void DrawScissors(Vector2& pos) const;

	void DrawPlayer();

	bool IsMouseHoveringRect(Vector2& rectPos, Vector2& rectSize);

	void LoadTextures();

	void UpdateSine();

	void UnloadTextures() const;

private:

	Vector2 m_ButtonSize{ 200, 50 };
	Vector2 m_ButtonPos{ GetScreenWidth() / 2 - m_ButtonSize.x / 2, 200 };

	bool m_IsDead{ 0 };

	Texture m_PlayerCharacter;
	Texture m_Scissors;
	Texture m_Background;

	float m_BackgroundX = 0;

	Vector2 m_PlayerPos{ 100 , (float)GetScreenHeight() / 2 };
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