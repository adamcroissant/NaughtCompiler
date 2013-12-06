#ifndef __TABLE_ELEMENT_CC__
#define __TABLE_ELEMENT_CC__

#include "table_element.h"

table_element::table_element(string &type, bool is_defined){
  this->type = type;
  this->is_defined = is_defined;
}

#endif
