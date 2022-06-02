#include "AVLtree.h"
#include <iostream>
using namespace std;

int AVLtree::depth() {
    int h = 0;
    if (this) {
        int lDepth = left->depth();
        int rDepth = right->depth();
        h = std::max(lDepth + 1, rDepth + 1);
    }
    return h;
}

void AVLtree::LR() {
    AVLtree& q = *this;
    AVLtree* p = q.right;
    q.right = p->left;
    p->left = new AVLtree(q);
    q = *p;
}

void AVLtree::RR() {
    AVLtree& p = *this;
    AVLtree* q = p.left;
    p.left = q->right;
    q->right = new AVLtree(p);
    p = *q;
}

void AVLtree::balance() {
    AVLtree& p = *this;
    if (p.bf == 2)
    {
        if (p.right->b() < 0)
            p.right->RR();
        p.LR();
    }
    if (p.bf == -2)
    {
        if (p.left->b() > 0)
            p.left->LR();
        p.RR();
    }
}

int AVLtree::b() {
    this->bf = right->depth() - left->depth();
    return bf;
}

AVLtree::AVLtree(int KEY) {
    key = KEY;
    left = NULL;
    right = NULL;
    bf = NULL;
}

AVLtree::AVLtree(int KEY, AVLtree LEFT, AVLtree RIGHT) {
    key = KEY;
    left = new AVLtree(LEFT);
    right = new AVLtree(RIGHT);
    bf = this->b();
}

AVLtree*& AVLtree::iterative_search(int k) {
    AVLtree* tree = this;
    if ((!tree->left and !tree->right) or !tree) return tree;
    while (k != tree->key) {
        //ѕроверка €вл€етс€ ли провер€емое дерево родителем искомого
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

void AVLtree::add(int k) {
    AVLtree* tree = this->iterative_search(k);
    if (k < tree->key) {
        tree->left = new AVLtree(k);
    }
    else if (k > tree->key) {
        tree->right = new AVLtree(k);
    }
    else return;
}

void AVLtree::bindel(int k) {
    AVLtree*& tree = this->iterative_search(k);// »щем ссылку на указатель удал€емого узла

    if (tree->key != k) return; // ¬ыход если узла который нужно удалить нету в дереве 

    // ѕервый случай
    if (!tree->left and !tree->right) {
        tree = NULL;
        return;
    }

    //¬торой случай
    if (tree->left and !tree->right) {
        tree = tree->left;
        return;
    }
    if (tree->right and !tree->left) {
        tree = tree->right;
        return;
    }

    //“ретий случай
    if (tree->left and tree->right) {
        int delkey;
        AVLtree* newTree = tree->right;
        while (newTree->left) {
            newTree = newTree->left;
        }
        delkey = newTree->key;

        this->bindel(delkey);
        this->iterative_search(k)->key = delkey;
    }
}

void AVLtree::del(int k) {
    this->bindel(k); //вызов метода удаление узла из бинарного дерева поиска 
/* ѕоиск самого нижнего узла с нарушенным баланса и вызов дл€ него метода балансировки */
    AVLtree* bfsearch = this;
    AVLtree* broken = NULL;
    while (bfsearch) {
        if (bfsearch->b() == -2 or bfsearch->bf == 2) {
            broken = bfsearch;
        }
        if (bfsearch->key > k) {
            bfsearch = bfsearch->left;
        }
        else {
            bfsearch = bfsearch->right;
        }
        if (broken) {
            broken->balance();
            broken = NULL;
            bfsearch = this;
        }
    }
}
void AVLtree::insert(int k) {
    AVLtree* tree = this->iterative_search(k);
    if (k < tree->key) {
        tree->left = new AVLtree(k);
    }
    else if (k > tree->key) {
        tree->right = new AVLtree(k);
    }
    
    AVLtree* bfsearch = this;
    AVLtree* broken = this;
    while (bfsearch != tree){
        if (bfsearch->b() == -2 or bfsearch->bf == 2) {
            broken = bfsearch;
        }
        if (bfsearch->key > k) {
            bfsearch = bfsearch->left;
        } 
        else {
            bfsearch = bfsearch->right;
        }
    }
    broken->balance();
}

void AVLtree::print(int u) {
    if (this) {
        right->print(u + 1);

        for (int i = 0; i < u; i++) {
            cout << " ";
        }
        cout << key << "\n";
        left->print(u + 1);
    }
}