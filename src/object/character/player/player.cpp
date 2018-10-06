/**
* @file player.cpp
* @brief プレイヤークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/07
*/
#include "player.h"
#include "../../../input/gamepad/gamepad_input.h"

/**
* @brief プレイヤーの初期化
* @param path テクスチャのパス
* @param w テクスチャの幅
* @param h テクスチャの高さ
* @param pos プレイヤーの初期位置
* @param rot プレイヤーの初期回転
* @param scale プレイヤーの初期拡大・縮小
*/
HRESULT Player::Init(WCHAR* path, const LONG w, const LONG h, VEC2 pos, float rot, float scale)
{
	transform.Init(pos, rot, scale);
	sprite.Init(path, true, w, h);
	return S_OK;
}

/**
* @brief プレイヤーの更新
*/
void Player::Update()
{

}

/**
* @brief プレイヤーの描画
*/
void Player::Render()
{
	sprite.Render();
}

/**
* @brief プレイヤーの破棄
*/
void Player::Destroy()
{

}