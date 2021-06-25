#include "Tr.h"
template<typename T>
inline Tr<T>::~Tr()
{
	this->reset(Root);
}

template<typename T>
void Tr<T>::insert(node<T> v)
{
	node<T> *vv = new node(v);
	node<T> *cur = Root;
	node<T> *par = Root;
	if (cur == nullptr)
		Root = vv;
	else
	{
		while (1)
		{
			if (cur.value == vv.value)
			{
				std::cout << "중복된 숫자입니다!\n";
				return;
			}
			if (cur.value > vv.value)
			{
				par = cur;
				cur = cur.left;
				if (cur == nullptr)
				{
					par.left = vv;
					break;
				}
			}
			else
			{
				par = cur;
				cur = cur.right;
				if (cur == nullptr)
				{
					par.right = vv;;
					break;
				}
			}
		}
	}
}

template<typename T>
void Tr<T>::Delete(node<T> v)
{
	node<T> *cur = Root;
	node<T> *par = Root;
	if (cur == nullptr)
	{
		std::cout << "노드를 찾을 수 없습니다!\n";
		return;
	}
	else
	{
		while (1)
		{
			if (cur.data == v.data)
			{
				break;
			}
			if (cur == nullptr)
			{
				std::cout << "노드를 찾을 수 없습니다!\n";
				return;
			}
			if (cur.value > v.value)
			{
				par = cur;
				cur = cur.left;
			}
			else
			{
				par = cur;
				cur = cur.right;
			}
		}
		node<T> *max;
		node<T> *max_par = cur;
		if (cur->left == nullptr)
		{
			if (cur->right == nullptr)
			{
				if (par.left == cur)
					par.left = nullptr;
				else
					par.right = nullptr;
			}
			else
			{
				if (par.left == cur)
					par.left = cur.right;
				else
					par.right = cur.right;
			}
			delete cur;
		}
		else
		{
			max = cur->left;
			while (max->right == nullptr)
			{
				max_par = max;
				max = max->right;
			}
			if (max_par == cur)
			{
				if (par.left == max)
					par.left = max;
				else
					par.right = max;

			}
			else
			{
				max_par.right = max.left;

				if (par.left == cur)
					par.left = max;
				else
					par.right = max;

				max.left = cur.left;
				max.right = cur.right;
			}
			delete cur;
		}
	}



}

template<typename T>
node<T> Tr<T>::Search(node<T> *root, T data)
{
	if (root == nullptr)
		return nullptr;
	else
	{
		if (root.data == data)
			return *root;

		node<T> res = nullptr;
		node<T> temp = nullptr;
		temp = Search(root->left, data);
		if (temp != nullptr)
			res = temp;

		temp = Search(root->right, data);
		if (temp != nullptr)
			res = temp;

		return res;
	}
}

template<typename T>
void Tr<T>::print(node<T> *root)
{
	if (root == nullptr)
		return;
	else
	{
		std::cout << root->value << " " << root->data << std::endl;
		print(root->left);
		print(root->right);
	}
}

template<typename T>
void Tr<T>::reset(node<T>* root)
{
	if (root == nullptr)
		return;

	reset(root->left);
	reset(root->right);

	delete root;
}
