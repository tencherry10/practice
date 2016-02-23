/* source: https://www.shiftedup.com/2015/05/07/five-programming-problems-every-software-engineer-should-be-able-to-solve-in-less-than-1-hour
** Write a function that computes the list of the first 100 Fibonacci numbers. 
** By definition, the first two numbers in the Fibonacci sequence are 0 and 1, 
** and each subsequent number is the sum of the previous two. 
** As an example, here are the first 10 Fibonnaci numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, and 34.
**/

// Would like to use arbitrary precision library

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "deps/kvec/kvec.h"

typedef kvec_t(__uint128_t) int_vec_t;

static char * qtoa(__uint128_t n) {
  static char buf[40];
  unsigned int i, j, m = 39;
  memset(buf, 0, 40);
  for (i = 128; i-- > 0;) {
    int carry = !!(n & ((__uint128_t)1 << i));
    for (j = 39; j-- > m + 1 || carry;) {
      int d = 2 * buf[j] + carry;
      carry = d > 9;
      buf[j] = carry ? d - 10 : d;
    }
    m = j;
  }
  for (i = 0; i < 38; i++) {
    if (buf[i]) {
      break;
    }
  }
  for (j = i; j < 39; j++) {
    buf[j] += '0';
  }
  return buf + i;
}

int_vec_t fibo_n(int n) {
  int_vec_t ret;
  kv_init(ret);
  kv_a(__uint128_t, ret, n-1);
  kv_A(ret, 0) = 0;
  kv_A(ret, 1) = 1;
  for(int i = 2 ; i < n; i++) {
    kv_A(ret, i) = kv_A(ret, i - 1) + kv_A(ret, i - 2);
  }
  return ret;
}

int main(void) {
  int_vec_t v = fibo_n(175);
  for(int i = 0 ; i < kv_size(v) ; i++) {
    printf("%d: %s\n", i, qtoa(kv_A(v,i)));
  }
  
  kv_destroy(v);
  return 0;
}

