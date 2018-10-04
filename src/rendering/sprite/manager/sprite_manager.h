/**
* @file sprite_manger.h
* @brief SpriteManager�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include "../../../common/singleton.h"
#include <SpriteBatch.h>
#include <wrl.h>
template<typename T>
using CP = Microsoft::WRL::ComPtr<T>;

/**
* @brief Sprite�֌W�̃f�o�C�X��`�掞�Ɍo�R������̂��Ǘ�����N���X
*/
class SpriteManager :public Singleton<SpriteManager>
{
	//�K�v�Ȃ���
	std::unique_ptr<DirectX::SpriteBatch> m_pSpriteBatch;
	//1�x�ǂݍ��񂾂��̂�2��ǂݍ��܂Ȃ�
	//�p�X�ŊǗ�
	std::unordered_map < WCHAR*, CP<ID3D11ShaderResourceView>> textureList;
	//�f�o�C�X
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
public:
	void Init();
	CP<ID3D11ShaderResourceView>& GetTexture(WCHAR*);
	~SpriteManager();


	/**
	* @brief SpriteBatch�̃Q�b�^
	* @return std::unique_ptr<DirectX::SpriteBatch>&
	*/
	std::unique_ptr<DirectX::SpriteBatch>& GetSpriteBatch() { return m_pSpriteBatch; }
	/**
	* @brief ID3D11Device�̃Q�b�^
	* @return ID3D11Device*&
	*/
	ID3D11Device*& GetDevice() { return device; }
	/**
	* @brief ID3D11DeviceContext�̃Q�b�^
	* @return ID3D11DeviceContext*&
	*/
	ID3D11DeviceContext*& GetDeviceContext() { return deviceContext; }

	/**
	* @brief �`����X�^�[�g
	*/
	void Start() { m_pSpriteBatch->Begin(); }
	/**
	* @brief �`����I��
	*/
	void End() { m_pSpriteBatch->End(); }
};