/**
* @file load_map.cpp
* @brief �}�b�v���[�h�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/11/28
*/
#include "load_map.h"
#include <string>
#include <fstream>
#include <sstream>

/**
* @brief �Q�[���}�b�v�̓ǂݍ���
* @param r_map_path �ǂݍ��ރ}�b�vcsv�̃p�X
* @param r_flu_path �ǂݍ��ޔ�Ԓ�csv�̃p�X
*/
void LoadMap::GameLoadingMap(WCHAR* r_map_path, WCHAR* r_fly_path)
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
		std::getline(ifs, str);
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
* @brief �Q�[���}�b�v�̍쐬
* @param m �}�b�v��std::vector
* @param enemy �G��std::list
* @param f_enemy ��ԓG��std::list
* @param boss �{�X��std::unique_ptr
* @param player �v���C���[��std::unique_ptr
* @param bullet_item �e�̃A�C�e����std::list
*/
void LoadMap::GameMakingMap(std::vector<MapObject>& m, std::list<NormalEnemy>& enemy,
	std::list<FlyEnemy>& f_enemy, std::unique_ptr<Boss>& boss,
	std::unique_ptr<Player>& player, std::list<BulletItem>& bullet_item)
{
	//�}�b�v�̃T�C�Y���擾
	int map_size_ver = static_cast<int>(map.size());
	int map_size_hor = static_cast<int>(map[0].size());
	//��������ꍇ�ɋ����邽�߂̃t���O
	bool player_flg = false;
	bool boss_flg = false;
	//excel�̏ꏊ���i�[���A�����₷������
	//INT2�͂��傤�ǎg���₷�����m�����������ߗ��p���Ă��邾���ŁA�n�b�V���Ƃ͊֌W�Ȃ�
	INT2 player_excel_pos{};
	INT2 boss_excel_pos{};
	for (int i = 0; i < map_size_ver; ++i)
	{
		for (int j = 0; j < map_size_hor; ++j)
		{
			Vec3 pos{ j*BLOCK_SIZE, -(i + 9 - map_size_ver) * BLOCK_SIZE,0 };
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
					pos, saki::vector3_zero<float>, Vec3{ BLOCK_SCALE,BLOCK_SCALE,1 });
			}
			break;
			case 3: //��΂Ȃ��G
			{
				enemy.push_front(NormalEnemy());
				std::begin(enemy)->Init(("normalenemy2"), L"monster1.png", 400, 366,
					pos, saki::vector3_zero<float>, Vec3{ BLOCK_SIZE / 400.0f*1.5f,BLOCK_SIZE / 400.0f*1.5f,1 });
			}
			break;

			case 4: //��ԓG
			{
				f_enemy.push_front(FlyEnemy());
				std::begin(f_enemy)->Init(("fly_enemy"), L"bird.png", 450, 415,
					pos, saki::vector3_zero<float>, Vec3{ BLOCK_SIZE / 450.0f*1.5f,BLOCK_SIZE / 450.0f*1.5f,1 });
				//��Ԓ��̃f�[�^�����邩�m�F����
				auto fly_itr = fly.find({ i, j });
				//�������ꍇ�͂��̒l���Z�b�g����
				if (fly_itr != std::end(fly))
				{
					std::begin(f_enemy)->SetMove(fly_itr->second.first, fly_itr->second.second);
				}
				else
				{
					WCHAR str[256];
					swprintf_s(str, L"excel�̏c%d,��%d�̃f�[�^������܂���", i + 2, j + 1);
					Comment(str);
				}
			}
			break;

			case 5: //�{�X
			{
				if (boss_flg)
				{
					WCHAR warning_str[256];
					swprintf_s(warning_str, L"�{�X��(%d,%d)��(%d,%d)�ɂ��܂�", boss_excel_pos.x, boss_excel_pos.y, i + 1, j + 1);
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

			case 6: //�v���C���[
			{
				if (player_flg)
				{
					WCHAR warning_str[256];
					swprintf_s(warning_str, L"�v���C���[��(%d,%d)��(%d,%d)�ɂ��܂�", player_excel_pos.x, player_excel_pos.y, i + 1, j + 1);
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
* @brief �^�C�g�����Z���N�g�}�b�v�̓ǂݍ���
* @param r_map_path �ǂݍ��ރ}�b�vcsv�̃p�X
*/
void LoadMap::TitleSelectLoadingMap(WCHAR* r_map_path)
{
	//�p�X�̃R�s�[
	wcscpy_s(map_path, r_map_path);
	//�z��̏���
	map.clear();
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
		std::getline(ifs, str);
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
}

/**
* @brief �Q�[���}�b�v�̍쐬
* @param m �}�b�v��std::vector
* @param player �v���C���[��std::unique_ptr
*/
void LoadMap::TitleSelectMakingMap(std::vector<MapObject>& m,
	std::unique_ptr<Player>& player, std::vector<SelectObj>& select_obj, StaticObject& sign)
{
	//�}�b�v�̃T�C�Y���擾
	int map_size_ver = static_cast<int>(map.size());
	int map_size_hor = static_cast<int>(map[0].size());
	//��������ꍇ�ɋ����邽�߂̃t���O
	bool player_flg = false;
	//excel�̏ꏊ���i�[���A�����₷������
	//INT2�͂��傤�ǎg���₷�����m�����������ߗ��p���Ă��邾���ŁA�n�b�V���Ƃ͊֌W�Ȃ�
	INT2 player_excel_pos{};
	for (int i = 0; i < map_size_ver; ++i)
	{
		for (int j = 0; j < map_size_hor; ++j)
		{
			Vec3 pos{ j * BLOCK_SIZE, -(i + 9 - map_size_ver) * BLOCK_SIZE,0 };
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
					pos + Vec3{ 0,0,1000 }, saki::vector3_zero<float>, Vec3{ BLOCK_SCALE,BLOCK_SCALE,1 });
			}
			break;

			case 6: //�v���C���[
			{
				if (player_flg)
				{
					WCHAR warning_str[256];
					swprintf_s(warning_str, L"�v���C���[��(%d,%d)��(%d,%d)�ɂ��܂�", player_excel_pos.x, player_excel_pos.y, i + 1, j + 1);
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