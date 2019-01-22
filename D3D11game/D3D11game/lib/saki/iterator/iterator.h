/**
* @file iterator.h
* @brief コンパイル時iterator
* @author 石山 悠
* @date 2019/01/09
*/
#pragma once
#ifndef SAKI_ITERATOR_2019_01_09
#define SAKI_ITERATOR_2019_01_09
#include <saki/macro/type_macro.h>
#include <saki/iterator/details/iterator_operator.h>

namespace saki
{
	namespace details
	{
		template<typename T>
		class iterator_base
		{
			template<typename TT>
			friend constexpr bool operator==(const iterator_base<TT>& itr1, const iterator_base<TT>& itr2);
			template<typename TT>
			friend constexpr bool operator!=(const iterator_base<TT>& itr1, const iterator_base<TT>& itr2);
		public:
			SAKI_TYPE_MACRO(T)
		public:
			T* itr;
			explicit constexpr iterator_base(T* pointer) : itr(pointer) {}
			constexpr T& operator*()const
			{
				return *itr;
			}
			constexpr T* operator->()const
			{
				return itr;
			}
			/**
			* @brief ++演算子(前置)
			*/
			constexpr saki::details::iterator_base<T>& operator++()
			{
				this->itr += 1;
				return *this;
			}
			/**
			* @brief ++演算子(後置)
			*/
			constexpr saki::details::iterator_base<T> operator++(int)
			{
				saki::details::iterator_base<T> temp = *this;
				this->itr += 1;
				return temp;
			}
			/**
			* @brief --演算子(前置)
			*/
			constexpr saki::details::iterator_base<T>& operator--()
			{
				this->itr -= 1;
				return *this;
			}
			/**
			* @brief --演算子(後置)
			*/
			constexpr saki::details::iterator_base<T> operator--(int)
			{
				saki::details::iterator_base<T> temp = *this;
				this->itr -= 1;
				return temp;
			}
		};
	}
	template<typename T>
	class iterator :public saki::details::iterator_base<T>
	{
	public:
		explicit constexpr iterator(T* pointer) :saki::details::iterator_base<T>(pointer) {}
	};
}
#endif //SAKI_ITERATOR_2019_01_09