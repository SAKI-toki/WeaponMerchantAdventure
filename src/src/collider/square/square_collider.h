/**
* @file square_collider.h
* @brief �l�p�`�̃R���C�_�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/12
*/
#pragma once
#include "../base/collider_base.h"
#include <saki/transform/transform.h>


/**
* @brief �l�p�`�R���C�_�N���X
*/
class SquareCollider :public ColliderBase
{

	/**
	* @brief �l�p�`�̃R���C�_�̃X�e�[�^�X
	*/
	struct SquareStatus
	{
		Vec3 center_pos;		//�ʒu
		float width, height;	//���A����
		/**
		* @brief ������
		* @param pos �ʒu
		* @param w,h ���A����
		* @param _rot ��]
		*/
		void Init(const Vec3& _pos, const float w, const float h)
		{
			center_pos = _pos, width = w, height = h;
		}
		/**
		* @brief �R�s�[������Z�q
		*/
		SquareStatus& operator=(const SquareStatus& other)
		{
			if (this != &other)
			{
				this->center_pos = other.center_pos;
				this->width = other.width;
				this->height = other.height;
			}
			return *this;
		}
	};
	//�l�p�`�̃X�e�[�^�X
	SquareStatus status;
	//�ÓI���ǂ���
	bool is_static;
public:
	//�R���X�g���N�^
	SquareCollider(ObjectBase*, bool = false, bool = false);
	//�X�e�[�^�X���Z�b�g����
	void SetStatus(const Vec3& pos, const float w, const float h, const Vec3& scale);
	//���������Ƃ��̉����o��
	void CollisionExtrusion(const Vec2&);
	/**
	* @brief �����蔻��̃X�e�[�^�X��Ԃ�
	* @return const SquareStatus& �X�e�[�^�X
	*/
	const SquareStatus& GetStatus()const { return status; }
	//�j��
	void Destroy();
	//�R�s�[�R���X�g���N�^
	SquareCollider& operator=(const SquareCollider& other);

};