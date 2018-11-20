/**
* @file status.h
* @brief �X�e�[�^�X�N���X�̐錾�A��`
* @author �ΎR�@�I
* @date 2018/10/15
*/
#pragma once

/**
* @brief �X�e�[�^�X�N���X
*/
class Status
{
public:
	float HP;
	float Attack;
	float Defense;
	/**
	* @brief ������
	* @param hp ����HP
	* @param attack �U����
	* @param defense �h���
	*/
	void Init(const float hp, const float attack, const float defense)
	{
		HP = hp; Attack = attack; Defense = defense;
	}

	/**
	* @brief �R�s�[������Z�q
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
