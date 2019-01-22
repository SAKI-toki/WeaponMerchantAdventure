/**
* @file array.h
* @brief �R���p�C�����Œ蒷�z��N���X
* @author �ΎR �I
* @date 2018/12/24
*/
#pragma once
#ifndef SAKI_ARRAY_2018_12_24
#define SAKI_ARRAY_2018_12_24
#include <cstddef>
#include <saki/macro/type_macro.h>
#include <saki/array/details/array_operator.h>

#include <saki/iterator/iterator.h>

namespace saki
{
	/**
	* @brief �R���p�C�����Œ蒷�z��N���X
	*/
	template<typename T, size_t Size>
	class Array
	{
	public:
		SAKI_TYPE_MACRO(T)
	private:
		value_type arr[Size]{};
	public:
		/**
		* @brief �����Ȃ��R���X�g���N�^
		* @details �S��0�ŏ�����
		*/
		constexpr Array()
		{}
		/**
		* @brief �z��̗v�f�����l���󂯎��R���X�g���N�^
		* @param u �z��̏������l
		*/
		template<typename ...U>
		explicit constexpr Array(const U& ...u) :
			arr{ u... }
		{}
		//�f�t�H���g���g�p
		//�f�t�H���g�ł̓����o�ϐ��̃R�s�[�A���[�u���s��
		Array(const Array<T, Size>&) = default;
		Array<T, Size>& operator=(const Array<T, Size>&) = default;
		Array(Array<T, Size>&&)noexcept = default;
		Array<T, Size>& operator=(Array<T, Size>&&)noexcept = default;
		/**
		* @brief []���Z�q
		*/
		constexpr reference operator[](size_t index)
		{
			return arr[index];
		}
		/**
		* @brief []���Z�q(constexpr)
		*/
		constexpr const_reference operator[](size_t index)const
		{
			return arr[index];
		}
		/**
		* @brief �z��̑傫�����擾
		* @return �z��̑傫��
		*/
		constexpr size_type size()const
		{
			return Size;
		}
		constexpr saki::iterator<T> begin()
		{
			return saki::iterator<T>(arr);
		}
		constexpr saki::iterator<T> end()
		{
			return saki::iterator<T>(arr + Size);
		}
	};

	template<typename T>
	class Array<T, 0>
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		/**
		* @brief �����Ȃ��R���X�g���N�^
		*/
		constexpr Array()
		{}
	};
	/**
	* @brief �z��̘A��
	* @param arr1,arr2 �A������z��
	* @return �A�������z��
	*/
	template<typename T, size_t Size1, size_t Size2>
	constexpr auto arraycat(const saki::Array<T, Size1>& arr1, const saki::Array<T, Size2>& arr2)
	{
		saki::Array<T, Size1 + Size2> arr{};
		size_t index = 0;
		for (size_t i = 0; i < arr1.size(); ++i)
		{
			arr[index++] = arr1[i];
		}
		for (size_t i = 0; i < arr2.size(); ++i)
		{
			arr[index++] = arr2[i];
		}
		return arr;
	}
}
#endif //SAKI_ARRAY_2018_12_24