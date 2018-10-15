/**
* @file square_collider.h
* @brief �l�p�`�̃R���C�_�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/12
*/
#pragma once
#include "../base/collider_base.h"
#include "../../transform/transform.h"



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
		VEC2 center_pos;
		float width, height;
		float rot;
		/**
		* @brief ������
		* @param pos �ʒu
		* @param w,h ���A����
		* @param _rot ��]
		*/
		void Init(VEC2 _pos, float w, float h, float _rot)
		{
			center_pos = _pos, width = w, height = h, rot = _rot;
		}
	};
	//�l�p�`�̃X�e�[�^�X
	SquareStatus status;
public:
	//�R���X�g���N�^
	SquareCollider(ObjectBase*, bool = false, bool = false);
	//�X�e�[�^�X���Z�b�g����
	void SetStatus(VEC2 pos, float w, float h, float rot);
	//���������Ƃ��̉����o��
	void CollisionExtrusion(const VEC2&);
	/**
	* @brief �����蔻��̃X�e�[�^�X��Ԃ�
	* @return const SquareStatus& �X�e�[�^�X
	*/
	const SquareStatus& GetStatus()const { return status; }
	//�j��
	void Destroy();
};