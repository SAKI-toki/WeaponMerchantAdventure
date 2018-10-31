/**
* @file singleton.h
* @brief Singletonテンプレートスーパークラスの定義
* @author 石山　悠
* @date 2018/10/02
*/
#pragma once
#include <memory>

/**
* @brief Singletonテンプレートスーパークラス
* @details publicで仮引数にそのクラスを入れて継承するとそのクラスがSingletonになる
*/
template<typename T>
class Singleton
{
public:
	/**
	* @brief インスタンスの取得
	* @return std::unique_ptr<T>& インスタンス
	*/
	static std::unique_ptr<T>& GetInstance()
	{
		static auto instance = std::make_unique<T>();
		return instance;
	}
	virtual ~Singleton() {};
protected:
	Singleton() {};
private:
	//コピー・ムーブ禁止
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
};