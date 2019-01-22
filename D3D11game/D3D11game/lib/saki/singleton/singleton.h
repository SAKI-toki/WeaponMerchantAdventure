/**
* @file singleton.h
* @brief �V���O���g���N���X
* @author �ΎR �I
* @date 2018/10/17
*/
/*
�N���X���V���O���g���ɂ���Ƃ��A���̃N���X���p�����邾���ŃV���O���g���ɂȂ�
���g����
class A:public saki::Singleton<A>{}
*/
#ifndef SAKI_SINGLETON_2018_10_17
#define SAKI_SINGLETON_2018_10_17
#include <memory> //for unique_ptr
namespace saki
{
	/**
	* @brief �p������ƃV���O���g���N���X�ɂȂ�
	*/
	template<typename T>
	class Singleton
	{
	public:
		/**
		* @brief �C���X�^���X���擾
		* @return std::unique_ptr<T> �C���X�^���X��Ԃ�
		*/
		static std::unique_ptr<T>& getinstance()
		{
			static auto instance = std::make_unique<T>();
			return instance;
		}

		virtual ~Singleton() {}

	protected:
		Singleton() {}
	private:
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;
	};
}
#endif //SAKI_SINGLETON_2018_10_17