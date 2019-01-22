/**
* @file scene.h
* @brief マネージャーを含まないシーンのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once
#include "base/scene_base.h"
#include <memory>
/**
* @brief マネージャーを含まないシーンのスーパークラス
* @details マネージャーはこのクラスを保持する
*/
class Scene :public SceneBase
{
public:
	virtual ~Scene() {}
	virtual std::shared_ptr<Scene> Update(std::shared_ptr<Scene>&) = 0;
	/**
	* @brief シーンが変わるときの更新
	*/
	virtual void ExitFadeUpdate() {};
};