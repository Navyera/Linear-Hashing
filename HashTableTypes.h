#ifndef __HASHTABLETYPES__
#define __HASHTABLETYPES__
/* This is the file HashTableTypes.h */


#define INITIALSIZE 8
#define EmptyKey 0
#define EmptyInfo 0
#define LOADLIMIT 2.4
#define HASH 1
#define REHASH 0

typedef int KeyType;
typedef int InfoType;
typedef struct TableEntry{
           KeyType Key;
           InfoType Info;
           struct TableEntry* next;
        } TableEntry;
typedef TableEntry* Table;

#endif
