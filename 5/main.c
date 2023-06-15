#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<readline/readline.h>
//#include<readline/history.h>
//#include <stdbool.h>
//#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include"func.h"
static const char* msgs[]={"0.Quit", "1.Add_Room", "2.Add_Corridor", "3.Delete Room", "4.Delete_Corrodor", "5.Show","6.TranslatorInWidth", "7. DistanceBetween","8.ChangeVer", "9.Closset"}; 
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file", "Not found"};
static int (*fptr[])(Maze*)={NULL, D_Addroom, D_Addcorr, D_Delete_Room, D_Delete_Corrodor, D_Show, D_TranslatorInWidth, D_DistanceBetween, D_ChangeVer,D_Closset};
int main()
{
    Maze* maze=NULL;
    maze=initializeMaze(maze);
    int rc;
    while(rc=dialog(msgs, Nmsgs)){
        if(!fptr[rc](maze)){
            break;
        }
    }
    deletemaze(maze);
    printf("Thx, Bye!\n");

}
