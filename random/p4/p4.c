/* source: https://www.shiftedup.com/2015/05/07/five-programming-problems-every-software-engineer-should-be-able-to-solve-in-less-than-1-hour
** Write a function that given a list of non negative integers, arranges them such that they form the largest possible number. 
** For example, given [50, 2, 1, 9], the largest formed number is 95021.
*/

// Would like to use arbitrary precision library

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "deps/kvec/kvec.h"

typedef kvec_t(uint8_t)   vec_u8_t;
typedef kvec_t(vec_u8_t)  vec_vec_u8_t;

vec_u8_t digify(int v) {
  vec_u8_t ret;
  kv_init(ret);
  int i = v;
  do {
    kv_push(uint8_t, ret, i % 10);
    i = i / 10;
  } while(i != 0);
  return ret;
}

int undigify(vec_u8_t v) {
  int ret = 0;
  int shift = 1;
  for(size_t i = 0 ; i < kv_size(v) ; i++) {
    ret += kv_A(v, i) * shift;
    shift *= 10;
  }
  return ret;
}

int undigify2(vec_u8_t v2, vec_u8_t v1) {
  int ret = 0;
  int shift = 1;
  for(size_t i = 0 ; i < kv_size(v1) ; i++) {
    ret += kv_A(v1, i) * shift;
    shift *= 10;
  }
  for(size_t i = 0 ; i < kv_size(v2) ; i++) {
    ret += kv_A(v2, i) * shift;
    shift *= 10;
  }  
  return ret;
}


vec_vec_u8_t digify_array(int *v, size_t n) {
  vec_vec_u8_t ret;
  kv_init(ret);
  kv_a(vec_u8_t, ret, n-1);
  for(size_t i = 0 ; i < n ; i ++) {
    kv_A(ret, i) = digify(v[i]);
  }
  return ret;
}

int compare_vec (const void *a, const void *b) {
  const vec_u8_t *da = (const vec_u8_t *) a;
  const vec_u8_t *db = (const vec_u8_t *) b;

  return undigify2(*db, *da) - undigify2(*da, *db);
}

int main(void) {
  int a[4] = {50, 2, 1, 9};
  int b[3] = {5, 50, 56};
  vec_vec_u8_t vv = digify_array(b, 3);
  
  qsort (vv.a, 3, sizeof(vec_u8_t), compare_vec);
  
  for(size_t i = 0 ; i < kv_size(vv) ; i++) {
    printf("%d", undigify(kv_A(vv,i)));
  }
  printf("\n");
  
  for(size_t i = 0 ; i < kv_size(vv) ; i++) {
    kv_destroy(kv_A(vv,i));
  }
  kv_destroy(vv);
  return 0;
}

