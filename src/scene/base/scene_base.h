#pragma once

enum class SCENE { TITLE, SELECT, GAME };

class SceneBase
{
public:
	virtual ~SceneBase() {}

	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};