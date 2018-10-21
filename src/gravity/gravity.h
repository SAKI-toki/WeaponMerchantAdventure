/**
* @file gravity.h
* @brief �d�͌n�̃N���X��錾
* @author �ΎR�@�I
* @date 2018/10/15
*/
#pragma once
#include "../common/common.h"
#include <cmath>
/**
* @brief �d�͂��Ǘ�����N���X
*/
class Gravity
{
	//�d�͉����x
	/*
	�ړ���(y)=��ɓ�����+�d�͉����x*����(s)*����(s)
	*/
	static constexpr float gravity = -30.0f;
	//�ő�d�́i�ړ��ʁj
	static constexpr float max_gravity = -20.0f;
	//��ɓ�����
	float power = 0;
	//�o�ߎ���
	int time = 0;
	//�����Ԃ��������ǂ���
	bool hit_head = false;
public:
	/**
	* @brief �R�s�[������Z�q
	*/
	Gravity& operator=(const Gravity& other)
	{
		if (this != &other)
		{
			this->power = other.power;
			this->time = other.time;
			this->hit_head = other.hit_head;
		}
		return *this;
	}
	float AddGravity();
	/**
	* @brief �����x�̃Z�b�g
	* @param �����x
	*/
	void SetPower(const float _power)
	{
		if (time == 0)power = _power;
	}
	/**
	* @param �d�͌n�̃��Z�b�g
	*/
	void ResetGravity()
	{
		time = 0;
		power = 0;
		hit_head = false;
	}
	/**
	* @brief �V��ɓ���������t���O�𗧂Ă�
	*/
	void HitHead()
	{
		time = 0;
		hit_head = true;
	}
};