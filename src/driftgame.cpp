#include "driftgame.h"
#include "utils.h"

DriftGame::DriftGame() 
{
	LoadTextures();

	m_ScissorsPos = { (float)GetScreenWidth(), (float)GetScreenHeight() / 2 - ( m_Scissors.height / 2) * .75f };
		
	m_ScissorsPosTwo = { m_ScissorsPos.x + GetScreenWidth() / 3 + (m_Scissors.width * 0.75f) , m_ScissorsPos.y };
	
	m_ScissorsPosThree = { m_ScissorsPos.x + ((GetScreenWidth() / 3) + (m_Scissors.width * 0.75f)) * 2 , m_ScissorsPos.y };
		
	m_ScissorsPos.y += GetRandomValue(-m_ScissorMaxDist , m_ScissorMaxDist);
		
	m_ScissorsPosTwo.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
		
	m_ScissorsPosThree.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
}

DriftGame::~DriftGame() 
{
	UnloadTextures();
}

void DriftGame::Update() 
{
	ClearBackground(SKYBLUE);

	DrawBackground();

	if (!m_IsDead) 
	{
		UpdateSine(m_sine);

		DrawPlayer();

		DrawScissors(m_ScissorsPos);

		DrawScissors(m_ScissorsPosTwo);

		DrawScissors(m_ScissorsPosThree);

		Score();

		if (IsKeyPressed(KEY_ESCAPE))
			Died();
	}
	else
		DrawDeadUI();
}
	
void DriftGame::DrawDeadUI()
{
	DrawText(std::to_string(m_Score).c_str(), m_ButtonPos.x + m_ButtonSize.x / 2 - MeasureText(std::to_string(m_Score).c_str(), 70) / 2, 100, 70, WHITE);

	if (IsMouseHoveringRect(m_ButtonPos, m_ButtonSize)) 
	{
		DrawRectangle(m_ButtonPos.x, m_ButtonPos.y, m_ButtonSize.x, m_ButtonSize.y, GRAY);

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
		{
				m_IsDead = false;

				m_Score = 0;

				m_ScissorsPos = { (float)GetScreenWidth(), (float)GetScreenHeight() / 2 - (m_Scissors.height / 2) * .75f };

				m_ScissorsPosTwo = { m_ScissorsPos.x + GetScreenWidth() / 3 + (m_Scissors.width * 0.75f) , m_ScissorsPos.y };

				m_ScissorsPosThree = { m_ScissorsPos.x + ((GetScreenWidth() / 3) + (m_Scissors.width * 0.75f)) * 2 , m_ScissorsPos.y };

				m_ScissorsPos.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);

				m_ScissorsPosTwo.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);

				m_ScissorsPosThree.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);

				m_PlayerPos = { 100 , (float)GetScreenHeight() / 2 };
		}
	}
	else
		DrawRectangle(m_ButtonPos.x, m_ButtonPos.y, m_ButtonSize.x, m_ButtonSize.y, WHITE);

	DrawText("Play Again", m_ButtonPos.x + (m_ButtonSize.x / 2 - MeasureText("Play Again",32) / 2), m_ButtonPos.y + 10, 32, BLACK);
}

void DriftGame::Died() 
{
	m_IsDead = true;
}

void DriftGame::Score()
{
	DrawText(std::to_string(m_Score).c_str(), GetScreenWidth() / 2 + MeasureText(std::to_string(m_Score).c_str(), 50) / 2, 100, 50, WHITE);

	if (m_PlayerPos.y <= 0 || m_PlayerPos.y >= GetScreenHeight())
		Died();

	if (m_ScissorsPos.x - m_PlayerPos.x < 100 && m_ScissorsPos.x - m_PlayerPos.x + m_Scissors.width > 0) 
	{
		m_ClosestScissorPos = m_ScissorsPos;
		m_Scoring = false;
	}
	else if (m_ScissorsPosTwo.x - m_PlayerPos.x < 100 && m_ScissorsPosTwo.x - m_PlayerPos.x + m_Scissors.width > 0) 
	{
		m_ClosestScissorPos = m_ScissorsPosTwo;
		m_Scoring = false;
	}
	else if (m_ScissorsPosThree.x - m_PlayerPos.x < 100 && m_ScissorsPosThree.x - m_PlayerPos.x + m_Scissors.width > 0) 
	{
		m_ClosestScissorPos = m_ScissorsPosThree;
		m_Scoring = false;
	}
	else
		return;

	if (RectCollisionCheck(m_PlayerPos, { (float)m_PlayerCharacter.width * 0.1f, (float)m_PlayerCharacter.height * 0.1f }, m_ClosestScissorPos, { (float)m_Scissors.width * 0.85f , ((m_Scissors.height * 0.85f) / 2) - 160 })
		|| RectCollisionCheck(m_PlayerPos, { (float)m_PlayerCharacter.width * 0.1f, (float)m_PlayerCharacter.height * 0.1f }, { m_ClosestScissorPos.x, m_ClosestScissorPos.y + m_Scissors.height / 2 - 30 }, { (float)m_Scissors.width * 0.85f , ((m_Scissors.height * 0.85f) / 2) }))
	{
		Died();
	}

	if(!m_Scoring)
	if (RectCollisionCheck({m_PlayerPos}, { (float)m_PlayerCharacter.width * 0.1f, (float)m_PlayerCharacter.height * 0.1f }, { m_ClosestScissorPos.x - 100 + m_Scissors.width *0.85f, m_ClosestScissorPos.y + (m_Scissors.height / 2) - 260 }, { m_PlayerCharacter.width * 0.1f + 4, 260 })) 
	{	
		m_Scoring = true;
		m_Score++;
	}
}

void DriftGame::DrawBackground() 
{
	m_BackgroundX -= GetFrameTime() * 100;

	if (m_BackgroundX <= -m_Background.width)
		m_BackgroundX = 0;

	DrawTexture(m_Background , m_BackgroundX , 0 , WHITE);

	DrawTexture(m_Background, m_BackgroundX + m_Background.width, 0, WHITE);
}

void DriftGame::DrawScissors(Vector2& pos) const 
{
	pos.x -= GetFrameTime() * m_ScissorsScrollSpeed;

	if (pos.x + (m_Scissors.width * 0.85f) <= 0) 
	{
		pos.y += GetRandomValue(-m_ScissorMaxDist, m_ScissorMaxDist);
		pos.x += GetScreenWidth() * 1.5f;
	}

	DrawTextureEx(m_Scissors, pos, 0, 0.75f, WHITE);
}

void DriftGame::DrawPlayer() 
{
	// Swaying
	m_PlayerRot += m_sine / 2;
	m_PlayerPos.y += m_sine / 4;

	// Gravity
	dy += m_Gravity * GetFrameTime();

	// Jump
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
		dy = -m_Gravity + 1.5f;
		
	m_PlayerPos.y += dy;

	// Draw Player
	DrawTextureEx (m_PlayerCharacter , m_PlayerPos , m_PlayerRot , .1f , WHITE);
}

void DriftGame::LoadTextures() 
{
	m_PlayerCharacter = LoadTexture("resources/Glider.png");
	m_Scissors = LoadTexture("resources/Scissors.png");
	m_Background = LoadTexture("resources/Background.png");
}

void DriftGame::UnloadTextures() const 
{
	UnloadTexture(m_PlayerCharacter);
	UnloadTexture(m_Scissors);
	UnloadTexture(m_Background);
}