#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>
#include <sys/types.h>
typedef struct Item{
        unsigned int key;
        unsigned int par;
        unsigned int offset;
}Item;
typedef struct Table{
        int maxsize;
        int csize;
        Item* ks;
        FILE* fd;
}Table;
int getInt(int *b);
int dialog(const char * msgs[], int N);
Table* init();
int create(Table* table, char* fname, int maxsize);
int save(Table *table);
int D_Show(Table* table);
int load(Table* table, char* fname);
int D_Load(Table* table);
int find(Table* table, int k);
int findInfo(Table*table, int k);
int D_Find(Table* table);
int findpar(Table* table, int par);
int findpar1(Table* table, int k);
int insert(Table* table, int k, int par, int info);
int D_Add(Table* table);
int deleteTable(Table* table);
int impttb(Table* table, char* name);
int D_Import(Table* table);
int D_Indtask(Table* table);
int D_Delete(Table* table);
