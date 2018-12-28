/**
* @file node.h
* @brief tree�N���X�Ŏg�p����m�[�h�N���X
* @author �ΎR �I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_NODE_2018_12_13
#define SAKI_NODE_2018_12_13
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>

namespace saki
{
	template<typename T>
	class Tree;
	template<typename T>
	class Node :public std::enable_shared_from_this<Node<T>>
	{
		friend class Tree<T>;
		//�l
		T value;
		//�m�[�h��
		std::string name;
		//�p�X
		std::string path;
		//�[�x
		int depth;
		//�e
		std::shared_ptr<Node<T>> parent_ptr;
		//�q
		std::list<std::shared_ptr<Node<T>>> child_list;
		/**
		* @brief �q��T��
		* @param node_name �m�[�h��
		*/
		bool find_child(const std::string& node_name)
		{
			for (const auto& c : child_list)
			{
				if (node_name == c->get_name())
				{
					return true;
				}
			}
			return false;
		}
		/**
		* @brief �q�̎擾
		* @param node_name �m�[�h��
		* @details ���s����Ǝ������g��Ԃ�
		*/
		std::shared_ptr<Node<T>> get_child(const std::string& node_name)
		{
			auto itr = std::begin(child_list);
			while (itr != std::end(child_list))
			{
				if (node_name == (*itr)->get_name())
				{
					return *itr;
				}
				++itr;
			}
			return shared_from_this();
		}
		/**
		* @brief �w�肳�ꂽ�q�m�[�h�̍폜
		* @param node_name �폜����q�m�[�h
		*/
		void delete_child_node(const std::string& node_name)
		{
			auto itr = std::begin(child_list);
			while (itr != std::end(child_list))
			{
				if (node_name == (*itr)->get_name())
				{
					//�q�m�[�h�̎q�m�[�h���폜
					(*itr)->delete_node();
					//�q�m�[�h�̍폜
					child_list.erase(itr);
					return;
				}
			}
		}
		/**
		* @brief �֐��̕Ԃ�l��true�̎q�m�[�h�̍폜
		* @param func ������
		* @param t �������ȍ~�̈���
		*/
		template<typename Func, typename ...T>
		void delete_child_node(Func&& func, T ...t)
		{
			auto itr = std::begin(child_list);
			while (itr != std::end(child_list))
			{
				if (func(*itr, ...t))
				{
					//�q�m�[�h�̎q�m�[�h���폜
					(*itr)->delete_node();
					//�q�m�[�h�̍폜
					child_list.erase(itr);
				}
			}
		}
	public:
		/**
		* @brief �m�[�h���̎擾
		* @return �m�[�h��
		*/
		std::string get_name()const
		{
			return name;
		}
		/**
		* @brief �p�X�̎擾
		* @return �p�X
		*/
		std::string get_path()const
		{
			return path;
		}
		/**
		* @brief �[�x�̎擾
		* @return �[�x
		*/
		int get_depth()const
		{
			return depth;
		}
		/**
		* @brief �q�̒ǉ�
		* @param c_itr �q
		* @param t �����l
		*/
		std::shared_ptr<Node<T>> add_child(const std::string& node_name, T t)
		{
			//�������O���������牽�����Ȃ�
			if (find_child(node_name))
			{
				return shared_from_this();
			}
			child_list.push_back(std::make_shared<Node>(shared_from_this(), node_name, path, depth, t));
			return get_child(node_name);
		}
		/**
		* @brief �R���X�g���N�^�Ɠ����ɐe�ƃm�[�h�������肷��
		* @param p_ptr �e
		* @param node_name �m�[�h��
		* @param current_path ���݂̃p�X
		* @param _depth �e�m�[�h�̐[��
		* @param t �����l
		*/
		Node(std::shared_ptr<Node<T>>& p_ptr, const std::string& node_name, const std::string& current_path, const int _depth, T t) :
			parent_ptr(p_ptr), name(node_name), path(current_path + "/" + node_name), depth(_depth + 1), value(t)
		{}
		/**
		* @brief �R���X�g���N�^(���[�g����)
		* @param p_ptr �e
		* @param node_name �m�[�h��
		* @param t �����l
		*/
		Node(std::shared_ptr<Node<T>>& p_ptr, const std::string& node_name, T t) :
			parent_ptr(p_ptr), name(node_name), path(node_name), depth(0), value(t)
		{}
		/**
		* @brief �������g���J�����g�f�B���N�g���Ƃ��ăm�[�h���߂���A���ǂ蒅�����m�[�h��Ԃ�
		* @details ���s����Ǝ������g��Ԃ�
		*/
		std::shared_ptr<Node<T>> get_node(const std::string& node_path = "")const
		{
			if (node_path == "")
			{
				return shared_from_this();
			}
			//��؂����p�X���i�[
			std::vector<std::string> str_list = saki::split(node_path);
			//�p�X���������Ȃ�
			if (str_list.size() <= 0)return shared_from_this();
			//�p�X�̃C�e���[�^�[
			auto str_itr = std::begin(str_list);
			if (*str_itr == ".")++str_itr;
			//�J�����g����X�^�[�g����
			std::shared_ptr<Node> node = shared_from_this();
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
					return shared_from_this();
				}
				++str_itr;
			}
			return node;

		}
		/**
		* @brief �m�[�h�̍폜
		*/
		void delete_node()
		{
			auto itr = std::begin(child_list);
			while (itr != std::end(child_list))
			{
				//�q�m�[�h�̎q�m�[�h���폜
				(*itr)->delete_node();
				//�q�m�[�h�̍폜
				itr = child_list.erase(itr);
			}
			//�e�m�[�h���玩�����g�̃m�[�h�̍폜
			parent_ptr->delete_child_node(this->get_name());
		}
		/**
		* @brief �������g�Ǝ����ȉ��̎q�m�[�h���ׂĂɊ֐������s����
		* @param func �֐�
		* @param t �������ȍ~�̈���
		*/
		template<typename Func, typename ...T>
		void all_child_func(Func&& func, T ...t)
		{
			func(shared_from_this(), t...);
			for (auto&& n : child_list)
			{
				n->all_child_func(func, t...);
			}
		}
		/**
		* @brief �l�̎擾
		* @return �l
		*/
		T get_value()const
		{
			return value;
		}
		/**
		* @brief �l�̎Q�Ƃ̎擾
		* @return �l�̎Q��
		*/
		T& get_reference()const
		{
			return (value);
		}
		/**
		* @brief �m�[�h�̃R�s�[
		* @param other_node �R�s�[����m�[�h
		*/
		void copy_node(const std::shared_ptr<Node<T>>& other_node)
		{
			for (const auto& other : other_node->child_list)
			{
				auto child = this->add_child(other->get_name());
				child->copy_node(other);
			}
		}
		/**
		* @brief �m�[�h�̃��[�u
		* @param other_node ���[�u����m�[�h
		*/
		void move_node(std::shared_ptr<Node<T>>&& other_node)noexcept
		{
			for (auto&& other : other_node->child_list)
			{
				auto child = this->add_child(other->get_name());
				child->move_node(std::move(other));
			}
		}
		/**
		* @brief �f�o�b�O�p�̏o�͊֐�
		*/
		void node_print()
		{
			for (int i = 0; i < depth; ++i)
			{
				std::cout << "---";
			}
			std::cout << get_name() << "(" << get_value() << ")" << std::endl;
			for (auto&& c : child_list)
			{
				c->node_print();
			}
		}
	};


}
#endif //SAKI_NODE_2018_12_13