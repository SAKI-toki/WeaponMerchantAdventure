/**
* @file tree.h
* @brief 木構造クラス
* @author 石山 悠
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
		//ルートノード
		std::shared_ptr<Node<T>> root;
	public:
		/**
		* @brief 引数なしコンストラクタ
		* @details rootの名前はrootにする
		*/
		Tree()
		{
			root = std::make_shared<Node<T>>(root, "root", T());
		}
		/**
		* @brief 引数ありコンストラクタ
		* @param name ルートノード名
		*/
		Tree(const std::string& name, T t)
		{
			root = std::make_shared<Node<T>>(root, name, t);
		}
		/**
		* @brief ノードの追加
		* @param path パス
		* @param node_name ノード名
		* @return ノードの追加に成功したかどうか
		* @details パスに空白を入れないでください
		*/
		std::shared_ptr<Node<T>> add_child(const std::string& node_name, T t)
		{
			return root->add_child(node_name, t);
		}

		/**
		* @brief ルートディレクトリからノードをめぐり、たどり着いたノードを返す
		* @details 失敗するとrootを返す
		*/
		std::shared_ptr<Node<T>> get_node(const std::string& node_path = "")const
		{
			if (node_path == "")
			{
				return root;
			}
			//区切ったパスを格納
			std::vector<std::string> str_list = saki::split(node_path);
			//パスが正しくない
			if (str_list.size() <= 0)return root;
			//パスのイテレーター
			auto str_itr = std::begin(str_list);
			if (*str_itr != ".")++str_itr;
			//カレントからスタートする
			std::shared_ptr<Node<T>> node = root;
			//ノードをめぐる
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
				//ノードが見つからなかった
				else
				{
					return root;
				}
				++str_itr;
			}
			return node;
		}
		/**
		* @brief rootの取得
		* @return root
		*/
		std::shared_ptr<Node<T>> get_root()const
		{
			return root;
		}
		/**
		* @brief コピーコンストラクタ
		* @details shared_ptrを使用しているため、デフォルトコピーコンストラクタではエラーが起きる
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
		* @brief デバッグ用の出力関数
		*/
		void all_node_name()
		{
			root->node_print();
		}
	};
}
#endif //SAKI_TREE_2018_12_13