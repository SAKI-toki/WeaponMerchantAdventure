/**
* @file status.h
* @brief ステータスクラスの宣言、定義
* @author 石山　悠
* @date 2018/10/15
*/
#pragma once

/**
* @brief ステータスクラス
*/
class Status
{
public:
	float HP;
	float Attack;
	float Defense;
	/**
	* @brief 初期化
	* @param hp 初期HP
	* @param attack 攻撃力
	* @param defense 防御力
	*/
	void Init(const float hp, const float attack, const float defense)
	{
		HP = hp; Attack = attack; Defense = defense;
	}

	/**
	* @brief コピー代入演算子
	*/
	Status& operator=(const Status& other)
	{
		if (this != &other)
		{
			this->HP = other.HP;
			this->Attack = other.Attack;
			this->Defense = other.Defense;
		}
		return *this;
	}

	bool Damage(const float);
};
