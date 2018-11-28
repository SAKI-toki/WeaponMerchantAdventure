#include "load_map.h"
#include <string>
#include <fstream>
#include <sstream>

void LoadMap::LoadingMap(WCHAR* r_map_path, WCHAR* r_fly_path)
{
	//�ȑO�ƃ}�b�v�̃p�X�Ɣ�ԓG�̃p�X�������Ȃ�
	if (wcscmp(map_path, r_map_path) == 0 && !wcscmp(fly_path, r_fly_path) == 0)
	{
		return;
	}
	//�p�X�̃R�s�[
	wcscpy_s(map_path, r_map_path);
	wcscpy_s(fly_path, r_fly_path);
	//�z��̏���
	map.clear();
	fly.clear();
	//�}�b�v�̓ǂݍ���
	{
		//csv�p�X��ݒ�
		WCHAR _map_path[256];
		wcscpy_s(_map_path, csv_path);
		wcscat_s(_map_path, map_path);
		std::ifstream ifs(_map_path);
		if (ifs.fail())
		{
			Comment(L"�t�@�C���̓ǂݍ��݂Ɏ��s", _map_path);
		}

		std::string str;
		//��s�ǂݍ���
		while (std::getline(ifs, str))
		{
			//�Ō�ɉ��s������ꍇ�ɏ������Ȃ��悤�ɂ���
			//return�ł�������������Ȃ�
			if (str.length() == 0)continue;
			map.push_back(std::vector<int>());
			std::string s;
			std::istringstream stream(str);
			//�J���}��؂�œǂݍ���
			while (std::getline(stream, s, ','))
			{
				//int�^�ɕϊ���push_back
				map[map.size() - 1].push_back(atoi(s.c_str()));
			}
		}
	}
	//��ԓG�̔�Ԕ͈͂Ƃ��̊Ԃ̎���
	{
		//csv�p�X��ݒ�
		WCHAR _fly_path[256];
		wcscpy_s(_fly_path, csv_path);
		wcscat_s(_fly_path, fly_path);
		std::ifstream ifs(_fly_path);
		if (ifs.fail())
		{
			Comment(L"�t�@�C���̓ǂݍ��݂Ɏ��s", _fly_path);
		}

		std::string str;
		//�ŏ��̈�s�͓ǂݔ�΂�
		std::getline(ifs, str);
		//��s�ǂݍ���
		while (std::getline(ifs, str))
		{
			//�Ō�ɉ��s������ꍇ�ɏ������Ȃ��悤�ɂ���
			//return�ł�������������Ȃ�
			if (str.length() == 0)continue;
			std::string s;
			std::istringstream stream(str);
			//�J���}��؂�œǂݍ���
			INT2 excel_pos;
			//��������邱�Ƃɂ��Asecond�̂ق��̌^���Ԃ�
			decltype(fly)::mapped_type fly_param;
			std::getline(stream, s, ',');
			//�G�N�Z���̂���1����n�܂�A���̒l����͂��邱�Ƃ�z�肵�Ă��邽�߁A0�X�^�[�g�ɂ��邽�߂�-1����
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
	//�}�b�v�̃T�C�Y���擾
	int map_size_ver = static_cast<int>(map.size());
	int map_size_hor = static_cast<int>(map[0].size());

	for (int i = 0; i < map_size_ver; ++i)
	{
		for (int j = 0; j < map_size_hor; ++j)
		{
			VEC2 pos{ j*BLOCK_SIZE, (i + 9 - map_size_ver) * BLOCK_SIZE };
			switch (map[i][j])
			{
			case 1: //�����Ȃ�
			{

			}
			break;

			case 2: //�u���b�N
			{
				m.push_back(MapObject());
				m[m.size() - 1].Init(("map"), L"map/map2.png", BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE,
					pos, 0.0f, BLOCK_SCALE);
			}
			break;
			case 3: //��΂Ȃ��G
			{
				enemy.push_front(NormalEnemy());
				std::begin(enemy)->Init(("normalenemy2"), L"monster1.png", 400, 366,
					pos, 0, 0.2f);
			}
			break;

			case 4: //��ԓG
			{
				f_enemy.push_front(FlyEnemy());
				std::begin(f_enemy)->Init(("fly_enemy"), L"bird.png", 450, 415,
					pos, 0, 0.25f);
				//��Ԓ��̃f�[�^�����邩�m�F����
				auto fly_itr = fly.find({ i, j });
				//�������ꍇ�͂��̒l���Z�b�g����
				if (fly_itr != std::end(fly))
				{
					std::begin(f_enemy)->SetMove(fly_itr->second.first, fly_itr->second.second);
				}
				else
				{
					Comment(L"csv�̔�Ԓ��̂ق��ɊԈႢ������܂�");
				}
			}
			break;

			case 5: //�{�X
			{
				boss->Init(("Boss"), L"boss.png", 303, 400,
					pos, 0, 0.5f);
			}
			break;

			case 6: //�v���C���[
			{
				player->Init(("player"), L"WizardWalkRight.png", 86, 128,
					pos, 0, 0.6f);
			}
			break;
			}
		}
	}
}