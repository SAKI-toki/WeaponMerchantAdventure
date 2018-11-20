/**
* @file random.h
* @brief ���߂�ꂽ�͈͂Ń����_���Ȓl���擾����
* @author �ΎR �I
* @date 2018/10/31
*/
/*
���߂�ꂽ�͈͂Ń����_���Ȓl���擾����֐��ł�
�C���[�W�Ƃ��Ă�Unity��Random.Range(0,10)�̂悤�Ȋ����ł�
*/
#ifndef SAKI_RANDOM_2018_10_31
#define SAKI_RANDOM_2018_10_31
#include <random>
#include <assert.h>	//for assert
namespace saki
{
	/**
	* @brief �ŏ��l�ƍő�l�������ɂƂ�A���̊Ԃ��烉���_���Ȓl��Ԃ�
	* @param min �ŏ��l
	* @param max �ő�l
	* @details �ő�l���܂ރ����_���Ȓl��Ԃ��AC++17���ȍ~�ł̎g�p�̂݉�
	*/
	template<typename T>
	T random(const T min, const T max)
	{
		assert(min <= max);
		std::random_device rd;
		std::mt19937 mt(rd());
		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<int> rnd(min, max);
			return rnd(mt);
		}
		else
		{
			std::uniform_real_distribution<T> rnd(min, max);
			return rnd(mt);
		}
	}

	/**
	* @brief int�^�͓��ꉻ����
	* @param min �ŏ��l
	* @param max �ő�l
	* @details �ő�l���܂ރ����_���Ȓl��Ԃ�
	*/
	/*template<>
	int random<int>(const int min, const int max)
	{

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> rnd(min, max);

		return rnd(mt);
	}*/
}
#endif //SAKI_RANDOM_2018_10_31