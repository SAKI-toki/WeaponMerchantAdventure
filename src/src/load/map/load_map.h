/**
* @file load_map.h
* @brief マップロードクラスの宣言
* @author 石山　悠
* @date 2018/11/28
*/
#pragma once
#include "../../common/common.h"
#include <saki/singleton/singleton.h>
#include "../../object/map/map.h"
#include "../../object/character/player/player.h"
#include "../../object/character/enemy/normal/normal_enemy.h"
#include "../../object/character/enemy/fly/fly_enemy.h"
#include "../../object/character/enemy/boss/boss.h"
#include "../../object/select/select_object.h"
#include "../../object/item/bullet/bullet_item.h"
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>


/**
* @brief マップロードクラス
*/
class LoadMap :public saki::Singleton<LoadMap>
{
	WCHAR map_path[256];
	WCHAR fly_path[256];

	std::vector<std::vector<int>> map;
	/**
	* @brief unordered_mapのhashのキーとして使えるようにする
	*/
	struct INT2
	{
		int x, y;
	};
	/**
	* @brief ハッシュ関数オブジェクト
	*/
	struct HashINT2
	{
		size_t operator()(const INT2& int2)const
		{
			return int2.x * 100000 + int2.y;
		}
	};
	/**
	* @brief イコール関数オブジェクト
	*/
	struct EqualINT2
	{
		bool operator()(const INT2& left, const INT2& right)const
		{
			return left.x == right.x&&left.y == right.y;
		}
	};

	std::unordered_map<INT2, std::pair<Vec2, float>, HashINT2, EqualINT2> fly;

public:
	void GameLoadingMap(WCHAR*, WCHAR*);
	void GameMakingMap(std::vector<MapObject>&, std::list<NormalEnemy>&,
		std::list<FlyEnemy>&, std::unique_ptr<Boss>&,
		std::unique_ptr<Player>&,std::list<BulletItem>&);

	void TitleSelectLoadingMap(WCHAR*);
	void TitleSelectMakingMap(std::vector<MapObject>&, std::unique_ptr<Player>&, 
		std::vector<SelectObj>&, StaticObject&);
};


