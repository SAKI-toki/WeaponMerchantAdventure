/**
* @file object_base.h
* @brief オブジェクトのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/11
*/
#pragma once
#include <Windows.h>//for HRESULT
#include "../../transform/transform.h"
#include "../../rendering/sprite/sprite.h"

enum class OBJECT_TAG { PLAYER, ENEMY, NONE };
/**
* @brief オブジェクトのスーパークラス
*/
class ObjectBase
{
protected:
	//テクスチャクラス
	Sprite sprite;
	//ワールドでの位置、回転、拡大・縮小
	Transform worldTransform;
	//子クラスで定義する
	virtual void InitProcess() = 0;
	virtual void RenderProcess(bool) = 0;
	virtual void UpdateProcess() = 0;
public:
	//オブジェクトのタグ
	OBJECT_TAG object_tag;
	//更新、描画するかどうか
	bool enabled;
	/**
	* @brief コンストラクタ
	*/
	ObjectBase() :enabled(true) {}

	//位置、回転、拡大・縮小(ローカル）
	Transform transform;

	void Init(std::string name, WCHAR* path, const LONG w, const LONG h, VEC2 pos,
		float rot = 0, float scale = 1, bool all_render = true);
	void Update();
	void Render(bool = true, const Transform& = NULL);

	virtual void Destroy() = 0;

	//ポリモーフィズムを利用するときはデストラクタは仮想関数にする
	virtual ~ObjectBase() {}

	//当たったときに実行する関数
	virtual void Collision(ObjectBase*,VEC2) {}
};