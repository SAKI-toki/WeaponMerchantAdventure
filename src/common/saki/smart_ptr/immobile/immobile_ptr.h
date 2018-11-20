/**
* @file immobile_ptr.h
* @brief コピー・ムーブ禁止のスマートポインタ
* @author 石山 悠
* @date 2018/10/18
*/
/*
標準ライブラリのstd::unique_ptrのムーブも禁止したバージョンです。
これ自体やこれを含むクラス等のvectorのようなムーブする可能性があるものを利用すると
不具合が起きるので、単体で使用してください。
※ムーブ禁止のため、std::make_uniqueのようなヘルパー関数を作成できない。
*/
#ifndef SAKI_IMMOBILE_PTR_2018_10_17
#define SAKI_IMMOBILE_PTR_2018_10_17
#include <assert.h>	//for assert
namespace saki
{
	/**
	* @brief コピー・ムーブ禁止のスマートポインタ
	*/
	template<typename T>
	class immobile_ptr
	{
	public:
		/**
		* @brief コンストラクタ時にメモリ確保
		* @param args Tのコンストラクタに必要な引数
		*/
		template<typename ...Args>
		explicit immobile_ptr(Args... args)
		{
			ptr = new T(args...);
		}
		/**
		* @brief デストラクタ時にメモリ解放
		*/
		~immobile_ptr()noexcept
		{
			release();
		}
		/**
		* @brief 明示的なメモリ解放
		*/
		void release()noexcept
		{
			if (ptr != nullptr)
			{
				delete(ptr);
				ptr = nullptr;
			}
		}
		/**
		* @brief 明示的なメモリ解放と新たにメモリ確保する
		* @param args Tのコンストラクタに必要な引数
		*/
		template<typename ...Args>
		void reset(Args ...args)
		{
			release();
			ptr = new T(args...);
		}
		/**
		* @brief 変換演算子
		*/
		explicit operator bool()const
		{
			return ptr != nullptr;
		}
		/**
		* @brief アロー演算子
		*/
		T* operator->()const
		{
			assert(ptr != nullptr);
			return ptr;
		}
		//コピー・ムーブ禁止
		immobile_ptr(const immobile_ptr&) = delete;
		immobile_ptr(immobile_ptr&&) = delete;
		immobile_ptr& operator=(const immobile_ptr&) = delete;
		immobile_ptr& operator=(immobile_ptr&&) = delete;
	private:
		//ポインタ
		T* ptr;
	};
}
#endif //SAKI_IMMOBILE_PTR_2018_10_17