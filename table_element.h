#ifndef __TABLE_ELEMENT_H__
#define __TABLE_ELEMENT_H__

#include <string>

class table_element {
 public:
  std::string type;
  bool is_defined;

  table_element(std::string& type, bool& is_defined);
};

#endif
