typedef struct nstring_st {
  int32_t    len;     // The length of the string, ignoring the trailing \0
  char       str[];   // This is a C-style string
} nstring_st;
