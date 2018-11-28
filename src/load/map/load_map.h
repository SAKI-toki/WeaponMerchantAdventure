/**
* @file load_map.h
* @brief �}�b�v���[�h�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/11/28
*/
#pragma once
#include "../../common/common.h"
#include "../../common/saki/singleton/singleton.h"
#include "../../object/map/map.h"
#include "../../object/character/player/player.h"
#include "../../object/character/enemy/normal/normal_enemy.h"
#include "../../object/character/enemy/fly/fly_enemy.h"
#include "../../object/character/enemy/boss/boss.h"
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>



class LoadMap :public saki::singleton<LoadMap>
{
	WCHAR map_path[256];
	WCHAR fly_path[256];

	std::vector<std::vector<int>> map;
	/**
	* @brief hash�̃L�[�Ƃ��Ďg����悤�ɂ���
	*/
	struct INT2
	{
		int x, y;
	};
	/**
	* @brief �n�b�V��
	*/
	struct HashINT2
	{
		size_t operator()(const INT2& int2)const
		{
			return int2.x * 100000 + int2.y;
		}
	};
	/**
	* @brief �C�R�[��
	*/
	struct EqualINT2
	{
		bool operator()(const INT2& left, const INT2& right)const
		{
			return left.x == right.x&&left.y == right.y;
		}
	};

	std::unordered_map<INT2, std::pair<VEC2, float>, HashINT2, EqualINT2> fly;

public:
	void LoadingMap(WCHAR*, WCHAR*);
	void MakingMap(std::vector<MapObject>&, std::list<NormalEnemy>&,
		std::list<FlyEnemy>&, std::unique_ptr<Boss>&,
		std::unique_ptr<Player>&);
};


