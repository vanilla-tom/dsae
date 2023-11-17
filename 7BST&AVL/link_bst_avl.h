#include<iostream>

using namespace std;

typedef struct node{
  int data;
  node *left;
  node *right;
  node *parent;
}node;

typedef struct nodeArr{
  node **arr;
  int maxsize;
  int pos = 0;
}nodeArr;

node *addChild(int data, node *parent = NULL, bool addleft = true);
node *generateBST(int list[], int n);
void lnrdfs(node *p, nodeArr *arr);
int *LNRTree(node *root, int n);
int getNodeNums(node *root);
int getSL(node *root, int k = 1);
float getASL(node *root);
node *getNodeByData(node *root, int x);
bool deleteNodeByPos(node *pos);