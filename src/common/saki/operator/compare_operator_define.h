/**
* @file compare_operator_define.h
* @brief 比較系のoperatorを自動で定義するマクロ
* @author 石山 悠
* @date 2018/10/31
*/
/*
operator<を定義していれば
operator==とoperator!=とoperator>とoperator<=とoperator>=が上の二つのoperatorをもとに定義される
※使用例
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
* @brief operatorを自動定義するマクロ
* @param name 定義するクラスの名前
* @details <が定義されていれば==と!=と>と<=と>=が自動定義される
*/
#ifndef SAKI_COMPARE_OPERATOR_DEFINE
#define SAKI_COMPARE_OPERATOR_DEFINE(name)			\
/*イコール											*/\
bool operator==(const name& other)const				\
{													\
	return !(*this < other) && !(other < *this);	\
}													\
/*ノットイコール									*/\
bool operator!=(const name& other)const				\
{													\
	return (*this < other) || (other < *this);		\
}													\
/*大なり											*/\
bool operator>(const name& other)const				\
{													\
	return other < *this;							\
}													\
/*小なりイコール									*/\
bool operator<=(const name& other)const				\
{													\
	return !(other < *this);						\
}													\
/*大なりイコール									*/\
bool operator>=(const name& other)const				\
{													\
	return !(*this < other);						\
}													\

#endif	//SAKI_COMPARE_OPERATOR_DEFINE
#endif	//SAKI_COMPARE_OPERATOR_DEFINE_2018_10_31