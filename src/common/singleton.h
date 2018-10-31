/**
* @file singleton.h
* @brief Singleton�e���v���[�g�X�[�p�[�N���X�̒�`
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once
#include <memory>

/**
* @brief Singleton�e���v���[�g�X�[�p�[�N���X
* @details public�ŉ������ɂ��̃N���X�����Čp������Ƃ��̃N���X��Singleton�ɂȂ�
*/
template<typename T>
class Singleton
{
public:
	/**
	* @brief �C���X�^���X�̎擾
	* @return std::unique_ptr<T>& �C���X�^���X
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
	//�R�s�[�E���[�u�֎~
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
};