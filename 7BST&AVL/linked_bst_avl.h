#pragma once

#include<iostream>
#include<vector>

typedef struct node {
    int data;
    node* left;
    node* right;
    node* parent;
    int leftH, rightH;
};

class BST {
protected:
    void deleteTree(node* p);
    int getSL(node* p, int k = 1);
    void LNRdfs(node* p, std::vector<int>& result);
    node* addChild(int data, node* parent = nullptr, bool addleft = true);
    node* getNodeByData(node* root, int x);
    node* deleteNodeByPos(node* pos);
public:
    int refreshHeight(node* p);
    node* root;       // 根节点
    int nodeNums;   // 节点数目
    int MAX_NODES = 1e5;
    BST();
    node* insertNode(int data);            // 插入元素
    node* deleteNode(int data);            // 删除元素
    void generateBST(std::vector<int> list);  // 从数组生成树
    std::vector<int> LNRTree();   // 中序遍历
    void levelOrderTraversal(node* root, std::vector<int>& result);   // 层序遍历
    float getASL();                       // 获取平均查找长度
    ~BST();
};

class AVL : public BST {
private:
    int getBF(node* p);
public:
    node* findUnbalanceNode(node* p);
    AVL() : BST() {};
    node* insertNode(int data);
    void generateAVL(std::vector<int> list);
    node* leftRotate(node* x);
    node* rightRotate(node* x);
    node* balanceAndRotate(node *x);
    node* AVLdeleteNode(int data);
};