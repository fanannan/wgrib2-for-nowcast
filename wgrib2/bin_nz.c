// http://troydhanson.github.io/uthash/userguide.html#_hooks
#include <stdio.h>
#include "uthash.h"　
#include "bin_nz.h"


struct hash *table= NULL;    /* important! initialize to NULL */
     
void regist_data(struct pair *id, float value) {
    struct hash *s;
    s = malloc(sizeof(struct hash));
    s->id = id;
    s->value = value;
    HASH_ADD_INT(table, id, s); 
}
            
struct hash *find_data(struct pair *id) {
    struct hash *s;
    HASH_FIND_INT(table, &id, s);  
    return s;
}

void delete_data(struct hash *data) {
    HASH_DEL(table, data);  
}

void add_data(struct pair *id, float value) {
    struct hash *s = find_data(id);
    if(s == NULL){
        regist_data(id, value);
    } else {
        s->value += value;
        /*
        //printf("HIT!\n");
        float v2 = s->value + value;
        //delete_data(s);
        HASH_DEL(table, s);  // delete it (advances to next) 
        free(s);            // free it 
        regist_data(id, v2);
        */
    }        
}
            
void delete_all() {
  struct hash *current, *tmp;
  HASH_ITER(hh, table, current, tmp) {
    HASH_DEL(table, current);  /* delete it (advances to next) */
    free(current);            /* free it */
  }
}
