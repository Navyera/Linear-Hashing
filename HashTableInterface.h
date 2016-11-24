#ifndef HASHTABLEINTERFACE
#define HASHTABLEINTERFACE

#include "HashTableTypes.h"

Table makeTable(Table T);
int h(KeyType Key,int L);
int Search(Table T,KeyType Key);
Table Insert(Table T,KeyType Key,int mode);
void printTable(Table T);
Table extendTable(Table T);
void Rehash(Table T);
void Remove(TableEntry* list,TableEntry* node);


#endif
