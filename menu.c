#include <stdio.h>
#include "HashTableInterface.h"

void menuInterface(void){

    printf("1.Insert integers manually to be hashed\n");
    printf("2.Insert integers from file\n");
    printf("3.Custom search\n");
    printf("4.Search for everything(from file)\n");
    printf("5.Print hash table\n");
    printf("6.Exit\n");


}



void menuManualInsert(Table* T){

    int num=-2;

    printf("You can now input integers greater than zero to be hashed.\n");
    printf("To terminate input type -1 and press enter.\n");

    while(num!=-1){

        scanf("%d",&num);
        if(num==-1){
            continue;
        }

        *T=Insert(*T,num,HASH);
    }
}

void menuFileInsert(Table* T){

    char a[150];
    int number;
    printf("Input filename:");
    scanf("%s",a);

    FILE* file=fopen(a,"r");

    if(!file){
        printf("Couldn't open file.\n");
        return;
    }

    while(fscanf(file,"%d",&number)==1){
        *T=Insert(*T,number,HASH);
    }

    printf("Read file successfully.\n");

}





void menuCustomSearch(Table T){

    int target,flag;
    printf("Which key should we search for? :");
    scanf("%d",&target);

    flag=Search(T,target);

    if(flag)
        printf("Found it!\n");
    else
        printf("Unsuccessful search.\n");



}

void menuSearchAll(Table T){

    char a[150];
    int number,count=0,flag=0,errors=0;
    printf("Input filename:");
    scanf("%s",a);

    FILE* file=fopen(a,"r");

    if(!file){
        printf("Couldn't open file.\n");
        return;
    }

    while(fscanf(file,"%d",&number)==1){
        flag=Search(T,number);
        if(flag==0)
            errors++;
        count++;
    }

    printf("Read file successfully.\n");
    printf("I searched for %d items.\n",count);
    printf("Errors were %d.\n",errors);


}

void menuPrint(Table T){

    printTable(T);

}
