#include "jcircle.h"

int main(){
  int a[7] = {3,1,7,2,4,8,4};
  int *b = outOrder(7,20,a);
  for(int i=0;i<7;i++){
    cout<<b[i]<<" ";
  }
  delete b;  //用完就删，从我做起（
  return 0;
}