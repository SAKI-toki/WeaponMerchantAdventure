#pragma once
#include "../sprite/sprite.h"
class EffectManager;
class Effect
{
	friend class EffectManager;
	size_t num;
	size_t life_time;
	float time_count = 0.0f;
	Sprite sprite;
	float speed;
	Vec3 start_pos;
	struct Param
	{
		Transform transform;
		Vec3 vector;
		Param(Transform&& t, Vec3&& v) :transform(t), vector(v) {}
	};
	std::vector<Param> param;

	bool Update();
	void Render();
	void Destroy();
public:
	void Init(std::string, WCHAR*, const float, const float);
	void SetParam(const size_t, const size_t, const float);
	void Start(const Vec3&);
};