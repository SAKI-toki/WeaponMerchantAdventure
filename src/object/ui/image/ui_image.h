#pragma once
#include "../../../rendering/sprite/sprite.h"
#include "../../../transform/transform.h"

class UiImage
{
	Transform transform;
	Sprite sprite;
	float percent = 1.0f;
	LONG max_w, max_h;
public:
	bool enabled = true;
	void Init(const std::string&, WCHAR*, const LONG, const LONG, const VEC2&, const float, const float);
	void Render();
	void SetColor(const float r, const float g, const float b, const float a)
	{
		sprite.ColorChange(r, g, b, a);
	}
	void SetPercent(const float percentage) { percent = percentage; }
};