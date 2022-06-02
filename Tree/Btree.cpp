#include "Btree.h"
#include <iostream>

using namespace std;

Btree*& Btree::iterative_search(int k) {
    Btree* tree = this;
    if (!tree->left or !tree->right or !tree) return tree;
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

void Btree::del(int k) {
    Btree*& tree = this->iterative_search(k);// Ищем ссылку на указатель удаляемого узла

    if (tree->key != k) return; // Выход если узла который нужно удалить нету в дереве 

    // Первый случай
    if (!tree->left and !tree->right) {
        tree = NULL;
        return;
    }

    //Второй случай
    if (tree->left and !tree->right) {
        tree = tree->left;
        return;
    }
    if (tree->right and !tree->left) {
        tree = tree->right;
        return;
    }

    //Третий случай
    if (tree->left and tree->right) {
        int delkey;
        Btree* newTree = tree->right;
        while (newTree->left) {
            newTree = newTree->left;
        }
        delkey = newTree->key;

        this->del(delkey);
        this->iterative_search(k)->key = delkey;
    }
}

int Btree::depth() {
    int ret = 0;
    if (this)
    {
        int lDepth = left->depth();
        int rDepth = right->depth();
        ret = std::max(lDepth + 1, rDepth + 1);
    }
    return ret;
}

void Btree::print(int u) {
    if (this) {
        right->print(u + 1);

        for (int i = 0; i < u; i++) {
            cout << " ";
        }
        cout << key << "\n";
        left->print(u + 1);
    }
}

Btree Btree::search(int k) {
    if (this == NULL) {
        return NULL;
    }
    if (k == key) {
        return *this;
    }
    if (k < key) {
        return this->left->search(k);
    }
    else {
        return this->right->search(k);
    }
}

Btree::Btree(int KEY, Btree LEFT, Btree RIGHT) {
    key = KEY;
    left = new Btree(LEFT);
    right = new Btree(RIGHT);
}
Btree::Btree(int KEY) {
    key = KEY;
    left = NULL;
    right = NULL;
}

void Btree::insert(int k) {
    Btree* tree = this->iterative_search(k);
    if (k < tree->key) {
        tree->left = new Btree(k);
    }
    else if (k > tree->key) {
        tree->right = new Btree(k);
    }
    else return;
}