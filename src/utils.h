#pragma once
#include "raylib.h"

bool IsMouseHoveringRect(const Vector2& rectPos, const Vector2& rectSize);

bool RectCollisionCheck(const Vector2& Rect1Pos, const Vector2& Rect1Size, const Vector2& Rect2Pos, const Vector2& Rect2Size);

void UpdateSine(float& sine);