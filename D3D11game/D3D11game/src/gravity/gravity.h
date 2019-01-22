/**
* @file gravity.h
* @brief �d�͌n�̃N���X��錾
* @author �ΎR�@�I
* @date 2018/10/29
*/
#pragma once
#include "../common/common.h"
#include <saki/transform/transform.h>
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
	static constexpr float gravity = -40.0f;
	//�ő�d�́i�ړ��ʁj
	static constexpr float max_gravity = 30.0f;
	//�ő剡�ړ����x
	float max_speed = 0;
	//��ɓ�����
	Vec2 power = Vec2(0, 0);
	//�o�ߎ���
	int time = 1;
	//�����Ԃ��������ǂ���
	bool hit_head = false;
public:
	/**
	* @brief ������
	* @param _max_speed �ő�X�s�[�h
	*/
	void Init(const float _max_speed)
	{
		max_speed = _max_speed;
	}
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
	Vec3 AddGravity();
	/**
	* @brief �d�͉����x�̃Z�b�g(�W�����v)
	* @param up_power �����x
	* @return bool �W�����v�ł������ǂ���
	*/
	bool SetUpPower(const float up_power)
	{
		if (time == 0)
		{
			power.y = up_power;
			return true;
		}
		return false;
	}
	/**
	* @brief ���ړ��̉����x�̃Z�b�g
	* @param side_power �����x
	*/
	void SetSidePower(const float side_power)
	{
		power.x += side_power;
		if (std::abs(power.x) > max_speed)
		{
			power.x = power.x > 0 ? max_speed : -max_speed;
		}
	}
	/**
	* @param �d�͌n�̃��Z�b�g
	*/
	void ResetGravity()
	{
		time = 0;
		power.y = 0;
		hit_head = false;
	}
	/**
	* @param �d�͌n�̉������̂݃��Z�b�g
	*/
	void ResetSideGravity()
	{
		power.x = 0;
	}
	/**
	* @brief �V��ɓ���������t���O�𗧂Ă�
	*/
	void HitHead()
	{
		time = 0;
		hit_head = true;
	}
	bool ReturnZero(const float speed);
	/**
	* @brief ���ډ��̗͂�����
	* @param side_power ���̗�
	*/
	void DirectSetSidePower(const float side_power)
	{
		power.x = side_power;
	}

	float GetSidePower()
	{
		return power.x;
	}

	void SetMaxSpeed(const float speed)
	{
		max_speed = speed;
	}
};