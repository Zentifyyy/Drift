#include "utils.h"

bool m_SineUp;

bool IsMouseHoveringRect(const Vector2& rectPos, const Vector2& rectSize) {

	Vector2 mousePos = GetMousePosition();

	if (mousePos.y > rectPos.y && mousePos.y < rectPos.y + rectSize.y) {

		if (mousePos.x > rectPos.x && mousePos.x < rectPos.x + rectSize.x) {
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

bool RectCollisionCheck(const Vector2& Rect1Pos, const Vector2& Rect1Size, const Vector2& Rect2Pos, const Vector2& Rect2Size) {
	if (Rect1Pos.x > Rect2Pos.x && Rect1Pos.x + Rect1Size.x < Rect2Pos.x + Rect2Size.x)
	{
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

void UpdateSine(float& sine){
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