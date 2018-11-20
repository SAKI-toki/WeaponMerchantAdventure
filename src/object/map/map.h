/**
* @file map.h
* @brief �}�b�v�ɔz�u����I�u�W�F�N�g�̃N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/11
*/
#pragma once
#include "../base/static/static_object.h"
#include "../../collider/square/square_collider.h"

/**
* @brief �}�b�v�ɔz�u����I�u�W�F�N�g�̃N���X
*/
class MapObject :public StaticObject
{
	//�R���C�_
	SquareCollider collider;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	void Destroy()final;
	/**
	* @brief �R���X�g���N�^
	*/
	MapObject() :collider(this, false, true)
	{
		object_tag = OBJECT_TAG::MAP;
	}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	MapObject(const MapObject& m) :
		collider(this, false, true)
	{
		this->transform = m.transform;
		this->enabled = m.enabled;
		this->object_tag = m.object_tag;
		this->sprite = m.sprite;
		this->use_gravity = m.use_gravity;
	}
	/**
	* @brief ���[�u�R���X�g���N�^
	*/
	MapObject(MapObject&& m)noexcept :
		collider(this, false, true)
	{
		this->transform = m.transform;
		this->enabled = m.enabled;
		this->object_tag = m.object_tag;
		this->sprite = m.sprite;
		this->use_gravity = m.use_gravity;
	}
	/**
	* @brief �R�s�[������Z�q
	*/
	MapObject& operator=(const MapObject& other)
	{
		if (this != &other)
		{
			this->collider = other.collider;
			StaticObject::operator=(other);
		}
		return *this;
	}

	/**
	* @brief ���[�u������Z�q
	*/
	MapObject& operator=(MapObject&& other)noexcept
	{
		if (this != &other)
		{
			this->collider = other.collider;
			StaticObject::operator=(other);
		}
		return *this;
	}
	void Collision(ObjectBase*, VEC2)final;

	/**
	* @brief �f�X�g���N�^
	*/
	~MapObject()
	{
		Destroy();
	}
};

/**
* @brief �}�b�v���쐬����֐�
* @param con �}�b�v���i�[���Ă���std::vector
* @param pos �ŏ��̈ʒu
* @param hor,ver ���A�c�ɂ�����
* @param name �L�[
* @param path �p�X
* @param w,h �e�N�X�`���̑傫��
* @param rot ��]
* @param scale �g��E�k��
*/
static void MakeMap(std::vector<MapObject>& con, const VEC2& pos, const int hor, const int ver,
	const std::string& name, WCHAR* path, LONG w, LONG h, float rot = 0, float scale = 1)
{
	for (int i = 0; i < hor; ++i)
	{
		for (int j = 0; j < ver; ++j)
		{
			con.push_back(MapObject());
			con[con.size() - 1].Init(name, path, w, h,
				pos + VEC2((i*(static_cast<float>(w)/* - 1*/))*scale, (j*(static_cast<float>(h)/* - 1*/))*scale),
				rot, scale);

		}
	}
}