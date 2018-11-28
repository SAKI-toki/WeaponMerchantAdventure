#include "load_map.h"
#include <string>
#include <fstream>
#include <sstream>

void LoadMap::LoadingMap(WCHAR* r_map_path, WCHAR* r_fly_path)
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
			excel_pos.x = atoi(s.c_str()) - 1;
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

void LoadMap::MakingMap(std::vector<MapObject>& m, std::list<NormalEnemy>& enemy,
	std::list<FlyEnemy>& f_enemy, std::unique_ptr<Boss>& boss,
	std::unique_ptr<Player>& player)
{
	//マップのサイズを取得
	int map_size_ver = static_cast<int>(map.size());
	int map_size_hor = static_cast<int>(map[0].size());

	for (int i = 0; i < map_size_ver; ++i)
	{
		for (int j = 0; j < map_size_hor; ++j)
		{
			VEC2 pos{ j*BLOCK_SIZE, (i + 9 - map_size_ver) * BLOCK_SIZE };
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
					pos, 0.0f, BLOCK_SCALE);
			}
			break;
			case 3: //飛ばない敵
			{
				enemy.push_front(NormalEnemy());
				std::begin(enemy)->Init(("normalenemy2"), L"monster1.png", 400, 366,
					pos, 0, 0.2f);
			}
			break;

			case 4: //飛ぶ敵
			{
				f_enemy.push_front(FlyEnemy());
				std::begin(f_enemy)->Init(("fly_enemy"), L"bird.png", 450, 415,
					pos, 0, 0.25f);
				//飛ぶ鳥のデータがあるか確認する
				auto fly_itr = fly.find({ i, j });
				//あった場合はその値をセットする
				if (fly_itr != std::end(fly))
				{
					std::begin(f_enemy)->SetMove(fly_itr->second.first, fly_itr->second.second);
				}
				else
				{
					Comment(L"csvの飛ぶ鳥のほうに間違いがあります");
				}
			}
			break;

			case 5: //ボス
			{
				boss->Init(("Boss"), L"boss.png", 303, 400,
					pos, 0, 0.5f);
			}
			break;

			case 6: //プレイヤー
			{
				player->Init(("player"), L"WizardWalkRight.png", 86, 128,
					pos, 0, 0.6f);
			}
			break;
			}
		}
	}
}