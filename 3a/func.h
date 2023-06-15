#ifndef FOO_H_ 
#define FOO_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
typedef struct Keyspace{
    unsigned int key;
    unsigned int par;
    unsigned int info;
}KeySpace;
typedef struct Table
{
    KeySpace* ks;
    int csize;
    int maxsize;
}Table;
int getInt(int* b);
int D_Findmi(Table* table, unsigned int key);
int D_Show(Table* table);
int impttb(Table* table, char* name);
int D_Import(Table* table);
int D_Delete(Table* table);
int D_Find(Table* table);
int D_Indtask(Table* table);
int D_Findpar(Table* table, int par);
int insert(Table* table, unsigned int k, unsigned int par, unsigned int info);
int D_Add(Table *ptab);
int deleteTable(Table* table);
int dialog(const char * msgs[], int N);
/*const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import", "6.Indtask"};
const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file"};
int (*fptr[])(Table*)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Indtask};
*/
Table* init();
#endif
