/**
* @file collider_manager.h
* @brief �R���C�_���Ǘ�����N���X��錾
* @author �ΎR�@�I
* @date 2018/10/15
*/
#pragma once
#include "../../common/singleton.h"
#include "../square/square_collider.h"
#include "../../rendering/font/font.h"
#include <vector>


/**
* @brief �R���C�_���Ǘ�����N���X
*/
class ColliderManager :public Singleton<ColliderManager>
{
private:

#ifdef _DEBUG
	size_t count = 0;
public:
	void DebugRender()
	{
		Font f;
		WCHAR str[255];
		swprintf_s(str, L"ColliderNum=%zd", count);
		f.Init(str, 1, 0, 0);
		f.SetTransform({ {500,0},0,5 });
		f.Render();
	}
private:
#endif

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

	//�������Ă��邩���肷��֐�
	bool CompareCollision(SquarePosCol&, SquarePosCol&,bool);

	ObjectBase* target;

	bool DistancePlayer(ObjectBase* obj)
	{
		if (target == nullptr||std::abs(target->transform.pos.x - obj->transform.pos.x) < WINDOW_WIDTH + 200.0f)
		{
			return true;
		}
		return false;
	}
public:
	void SetTarget(ObjectBase* obj) { target = obj; }
	//���std::vector�ɃZ�b�g����֐�
	void SetCollider(SquareCollider*, bool is_static);
	//�S�Ă𑖍�����֐�
	void CheckCollision();
	//�w�肵���v�f���폜
	void DeleteCollider(SquareCollider*);
	//�V�[���J�ڂ̎��ɂ��ׂẴR���C�_���폜����
	void Reset();

};