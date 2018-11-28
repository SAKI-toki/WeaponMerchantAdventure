/**
* @file game_over.h
* @brief ゲームオーバーシーンの定義
* @author 石山　悠
* @date 2018/11/26
*/
#pragma once
#include "../../../../common/saki/singleton/singleton.h"
#include "../../../../rendering/font/font.h"
#include "../../../../rendering/sprite/sprite.h"
#include "../../../scene.h"
#include <vector>

/**
* @brief ゲームオーバークラス
*/
class GameOver :public saki::singleton<GameOver>
{
	//明るさ関係
	float brightness = (brightness_uplimit + brightness_downlimit) * 0.5f;
	static constexpr float brightness_downlimit = 0.8f;
	static constexpr float brightness_uplimit = 1.0f;
	//明るさが現在下がっているかどうか
	bool bright_down = false;
	//最初かどうかのフラグ
	bool first = true;
	//透明度の上限
	static constexpr float alpha_limit = 0.7f;
	//透明度(Fade)
	float alpha = 0.0f;
	//ディレイ
	static constexpr int delay = 120;
	//ディレイを計測するための変数
	int time = 0;
	//テクスチャ
	Sprite black;
	Sprite game_over;
	Sprite next_scene[3];
	Sprite blood;
	//自分が選択している枠の番号
	int current_select = 0;
	bool upflg = false;
	bool downflg = false;
	//描画するかどうか
	bool rendering_flg = false;
	//血の位置と大きさを表す構造体
	struct blood_status
	{
		VEC2 pos;
		float scale;
	};
	//血の位置と大きさを格納するvector
	std::vector<blood_status> blood_pos;
	//次の血が落ちるまでの時間
	int blood_time = 0;
	//現在の時間
	int current_blood_time = 0;
public:
	void Init();
	/**
	* @brief 値をリセットする
	*/
	void Reset()
	{
		alpha = 0.0f;
		current_select = 0;
		time = 0; 
		upflg = false;
		downflg = false;
		first = true;
		next_scene[0].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
		next_scene[1].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
		next_scene[2].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
		rendering_flg = false;
		blood_pos.clear();
	}
	/**
	* @brief フェード時に色をセットする
	*/
	void SetColor()
	{
		black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
		game_over.ColorChange(1.0f, 0.0f, 0.0f, alpha);
	}
	void Update(std::shared_ptr<Scene>&, std::shared_ptr<Scene>&&);
	void Render();
};