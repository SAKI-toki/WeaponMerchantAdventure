/**
* @file fade.cpp
* @brief フェードクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/30
*/
#include "fade.h"
#include "../../sound/bgm/bgm.h"

void Fade::Init()
{
	//黒のテクスチャの読み込み
	black.Init(std::string("black"), L"black.png", 1920, 1080, 1.0f, 1.0f, 1.0f, 0.0f);
	//位置は中央で、scaleは0から
	transform.Init(VEC2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f), 0.0f, 1.0f);
}

/**
* @brief 更新
* @param fade_in フェードインかどうか
* @return bool フェードインかアウトが終わったらtrue
*/
bool Fade::Update(const bool fade_in)
{
	//BGMのフェードインアウト
	BGM::GetInstance()->Fade(fade_in);
	//フェードインかアウトによって加算するか減算するか決める
	alpha += fade_in ? -FADE_SPEED : FADE_SPEED;
	//0より小さくなったら0に戻し、trueを返す
	if (alpha < 0.0f)
	{
		alpha = 0.0f;
		black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
		return true;
	}
	//1より大きくなったら1に戻し、trueを返す
	else if (alpha > 1.0f)
	{
		alpha = 1.0f;
		black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
		return true;
	}
	//終わってなかったらfalse
	black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
	return false;

}

/**
* @brief 描画
*/
void Fade::Render()
{
	black.Render(transform, false);
}

/**
* @brief 破棄
*/
void Fade::Destroy()
{

}