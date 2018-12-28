#include "effect.h"
#include "manager/effect_manager.h"
#include <saki/random/random.h>
#include <saki/pi.h>

bool Effect::Update()
{
	if (++time_count > life_time)return true;
	for (auto&& p : param)
	{
		p.transform.move(Vec3(p.vector.x, p.vector.y, 0)*speed);
	}
	sprite.ColorChange(1.0f, 1.0f, 1.0f, 1.0f - (time_count / life_time));
	return false;
}
void Effect::Render()
{
	for (auto&& p : param)
	{
		sprite.Render(p.transform + Transform{ start_pos,saki::vector3_zero<float>,saki::vector3_zero<float> });
	}
}
void Effect::Destroy()
{

}

void Effect::Init(std::string name, WCHAR* path, const float w, const float h)
{
	sprite.Init(name, path, Vec2(w, h));
}

void Effect::SetParam(const size_t n, const size_t life, const float _speed)
{
	num = n;
	life_time = life;
	speed = _speed;
	param.reserve(num);
	for (size_t i = 0; i < num; ++i)
	{
		auto angle = saki::random(0.0f, saki::PI<float> * 2);

		param.push_back(Param(Transform(
			{ saki::random(-10.0f,10.0f),saki::random(-10.0f,10.0f),0 }, saki::vector3_zero<float>, saki::vector3_one<float>),
			{ std::cos(angle),std::sin(angle),0 }));
	}
}

void Effect::Start(const Vec3& start)
{
	start_pos = start;
	EffectManager::getinstance()->AddEffect(*this);
}
