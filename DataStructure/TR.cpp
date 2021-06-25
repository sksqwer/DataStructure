#include "TR.h"
#include "stddef.h"
#include <iostream>
#include <string>


template<typename T>
inline Tr<T>::~Tr()
{
	this->reset(Root);
}

template<typename T>
void Tr<T>::insert(node<T> v)
{
	node<T> *vv = new node<T>;
	vv->value = v.value;
	vv->data = v.data;
	node<T> *cur = Root;
	node<T> *par = Root;
	if (cur == NULL)
		Root = vv;
	else
	{
		while (1)
		{
			if (cur->value == vv->value)
			{
				std::cout << "중복된 숫자입니다!\n";
				return;
			}
			if (cur->value > vv->value)
			{
				par = cur;
				cur = cur->left;
				if (cur == NULL)
				{
					par->left = vv;
					break;
				}
			}
			else
			{
				par = cur;
				cur = cur->right;
				if (cur == NULL)
				{
					par->right = vv;;
					break;
				}
			}
		}
	}
}

template<typename T>
void Tr<T>::Delete(int n)
{
	node<T> *cur = Root;
	node<T> *par = Root;
	if (cur == NULL)
	{
		std::cout << "노드를 찾을 수 없습니다!\n";
		return;
	}
	else
	{
		while (1)
		{
			if (cur == NULL)
				break;

			if (cur->value == n)
				break;

			par = cur;
			if (cur->value > n)
				cur = cur->left;
			else
				cur = cur->right;
		}

		if(cur == NULL)
		{
			std::cout << "노드를 찾을 수 없습니다!\n";
			return;
		}


		node<T> *max = cur->left;
		node<T> *max_par = cur;
		if (cur->left == NULL)
		{
			if (cur->right == NULL)
			{
				if (par->left == cur)
					par->left = NULL;
				else
					par->right = NULL;
			}
			else
			{
				if (par->left == cur)
					par->left = cur->right;
				else
					par->right = cur->right;
			}
			if (cur == Root)
				Root = cur->right;
		}
		else
		{
			while (max->right != NULL)
			{
				max_par = max;
				max = max->right;
			}
			if (max_par == cur)
			{
				if (par->left == cur)
				{
					par->left = max;
					max->right = cur->right;
				}
				else 
				{
					par->right = max;
					max->right = cur->right;
				}

			}
			else
			{
				max_par->right = max->left;

				if (par->left == cur)
				{
					par->left = max;
				}
				else 
				{
					par->right = max;
				}
				
				max->left = cur->left;
				max->right = cur->right;
			}
			if (cur == Root)
				Root = max;
		}


		std::cout << cur->value << " " << cur->data << "가 삭제되었습니다.\n";
		delete cur;
	}



}
template<typename T>
node<T>* Tr<T>::Search(node<T> *root, T data)
{
	if (root == NULL)
		return NULL;
	else
	{
		if (root->data == data)
			return root;

		node<T>* res = NULL;
		node<T>* temp = NULL;
		temp = Search(root->left, data);
		if (temp != NULL)
			res = temp;

		temp = Search(root->right, data);
		if (temp != NULL)
			res = temp;

		return res;
	}
}
template<typename T>
node<T>* Tr<T>::Search(node<T> *root, int n)
{
	if (root == NULL)
		return NULL;
	else
	{
		node<T>* cur = root;

		while (cur->value != n)
		{
			if (cur->value == NULL)
				return NULL;


			if (cur->value > n)
				cur = cur->left;
			else
				cur = cur->right;
		}
	}
}

template<typename T>
void Tr<T>::print(node<T> *root)
{

	if (root == NULL)
		return;
	else
	{
		print(root->left);
		std::cout << root->value << " " << root->data << std::endl;
		print(root->right);
	}
}

template<typename T>
void Tr<T>::reset(node<T>* root)
{
	if (root == NULL)
		return;

	reset(root->left);
	reset(root->right);

	delete root;
}
