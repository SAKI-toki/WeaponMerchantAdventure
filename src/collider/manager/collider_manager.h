/**
* @file collider_manager.h
* @brief �R���C�_���Ǘ�����N���X��錾
* @author �ΎR�@�I
* @date 2018/10/15
*/
#pragma once
#include "../../common/singleton.h"
#include "../square/square_collider.h"
#include <vector>

/**
* @brief �R���C�_���Ǘ�����N���X
*/
class ColliderManager :public Singleton<ColliderManager>
{
private:
	/**
	* @brief �l�p�R���C�_���M��1�t���[���O�̈ʒu�ƍ��̈ʒu���i�[
	*/
	struct SquarePosCol
	{
		SquareCollider* col;
		VEC2 prev_pos;
		VEC2 current_pos;
		SquarePosCol() {}
		SquarePosCol(const SquarePosCol& spc)
		{
			col = spc.col;
			prev_pos = spc.prev_pos;
			current_pos = spc.current_pos;
		}
	};
	//�ÓI�I�u�W�F�N�g�̎l�p�`�R���C�_
	std::vector<SquarePosCol> staticSquareColliderList;

	//���I�I�u�W�F�N�g�̎l�p�`�R���C�_
	std::vector<SquarePosCol> dynamicSquareColliderList;
protected:
	//�������Ă��邩���肷��֐�
	bool CompareCollision(SquarePosCol&, SquarePosCol&);
public:
	//���std::vector�ɃZ�b�g����֐�
	void SetCollider(SquareCollider*, bool is_static);
	//�S�Ă𑖍�����֐�
	void CheckCollision();
	//�w�肵���v�f���폜
	void DeleteCollider(SquareCollider*);
};