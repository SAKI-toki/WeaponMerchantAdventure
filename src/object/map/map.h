/**
* @file map.h
* @brief マップに配置するオブジェクトのクラスの宣言
* @author 石山　悠
* @date 2018/10/11
*/
#pragma once
#include "../base/static/static_object.h"
#include "../../collider/square/square_collider.h"

/**
* @brief マップに配置するオブジェクトのクラス
*/
class MapObject :public StaticObject
{
	//コライダ
	SquareCollider collider;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	void Destroy()final;
	/**
	* @brief コンストラクタ
	*/
	MapObject() :collider(this, false, true)
	{
		object_tag = OBJECT_TAG::MAP;
	}
	/**
	* @brief コピーコンストラクタ
	*/
	MapObject(const MapObject& m) :
		collider(this, false, true)
	{
		this->transform = m.transform;
		this->enabled = m.enabled;
		this->object_tag = m.object_tag;
		this->sprite = m.sprite;
		this->use_gravity = m.use_gravity;
	}
	/**
	* @brief ムーブコンストラクタ
	*/
	MapObject(MapObject&& m)noexcept :
		collider(this, false, true)
	{
		this->transform = m.transform;
		this->enabled = m.enabled;
		this->object_tag = m.object_tag;
		this->sprite = m.sprite;
		this->use_gravity = m.use_gravity;
	}
	/**
	* @brief コピー代入演算子
	*/
	MapObject& operator=(const MapObject& other)
	{
		if (this != &other)
		{
			this->collider = other.collider;
			StaticObject::operator=(other);
		}
		return *this;
	}

	/**
	* @brief ムーブ代入演算子
	*/
	MapObject& operator=(MapObject&& other)noexcept
	{
		if (this != &other)
		{
			this->collider = other.collider;
			StaticObject::operator=(other);
		}
		return *this;
	}
	void Collision(ObjectBase*, VEC2)final;

	/**
	* @brief デストラクタ
	*/
	~MapObject()
	{
		Destroy();
	}
};

/**
* @brief マップを作成する関数
* @param con マップを格納しているstd::vector
* @param pos 最初の位置
* @param hor,ver 横、縦にいくつか
* @param name キー
* @param path パス
* @param w,h テクスチャの大きさ
* @param rot 回転
* @param scale 拡大・縮小
*/
static void MakeMap(std::vector<MapObject>& con, const VEC2& pos, const int hor, const int ver,
	const std::string& name, WCHAR* path, LONG w, LONG h, float rot = 0, float scale = 1)
{
	for (int i = 0; i < hor; ++i)
	{
		for (int j = 0; j < ver; ++j)
		{
			con.push_back(MapObject());
			con[con.size() - 1].Init(name, path, w, h,
				pos + VEC2((i*(static_cast<float>(w)/* - 1*/))*scale, (j*(static_cast<float>(h)/* - 1*/))*scale),
				rot, scale);

		}
	}
}