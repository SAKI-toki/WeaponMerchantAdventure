/**
* @file scene_base.h
* @brief マネージャーを含むシーンのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once

/**
* @brief シーン遷移を円滑にするためのenum class
*/
enum class SCENE { TITLE, SELECT, GAME };

/**
* @brief マネージャーを含むシーンのスーパークラス
*/
class SceneBase
{
protected:
	SCENE my_scene;
public:
	virtual ~SceneBase() {}

	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};