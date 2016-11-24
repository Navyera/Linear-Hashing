#include <stdio.h>
#include <stdlib.h>
#include "HashTableTypes.h"
#include "HashTableInterface.h"


int L=0;
int p=0;
double load=0.0;
int entries=0;
int buckets=INITIALSIZE;

/*Allocate memory for starting buckets and initialize them as empty*/

Table makeTable(Table T){
    int i;
    T=malloc(INITIALSIZE*sizeof(TableEntry));

    for(i=0;i<INITIALSIZE;i++){

        T[i].Key=EmptyKey;
        T[i].Info=EmptyInfo;
        T[i].next=NULL;
    }
    return T;
}

/* Our hash function */
int h(KeyType Key,int L) {
    int c = 3;
    int M = 1048583;
    int result = ((Key*c)%M)%(INITIALSIZE << L);
    return result;
}

/*Search function*/
int Search(Table T,KeyType Key){

        int addr;
        TableEntry* temp;


        addr=h(Key,L);    /*Compute address of round L*/
        if(addr<p)         /*If that bucket is already rehashed*/
            addr=h(Key,L+1);   /*Address should be the result for round L+1*/

        temp=&(T[addr]);    /*Pointer to the start of the bucket*/

        while(temp){        /*Traverse bucket*/
            if(temp->Key==Key) /*Did we find it?*/
                return 1;       /*Yes*/
            temp=temp->next;    /*No, next one then*/
        }

        return 0;   /*Failure*/

}

/*Insert function*/

Table Insert(Table T,KeyType Key,int mode){

    int hashresult;
    TableEntry* temp;
    TableEntry* newentry;

    if(mode==HASH){
        entries++;
        load=(double)entries/buckets;
        hashresult = h(Key,L);
       if(hashresult<p)
          hashresult = h(Key,L+1);
    }
    else{  /*mode==REHASH*/
        hashresult = h(Key,L+1);

    }

    if(T[hashresult].Key==EmptyKey)     /*If bucket is empty*/
       T[hashresult].Key = Key;         /*Just copy the key to it*/
    else{
        temp = &(T[hashresult]);        /*pointer to the start of the bucket*/
        while(temp->next){              /*traverse to the end of the bucket*/
            temp = temp->next;
        }

        newentry=malloc(sizeof(TableEntry));    /*allocate memory*/
        temp->next=newentry;                    /*make the last element point to the new one*/
        newentry->Key=Key;                      /*initialize new element*/
        newentry->Info=0;
        newentry->next=NULL;

    }
    if(mode==HASH){
        if(load>LOADLIMIT){                    /*Should we rehash?*/
            if(p==0)                           /*Do we need new memory for that?*/
               T=extendTable(T);

            buckets++;                         /*One new bucket*/
            Rehash(T);                         /*Rehash bucket p */
            p++;                               /*update p to the next bucket*/

            if(p%(INITIALSIZE<<L)==0){         /*Are we finished with this round?*/
                L++;                           /*Yes,update L and p*/
                p=0;
            }
        }
    }
    return T;
}


/*Printing function for the hash table*/
void printTable(Table T){
    TableEntry* temp;
    int i,count=0,empty=0;

    for(i=0;i<buckets;i++){
        printf("%d:",i);
        temp=&(T[i]);
        while(temp){
            printf("%d,",temp->Key);
            if(temp->Key==0)
                empty++;

            count++;
            temp=temp->next;
        }
        printf("\b \n");
    }
    printf("I printed %d items.\n",count);
    printf("Empty buckets are %d.\n",empty);
}

/*Function that doubles allocated memory when needed*/
Table extendTable(Table T){
    int i;
    T=realloc(T,(INITIALSIZE<<(L+1))*sizeof(TableEntry));

    for(i=(INITIALSIZE<<L);i<(INITIALSIZE<<(L+1));i++){
        T[i].Key=EmptyKey;
        T[i].Info=EmptyInfo;
        T[i].next=NULL;
    }

    return T;
}
/*Rehashing function*/
void Rehash(Table T){

    TableEntry* temp;
    TableEntry* temp2;


    temp=&(T[p]);                                       /*Pointer to the start of the bucket to be rehashed*/
    /*TREATMENT FOR THE FIRST ELEMENT*/

    while(h(temp->Key,L+1)>((INITIALSIZE<<L)-1)){       /*Is the current element hashed to the new bucket?*/
            Insert(T,temp->Key,REHASH);                 /*then insert it*/

            if(temp->next==NULL){                       /*If this was the first and only element of the bucket*/
                temp->Key=EmptyKey;                     /*Make the bucket empty again*/
            }
            else{
                temp->Key=temp->next->Key;              /*else update list and free the entry that was moved*/
                temp2=temp->next;
                temp->next=temp->next->next;
                free(temp2);
            }

    }

    /*TREATMENT FOR ALL OTHER ELEMENTS*/
    temp=temp->next;

    while(temp){
        temp2=temp->next;
        if(h(temp->Key,L+1)>((INITIALSIZE<<L)-1)){
            Insert(T,temp->Key,REHASH);
            Remove(&T[p],temp);
        }
        temp=temp2;
    }


}

/*List removal function for all elements of a bucket EXCEPT FOR the first one*/
void Remove(TableEntry* list,TableEntry* node){

    TableEntry* temp;
    temp = list;

    while(temp->next!=node)
        temp=temp->next;

    temp->next=temp->next->next;
    free(node);

}


