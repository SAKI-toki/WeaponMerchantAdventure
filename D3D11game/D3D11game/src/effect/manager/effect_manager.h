#pragma once
#include <saki/singleton/singleton.h>
#include "../../common/common.h"
#include <saki/transform/transform.h>
#include "../../sprite/sprite.h"
#include <list>
#include "../effect.h"

class EffectManager :public saki::Singleton<EffectManager>
{
	std::list<Effect> effect_list;
public:
	void AddEffect(const Effect&);
	void Update();
	void Render();
	void Clear();
};