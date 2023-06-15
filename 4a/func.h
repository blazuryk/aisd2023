#ifndef FOO_H_ 
#define FOO_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include<time.h>
typedef struct Node{
    unsigned int key;
    unsigned int* data;
    struct Node *right; 
    struct Node *left;
    struct Node *par;
    int size;
}Node;
int getInt(int* b);
Node* insert(Node* root, int key, int info);
int impttb(Node** table, char* name);
int D_Import(Node** root);
int dialog(const char * msgs[], int N);
Node* createNode(int key, int info);
Node* find(Node* root, int key);
Node* minimum(Node* temp);
void trans(struct Node* h, struct Node* g);
Node* findClosest(Node* root, unsigned int val);
void print_reversed(Node* node, unsigned int max_key);
int deleteel(Node** root, int key, int value);
void deleteTree(Node *node);
void printTree(Node* root, int level);
int D_Show(Node** root);
int D_Traversal(Node** root);
int D_Indtask(Node** root);
int D_Add(Node** root);
int D_Find(Node** root);
int D_Timing(Node**);
int D_Tidelete(Node**);
int D_TInsrt(Node**);
int D_Delete(Node** root);
#endif
