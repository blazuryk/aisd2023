#ifndef FOO_H_
#define FOO_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
typedef struct Item{
        char* key;
        int offsetkey;
        int offsetinfo;
        int lenkey;
        int leninfo;
        int busy;
}Item;
typedef struct Table{
        int capacity;
        int csize;
        int step;
//        int csize;
        Item* data;
        FILE* fd;
}Table;
int insert(Table* table, char* key, char* info);
int getInt(int* b);
int recsr(int a, int b) ;
int vzpr(int n) ;
unsigned long long hash(unsigned char *str);
int dialog(const char * msgs[], int N);
int deleteTable(Table* table);
int D_Show(Table* table);
int create(Table* table, char* fname, int maxsize);
int save(Table *table);
int impttb(Table* table, char* name);
int D_Import(Table* table);
Table* init();
int load(Table* table, char* fname);
int D_Load(Table* table);
int deletekey(Table* table, char* key);
int D_Delete(Table* table);
char* findInfo(Table*table, char* k);
int D_Find(Table* table);
int D_Add(Table* table);
#endif
