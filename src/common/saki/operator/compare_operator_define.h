/**
* @file compare_operator_define.h
* @brief ��r�n��operator�������Œ�`����}�N��
* @author �ΎR �I
* @date 2018/10/31
*/
/*
operator<���`���Ă����
operator==��operator!=��operator>��operator<=��operator>=����̓��operator�����Ƃɒ�`�����
���g�p��
class A
{
public:
	int n = 0;
	bool operator<(const A& a)const
	{
		return this->n < a.n;
	}
	SAKI_COMPARE_OPERATOR_DEFINE(A)
};
*/

#ifndef SAKI_COMPARE_OPERATOR_DEFINE_2018_10_31
#define SAKI_COMPARE_OPERATOR_DEFINE_2018_10_31

/**
* @brief operator��������`����}�N��
* @param name ��`����N���X�̖��O
* @details <����`����Ă����==��!=��>��<=��>=��������`�����
*/
#ifndef SAKI_COMPARE_OPERATOR_DEFINE
#define SAKI_COMPARE_OPERATOR_DEFINE(name)			\
/*�C�R�[��											*/\
bool operator==(const name& other)const				\
{													\
	return !(*this < other) && !(other < *this);	\
}													\
/*�m�b�g�C�R�[��									*/\
bool operator!=(const name& other)const				\
{													\
	return (*this < other) || (other < *this);		\
}													\
/*��Ȃ�											*/\
bool operator>(const name& other)const				\
{													\
	return other < *this;							\
}													\
/*���Ȃ�C�R�[��									*/\
bool operator<=(const name& other)const				\
{													\
	return !(other < *this);						\
}													\
/*��Ȃ�C�R�[��									*/\
bool operator>=(const name& other)const				\
{													\
	return !(*this < other);						\
}													\

#endif	//SAKI_COMPARE_OPERATOR_DEFINE
#endif	//SAKI_COMPARE_OPERATOR_DEFINE_2018_10_31