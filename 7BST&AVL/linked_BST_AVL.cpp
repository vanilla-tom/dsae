#pragma once

#include<iostream>
#include"linked_BST_AVL.h"
#include <vector>
#include<queue>

//构造函数
BST::BST() {
    root = new node; //初始化树一并初始化根节点
    nodeNums = 0;
    root = nullptr;
}

void BST::deleteTree(node* p) {
    if (p == nullptr) return;
    deleteTree(p->left);
    deleteTree(p->right);
    delete p;
}

BST::~BST() {
    deleteTree(root);
}

//插入、删除元素以及生成树相关
node* BST::addChild(int data, node* parent, bool addleft) {
    node* child = new node;
    child->data = data;
    child->left = nullptr;
    child->right = nullptr;
    child->parent = parent;
    if (addleft) {
        parent->left = child;
    }
    else {
        parent->right = child;
    }
    nodeNums++;
    return child;
}

node* BST::insertNode(int data) {
    node* p = root;
    if (nodeNums >= MAX_NODES) {
        return nullptr;
    }
    if (p == nullptr) {
        root = new node;
        root->data = data;
        root->parent = nullptr;
        root ->left = nullptr;
        root->right = nullptr;
        return root;
    }
    while (true) {
        if (data < p->data) {
            if (p->left != nullptr) p = p->left;
            else {
                p->left = addChild(data, p, true);
                return p->left;
            }
        }
        else if (data > p->data) {
            if (p->right != nullptr) p = p->right;
            else {
                p->right = addChild(data, p, false);
                return p->right;
            }
        }
        else {
            return nullptr;
        }
    }
}

node* findMax(node* p) {
    while (p->right != nullptr) {
        p = p->right;
    }
    return p;
}

void BST::generateBST(std::vector<int> list) {
    for (int i = 0; i < list.size(); i++) {
        insertNode(list[i]);
    }
}

node* BST::getNodeByData(node* p, int x) {
    if (p == nullptr) return nullptr;
    if (p->data > x) return getNodeByData(p->left, x);
    else if (p->data < x) return getNodeByData(p->right, x);
    else return p;
}

node* BST::deleteNodeByPos(node* pos) {
    if (pos == nullptr) return nullptr;
    nodeNums--;
    if (pos->left == nullptr) {
        if (pos == root) {
            root = pos->right;
            delete pos;
            return root;
        }
        else {
            auto tmp = pos->parent;
            tmp->data > pos->data ? tmp->left = pos->right : tmp->right = pos->right;
            delete pos;
            return tmp;
        }
    }
    else if (pos->right == nullptr) {
        if (pos == root) {
            root = pos->left;
            delete pos;
            return root;
        }
        else {
            auto tmp = pos->parent;
            tmp->data > pos->data ? tmp->left = pos->left : tmp->right = pos ->left;
            delete pos;
            return tmp;
        } 
    } else {
    auto successor = findMax(pos->left);
    auto v = successor->data;
    nodeNums++;
    auto res = deleteNodeByPos(successor);
    pos->data = v;
    return res;
    }
}

node* BST::deleteNode(int data) {
    node* p = getNodeByData(root, data);
    return deleteNodeByPos(p);
}

//遍历以及ASL相关

void BST::levelOrderTraversal(node* root, std::vector<int>& result) {
    if (!root) return;
    auto h = refreshHeight(root);
    std::queue<node*> q;
    q.push(root);
    for (int i = 0; i < ((1 << h) - 1);i++ ) {
        node* current = q.front();
        q.pop();
        if (current) {
            result.push_back(current->data);
            q.push(current->left);
            q.push(current->right);
        }
        else {
            result.push_back(-1); 
            q.push(nullptr);
            q.push(nullptr);
        }
    }
}

void BST::LNRdfs(node* p, std::vector<int>& result) {
    if (p == nullptr) return;
    LNRdfs(p->left, result);
    result.push_back(p->data);
    LNRdfs(p->right, result);
}

std::vector<int> BST::LNRTree() {
    std::vector<int> result;
    LNRdfs(root, result);
    return result;
}

int BST::getSL(node* p, int k) {
    int d = k;  //记录当前查找长度
    if (p->left != nullptr) {
        d += getSL(p->left, k + 1);  //把所有左子树的查找长度加进d
    }
    if (p->right != nullptr) {
        d += getSL(p->right, k + 1);
    }
    return d;
}

float BST::getASL() {
    return getSL(root) * 1.0 / nodeNums;
}

int BST::refreshHeight(node* p) {
    if (p == nullptr) return 0;
    if (p->left == nullptr && p->right == nullptr) {
        p->leftH = p->rightH = 0;
        return 1;
    }
    else if (p->left == nullptr) {
        p->leftH = 0;
        p->rightH = refreshHeight(p->right);
        return p->rightH + 1;
    }
    else if (p->right == nullptr) {
        p->rightH = 0;
        p->leftH = refreshHeight(p->left);
        return p->leftH + 1;
    }
    else {
        p->leftH = refreshHeight(p->left);
        p->rightH = refreshHeight(p->right);
        return p->leftH > p->rightH ? p->leftH + 1 : p->rightH + 1;
    }
}

int AVL::getBF(node* p) {
    return p->leftH - p->rightH;
}

node* AVL::insertNode(int data) {
    node* p = root;
    if (nodeNums >= MAX_NODES) {
        return nullptr;
    }
    if (p == nullptr) {
        root = new node;
        root->data = data;
        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    while (true) {
        if (data < p->data) {
            if (p->left != nullptr) p = p->left;
            else {
                p->left = addChild(data, p, true);
                return p->left;
            }
        }
        else if (data > p->data) {
            if (p->right != nullptr) p = p->right;
            else {
                p->right = addChild(data, p, false);
                return p->right;
            }
        }
        else {
            return nullptr;
        }
    }
}

node* AVL::findUnbalanceNode(node* p) {
    int balance;
    while (p != nullptr) {
        balance = getBF(p);
        if (balance > 1 || balance < -1) {
            return p;
        }
        p = p->parent;
    }
    return nullptr;
}

node* AVL::leftRotate(node* x) {
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;
    y->parent = x->parent;
    x->parent = y;
    if (T2 != nullptr) {
        T2->parent = x;
    }
    refreshHeight(y);
    return y;
}

node* AVL::rightRotate(node* y) {
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;
    x->parent = y->parent;
    y->parent = x;
    if (T2 != nullptr) {
        T2->parent = y;
    }

    refreshHeight(x);
    return x;
}

node* AVL::balanceAndRotate(node* p) {
    int balance = getBF(p);

    if (balance > 1) {
        if (getBF(p->left) >= 0) {
            return rightRotate(p);
        }
        else {
            p->left = leftRotate(p->left);
            return rightRotate(p);
        }
    }

    else if (balance < -1) {
        if (getBF(p->right) <= 0) {
            return leftRotate(p);
        }
        else {
            p->right = rightRotate(p->right);
            return leftRotate(p);
        }
    }
}

void AVL::generateAVL(std::vector<int> list) {
    for (auto i = list.begin();i != list.end();i++) {
        auto p = insertNode(*i);
        if (p == nullptr) {
            continue;
        }
        refreshHeight(root);
        auto unBalance = findUnbalanceNode(p);
        if (unBalance == nullptr) {
            continue;
        }
        if (unBalance == root) {
            root = balanceAndRotate(unBalance);
        }
        else {
            auto  tmp = unBalance->parent;
            unBalance = balanceAndRotate(unBalance);
            unBalance ->data > tmp ->data ? tmp ->right = unBalance : tmp->left =unBalance;
        }
    }
}
