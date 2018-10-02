#pragma once
#include "base/scene_base.h"
class Scene :public SceneBase
{
public:
	virtual ~Scene() {}
	virtual SCENE Update() = 0;
};