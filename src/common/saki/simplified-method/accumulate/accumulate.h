/**
* @file accumulate.h
* @brief ������accumulate�֐��̊ȗ���
* @author �ΎR �I
* @date 2018/10/07
*/
/*
�S�Ă̗v�f�����v�i���͎w�肵�����Z�q�j���R���e�i�N���X�Ə����l��n�������ŉ\�ɂ���
�W�����C�u�����ł�Iterator��n���̂ŁA�S�ĂȂ炱�������g�����ق����ǂ�
*/
#ifndef SAKI_ACCUMULATE_2018_10_07
#define SAKI_ACCUMULATE_2018_10_07
namespace saki
{
	/**
	* @brief			�S�Ă̒l�̍��v
	* @param con		�R���e�i�N���X
	* @param init		�����l
	* @return			���v��Ԃ�
	*/
	template<typename Container, typename T>
	T accumulate(const Container& con, T init)
	{
		for (const auto& n : con)
		{
			init = init + n;
		}
		return init;
	}
	/**
	* @brief			������2�̊֐����w�肵�A��������ׂĂ̗v�f�ŉ�
	* @param con		�R���e�i�N���X
	* @param init		�����l
	* @param binary_op	������2�̊֐�
	* @return			�S�Ă̗v�f���񂵂�����
	* @details			���ӁF0���Z�ɋC��t���Ă�������
	*/
	template<typename Container, typename T, typename BinaryOperation>
	T accumulate(const Container& con, T init, const  BinaryOperation& binary_op)
	{
		for (const auto& n : con)
		{
			init = binary_op(init, n);
		}
		return init;
	}

}
#endif //SAKI_ACCUMULATE_2018_10_07