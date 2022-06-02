#include <iostream>
#include <math.h>
#include "Btree.h"
#include "AVLtree.h"
#include "RBtree.h"

int* sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return arr;
}

// массив передается заранее отсортированный
Btree balancing(int* arr, int end, int start = 0) { 
    int mid = floor((start + end) / 2);
    Btree tree = Btree(arr[mid]);
    // с помощью start и end массив передается с значениями зарание меньше значения родителя
    if (!(mid - 1 < start)) {
        // создание левого поддерева,
        tree.left = new Btree(balancing(arr, mid - 1, start));
    }
    if (!(end < mid + 1)) {
        // создание правого поддерева,
        tree.right = new Btree(balancing(arr, end, mid + 1));
    }
    return tree;
}


int main() {
    RBtree p(10, false);
    for (int i = 1; i < 1000; i++) {
        p.insert(i);
    }
    for (int i = 1; i > -1000; i--) {
        p.insert(i);
    }
    p.print();
    std::cout << "\n\n\n\n";
    for (int i = -1000; i < 1000; i += 3) {
        p.del(i);
    }
    p.del(4);
    p.print();
    //AVLtree k(10);
    //k.add(6);
    //k.add(7);
    ////k.add(5);
    //k.add(11);
    //k.print();
    
    //k.left->LR();
    //k.RR();
    //k.print();
    /*AVLtree ll(4);
    AVLtree ff(8);
    AVLtree l(6, ll, ff);
    AVLtree kk(12, { 11 }, {13});
    AVLtree zz(18, {16, {17}, {15}}, {19});
    AVLtree r(14, kk, zz);
    AVLtree* p = new AVLtree(10, l, r);*/
    //p.insert(13);
    //p.insert(14);
    //p.insert(15);
    //std::cout << p.search(3).key;
    //p.print();
    

    //AVLtree* p = new AVLtree(1);
    //for (int i = 0; i < 100; i++) {
    //    p->insert(i);
    //}
    //p->print();
    //std::cout << "\n\n\n\n";
    //for (int i = 0; i < 100; i+= 7) {
    //    p->del(i);
    //}
    //
    //p->print();
    

    /*p.insert(15);
    p.insert(12);
    p.insert(19);*/

    //p.print();
   /* cout << p.left->depth() - p.right->depth();
    cout << *p.balance;*/
    //int node[] = { 7,6,3,4,5,1,2 };
    //balancing(sort(node, 7), 6).print();
    /*p.del(14);
    p.del(10);
    p.del(4);
    p.del(6);*/
    //p.print();
}