#pragma once
#include <iostream>
class RBtree{
public:
	int key;
	RBtree* left;
	RBtree* right;
	RBtree* parent;
	bool color_red; // black - false | red - true
	RBtree(int KEY, bool color = true, RBtree* PARENT = NULL);
	RBtree(int KEY, RBtree LEFT, RBtree RIGHT, bool COLOR);
	void print(int u = 0);
	void insert(int k);
	RBtree*& iterative_search(int k);
	bool RED();
	void LR();
	void RR();
	void reparent(bool a = true);
	void del(int k);
	void balanceBlack(int k);
};

