/**
* @file singleton.h
* @brief シングルトンクラス
* @author 石山 悠
* @date 2018/10/17
*/
/*
クラスをシングルトンにするとき、このクラスを継承するだけでシングルトンになる
※使い方
class A:public saki::Singleton<A>{}
*/
#ifndef SAKI_SINGLETON_2018_10_17
#define SAKI_SINGLETON_2018_10_17
#include <memory> //for unique_ptr
namespace saki
{
	/**
	* @brief 継承するとシングルトンクラスになる
	*/
	template<typename T>
	class Singleton
	{
	public:
		/**
		* @brief インスタンスを取得
		* @return std::unique_ptr<T> インスタンスを返す
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