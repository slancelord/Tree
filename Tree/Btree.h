#pragma once
class Btree {
public:
    int key;
    Btree* left;
    Btree* right;
    Btree(int KEY);
    Btree(int KEY, Btree LEFT, Btree RIGHT);
    Btree search(int searchKey);
    Btree*& iterative_search(int searchKey);
    int depth();
    void print(int u = 0);
    void insert(int k);
    void del(int k);
};

