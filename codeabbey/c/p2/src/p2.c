
#include <stdio.h>
#include <stdlib.h>
#include "sds/sds.h"

sds safe_gets(sds s) {
  sdsclear(s);
  
  if(sdsavail(s)==0) {
    s = sdsMakeRoomFor(s, 32);
    if(s == NULL) {
      return s;
    }
  }
      
  while(1) {
    size_t oldlen = sdslen(s);
    fgets(s + oldlen, sdsavail(s), stdin);
    sdsupdatelen(s);
    
    if( (s[sdslen(s)-1] == '\n') || (sdslen(s) == sdsavail(s)) )
      break;
    
    s = sdsMakeRoomFor(s, sdsavail(s) * 2);
  }
  
  return s;
}

int main(int argc, char ** argv) {
  int tokcnt;
  int sum = 0;
  sds s = sdsempty();
  s = safe_gets(s);     // don't use sscanf here b/c we want to support arbitrary number of tokens
  sds *toks = sdssplitlen(s, sdslen(s), " ", 1, &tokcnt);
  
  for(int i = 0 ; i < tokcnt ; i++) {
    if(i >= 2) break;                   // comment this out if you want to sum more than 2
    sum += strtol(toks[i], NULL, 10);
  }
  
  printf("%d\n", sum);
  
  sdsfreesplitres(toks, tokcnt);
  sdsfree(s);
  return 0;
}

