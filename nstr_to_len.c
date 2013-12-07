#ifndef __NSTR_TO_LEN_C__
#define __NSTR_TO_LEN_C__

#include "nstr_to_len.h"

int32_t nstr_to_len(char * s){
  s -= 4;
  return *((int32_t *) s);

}

#endif
