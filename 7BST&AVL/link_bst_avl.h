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


class BST
{
private:
  nodeArr *arr;
  void deleteTree(node *p);
  int getSL(node *p, int k = 1);
  void lnrdfs(node *p, nodeArr *arr);
public:
  node *root;
  int nodeNums = 0;
  BST(int data);
  node *addChild(int data, node *parent = NULL, bool addleft = true);
  node *generateBST(int list[], int n);
  int *LNRTree(int n);
  float getASL();
  node *getNodeByData(node *root, int x);
  bool deleteNodeByPos(node *pos);
  ~BST();
};

BST::BST(int data){
  root = new node;
  nodeNums++;
  root->data = data;
  root->left = NULL;
  root->right = NULL;
  root->parent = NULL;
}

void BST::deleteTree(node *p){
  if(p == NULL) return;
  deleteTree(p->left);
  deleteTree(p->right);
  delete p;
}

BST::~BST(){
  deleteTree(root);
}

node *BST::addChild(int data, node *parent, bool addleft){
  node *child = new node;
  child->data = data;
  child->left = NULL;
  child->right = NULL;
  child->parent = parent;
  if(addleft){
    parent->left = child;
  }else{
    parent->right = child;
  }
  nodeNums++;
  return child;
}

node *BST::generateBST(int list[], int n){
  node *p = root;
  for(int i = 1; i < n; i++){
    p = root;
    while (true){
      if(list[i] < p->data){
        if(p->left != NULL) p = p->left;
        else {
          p->left = addChild(list[i], p, true);
          break;
        }
      }else if(list[i] > p->data){
        if(p->right != NULL) p = p->right;
        else {
          p->right = addChild(list[i], p, false);
          break;
        }
      }
    }
  }
  return root;
}

void BST::lnrdfs(node *p, nodeArr *arr){
  if(p == NULL) return;
  lnrdfs(p->left, arr);
  arr->arr[arr->pos++] = p;
  lnrdfs(p->right, arr);
}

int *BST::LNRTree(int n){
  nodeArr *orderArr= new nodeArr;
  orderArr->maxsize = n;
  orderArr->arr = new node*[n];
  lnrdfs(root, orderArr);
  int *outarr = new int[n];
  for(int i = 0; i < n; i++){
    outarr[i] = orderArr->arr[i]->data;
  }
  return outarr;
}

int BST::getSL(node *p, int k){
  int d = k;  //记录当前查找长度
  if(p->left != NULL){
    d += getSL(p->left, k + 1);  //把所有左子树的查找长度加进d
  }
  if(p->right != NULL){
    d += getSL(p->right, k + 1);
  }
  return d;
}

float BST::getASL(){
  return getSL(root) * 1.0 / nodeNums;
}

node * BST::getNodeByData(node *p, int x){
  if(p == NULL) return 0;
  if(p->data > x) return getNodeByData(p->left, x);
  else{
    if(p->data == x) return p;
    else return getNodeByData(p->right, x);
  }
}

bool BST::deleteNodeByPos(node *pos){
  if(pos == NULL) return false;
  nodeNums--;
  node *p = pos->left;
  node *q = pos->right;
  if(p == NULL && q == NULL){
    delete pos;
    pos = NULL;
  }
  else if(p == NULL){
    pos->data = q->data;
    pos->right = q->right;
    pos->left = q->left;
    delete q;
    q = NULL;
  }
  else if(q == NULL){
    pos->data = p->data;
    pos->right = p->right;
    pos->left = p->left;
    delete p;
    p = NULL;
  }else{
    node *r = q;
    while(r->left != NULL){
      r = r->left;
    }
    pos->data = r->data;
    pos->right = r->right;
    pos->left = r->left;
    delete r;
    r = NULL;
  }
  return true;
}