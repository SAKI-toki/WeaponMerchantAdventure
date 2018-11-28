/**
* @file collider_manager.cpp
* @brief �R���C�_���Ǘ�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/15
*/

#include "collider_manager.h"
#include "../../common/common.h"
#include <queue>

/**
* @brief �l�p�`�R���C�_��z��Ɋi�[����
* @param obj �l�p�`�R���C�_
* @param is_static �ÓI�����I��
*/
void ColliderManager::SetCollider(SquareCollider* obj, bool is_static)
{
	SquarePosCol spc;
	spc.col = obj;
	//�s�s�����N���Ȃ��悤�ɏ������Ƃ���1�t���[���O�ɂ����̈ʒu���i�[����
	spc.current_pos = obj->GetStatus().center_pos;
	spc.prev_pos = spc.current_pos;
	if (is_static)
	{
		staticSquareColliderList.push_back(spc);
	}
	else
	{
		dynamicSquareColliderList.push_back(spc);
	}
}

/**
* @brief �S�ẴR���C�_�𑖍�����
*/
void ColliderManager::CheckCollision()
{
	//�S�ẴR���C�_�𑖍����Ă���֐������s���邽�߁A�ꎞ�I�Ɋi�[����ꏊ
	std::queue<std::pair<std::function<void(ObjectBase*, VEC2)>, SquarePosCol>> func_queue;

#ifdef _DEBUG
	count = 0; 
	count = staticSquareColliderList.size() + dynamicSquareColliderList.size();
#endif

	//�O�̈ʒu���i�[
	for (auto&& sc : staticSquareColliderList)
	{
		sc.prev_pos = sc.current_pos;
	}
	for (auto&& dc : dynamicSquareColliderList)
	{
		dc.prev_pos = dc.current_pos;
		dc.col->collision_is_static_x = false;
		dc.col->collision_is_static_y = false;
	}
	//�ÓI�ȃI�u�W�F�N�g�Ɠ��I�ȃI�u�W�F�N�g�̓����蔻��
	for (auto&& sobj : staticSquareColliderList)
	{
		if (sobj.col->enabled&&DistancePlayer(sobj.col->object))
		{
			for (auto&& dobj : dynamicSquareColliderList)
			{
				if (dobj.col->enabled&&DistancePlayer(dobj.col->object))
				{
					//��ׂ�
					if (CompareCollision(sobj, dobj, true))
					{
						//�q�b�g
						//�֐����i�[����
						func_queue.push(std::make_pair(dobj.col->collision_func, sobj));
						func_queue.push(std::make_pair(sobj.col->collision_func, dobj));
					}
				}
			}
		}
	}
	//���I�ȃI�u�W�F�N�g���m�̓����蔻��
	for (auto dc1 = std::begin(dynamicSquareColliderList); dc1 != std::end(dynamicSquareColliderList); ++dc1)
	{
		if (dc1->col->enabled&&DistancePlayer(dc1->col->object))
		{
			for (auto dc2 = dc1 + 1; dc2 != std::end(dynamicSquareColliderList); ++dc2)
			{
				if (dc2->col->enabled&&DistancePlayer(dc2->col->object))
				{
					//��ׂ�
					if (CompareCollision(*dc1, *dc2, false))
					{
						//�q�b�g
						//�֐����i�[����
						func_queue.push(std::make_pair(dc1->col->collision_func, *dc2));
						func_queue.push(std::make_pair(dc2->col->collision_func, *dc1));
					}
				}
			}
		}
	}


	while (!func_queue.empty())
	{
		try
		{
			//�Ȃ��I�u�W�F�N�g���Q�Ƃ��Ȃ��悤�ɂ���
			//volatile�Ƃ����ɂ͍œK�������Ȃ����߂̏C���q
			//[[maybe_unused]]�����Ƃ����͈̂Ӑ}�I�ɖ��g�p�̗v�f���`���Ă��邱�Ƃ��R���p�C���ɓ`���A�x����}�����邽�߂̑���
			[[maybe_unused]]volatile auto temp = func_queue.front().second.col->object->enabled;
			if (func_queue.front().second.col->object == nullptr)
			{
				throw;
			}
			func_queue.front().first(func_queue.front().second.col->object, func_queue.front().second.col->GetStatus().center_pos - func_queue.front().second.prev_pos);
		}
		catch (...)
		{
#ifdef _DEBUG
			Comment(L"�Ȃ��I�u�W�F�N�g���Q��", L"collider_manager.cpp");
#endif
		}
		func_queue.pop();
	}

	//���݂̈ʒu���i�[
	for (auto&& sc : staticSquareColliderList)
	{
		sc.current_pos = sc.col->GetStatus().center_pos;
	}
	for (auto&& dc : dynamicSquareColliderList)
	{
		dc.current_pos = dc.col->GetStatus().center_pos;
	}
}

