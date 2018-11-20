/**
* @file for_each.h
* @brief ������for_each�֐��̊ȗ����{�g��
* @author �ΎR �I
* @date 2018/10/17
*/
/*
�S�Ă̗v�f�Ɋ֐���K�p����Ƃ��ɃR���e�i�N���X�Ɗ֐���n�������ŉ\�ɂ���
����ɁA�g���@�\�Ƃ��āA����2�ȍ~�ɔC�ӂ̒l�����Ď��s���邱�Ƃ��ł���悤�ɂ���
�W�����C�u�����ł�Iterator��n���̂ŁA�S�ĂȂ炱�������g�����ق����ǂ�
*/
#ifndef SAKI_FOR_EACH_2018_10_17
#define SAKI_FOR_EACH_2018_10_17
namespace saki
{
	/**
	* @brief �֐������ׂĂ̗v�f�Ŏ��s����
	* @param con �R���e�i�N���X
	* @param f ���s����֐�
	* @param args ���s����֐��̈����Q�ȍ~�ɓ����l
	*/
	template<typename Container, typename Func, typename ...Args>
	void for_each(Container& con, Func& f, const Args ...args)
	{
		for (auto&& n : con)
		{
			f(n, args...);
		}
	}
}

#endif //SAKI_FOR_EACH_2018_10_17