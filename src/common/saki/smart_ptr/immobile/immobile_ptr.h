/**
* @file immobile_ptr.h
* @brief �R�s�[�E���[�u�֎~�̃X�}�[�g�|�C���^
* @author �ΎR �I
* @date 2018/10/18
*/
/*
�W�����C�u������std::unique_ptr�̃��[�u���֎~�����o�[�W�����ł��B
���ꎩ�̂₱����܂ރN���X����vector�̂悤�ȃ��[�u����\����������̂𗘗p�����
�s����N����̂ŁA�P�̂Ŏg�p���Ă��������B
�����[�u�֎~�̂��߁Astd::make_unique�̂悤�ȃw���p�[�֐����쐬�ł��Ȃ��B
*/
#ifndef SAKI_IMMOBILE_PTR_2018_10_17
#define SAKI_IMMOBILE_PTR_2018_10_17
#include <assert.h>	//for assert
namespace saki
{
	/**
	* @brief �R�s�[�E���[�u�֎~�̃X�}�[�g�|�C���^
	*/
	template<typename T>
	class immobile_ptr
	{
	public:
		/**
		* @brief �R���X�g���N�^���Ƀ������m��
		* @param args T�̃R���X�g���N�^�ɕK�v�Ȉ���
		*/
		template<typename ...Args>
		explicit immobile_ptr(Args... args)
		{
			ptr = new T(args...);
		}
		/**
		* @brief �f�X�g���N�^���Ƀ��������
		*/
		~immobile_ptr()noexcept
		{
			release();
		}
		/**
		* @brief �����I�ȃ��������
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
		* @brief �����I�ȃ���������ƐV���Ƀ������m�ۂ���
		* @param args T�̃R���X�g���N�^�ɕK�v�Ȉ���
		*/
		template<typename ...Args>
		void reset(Args ...args)
		{
			release();
			ptr = new T(args...);
		}
		/**
		* @brief �ϊ����Z�q
		*/
		explicit operator bool()const
		{
			return ptr != nullptr;
		}
		/**
		* @brief �A���[���Z�q
		*/
		T* operator->()const
		{
			assert(ptr != nullptr);
			return ptr;
		}
		//�R�s�[�E���[�u�֎~
		immobile_ptr(const immobile_ptr&) = delete;
		immobile_ptr(immobile_ptr&&) = delete;
		immobile_ptr& operator=(const immobile_ptr&) = delete;
		immobile_ptr& operator=(immobile_ptr&&) = delete;
	private:
		//�|�C���^
		T* ptr;
	};
}
#endif //SAKI_IMMOBILE_PTR_2018_10_17