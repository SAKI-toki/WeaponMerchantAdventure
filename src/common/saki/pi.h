/**
* @file pi.h
* @brief �~�����̃e���v���[�g�ϐ�
* @author �ΎR �I
* @date 2018/10/15
*/
/*
�~�����̃e���v���[�g�ϐ��ł��B
�g����
auto foo = saki::PI<float>;
*/
#ifndef SAKI_PI_2018_10_15
#define SAKI_PI_2018_10_15
namespace saki
{
	/**
	* @brief �~�����̃e���v���[�g�ϐ�
	* @details C++14���ȍ~�ł̎g�p�̂݉�
	*/
	template<typename T>
	static constexpr auto PI = static_cast<T>(3.14159265358979323846264338327950288);
}
#endif //SAKI_PI_2018_10_15