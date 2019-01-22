/**
* @file object_base.h
* @brief オブジェクトのスーパークラスを宣言
* @author 石山　悠
* @date 2018/10/11
*/
#pragma once
#include "../../common/common.h"
#include <saki/transform/transform.h>
#include "../../sprite/sprite.h"
#include "../../gravity/gravity.h"
#include "../../status/status.h"

enum class OBJECT_TAG { PLAYER, ENEMY, MAP, WEAPON, BOSS, BOSS_BULLET, BOSS_ZONE, SELECT, BULLET_ITEM, NONE };
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
#ifdef _DEBUG
	virtual float DebugCollisionScale() { return 1; }
#endif
public:
	Vec2 size;
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
	/**
	* @brief コピーコンストラクタ
	*/
	ObjectBase(const ObjectBase& other)
	{
		this->size = other.size;
		this->sprite = other.sprite;
		this->status = other.status;
		this->gravity = other.gravity;
		this->use_gravity = other.use_gravity;
		this->object_tag = other.object_tag;
		this->enabled = other.enabled;
		this->transform = other.transform;
	}
	/**
	* @brief コピー代入演算子
	*/
	ObjectBase& operator=(const ObjectBase& other)
	{
		if (this != &other)
		{
			this->size = other.size;
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


	void Init(std::string name, WCHAR* path, const float w, const float h, Vec3 pos,
		Vec3 rot = saki::vector3_zero<float>, Vec3 scale = saki::vector3_one<float>);
	void Update();
	void Render(bool = true, const Transform& = 
		Transform(saki::vector3_zero<float>, saki::vector3_zero<float>, saki::vector3_zero<float>));

	virtual void Destroy() = 0;

	//ポリモーフィズムを利用するときはデストラクタは仮想関数にする
	virtual ~ObjectBase() {}

	//当たったときに実行する関数
	virtual void Collision(ObjectBase*, Vec2) {}
};