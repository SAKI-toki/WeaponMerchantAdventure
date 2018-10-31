/**
* @file sprite_manager.h
* @brief SpriteManager�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/19
*/
#pragma once
#include "../../../common/singleton.h"
#include "../../../transform/transform.h"
#include <SpriteBatch.h>
#include <CommonStates.h>
#include <wrl.h>
#include "../../../../Main.h"
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
	//���O�ŊǗ�
	std::unordered_map < std::string, CP<ID3D11ShaderResourceView>> textureList;
	//�f�o�C�X�֌W
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	std::unique_ptr<DirectX::CommonStates> commonState;
public:
	void Init();
	void SetTexture(std::string, WCHAR*);
	void Render(const Transform&, bool, bool, const std::string&, const DirectX::XMVECTOR&, const RECT&, const DirectX::SpriteEffects);
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
	
	void Start() 
	{
		m_pSpriteBatch->Begin(DirectX::SpriteSortMode_Deferred, commonState->NonPremultiplied());
	}
	/**
	* @brief �`����I��
	*/
	void End() { m_pSpriteBatch->End(); }
};