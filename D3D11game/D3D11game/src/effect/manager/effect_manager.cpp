#include "effect_manager.h"
void EffectManager::AddEffect(const Effect& effect)
{
	effect_list.push_front(effect);
}

void EffectManager::Update()
{
	auto itr = std::begin(effect_list);
	while (itr != std::end(effect_list))
	{
		if (itr->Update())
		{
			itr = effect_list.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void EffectManager::Render()
{
	for (auto&& e : effect_list)
	{
		e.Render();
	}
}

void EffectManager::Clear()
{
	effect_list.clear();
}