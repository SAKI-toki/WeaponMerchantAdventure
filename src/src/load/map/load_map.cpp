/**
* @file load_map.cpp
* @brief マップロードクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/11/28
*/
#include "load_map.h"
#include <string>
#include <fstream>
#include <sstream>

/**
* @brief ゲームマップの読み込み
* @param r_map_path 読み込むマップcsvのパス
* @param r_flu_path 読み込む飛ぶ鳥csvのパス
*/
void LoadMap::GameLoadingMap(WCHAR* r_map_path, WCHAR* r_fly_path)
{
	//以前とマップのパスと飛ぶ敵のパスが同じなら
	if (wcscmp(map_path, r_map_path) == 0 && !wcscmp(fly_path, r_fly_path) == 0)
	{
		return;
	}
	//パスのコピー
	wcscpy_s(map_path, r_map_path);
	wcscpy_s(fly_path, r_fly_path);
	//配列の消去
	map.clear();
	fly.clear();
	//マップの読み込み
	{
		//csvパスを設定
		WCHAR _map_path[256];
		wcscpy_s(_map_path, csv_path);
		wcscat_s(_map_path, map_path);
		std::ifstream ifs(_map_path);
		if (ifs.fail())
		{
			Comment(L"ファイルの読み込みに失敗", _map_path);
		}

		std::string str;
		std::getline(ifs, str);
		//一行読み込む
		while (std::getline(ifs, str))
		{
			//最後に改行がある場合に処理しないようにする
			//returnでもいいかもしれない
			if (str.length() == 0)continue;
			map.push_back(std::vector<int>());
			std::string s;
			std::istringstream stream(str);
			//カンマ区切りで読み込む
			while (std::getline(stream, s, ','))
			{
				//int型に変換しpush_back
				map[map.size() - 1].push_back(atoi(s.c_str()));
			}
		}
	}
	//飛ぶ敵の飛ぶ範囲とその間の時間
	{
		//csvパスを設定
		WCHAR _fly_path[256];
		wcscpy_s(_fly_path, csv_path);
		wcscat_s(_fly_path, fly_path);
		std::ifstream ifs(_fly_path);
		if (ifs.fail())
		{
			Comment(L"ファイルの読み込みに失敗", _fly_path);
		}

		std::string str;
		//最初の一行は読み飛ばす
		std::getline(ifs, str);
		//一行読み込む
		while (std::getline(ifs, str))
		{
			//最後に改行がある場合に処理しないようにする
			//returnでもいいかもしれない
			if (str.length() == 0)continue;
			std::string s;
			std::istringstream stream(str);
			//カンマ区切りで読み込む
			INT2 excel_pos;
			//これをすることにより、secondのほうの型が返る
			decltype(fly)::mapped_type fly_param;
			std::getline(stream, s, ',');
			//エクセルのため1から始まり、その値を入力することを想定しているため、0スタートにするために-1する
			excel_pos.x = atoi(s.c_str()) - 2;
			std::getline(stream, s, ',');
			excel_pos.y = atoi(s.c_str()) - 1;
			std::getline(stream, s, ',');
			fly_param.first.x = static_cast<float>(atof(s.c_str()))*BLOCK_SIZE;
			std::getline(stream, s, ',');
			fly_param.first.y = static_cast<float>(atof(s.c_str()))*BLOCK_SIZE;
			std::getline(stream, s, ',');
			fly_param.second = static_cast<float>(atof(s.c_str()));
			fly.insert(std::make_pair(excel_pos, fly_param));
		}
	}
}

