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
#include "../../gravity/gravity.h"
#include "../../status/status.h"

enum class OBJECT_TAG { PLAYER, ENEMY, MAP, NONE };
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
	//ステータス
	Status status;
	//重力
	Gravity gravity;
	//重力系を利用するかどうか
	bool use_gravity;
	//オブジェクトのタグ
	OBJECT_TAG object_tag;
	//更新、描画するかどうか
	bool enabled = true;
	//位置、回転、拡大・縮小(ローカル）
	Transform transform;
	/**
	* @brief コンストラクタ
	*/
	ObjectBase(bool _gravity = false) : use_gravity(_gravity) {}
	ObjectBase(const ObjectBase& o)
	{
		this->transform = o.transform;
		this->enabled = o.enabled;
		this->object_tag = o.object_tag;
		this->sprite = o.sprite;
		this->use_gravity = o.use_gravity;
	}
	/**
	* @brief コピー代入演算子
	*/
	ObjectBase& operator=(const ObjectBase& other)
	{
		if (this != &other)
		{
			this->sprite = other.sprite;
			this->status = other.status;
			this->gravity = other.gravity;
			this->use_gravity = other.use_gravity;
			this->object_tag = other.object_tag;
			this->enabled = other.enabled;
			this->transform = other.transform;
		}
		return *this;
	}


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