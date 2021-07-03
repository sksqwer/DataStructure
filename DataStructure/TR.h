#pragma once
#ifndef TREE_H_
#define TREE_H_

template<typename T>
struct node
{
	int value;
	T data;
	node * left = NULL;
	node * right = NULL;
};

template<typename T>
class Tr
{
public:
	node<T> *Root = NULL;
	Tr() {}
	~Tr();
	void insert(node<T> v);
	void Delete(int n);
	node<T>* Search(node<T> *root, T data);
	node<T>* Search(node<T> *root, int n);
	void print(node<T> *root);
	void reset(node<T> *root);
	int check_depth(node<T> *root);
	void toAVL(node<T> *root, node<T>* R);
	void print_Tree();
	void drawarr(node<T> *root, int depth, int itr, int arr[][1025]);
};

#endif // !TREE_H_
