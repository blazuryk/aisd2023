#ifndef FOO_H_
#define FOO_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>
#include <sys/types.h>
//static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import","6.Indtask", "7. Traversal", "8.TiIns", "9.Tidel", "10.Tisc"};
//static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
//static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file", "Not found"};
typedef struct Node{
    char* key;
    char** data;
    int size;
    int h;
    struct Node* left;
    struct Node* right;
}Node;
int getInt(int* b);
int dialog(const char * msgs[], int N);
void uphe(Node* node);
int bf(Node* node);
Node* turnr(Node* node);
Node* turnl(Node* node);
Node* balance(Node* node);
Node* find(Node* root, char* key);
Node *createNode(char *key, char *info);
Node* minimum(Node* temp);
Node* delmin(Node* temp);
Node* deleteel(Node* root, char* key, int ver);
void deleteTree(Node *node);
Node* insert(Node* root, char* key, char* info);
void printTree(Node* root, int level);
void print_reversed(Node* node, char* max_key);
int D_Show(Node** root);
int D_Traversal(Node** root);
Node* findClosest(Node* root, char* val);
int D_Indtask(Node** root);
int D_Add(Node** root);
int D_Find(Node** root);
int D_Delete(Node** root);
int impttb(Node** table, char* name);
char *rd(int len);
int D_Timing(Node**);
int D_Tidelete(Node**);
int D_TInsrt(Node**);
int D_Import(Node** root);
//static int (*fptr[])(Node**)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Indtask, D_Traversal, D_TInsrt, D_Tidelete,D_Timing};
#endif
