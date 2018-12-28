#pragma once
#include "../../../sprite/sprite.h"
#include <saki/transform/transform.h>

class UiImage
{
	Transform transform;
	Sprite sprite;
	float percent = 1.0f;
	float max_w, max_h;
public:
	bool enabled = true;
	void Init(const std::string&, WCHAR*, const float, const float, const Vec3&, const Vec3&, const Vec3&);
	void Render();
	void SetColor(const float r, const float g, const float b, const float a)
	{
		sprite.ColorChange(r, g, b, a);
	}
	void SetPercent(const float percentage) { percent = percentage; }
};