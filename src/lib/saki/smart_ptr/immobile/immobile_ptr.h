/**
* @file immobile_ptr.h
* @brief コピー・ムーブ禁止のスマートポインタ
* @author 石山 悠
* @date 2018/11/26
*/
/*
標準ライブラリのstd::unique_ptrのムーブも禁止したバージョンです。
boostのscoped_ptrと仕様はだいたい一緒ですが、swap等も削除しているのでより唯一なものになってます。
*/
#pragma once
#ifndef SAKI_IMMOBILE_PTR_2018_11_26
#define SAKI_IMMOBILE_PTR_2018_11_26
#include <cassert>	//for assert
namespace saki
{
	/**
	* @brief コピー・ムーブ禁止のスマートポインタ
	*/
	template<typename T>
	class ImmobilePtr
	{
	public:
		/**
		* @brief コンストラクタ時にメモリ確保
		* @param args Tのコンストラクタに必要な引数
		*/
		template<typename ...Args>
		explicit ImmobilePtr(Args... args)
		{
			ptr = new T(args...);
		}
		/**
		* @brief デストラクタ時にメモリ解放
		*/
		~ImmobilePtr()noexcept
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
		* @brief リソースの取得
		*/
		T* get()
		{
			check();
			return ptr;
		}
		/**
		* @brief リソースのアドレスを取得
		*/
		T** get_address()
		{
			check();
			return &ptr;
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
			check();
			return ptr;
		}
		/**
		* @brief 参照演算子
		*/
		T operator*()const
		{
			return *ptr;
		}
		//コピー・ムーブ禁止
		ImmobilePtr(const ImmobilePtr&) = delete;
		ImmobilePtr(ImmobilePtr&&) = delete;
		ImmobilePtr& operator=(const ImmobilePtr&) = delete;
		ImmobilePtr& operator=(ImmobilePtr&&) = delete;
	private:
		//ポインタ
		T* ptr;
		/**
		* @brief リソースがあるかどうか判定する
		*/
		void check()const
		{
			assert(ptr != nullptr);
		}
	};
}
#endif //SAKI_IMMOBILE_PTR_2018_11_26