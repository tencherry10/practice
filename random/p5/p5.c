/* source: https://www.shiftedup.com/2015/05/07/five-programming-problems-every-software-engineer-should-be-able-to-solve-in-less-than-1-hour
** Write a program that outputs all possibilities to put + or - or nothing between the numbers 1, 2, ..., 9 
** (in this order) such that the result is always 100. For example: 1 + 2 + 34 - 5 + 67 - 8 + 9 = 100.
*/

// Would like to use arbitrary precision library

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "deps/kvec/kvec.h"

typedef kvec_t(uint8_t *) vec_op_t;
typedef kvec_t(uint8_t)   vec_u8_t;
typedef kvec_t(uint32_t)  vec_u32_t;

uint32_t undigify(vec_u8_t v) {
  int ret = 0;
  int shift = 1;
  for(size_t i = 0 ; i < kv_size(v) ; i++) {
    ret += kv_A(v, kv_size(v)-1-i) * shift;
    shift *= 10;
  }
  return ret;
}

void enum_possibility(vec_op_t* acc, uint8_t* op, size_t op_idx, size_t num_ops, size_t num_op_type) {
  for(size_t i = 0 ; i < num_op_type ; i++) {
    op[op_idx] = i;
    if(op_idx == (num_ops - 1)) {
      //~ for(size_t j = 0 ; j < num_ops; j++) {
        //~ printf("%d", op[j]);
      //~ }
      //~ printf("\n");
      uint8_t * complete_op = malloc(num_ops*sizeof(uint8_t));
      memcpy(complete_op, op, num_ops);
      
      kv_push(uint8_t*, *acc, complete_op);
    } else {
      enum_possibility(acc, op, op_idx+1, num_ops, num_op_type);
    }
  }
}

int compute_possibility(int *a, uint8_t * op, size_t len) {
  vec_u8_t  digits;
  vec_u8_t  newops;
  vec_u32_t numbers;
  int sum = 0;
  kv_init(digits);
  kv_init(newops);  
  kv_init(numbers);  
  kv_push(uint8_t, digits, a[0]);
  //~ printf("digit push %d\n", a[0]);
  for(int i = 0 ; i < (len-1) ; i++) {
    if(op[i] == 0) {
      //~ printf("digit push %d\n", a[i]);
      kv_push(uint8_t, digits, a[i+1]);
    }
    if(op[i] != 0) {
      //~ printf("number push %d\n", undigify(digits));
      //~ printf("op push %d\n", op[i]);
      kv_push(uint32_t, numbers, undigify(digits));
      kv_push(uint8_t, newops, op[i]);
      digits.n = 0;
      //~ printf("digit push %d\n", a[i+1]);
      kv_push(uint8_t, digits, a[i+1]);
    }
  }
  //~ printf("number push %d\n", undigify(digits));
  kv_push(uint32_t, numbers, undigify(digits));
  
  sum = kv_A(numbers, 0);
  //~ printf("sum %d\n", sum);
  for(int i = 0 ; i < kv_size(newops) ; i++) {
    assert(kv_A(newops,i) != 0);
    if(kv_A(newops,i) == 1)
      sum += kv_A(numbers, i+1);
    if(kv_A(newops,i) == 2)
      sum -= kv_A(numbers, i+1);
    //~ printf("numbers[%d]=%d sum %d\n", i+1, kv_A(numbers, i+1), sum);
  }
  kv_destroy(digits);
  kv_destroy(newops);
  kv_destroy(numbers);
  return sum;
}

vec_op_t find_possibility(int *a, size_t len, vec_op_t all, int search) {
  vec_op_t ret;
  kv_init(ret);
  for(int i = 0 ; i < kv_size(all) ; i++) {
    if(search == compute_possibility(a, kv_A(all, i), len)) {
      kv_push(uint8_t*, ret, kv_A(all, i));
    }
  }
  return ret;
}

int main(void) {
  vec_op_t v;
  vec_op_t found;
  uint8_t op_data[8];
  int     numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  
  kv_init(v);  
  enum_possibility(&v, op_data, 0, 8, 3);
  found = find_possibility(numbers, 9, v, 100);
  

  for(int i = 0 ; i < kv_size(found) ; i++) {
    printf("%d", numbers[0]);
    for(size_t j = 1 ; j < 9; j++) {
      printf("%s", kv_A(found,i)[j-1] == 0 ? "" : kv_A(found,i)[j-1] == 1 ? " + " : " - ");
      printf("%d", numbers[j]);
    }
    printf("\n");
  }
  
  //~ uint8_t all_add [8] = {1, 1, 0, 2, 1, 0, 2, 1};
  
  
  
  for(int i = 0 ; i < kv_size(v) ; i ++) {
    free(kv_A(v,i));
  }
  kv_destroy(found);
  kv_destroy(v);
  return 0;
}

