#include "RBtree.h"
#include <iostream>

using namespace std;

RBtree::RBtree(int KEY, bool color, RBtree* PARENT) {
	key = KEY;
	left = NULL;
	right = NULL;
	parent = PARENT;
	color_red = color;
}

RBtree::RBtree(int KEY, RBtree LEFT, RBtree RIGHT, bool COLOR) {
	key = KEY;
	left = new RBtree(LEFT);
	right = new RBtree(RIGHT);
	parent = NULL;
	color_red = COLOR;
}



void RBtree::print(int u) {
	if (this) {
		right->print(u + 1);

		for (int i = 0; i < u; i++) {
			cout << " ";
		}
		cout << key << "\n";
		left->print(u + 1);
	}
}

void RBtree::reparent(bool a) {
	if (a) this->parent = NULL;
	if (this->left) {
		this->left->parent = this;
		this->left->reparent(false);
	}
	if (this->right) {
		this->right->parent = this;
		this->right->reparent(false);
	}
}

void RBtree::LR() {
	RBtree& q = *this;
	RBtree* p = q.right;
	q.right = p->left;
	p->left = new RBtree(q);
	q = *p;
}


void RBtree::RR() {
	RBtree& p = *this;
	RBtree* q = p.left;
	p.left = q->right;
	q->right = new RBtree(p);
	p = *q;
}

RBtree*& RBtree::iterative_search(int k) {
	RBtree* tree = this;
	if ((!tree->left and !tree->right) or !tree) return tree;
	while (k != tree->key) {
		//Проверка является ли проверяемое дерево родителем искомого
		if (tree->left) {
			if (tree->left->key == k) return tree->left;
		}
		if (tree->right) {
			if (tree->right->key == k) return tree->right;
		}

		if (k < tree->key) {
			if (!tree->left) return tree;
			tree = tree->left;
		}
		else {
			if (!tree->right) return tree;
			tree = tree->right;
		}
	}
	return tree;
}

bool RBtree::RED() {
	if (this) {
		return this->color_red;
	} 
	return false;
}

void RBtree::insert(int k) {
	RBtree* tree = this->iterative_search(k);
	RBtree* x;
	if (k < tree->key) {
		tree->left = new RBtree(k, true, tree);//true - красный, tree ссылка на родителя
		x = tree->left;
	}
	else if (k > tree->key) {
		tree->right = new RBtree(k, true, tree);
		x = tree->right;
	}
	else return;
	
	while (x->parent and x->parent->RED()) {
		if (!x->parent->parent) return;
		if (x->parent == x->parent->parent->left) {
			RBtree* y = x->parent->parent->right;
			if (y->RED()) { // случай 1
				x->parent->color_red = false;
				y->color_red = false;
				x->parent->parent->color_red = true;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) { // случай 3
					x->color_red = false;
					x->parent->LR();
					this->reparent();
					x = this->iterative_search(k);
					x->parent->color_red = true;
					x->parent->RR();
					this->reparent();
					x = this->iterative_search(k);
				}
				else { // случай 2
					x->parent->color_red = false;
					x->parent->parent->color_red = true;
					x->parent->parent->RR();
					this->reparent();
					x = this->iterative_search(k);
				}
				
			}
		}
		else {
			RBtree* y = x->parent->parent->left;
			if (y->RED()) { // случай 1
				x->parent->color_red = false;
				y->color_red = false;
				x->parent->parent->color_red = true;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->left) { // случай 3
					x->color_red = false;
					x->parent->RR();
					this->reparent();
					x = this->iterative_search(k);
					x->parent->color_red = true;
					x->parent->LR();
					this->reparent();
					x = this->iterative_search(k);
				}
				else {
					x->parent->color_red = false;
					x->parent->parent->color_red = true;
					x->parent->parent->LR();
					this->reparent();
					x = this->iterative_search(k);
				}
			}
		}
	}
	if (x->parent == NULL) x->color_red = false;
	this->reparent();
}

void RBtree::balanceBlack(int k) {
	this->reparent();
	RBtree* x = this->iterative_search(k);;
	while (x->parent and !x->color_red) {
		if (x = x->parent->left) {
			RBtree* b = x->parent->right; // брат удаляемого узла
			if (b->RED()) { // случай 4
				b->color_red = false;
				x->parent->color_red = true;
				x->parent->LR();
				this->reparent();
				x = this->iterative_search(k);
				b = x->parent->right;
			}
			if (!b->left->RED() and !b->right->RED()) {// случай 1 или 5
				b->color_red = true;
				x = x->parent;
				k = x->parent->key;
			}
			else {
				if (!b->right->RED()) { // случай 3
					if (b->left) b->left->color_red = false;
					b->color_red = true;
					b->parent->RR();
					this->reparent();
					b = x->parent->right;
				}
				// случай 2
				b->color_red = x->parent->color_red;
				x->parent->color_red = false;
				b->right->color_red = false;
				x->parent->LR();
				break;
			}
		}
		else {
			RBtree* b = x->parent->left; // брат удаляемого узла
			if (b->RED()) { // случай 4
				b->color_red = false;
				x->parent->color_red = true;
				x->parent->RR();
				this->reparent();
				x = this->iterative_search(k);
				b = x->parent->left;
			}
			if (!b->right->RED() and !b->left->RED()) {// случай 1 или 5
				b->color_red = true;
				x = x->parent;
				k = x->parent->key;
			}
			else {
				if (!b->left->RED()) { // случай 3
					if (b->right) b->right->color_red = false;
					b->color_red = true;
					b->parent->LR();
					this->reparent();
					b = x->parent->left;
				}
				// случай 2
				b->color_red = x->parent->color_red;
				x->parent->color_red = false;
				b->left->color_red = false;
				x->parent->LR();
				break;
			}
		}
	}
	this->reparent();
	x = this->iterative_search(k);
	x->color_red = false;
}

void RBtree::del(int k) {
	RBtree*& tree = this->iterative_search(k);// Ищем ссылку на указатель удаляемого узла
	if (tree->key != k) return; // Выход если узла который нужно удалить нету в дереве 

	// Первый случай
	if (!tree->left and !tree->right) {
		this->balanceBlack(tree->key);
		RBtree*& tree = this->iterative_search(k);
		tree = NULL;
		return;
	}

	//Второй случай
	if (tree->left and !tree->right) {
		tree->left->color_red = false;
		tree = tree->left;
		return;
	}
	if (tree->right and !tree->left) {
		tree->right->color_red = false;
		tree = tree->right;
		return;
	}

	//Третий случай
	if (tree->left and tree->right) {
		int delkey;
		RBtree* newTree = tree->right;
		while (newTree->left) {
			newTree = newTree->left;
		}
		delkey = newTree->key;

		this->del(delkey);
		this->iterative_search(k)->key = delkey;
	}
}
