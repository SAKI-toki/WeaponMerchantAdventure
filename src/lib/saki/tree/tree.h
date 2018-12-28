/**
* @file tree.h
* @brief �؍\���N���X
* @author �ΎR �I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_TREE_2018_12_13
#define SAKI_TREE_2018_12_13
#include <list>
#include <saki/tree/node/node.h>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <saki/split/split.h>

namespace saki
{
	template<typename T>
	class Tree
	{
		//���[�g�m�[�h
		std::shared_ptr<Node<T>> root;
	public:
		/**
		* @brief �����Ȃ��R���X�g���N�^
		* @details root�̖��O��root�ɂ���
		*/
		Tree()
		{
			root = std::make_shared<Node<T>>(root, "root", T());
		}
		/**
		* @brief ��������R���X�g���N�^
		* @param name ���[�g�m�[�h��
		*/
		Tree(const std::string& name, T t)
		{
			root = std::make_shared<Node<T>>(root, name, t);
		}
		/**
		* @brief �m�[�h�̒ǉ�
		* @param path �p�X
		* @param node_name �m�[�h��
		* @return �m�[�h�̒ǉ��ɐ����������ǂ���
		* @details �p�X�ɋ󔒂����Ȃ��ł�������
		*/
		std::shared_ptr<Node<T>> add_child(const std::string& node_name, T t)
		{
			return root->add_child(node_name, t);
		}

		/**
		* @brief ���[�g�f�B���N�g������m�[�h���߂���A���ǂ蒅�����m�[�h��Ԃ�
		* @details ���s�����root��Ԃ�
		*/
		std::shared_ptr<Node<T>> get_node(const std::string& node_path = "")const
		{
			if (node_path == "")
			{
				return root;
			}
			//��؂����p�X���i�[
			std::vector<std::string> str_list = saki::split(node_path);
			//�p�X���������Ȃ�
			if (str_list.size() <= 0)return root;
			//�p�X�̃C�e���[�^�[
			auto str_itr = std::begin(str_list);
			if (*str_itr != ".")++str_itr;
			//�J�����g����X�^�[�g����
			std::shared_ptr<Node<T>> node = root;
			//�m�[�h���߂���
			while (str_itr != std::end(str_list))
			{
				if (*str_itr == "..")
				{
					node = node->parent_ptr;
				}
				else if (node->find_child(*str_itr))
				{
					node = node->get_child(*str_itr);
				}
				//�m�[�h��������Ȃ�����
				else
				{
					return root;
				}
				++str_itr;
			}
			return node;
		}
		/**
		* @brief root�̎擾
		* @return root
		*/
		std::shared_ptr<Node<T>> get_root()const
		{
			return root;
		}
		/**
		* @brief �R�s�[�R���X�g���N�^
		* @details shared_ptr���g�p���Ă��邽�߁A�f�t�H���g�R�s�[�R���X�g���N�^�ł̓G���[���N����
		*/
		Tree(const Tree& other)
		{
			this->root = std::make_shared<Node<T>>(this->root, other.root->name,other.root->get_value());
			root->copy_node(other.root);
		}
		Tree<T>& operator=(const Tree&) = default;
		Tree(Tree&& other)noexcept
		{
			this->root = std::make_shared<Node<T>>(this->root, other.root->name, other.root->get_value());
			root->move_node(std::move(other.root));

		}
		Tree<T>& operator=(Tree&&)noexcept = default;

		/**
		* @brief �f�o�b�O�p�̏o�͊֐�
		*/
		void all_node_name()
		{
			root->node_print();
		}
	};
}
#endif //SAKI_TREE_2018_12_13