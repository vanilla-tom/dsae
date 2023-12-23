#include<iostream>
#include<string>
#include<cmath>

using namespace std;

typedef struct Item {
    int coeff;
    int degree;
    Item *next;
} Item;

typedef struct Polynomial {
    Item *first;
    int n;
} Polynomial;

Polynomial *init() {
    Polynomial *p = new Polynomial;
    p->first = nullptr;
    p->n = 0;
    return p;
}

Item *create(int coeff, int degree) {
    Item *p = new Item;
    p->coeff = coeff;
    p->degree = degree;
    p->next = nullptr;
    return p;
}

Item *findsamed(Polynomial *p, int aimd) {
    Item *now = p->first;
    while (now != nullptr) {
        if (now->degree == aimd) {
            return now;
        }
        now = now->next;
    }
    return nullptr;
}

bool input(Polynomial *p) {
  cout << "input numbers:\n";
  cin >> p->n;
  if(p->n < 0){
    return false;
  }
  cout << "input items:\n";
  Item *last = nullptr;
  for(int i = 0; i < p->n; i++){
    int c, d;
    cin >> c >> d;
    Item *n = create(c, d);
    if(i == 0){
      p->first = n;
      last = n;
    }else{
      last->next = n;
      last = n;
    }
  }
  return true;
}

void psort(Polynomial *p){
  //选择排序
  Item *pos = p->first;
  Item *n, *tmp;
  int tmpc, tmpd;
  while(pos != nullptr){
    n = pos;
    int maxc, maxd = -999;
    while(n != nullptr){
      if(n->degree > maxd){
        maxd = n->degree;
        maxc = n->coeff;
        tmp = n;
      }
      n = n->next;
    }
    tmpc = pos->coeff;
    tmpd = pos->degree;
    pos->coeff = maxc;
    pos->degree = maxd;
    tmp->coeff = tmpc;
    tmp->degree = tmpd;
    pos = pos->next;
  }
}

void output(Polynomial *p){
  cout << p->n;
  Item *t = p->first;
  while(t != nullptr){
    cout << " " << t->coeff << " " << t->degree;
    t = t->next;
  }
  cout << endl;
}

void copy(Polynomial *aim, Polynomial *src){
  aim->n = src->n;
  aim->first = nullptr;
  Item *t = src->first;
  Item *last = nullptr;
  while(t != nullptr){
    Item *tmp = create(t->coeff, t->degree);
    if(aim->first == nullptr){
      aim->first = tmp;
    }else{
      last->next = tmp;
    }
    last = tmp;
    t = t->next;
  }
}

Polynomial *operation(Polynomial *a, Polynomial *b, int op){
  Polynomial *p = new Polynomial;
  copy(p, a);
  Item *t = b->first;
  while(t != nullptr){
    Item *tmp = findsamed(p, t->degree);
    if(tmp == nullptr){
      tmp = create((t->coeff)*op, t->degree);
      tmp->next = p->first;
      p->first = tmp;
      p->n++;
    }else{
      tmp->coeff = tmp->coeff + (t->coeff) * op;
    }
    t = t->next;
  }
  return p;
}

double calc(Polynomial *p, double x){
  double ans = 0;
  Item *t = p->first;
  while(t != nullptr){
    ans += t->coeff * pow(x, t->degree);
    t = t->next;
  }
  return ans;
}

int main(){
  Polynomial *pna = init();
  Polynomial *pnb = init();
  A:
  if(input(pna)){
    psort(pna);
  }else{
    cout << "error input, please input again:" << endl;
    goto A;
  }
  B:
  if(input(pnb)){
    psort(pnb);
  }else{
    cout << "error input, please input again:" << endl;
    goto B;
  }
  cout << "a: ";
  output(pna);
  cout << "b: ";
  output(pnb);
  Polynomial *pnc = operation(pna, pnb, 1);
  Polynomial *pnd = operation(pna, pnb, -1);
  cout << "a+b: ";
  output(pnc);
  cout << "a-b: ";
  output(pnd);
  cout << "please input value of x:";
  double x = 0;
  cin >> x;
  cout << "a(" << x << "): " << calc(pna, x) << endl;
  cout << "b(" << x << "): " << calc(pnb, x) << endl;
  cout << "a+b(" << x << "): " << calc(pnc, x) << endl;
  cout << "a-b(" << x << "): " << calc(pnd, x) << endl;
  return 0;
}