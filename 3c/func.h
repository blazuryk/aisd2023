#ifndef FOO_H_
#define FOO_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
typedef struct Item{
    char* key;
    int busy;
    char* info;
}Item;
typedef struct Table
{
    Item* data;
    int capacity;
    int step;
}Table;
int getInt(int* b);
int recsr(int a, int b);
int vzpr(int n);
int dialog(const char * msgs[], int N);
unsigned long long hash(unsigned char *str);
int D_Show(Table* table);
int insert(Table* table, char* key, char* info);
int impttb(Table* table, char* name);
int D_Import(Table* table);
Item finder(Table* table, char* key);
int D_Add(Table *ptab);
int D_Find(Table* table);
int deletekey(Table* table, char* key);
int D_Delete(Table* table);
int deleteTable(Table* table);
Table* init();
#endif
