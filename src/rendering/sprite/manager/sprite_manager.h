/**
* @file sprite_manager.h
* @brief SpriteManagerクラスの宣言
* @author 石山　悠
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
* @brief Sprite関係のデバイスや描画時に経由するものを管理するクラス
*/
class SpriteManager :public Singleton<SpriteManager>
{
	//必要なもの
	std::unique_ptr<DirectX::SpriteBatch> m_pSpriteBatch;
	//1度読み込んだものは2回読み込まない
	//名前で管理
	std::unordered_map < std::string, CP<ID3D11ShaderResourceView>> textureList;
	//デバイス関係
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	std::unique_ptr<DirectX::CommonStates> commonState;
public:
	void Init();
	void SetTexture(std::string, WCHAR*);
	void Render(const Transform&, bool, bool, const std::string&, const DirectX::XMVECTOR&, const RECT&, const DirectX::SpriteEffects);
	~SpriteManager();


	/**
	* @brief SpriteBatchのゲッタ
	* @return std::unique_ptr<DirectX::SpriteBatch>&
	*/
	std::unique_ptr<DirectX::SpriteBatch>& GetSpriteBatch() { return m_pSpriteBatch; }
	/**
	* @brief ID3D11Deviceのゲッタ
	* @return ID3D11Device*&
	*/
	ID3D11Device*& GetDevice() { return device; }
	/**
	* @brief ID3D11DeviceContextのゲッタ
	* @return ID3D11DeviceContext*&
	*/
	ID3D11DeviceContext*& GetDeviceContext() { return deviceContext; }

	/**
	* @brief 描画をスタート
	*/
	
	void Start() 
	{
		m_pSpriteBatch->Begin(DirectX::SpriteSortMode_Deferred, commonState->NonPremultiplied());
	}
	/**
	* @brief 描画を終了
	*/
	void End() { m_pSpriteBatch->End(); }
};