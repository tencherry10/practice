/* source: https://www.shiftedup.com/2015/05/07/five-programming-problems-every-software-engineer-should-be-able-to-solve-in-less-than-1-hour
** Write a function that combines two lists by alternatingly taking elements. 
** For example: given the two lists [a, b, c] and [1, 2, 3], 
** the function should return [a, 1, b, 2, c, 3].
**/


#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "deps/strdup/strdup.h"
#include "deps/kvec/kvec.h"

typedef enum {
  TYPENAME_U8,  TYPENAME_I8, 
  TYPENAME_U16, TYPENAME_I16,
  TYPENAME_U32, TYPENAME_I32,
  TYPENAME_CSTR,
} typename_t;

typedef struct {
  void *  obj;
  int     type;
} dyn_obj_t;

typedef kvec_t(dyn_obj_t) dyn_vec_t;

dyn_obj_t clone_obj(void * v, size_t idx, typename_t type) {
  dyn_obj_t ret;
  switch(type) {
  case TYPENAME_U8    : ret.obj = malloc(sizeof(uint8_t));  *((uint8_t*)  ret.obj) = *(((uint8_t*)  v) + idx); break;
  case TYPENAME_I8    : ret.obj = malloc(sizeof(int8_t));   *((int8_t*)   ret.obj) = *(((int8_t*)   v) + idx); break;
  case TYPENAME_U16   : ret.obj = malloc(sizeof(uint16_t)); *((uint16_t*) ret.obj) = *(((uint16_t*) v) + idx); break;
  case TYPENAME_I16   : ret.obj = malloc(sizeof(int16_t));  *((int16_t*)  ret.obj) = *(((int16_t*)  v) + idx); break;
  case TYPENAME_U32   : ret.obj = malloc(sizeof(uint32_t)); *((uint32_t*) ret.obj) = *(((uint32_t*) v) + idx); break;
  case TYPENAME_I32   : ret.obj = malloc(sizeof(int32_t));  *((int32_t*)  ret.obj) = *(((int32_t*)  v) + idx); break;
  case TYPENAME_CSTR  : ret.obj = strdup(*(((char**) v) + idx)); break;
  default             : assert(0);
  }
  ret.type = type;
  return ret;
}

void disp_obj(dyn_obj_t d) {
  switch(d.type) {
  case TYPENAME_U8    : printf("%u", *((uint8_t*)  d.obj)); break;
  case TYPENAME_I8    : printf("%d", *((int8_t*)   d.obj)); break;
  case TYPENAME_U16   : printf("%u", *((uint16_t*) d.obj)); break;
  case TYPENAME_I16   : printf("%d", *((int16_t*)  d.obj)); break;
  case TYPENAME_U32   : printf("%u", *((uint32_t*) d.obj)); break;
  case TYPENAME_I32   : printf("%d", *((int32_t*)  d.obj)); break;
  case TYPENAME_CSTR  : printf("%s", (char *) d.obj); break;
  default             : assert(0);
  }
}

void free_obj(dyn_obj_t d) {
  free(d.obj);
}

void free_dyn_vec(dyn_vec_t v) {
  for(int i = 0 ; i < kv_size(v) ; i++) {
    free_obj(kv_A(v, i));
  }
  kv_destroy(v);
}


dyn_vec_t interleave(
  void * a, size_t len_a, typename_t type_a,
  void * b, size_t len_b, typename_t type_b) 
{
  dyn_vec_t ret;
  kv_init(ret);
  for(int i = 0 ; i < len_a ; i++) {
    if(i >= len_b) break;
    kv_push(dyn_obj_t, ret, clone_obj(a, i, type_a));
    kv_push(dyn_obj_t, ret, clone_obj(b, i, type_b));
  }
  return ret;
}

int main(void) {
  dyn_vec_t v;
  char *  a[] = {"ab", "bc", "cd", "ZZ"};
  int     b[] = {1, 2, 3, -1};
  
  v = interleave(a, 4, TYPENAME_CSTR, b, 4, TYPENAME_I32);
  for(int i = 0 ; i < kv_size(v) ; i++) {
    disp_obj(kv_A(v, i));
    printf(" ");
  }
  printf("\n");
  
  free_dyn_vec(v);
  return 0;
}

