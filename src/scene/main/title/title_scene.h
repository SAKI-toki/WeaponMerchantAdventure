#pragma once
#include "../../scene.h"
class TitleScene :public Scene
{
public:
	void Init()final;
	SCENE Update()final;
	void Render()final;
	void Destroy()final;
};