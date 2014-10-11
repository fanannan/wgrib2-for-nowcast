// http://troydhanson.github.io/uthash/userguide.html#_hooks
#include "uthash.h"　

struct pair {
    float latitude;
    float longtitude;
};
  
struct hash {
    struct pair *id;                    /* key */
    float value;
    UT_hash_handle hh;         /* makes this structure hashable */
};

