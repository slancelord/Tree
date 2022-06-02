#pragma once
class AVLtree {
public:
    int key;
	AVLtree* left;
	AVLtree* right;
	int bf;
	AVLtree(int KEY);
	AVLtree(int KEY, AVLtree LEFT, AVLtree RIGHT);
	int depth();
	AVLtree*& iterative_search(int k);
	void insert(int k);
	void print(int u = 0);
	int b();
	void LR();
	void RR();
	void balance();
	void add(int k);
	void del(int k);
	void bindel(int k);
};

