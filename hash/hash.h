#ifndef _HASH_H_
#define _HASH_H_

typedef struct hash HASH;
typedef struct table TABLE;

TABLE* create_hash(int);

void add_hash(TABLE *, int);

void search_hash(TABLE *, int);

void destroy_hash(TABLE *);

#endif