/**
* @brief �l�p�`���m���������Ă��邩�𔻒肷��
* @param col1,col2 ��ׂ��̎l�p�`�R���C�_
* @param col1_static �X�^�e�B�b�N���ǂ���
* @return bool �������Ă��邩�ǂ���
*/
bool ColliderManager::CompareCollision(SquarePosCol& col1, SquarePosCol& col2, bool col1_static)
{
	/*
	decltype(auto)
	�Q�Ƃ��ǂ��������_���Ă����iauto���ƎQ�Ƃł͂Ȃ��A�R�s�[���Ă��܂��p�t�H�[�}���X��������j
	*/
	decltype(auto) status1 = col1.col->GetStatus();
	decltype(auto) status2 = col2.col->GetStatus();

	//����ȏ㗣��Ă������΂ɓ�����Ȃ��l���擾����
	//�������̂��݂��̒��S���璆�S�̋��������߂�
	float maxDistance = std::sqrt(std::pow(status1.width, 2) + std::pow(status1.height, 2)) +
		std::sqrt(std::pow(status2.width, 2) + std::pow(status2.height, 2));

	//��΂ɓ�����Ȃ��l��葽���ꍇ������Ȃ��̂�false
	if (std::abs(status1.center_pos.x - status2.center_pos.x) > maxDistance ||
		std::abs(status1.center_pos.y - status2.center_pos.y) > maxDistance)
	{
		return false;
	}
	//���̍��v
	auto sum_width = status1.width + status2.width;
	//�c�̍��v
	auto sum_height = status1.height + status2.height;
	//TODO:��]���l������
	//�����������ǂ����̔���
	if (std::abs(status1.center_pos.x - status2.center_pos.x) < sum_width&&
		std::abs(status1.center_pos.y - status2.center_pos.y) < sum_height)
	{
		//�ǂ����trigger�Ȃ瓖���������Ƃ̂ݕԂ�
		if (col1.col->is_trigger || col2.col->is_trigger)
		{
			return true;
		}
		//�ǂ����ENEMY�Ȃ瓖���������Ƃ̂ݕԂ�
		if (col1.col->object->object_tag == OBJECT_TAG::ENEMY&&
			col2.col->object->object_tag == OBJECT_TAG::ENEMY)
		{
			return true;
		}

		//�x�N�g��
		auto col1vec = col1.col->GetStatus().center_pos - col1.prev_pos;
		auto col2vec = col2.col->GetStatus().center_pos - col2.prev_pos;
		//1�t���[���O��x���W���������Ă��邩�ǂ���
		if (std::abs(col1.prev_pos.x - col2.prev_pos.x) < sum_width)
		{
			//�ǂ���������o���ꍇ
			if (!col1_static && !col1.col->collision_is_static_y && !col2.col->collision_is_static_y)
			{
				//�����o���ʁi�ǂ���������o�����ߔ����j
				//float�̌덷��h�����߂�+0.001f���Ă���
				auto diff = (sum_height - std::abs(status1.center_pos.y - status2.center_pos.y) + 0.001f)  *0.5f;
				//�������Ԃ����Ă�l���ʒu�������
				col1.col->CollisionExtrusion(VEC2(
					col1.col->GetStatus().center_pos.x,
					(col1.prev_pos.y > col2.prev_pos.y) ?
					col1.col->GetStatus().center_pos.y + diff :
					col1.col->GetStatus().center_pos.y - diff));
				col2.col->CollisionExtrusion(VEC2(
					col2.col->GetStatus().center_pos.x,
					(col2.prev_pos.y > col1.prev_pos.y) ?
					col2.col->GetStatus().center_pos.y + diff :
					col2.col->GetStatus().center_pos.y - diff));
			}
			//�Е��������o���ꍇ
			else if (col1_static || !col1.col->collision_is_static_y || !col2.col->collision_is_static_y)
			{
				//is_trigger����Ȃ��ق����^�[�Q�b�g�ɂ���
				decltype(auto) target_col = ((col1.col->collision_is_static_y || col1_static) ? col2 : col1);
				if (!target_col.col->collision_is_static_y)
				{
					//�����o����
					//float�̌덷��h�����߂�+0.001f���Ă���
					auto diff = sum_height - std::abs(status1.center_pos.y - status2.center_pos.y) + 0.001f;
					//�^�[�Q�b�g����Ȃ��ق����i�[
					decltype(auto) not_target_col = (!(col1.col->collision_is_static_y || col1_static) ? col2 : col1);
					//y����������ȏ㓮�����Ȃ����߂ɂ���
					target_col.col->collision_is_static_y = true;
					//�^�[�Q�b�g�̂݉����o�����������邽�߉����o���ʑS�Ď󂯂�
					target_col.col->CollisionExtrusion(VEC2(
						target_col.col->GetStatus().center_pos.x,
						(target_col.prev_pos.y > not_target_col.prev_pos.y) ?
						target_col.col->GetStatus().center_pos.y + diff :
						target_col.col->GetStatus().center_pos.y - diff));
					//�d�͊֌W
					if (target_col.col->object->use_gravity)
					{
						//������������d�̓��Z�b�g
						if (target_col.prev_pos.y < not_target_col.prev_pos.y)
						{
							target_col.col->object->gravity.ResetGravity();
						}
						//�������������痎���ɐ؂�ւ�
						else
						{
							target_col.col->object->gravity.HitHead();
						}
					}
				}
			}
			//�ǂ���������o���Ȃ��ꍇ�����������Ȃ�
			//else {}
		}
		//1�t���[���O��y���W���������Ă��邩�ǂ���
		if (std::abs(col1.prev_pos.y - col2.prev_pos.y) < sum_height)
		{
			//�ǂ���������o���ꍇ
			if (!col1_static && !col1.col->collision_is_static_x && !col2.col->collision_is_static_x)
			{
				//�����o���ʁi�ǂ���������o�����ߔ����j
				//float�̌덷��h�����߂�+0.001f���Ă���
				auto diff = (sum_width - std::abs(status1.center_pos.x - status2.center_pos.x) + 0.001f) *0.5f;
				//�������Ԃ����Ă�l���ʒu�������
				col1.col->CollisionExtrusion(VEC2(
					(col1.prev_pos.x > col2.prev_pos.x) ?
					col1.col->GetStatus().center_pos.x + diff :
					col1.col->GetStatus().center_pos.x - diff,
					col1.col->GetStatus().center_pos.y));
				col2.col->CollisionExtrusion(VEC2(
					(col2.prev_pos.x > col1.prev_pos.x) ?
					col2.col->GetStatus().center_pos.x + diff :
					col2.col->GetStatus().center_pos.x - diff,
					col2.col->GetStatus().center_pos.y));
			}
			//�Е��������o���ꍇ
			else if (col1_static || !col1.col->collision_is_static_x || !col2.col->collision_is_static_x)
			{
				//is_trigger����Ȃ��ق����^�[�Q�b�g�ɂ���
				decltype(auto) target_col = ((col1.col->collision_is_static_x || col1_static) ? col2 : col1);
				if (!target_col.col->collision_is_static_x)
				{
					//�����o����
					//float�̌덷��h�����߂�+0.001f���Ă���
					auto diff = sum_width - std::abs(status1.center_pos.x - status2.center_pos.x) + 0.001f;
					//�^�[�Q�b�g����Ȃ��ق����i�[
					decltype(auto) not_target_col = (!(col1.col->collision_is_static_x || col1_static) ? col2 : col1);
					//x����������ȏ㓮�����Ȃ����߂ɂ���
					target_col.col->collision_is_static_x = true;
					//�^�[�Q�b�g�̂݉����o�����������邽�߉����o���ʑS�Ď󂯂�
					target_col.col->CollisionExtrusion(VEC2(
						(target_col.prev_pos.x > not_target_col.prev_pos.x) ?
						target_col.col->GetStatus().center_pos.x + diff :
						target_col.col->GetStatus().center_pos.x - diff,
						target_col.col->GetStatus().center_pos.y));
					//�d�͊֌W
					if (target_col.col->object->use_gravity)
					{
						target_col.col->object->gravity.ResetSideGravity();
					}
				}
			}
			//�ǂ���������o���Ȃ��ꍇ�����������Ȃ�
			//else {}
		}
		return true;
	}

	return false;

}

/**
* @brief �l�p�`�R���C�_�̍폜
* @param col �l�p�`�R���C�_
*/
void ColliderManager::DeleteCollider(SquareCollider* col)
{
	for (auto itr = std::begin(dynamicSquareColliderList); itr != std::cend(dynamicSquareColliderList); ++itr)
	{
		//��v������폜
		if (itr->col == col)
		{
			dynamicSquareColliderList.erase(itr);
			return;
		}
	}
	for (auto itr = std::begin(staticSquareColliderList); itr != std::cend(staticSquareColliderList); ++itr)
	{
		//��v������폜
		if (itr->col == col)
		{
			staticSquareColliderList.erase(itr);
			return;
		}
	}

}

/**
* @brief �R���C�_���X�g���N���A����
*/
void ColliderManager::Reset()
{
	dynamicSquareColliderList.clear();
	staticSquareColliderList.clear();
}
