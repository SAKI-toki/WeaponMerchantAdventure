/**
* @file node.h
* @brief treeクラスで使用するノードクラス
* @author 石山 悠
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
		//値
		T value;
		//ノード名
		std::string name;
		//パス
		std::string path;
		//深度
		int depth;
		//親
		std::shared_ptr<Node<T>> parent_ptr;
		//子
		std::list<std::shared_ptr<Node<T>>> child_list;
		/**
		* @brief 子を探す
		* @param node_name ノード名
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
		* @brief 子の取得
		* @param node_name ノード名
		* @details 失敗すると自分自身を返す
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
		* @brief 指定された子ノードの削除
		* @param node_name 削除する子ノード
		*/
		void delete_child_node(const std::string& node_name)
		{
			auto itr = std::begin(child_list);
			while (itr != std::end(child_list))
			{
				if (node_name == (*itr)->get_name())
				{
					//子ノードの子ノードを削除
					(*itr)->delete_node();
					//子ノードの削除
					child_list.erase(itr);
					return;
				}
			}
		}
		/**
		* @brief 関数の返り値がtrueの子ノードの削除
		* @param func 条件式
		* @param t 第二引数以降の引数
		*/
		template<typename Func, typename ...T>
		void delete_child_node(Func&& func, T ...t)
		{
			auto itr = std::begin(child_list);
			while (itr != std::end(child_list))
			{
				if (func(*itr, ...t))
				{
					//子ノードの子ノードを削除
					(*itr)->delete_node();
					//子ノードの削除
					child_list.erase(itr);
				}
			}
		}
	public:
		/**
		* @brief ノード名の取得
		* @return ノード名
		*/
		std::string get_name()const
		{
			return name;
		}
		/**
		* @brief パスの取得
		* @return パス
		*/
		std::string get_path()const
		{
			return path;
		}
		/**
		* @brief 深度の取得
		* @return 深度
		*/
		int get_depth()const
		{
			return depth;
		}
		/**
		* @brief 子の追加
		* @param c_itr 子
		* @param t 初期値
		*/
		std::shared_ptr<Node<T>> add_child(const std::string& node_name, T t)
		{
			//同じ名前があったら何もしない
			if (find_child(node_name))
			{
				return shared_from_this();
			}
			child_list.push_back(std::make_shared<Node>(shared_from_this(), node_name, path, depth, t));
			return get_child(node_name);
		}
		/**
		* @brief コンストラクタと同時に親とノード名を決定する
		* @param p_ptr 親
		* @param node_name ノード名
		* @param current_path 現在のパス
		* @param _depth 親ノードの深さ
		* @param t 初期値
		*/
		Node(std::shared_ptr<Node<T>>& p_ptr, const std::string& node_name, const std::string& current_path, const int _depth, T t) :
			parent_ptr(p_ptr), name(node_name), path(current_path + "/" + node_name), depth(_depth + 1), value(t)
		{}
		/**
		* @brief コンストラクタ(ルート限定)
		* @param p_ptr 親
		* @param node_name ノード名
		* @param t 初期値
		*/
		Node(std::shared_ptr<Node<T>>& p_ptr, const std::string& node_name, T t) :
			parent_ptr(p_ptr), name(node_name), path(node_name), depth(0), value(t)
		{}
		/**
		* @brief 自分自身をカレントディレクトリとしてノードをめぐり、たどり着いたノードを返す
		* @details 失敗すると自分自身を返す
		*/
		std::shared_ptr<Node<T>> get_node(const std::string& node_path = "")const
		{
			if (node_path == "")
			{
				return shared_from_this();
			}
			//区切ったパスを格納
			std::vector<std::string> str_list = saki::split(node_path);
			//パスが正しくない
			if (str_list.size() <= 0)return shared_from_this();
			//パスのイテレーター
			auto str_itr = std::begin(str_list);
			if (*str_itr == ".")++str_itr;
			//カレントからスタートする
			std::shared_ptr<Node> node = shared_from_this();
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
					return shared_from_this();
				}
				++str_itr;
			}
			return node;

		}
		/**
		* @brief ノードの削除
		*/
		void delete_node()
		{
			auto itr = std::begin(child_list);
			while (itr != std::end(child_list))
			{
				//子ノードの子ノードを削除
				(*itr)->delete_node();
				//子ノードの削除
				itr = child_list.erase(itr);
			}
			//親ノードから自分自身のノードの削除
			parent_ptr->delete_child_node(this->get_name());
		}
		/**
		* @brief 自分自身と自分以下の子ノードすべてに関数を実行する
		* @param func 関数
		* @param t 第二引数以降の引数
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
		* @brief 値の取得
		* @return 値
		*/
		T get_value()const
		{
			return value;
		}
		/**
		* @brief 値の参照の取得
		* @return 値の参照
		*/
		T& get_reference()const
		{
			return (value);
		}
		/**
		* @brief ノードのコピー
		* @param other_node コピーするノード
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
		* @brief ノードのムーブ
		* @param other_node ムーブするノード
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
		* @brief デバッグ用の出力関数
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