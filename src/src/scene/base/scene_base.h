/**
* @file scene_base.h
* @brief マネージャーを含むシーンのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once


/**
* @brief マネージャーを含むシーンのスーパークラス
*/
class SceneBase
{
public:
	virtual ~SceneBase() {}

	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};