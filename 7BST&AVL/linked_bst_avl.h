#include<iostream>

using namespace std;

typedef struct node{
  int data;
  node *left;
  node *right;
  node *parent;
  int leftH, rightH;
}node;

typedef struct nodeArr{
  node **arr;
  int maxsize;
  int pos = 0;
}nodeArr;

class BST {
protected:
  nodeArr *arr;   // 用来记录节点的数组，好像没什么用（但好像又有点用
  void deleteTree(node *p);
  int getSL(node *p, int k = 1);
  void lnrdfs(node *p, nodeArr *arr);
  node *addChild(int data, node *parent = NULL, bool addleft = true);
  node *getNodeByData(node *root, int x);
  bool deleteNodeByPos(node *pos);
public:
  node *root;       // 根节点
  int nodeNums = 0; // 节点数目
  BST(int data);
  node *insertNode(int data);            // 插入元素
  bool deleteNode(int data);            // 删除元素
  void generateBST(int list[], int n);  // 从数组生成树
  int *LNRTree();                       // 中序遍历
  float getASL();                       // 获取平均查找长度
  ~BST();
};

class AVL : public BST {
private:
  int refreshHeight(node *p);
  int getBF(node *p);
  node *findUnbalanceNode(node *p);
public:
  AVL(int data) : BST(data) {};
  bool avlInsertNode(int data);
  void generateAVL(int list[], int n);
};

//解析析构
BST::BST(int data){
  root = new node; //初始化树一并初始化根节点
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

//插入、删除元素以及生成树相关
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

node *BST::insertNode(int data){
  node *p = root;
  while(true){
    if(data < p->data){
      if(p->left != NULL) p = p->left;
      else{
        p->left = addChild(data, p, true);
        return p->left;
      }
    }else if(data > p->data){
      if(p->right != NULL) p = p->right;
      else{
        p->right = addChild(data, p, false);
        return p->right;
      }
    }else{
      return NULL;
    }
  }
}

void BST::generateBST(int list[], int n){
  for(int i = 1; i < n; i++){
    insertNode(list[i]);
  }
}

node * BST::getNodeByData(node *p, int x){
  if(p == NULL) return 0;
  if(p->data > x) return getNodeByData(p->left, x);
  else if(p->data < x) return getNodeByData(p->right, x);
  else return p;
}

bool BST::deleteNodeByPos(node *pos){
  if(pos == NULL) return false;
  nodeNums--;
  node *p = pos->left;
  node *q = pos->right;
  node *r = q;
  if(p == NULL && q == NULL){
    //不做任何操作
  }else if(p == NULL){
    pos->data = q->data;
    pos->right = q->right;
    pos->left = q->left;
    pos = q;
  }else if(q == NULL){
    pos->data = p->data;
    pos->right = p->right;
    pos->left = p->left;
    pos = p;
  }else{
    while(r->left != NULL){
      r = r->left;
    }
    pos->data = r->data;
    pos->right = r->right;
    pos->left = r->left;
    pos = r;
  }
  //把双亲节点的指向设为NULL
  if(pos->parent->left == pos) pos->parent->left = NULL;
  else pos->parent->right = NULL;
  delete pos;
  pos = NULL;
  return true;
}

bool BST::deleteNode(int data){
  node *p = getNodeByData(root, data);
  return deleteNodeByPos(p);
}

//遍历以及ASL相关
void BST::lnrdfs(node *p, nodeArr *arr){
  if(p == NULL) return;
  lnrdfs(p->left, arr);
  arr->arr[arr->pos++] = p;
  lnrdfs(p->right, arr);
}

int *BST::LNRTree(){
  nodeArr *orderArr= new nodeArr;
  orderArr->maxsize = nodeNums;
  orderArr->arr = new node*[nodeNums];
  lnrdfs(root, orderArr);
  int *outarr = new int[nodeNums];
  for(int i = 0; i < nodeNums; i++){
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

/*
 * AVL相关函数
*/

int AVL::refreshHeight(node *p){
  if(p == NULL) return 0;
  if(p->left == NULL && p->right == NULL){
    p->leftH = p->rightH = 0;
    return 1;
  }else if(p->left == NULL){
    p->leftH = 0;
    p->rightH = refreshHeight(p->right);
    return p->rightH + 1;
  }else if(p->right == NULL){
    p->rightH = 0;
    p->leftH = refreshHeight(p->left);
    return p->leftH + 1;
  }else{
    p->leftH = refreshHeight(p->left);
    p->rightH = refreshHeight(p->right);
    return p->leftH > p->rightH ? p->leftH + 1 : p->rightH + 1;
  }
}

int AVL::getBF(node *p){
  return p->leftH - p->rightH;
}

node *AVL::findUnbalanceNode(node *p){
  int bf = getBF(p);
  node *t = p;
  while(bf >= -1 && bf <= 1){
    t = t->parent;
  }
  return t;
}

bool AVL::avlInsertNode(int data){
  node *p = insertNode(data);
  if(p == NULL) return false;
  refreshHeight(root);
  p = findUnbalanceNode(p);
  //todo
}

void AVL::generateAVL(int list[], int n){
  for(int i = 1; i < n; i++){
    insertNode(list[i]);
  } 
}