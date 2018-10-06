/**
* @file player.cpp
* @brief �v���C���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/07
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"

/**
* @brief �v���C���[�̏�����
* @param path �e�N�X�`���̃p�X
* @param w �e�N�X�`���̕�
* @param h �e�N�X�`���̍���
* @param pos �v���C���[�̏����ʒu
* @param rot �v���C���[�̏�����]
* @param scale �v���C���[�̏����g��E�k��
*/
HRESULT Player::Init(WCHAR* path, const LONG w, const LONG h, VEC2 pos, float rot, float scale)
{
	transform.Init(pos, rot, scale);
	sprite.Init(path, true, w, h);
	return S_OK;
}

/**
* @brief �v���C���[�̍X�V
*/
void Player::Update()
{

}

/**
* @brief �v���C���[�̕`��
*/
void Player::Render()
{
	sprite.Render();
}

/**
* @brief �v���C���[�̔j��
*/
void Player::Destroy()
{

}