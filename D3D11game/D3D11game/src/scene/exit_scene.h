#pragma once
#include "scene.h"
extern void ExitGame();
class ExitScene :public Scene
{
public:
	void Init()final
	{
		ExitGame();
	}
	std::shared_ptr<Scene> Update(std::shared_ptr<Scene>& p)final { return p; }
	void Render() final {}
	void Destroy()final {}
};