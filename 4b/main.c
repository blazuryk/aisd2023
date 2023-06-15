#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include"func.h"
static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import","6.Indtask", "7. Traversal", "8.TiIns", "9.Tidel", "10.Tisc"};
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file", "Not found"};
static int (*fptr[])(Node**)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Indtask, D_Traversal, D_TInsrt, D_Tidelete,D_Timing};
int main()
{
    Node* root=NULL;
 //   if(table!=NULL){
    int rc;
//    root=insert(root, 1, 2);
    while(rc=dialog(msgs, Nmsgs)){
        if(!fptr[rc](&root)){
            break;
        }
    }
    deleteTree(root);
    printf("Thx, Bye!\n");

}
