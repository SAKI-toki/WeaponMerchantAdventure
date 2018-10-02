/**
* @file scene.h
* @brief マネージャーを含まないシーンのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once
#include "base/scene_base.h"
/**
* @brief マネージャーを含まないシーンのスーパークラス
* @details マネージャーはこのクラスを保持する
*/
class Scene :public SceneBase
{
public:
	virtual ~Scene() {}
	virtual SCENE Update() = 0;
};