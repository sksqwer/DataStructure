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


	print_Tree();
	toAVL(Root, Root);
	print_Tree();
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
				if (cur == Root)
				{
					Root = NULL;
				}
				else if (par->left == cur)
					par->left = NULL;
				else
					par->right = NULL;
			}
			else
			{
				if (cur == Root)
				{
					Root = cur->right;
				}
				else if (par->left == cur)
					par->left = cur->right;
				else
					par->right = cur->right;
			}
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
				if (cur == Root)
				{
					Root = max;
					max->right = cur->right;
				}
				else if (par->left == cur)
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

				if (cur == Root)
				{
					Root = max;
				}
				else if (par->left == cur)
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
		}


		std::cout << cur->value << " " << cur->data << "가 삭제되었습니다.\n";
		delete cur;
	}

	print_Tree();
	toAVL(Root, Root);
	print_Tree();



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

template<typename T>
int Tr<T>::check_depth(node<T>* root)
{
	if (root == NULL)
		return 0;

	int res = 1, l, r;
	l = check_depth(root->left);
	r = check_depth(root->right);

	if (l > r)
		res += l;
	else
		res += r;

	return res;
}

template<typename T>
void Tr<T>::toAVL(node<T>* root, node<T>* R)
{
	if (root == NULL) return;

	toAVL(root->left, root);
	toAVL(root->right, root);

	int ldepth = check_depth(root->left);
	int rdepth = check_depth(root->right);

	if (abs(ldepth - rdepth) > 1)
	{
		if (ldepth > rdepth)
		{
			if (root->left == NULL)
				return;

			ldepth = check_depth(root->left->left);
			rdepth = check_depth(root->left->right);

			if (abs(ldepth - rdepth) > 1)
			{
				if (ldepth > rdepth)
				{
					if (root == Root)
					{
						node<T> *temp = root->left->right;
						Root = root->left;
						Root->right = root;
						root->right = temp;
					}
					else
					{
						if (R->left = root)
						{
							node<T> *temp = root->left->right;
							R->left = root->left;
							R->left->right = root;
							root->left = temp;
						}
						else
						{
							node<T> *temp = root->left->right;
							R->right = root->left;
							R->right->right = root;
							root->left = temp;
						}
					}


				}
				else
				{
					if (root == Root)
					{
						node<T> *temp = root->left->right->left;
						node<T> *temp2 = root->left->right->right;
						Root = root->left->right;
						Root->right = root;
						Root->left = root->left;
						root->left->right = temp;
						root->left = temp2;
					}
					else
					{
						if (R->left = root)
						{
							node<T> *temp = root->left->right->left;
							node<T> *temp2 = root->left->right->right;
							R->left = root->left->right;
							R->left->right = root;
							R->left->left = root->left;
							root->left->right = temp;
							root->left = temp2;
						}
						else
						{
							node<T> *temp = root->left->right->left;
							node<T> *temp2 = root->left->right->right;
							R->right = root->left->right;
							R->right->right = root;
							R->right->left = root->left;
							root->left->right = temp;
							root->left = temp2;
						}
					}
				}
			}
		}
		else
		{
			if (root->right == NULL)
				return;

			ldepth = check_depth(root->right->left);
			rdepth = check_depth(root->right->right);

			if (abs(ldepth - rdepth) > 1)
			{
				if (ldepth > rdepth)
				{
					if (root == Root)
					{
						node<T> *temp = root->right->left;
						Root = root->right;
						Root->left = root;
						root->right = temp;
					}
					else
					{
						if (R->left = root)
						{
							node<T> *temp = root->right->left;
							R->left = root->right;
							R->left->left = root;
							root->right = temp;
						}
						else
						{
							node<T> *temp = root->right->left;
							R->right = root->right;
							R->right->left = root;
							root->right = temp;
						}
					}


				}
				else
				{
					if (root == Root)
					{
						node<T> *temp = root->right->left->left;
						node<T> *temp2 = root->right->left->right;
						Root = root->right->left;
						Root->left = root;
						Root->right = root->right;
						root->right = temp;
						Root->right->left = temp2;
					}
					else
					{
						if (R->left = root)
						{
							node<T> *temp = root->right->left->left;
							node<T> *temp2 = root->right->left->right;
							R->left = root->right->left;
							R->left->left = root;
							R->left->right = root->right;
							root->right = temp;
							R->left->right->left = temp2;
						}
						else
						{
							node<T> *temp = root->right->left->left;
							node<T> *temp2 = root->right->left->right;
							R->right = root->right->left;
							R->right->left = root;
							R->right->right = root->right;
							root->right = temp;
							R->right->right->left = temp2;
						}
					}
				}
			}
		}
	}

}

template<typename T>
void Tr<T>::print_Tree()
{
	if (Root == nullptr || Root == NULL)
		return;

	int depth = check_depth(Root);
	int w = pow(2, depth);

	int arr[10][1025] = { -1 };
	memset(arr, -1, sizeof(int) * 10 * 1025);



	int itr = w / 2;
	drawarr(Root, 0, itr, arr);

	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (arr[i][j] == -1)
				std::cout << " ";
			else
				std::cout << arr[i][j];
		}
		std::cout << std::endl;
	}

}

template<typename T>
void Tr<T>::drawarr(node<T> *root, int depth, int itr, int arr[][1025])
{

	if (root == nullptr)
		return;

	arr[depth][itr] = root->value;
	int n = pow(2, check_depth(this->Root) - depth - 2);
	drawarr(root->left, depth + 1, itr - n, arr);
	drawarr(root->right, depth + 1, itr + n, arr);


}
