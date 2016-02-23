/* source: https://www.shiftedup.com/2015/05/07/five-programming-problems-every-software-engineer-should-be-able-to-solve-in-less-than-1-hour
** Write three functions that compute the 
** sum of the numbers in a given list using 
** a for-loop, a while-loop, and recursion.
**/


#include <stdio.h>

int recur_sum(int * a, size_t len) {
  return len > 1 ? a[0] + recur_sum(&a[1], len-1) : a[0];
}


int main(void) {
  
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  int sum = 0;
  for(int i = 0 ; i < sizeof(a)/sizeof(a[0]) ; i ++) {
    sum += a[i];
  }
  printf("sum = %d\n", sum);
  
  int sum2 = 0;
  int i = 0;
  while(i < sizeof(a)/sizeof(a[0])) {
    sum2 += a[i++];
  }
  printf("sum2 = %d\n", sum2);
  
  int sum3 = recur_sum(a, sizeof(a)/sizeof(a[0]));
  printf("sum3 = %d\n", sum3);
  
  return 0;
}