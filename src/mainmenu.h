#pragma once
#include <raylib.h>
#include "utils.h"

class MainMenu {

public: // Constructer + Destructer

	MainMenu(Vector2 windowSize);

	~MainMenu();

public: // Public Functions

	void Update();

private: // Private Functions

	void DrawPlayer();

	void LoadTextures();

	void UnloadTextures() const;

public:

	bool IsMenuActive = true;
	bool CloseGame = false;

private: // Private Variables

	Texture m_Glider;
	Texture m_Background;

	Vector2 m_ButtonSize{ 200, 50 };

	Vector2 m_PlayerPos{ };
	float m_PlayerRot = 0;
	float m_PlayerScale = 0.1f;

	Vector2 m_PlayRectPos{};

	Color m_PlayButtonCol = WHITE;

	float m_Sine = 0;
};