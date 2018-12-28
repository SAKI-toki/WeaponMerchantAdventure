/**
* @file animation.h
* @brief �A�j���[�V�����N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/29
*/
#pragma once
#include "../common/common.h"

/**
* @brief �A�j���[�V�����N���X
*/
class Animation
{
	//��̃T�C�Y
	Vec2 one_size;
	//�c�̐�
	int ver_num;
	//���̐�
	int hor_num;
	//�Ԋu
	int interval;
	//���݂̃A�j���[�V�����̈ʒu
	int current_ver_num = INT_MAX;
	int current_hor_num = 0;
	//���̃A�j���[�V���������鎞��
	int time;
	int current_time = 0;
public:
	Animation() {}
	void Changetime(const int t) { time = t; }
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	Animation(const Animation& other)
	{
		this->one_size = other.one_size;
		this->ver_num = other.ver_num;
		this->hor_num = other.hor_num;
		this->interval = other.interval;
		this->current_ver_num = other.current_ver_num;
		this->current_hor_num = other.current_hor_num;
		this->time = other.time;
		this->current_time = other.current_time;
	}
	/**
	* @brief �R�s�[������Z�q
	*/
	Animation& operator=(const Animation& other)
	{
		if (this != &other)
		{
			this->one_size = other.one_size;
			this->ver_num = other.ver_num;
			this->hor_num = other.hor_num;
			this->interval = other.interval;
			this->current_ver_num = other.current_ver_num;
			this->current_hor_num = other.current_hor_num;
			this->time = other.time;
			this->current_time = other.current_time;
		}
		return *this;
	}
	void Init(const Vec2&, const int, const int, const int);
	void Update();
	Vec2 GetAnimation()const;
	void ChangeAnimation(const int, const int, const bool = false);
};