/**
* @brief ゲームマップの作成
* @param m マップのstd::vector
* @param enemy 敵のstd::list
* @param f_enemy 飛ぶ敵のstd::list
* @param boss ボスのstd::unique_ptr
* @param player プレイヤーのstd::unique_ptr
* @param bullet_item 弾のアイテムのstd::list
*/
void LoadMap::GameMakingMap(std::vector<MapObject>& m, std::list<NormalEnemy>& enemy,
	std::list<FlyEnemy>& f_enemy, std::unique_ptr<Boss>& boss,
	std::unique_ptr<Player>& player, std::list<BulletItem>& bullet_item)
{
	//マップのサイズを取得
	int map_size_ver = static_cast<int>(map.size());
	int map_size_hor = static_cast<int>(map[0].size());
	//複数いる場合に教えるためのフラグ
	bool player_flg = false;
	bool boss_flg = false;
	//excelの場所を格納し、直しやすくする
	//INT2はちょうど使いやすいモノがあったため利用しているだけで、ハッシュとは関係ない
	INT2 player_excel_pos{};
	INT2 boss_excel_pos{};
	for (int i = 0; i < map_size_ver; ++i)
	{
		for (int j = 0; j < map_size_hor; ++j)
		{
			Vec3 pos{ j*BLOCK_SIZE, -(i + 9 - map_size_ver) * BLOCK_SIZE,0 };
			switch (map[i][j])
			{
			case 1: //何もない
			{

			}
			break;

			case 2: //ブロック
			{
				m.push_back(MapObject());
				m[m.size() - 1].Init(("map"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE,
					pos, saki::vector3_zero<float>, Vec3{ BLOCK_SCALE,BLOCK_SCALE,1 });
			}
			break;
			case 3: //飛ばない敵
			{
				enemy.push_front(NormalEnemy());
				std::begin(enemy)->Init(("normalenemy2"), L"monster1.png", 400, 366,
					pos, saki::vector3_zero<float>, Vec3{ BLOCK_SIZE / 400.0f*1.5f,BLOCK_SIZE / 400.0f*1.5f,1 });
			}
			break;

			case 4: //飛ぶ敵
			{
				f_enemy.push_front(FlyEnemy());
				std::begin(f_enemy)->Init(("fly_enemy"), L"bird.png", 450, 415,
					pos, saki::vector3_zero<float>, Vec3{ BLOCK_SIZE / 450.0f*1.5f,BLOCK_SIZE / 450.0f*1.5f,1 });
				//飛ぶ鳥のデータがあるか確認する
				auto fly_itr = fly.find({ i, j });
				//あった場合はその値をセットする
				if (fly_itr != std::end(fly))
				{
					std::begin(f_enemy)->SetMove(fly_itr->second.first, fly_itr->second.second);
				}
				else
				{
					WCHAR str[256];
					swprintf_s(str, L"excelの縦%d,横%dのデータがありません", i + 2, j + 1);
					Comment(str);
				}
			}
			break;

			case 5: //ボス
			{
				if (boss_flg)
				{
					WCHAR warning_str[256];
					swprintf_s(warning_str, L"ボスが(%d,%d)と(%d,%d)にいます", boss_excel_pos.x, boss_excel_pos.y, i + 1, j + 1);
					Comment(warning_str, map_path);
				}
				else
				{
					boss->Init(("Boss"), L"boss.png", 303, 400,
						pos, saki::vector3_zero<float>, Vec3{ BLOCK_SIZE / 400.0f*3.0f,BLOCK_SIZE / 400.0f*3.0f,1 });
					boss_flg = true;
					boss_excel_pos.x = i + 1;
					boss_excel_pos.y = j + 1;
				}
			}
			break;

			case 6: //プレイヤー
			{
				if (player_flg)
				{
					WCHAR warning_str[256];
					swprintf_s(warning_str, L"プレイヤーが(%d,%d)と(%d,%d)にいます", player_excel_pos.x, player_excel_pos.y, i + 1, j + 1);
					Comment(warning_str, map_path);
				}
				else
				{
					player->Init(("player"), L"WizardWalkRight.png", 86, 128,
						pos, saki::vector3_zero<float>, Vec3{ BLOCK_SIZE / 128.0f*1.3f,BLOCK_SIZE / 128.0f*1.3f,1 });
					player_flg = true;
					player_excel_pos.x = i + 1;
					player_excel_pos.y = j + 1;
				}
			}
			break;
			case 7:
			{
				bullet_item.push_front(BulletItem());
				std::begin(bullet_item)->Init(("bullet_item"), L"bullet.png", 32, 32,
					pos, saki::vector3_zero<float>, Vec3{ BLOCK_SIZE / 32.0f*0.5f,BLOCK_SIZE / 32.0f*0.5f,1 });
			}
			break;
			}
		}
	}
}

/**
* @brief タイトルかセレクトマップの読み込み
* @param r_map_path 読み込むマップcsvのパス
*/
void LoadMap::TitleSelectLoadingMap(WCHAR* r_map_path)
{
	//パスのコピー
	wcscpy_s(map_path, r_map_path);
	//配列の消去
	map.clear();
	//マップの読み込み
	{
		//csvパスを設定
		WCHAR _map_path[256];
		wcscpy_s(_map_path, csv_path);
		wcscat_s(_map_path, map_path);
		std::ifstream ifs(_map_path);
		if (ifs.fail())
		{
			Comment(L"ファイルの読み込みに失敗", _map_path);
		}

		std::string str;
		std::getline(ifs, str);
		//一行読み込む
		while (std::getline(ifs, str))
		{
			//最後に改行がある場合に処理しないようにする
			//returnでもいいかもしれない
			if (str.length() == 0)continue;
			map.push_back(std::vector<int>());
			std::string s;
			std::istringstream stream(str);
			//カンマ区切りで読み込む
			while (std::getline(stream, s, ','))
			{
				//int型に変換しpush_back
				map[map.size() - 1].push_back(atoi(s.c_str()));
			}
		}
	}
}

/**
* @brief ゲームマップの作成
* @param m マップのstd::vector
* @param player プレイヤーのstd::unique_ptr
*/
void LoadMap::TitleSelectMakingMap(std::vector<MapObject>& m,
	std::unique_ptr<Player>& player, std::vector<SelectObj>& select_obj, StaticObject& sign)
{
	//マップのサイズを取得
	int map_size_ver = static_cast<int>(map.size());
	int map_size_hor = static_cast<int>(map[0].size());
	//複数いる場合に教えるためのフラグ
	bool player_flg = false;
	//excelの場所を格納し、直しやすくする
	//INT2はちょうど使いやすいモノがあったため利用しているだけで、ハッシュとは関係ない
	INT2 player_excel_pos{};
	for (int i = 0; i < map_size_ver; ++i)
	{
		for (int j = 0; j < map_size_hor; ++j)
		{
			Vec3 pos{ j * BLOCK_SIZE, -(i + 9 - map_size_ver) * BLOCK_SIZE,0 };
			switch (map[i][j])
			{
			case 1: //何もない
			{

			}
			break;

			case 2: //ブロック
			{
				m.push_back(MapObject());
				m[m.size() - 1].Init(("map"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE,
					pos + Vec3{ 0,0,1000 }, saki::vector3_zero<float>, Vec3{ BLOCK_SCALE,BLOCK_SCALE,1 });
			}
			break;

			case 6: //プレイヤー
			{
				if (player_flg)
				{
					WCHAR warning_str[256];
					swprintf_s(warning_str, L"プレイヤーが(%d,%d)と(%d,%d)にいます", player_excel_pos.x, player_excel_pos.y, i + 1, j + 1);
					Comment(warning_str, map_path);
				}
				else
				{
					player->Init(("player"), L"WizardWalkRight.png", 86, 128,
						pos, saki::vector3_zero<float>, Vec3{ BLOCK_SIZE / 128.0f*1.3f, BLOCK_SIZE / 128.0f*1.3f,1 });
					player_flg = true;
					player_excel_pos.x = i + 1;
					player_excel_pos.y = j + 1;
				}
			}
			break;

			case 97: //Easy
			{
				select_obj.push_back(SelectObj());
				select_obj[select_obj.size() - 1].Init("select_obj_easy", L"select_easy.png", 599, 550,
					pos - Vec3(0.0f, BLOCK_SIZE / 599.0f * 3.0f*49.0f / 2.0f, -5), saki::vector3_zero<float>,
					Vec3{ BLOCK_SIZE / 599.0f * 3.0f, BLOCK_SIZE / 599.0f * 3.0f,30 });
			}
			break;

			case 98: //Normal
			{
				select_obj.push_back(SelectObj());
				select_obj[select_obj.size() - 1].Init("select_obj_normal", L"select_normal.png", 599, 550,
					pos - Vec3(0.0f, BLOCK_SIZE / 599.0f * 3.0f*49.0f / 2.0f,-5), saki::vector3_zero<float>, 
					Vec3{ BLOCK_SIZE / 599.0f * 3.0f, BLOCK_SIZE / 599.0f * 3.0f,30 });
			}
			break;

			case 99: //Hard
			{
				select_obj.push_back(SelectObj());
				select_obj[select_obj.size() - 1].Init("select_obj_hard", L"select_hard.png", 599, 550,
					pos - Vec3(0.0f, BLOCK_SIZE / 599.0f * 3.0f*49.0f / 2.0f,-5), saki::vector3_zero<float>, 
					Vec3{ BLOCK_SIZE / 599.0f * 3.0f, BLOCK_SIZE / 599.0f * 3.0f,30 });
			}
			break;

			case 100: //exit
				sign.Init("ExitSign", L"exit_sign.png", 599, 549,
					pos - Vec3(0.0f, BLOCK_SIZE / 599.0f * 3.0f*50.0f / 2.0f,-5), saki::vector3_zero<float>, 
					Vec3{ BLOCK_SIZE / 599.0f * 3.0f, BLOCK_SIZE / 599.0f * 3.0f,30 });
				break;
			}
		}
	}
}