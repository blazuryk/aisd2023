#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include"func.h"
static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import", "6.Indtask"};
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file", "Not found"};
int getInt(int* b){
    int k;
    int r =scanf("%d", &k);
    if(r==1){
        if(k>=0){
        *b=k;
         scanf("%*[^\n]");
         scanf("%*c");
        return 1;
        }
        else{
            return 0;
        }
    }
    if (r==0){
         scanf("%*[^\n]");
         scanf("%*c");
        return 0;
    }
    if (r==-1){
        scanf("%*[^\n]");
        scanf("%*c");
        return -1;
    }
}
int D_Findmi(Table* table, unsigned int key);
int D_Show(Table* table){
    if(table==NULL){
        return 0;
    }
    if(table->ks==NULL){
        printf("Table if empty\n");
        return 1;
    }
    for(int i=0; i<table->csize; i++){
        printf("key: %d par key: %d info : %d \n", table->ks[i].key, table->ks[i].par, table->ks[i].info);
    }
    return 1;
}
int impttb(Table* table, char* name){
        FILE *file;
        unsigned int key;
        unsigned int par;
        int records=0;
        int info;
        int k=table->csize;
        file=fopen(name, "r");
        free(name);
        if(file==NULL){
                return 4;
        }
        int read=0;
        while(read=fscanf(file, "%d%*c%d%*c%d*c", &key, &par,&info)!=EOF){
                if(read!=1 && feof(file)){
                        return 4;
                }
        table->csize++;
        if(table->csize>table->maxsize){
                table->csize=k;
                fclose(file);
                return 2;
        }
        if(table->csize-1==0){
                table->ks=malloc(sizeof(KeySpace));
        }
        else{
             table->ks=realloc(table->ks, table->csize*sizeof(KeySpace));
        }
        table->ks[k].key=key;
        table->ks[k].par=par;
        table->ks[k].info=info;
        k++;
        if(read==1) records++;
        }while(!feof(file));
        fclose(file);
        return 0;

}
int D_Import(Table* table){
        char* name=readline("Enter th name of file\n");
        if(name==NULL){
            return 0;
        }
        int rc=impttb(table, name);
        printf("%s\n", errmsgs[rc]);
        return 1;
}
int D_Delete(Table* table){
 //       if(table==NULL){
  //      return 0;
 //   }
    if(table->ks==NULL){
        printf("Table if empty\n");
        return 1;
    }
    int b;
    printf("Enter the key of the element wich you want to delete\n");
    int n=getInt(&b);
    while(n!=1){
        if(n==-1){
            return 0;
        }
        printf("Pls, try again\n");
        n=getInt(&b);
    }
    int flag=0;
    int flag1=0;
    int i;
    for(i=0; i<table->csize; i++){
        if(table->ks[i].key==b){
            flag=1;
            break;
        }
    }
    for(int j=0;j<table->csize; j++){
        if(table->ks[j].par==b){
            flag1=1;
            break;
        }
    }
    if(flag==0){
        printf("No element with this key\n");
        return 1;
    }
    if(flag1==1){
        printf("This key have a child key, you cant delete him\n");
        return 1;
    }
    if (flag==1){
        table->csize--;
        if(table->csize==0){
            free(table->ks);
            table->ks=NULL;
            return 1;
        }
        for(int j=i; j<table->csize; j++){
            table->ks[j]=table->ks[j+1];
        }
        table->ks=(KeySpace*)realloc(table->ks, table->csize*sizeof(KeySpace));
        return 1;
    }
    }
int D_Find(Table* table){
    if(table==NULL){
        return 0;
    }
    if(table->ks==NULL){
        printf("Empty table\n");
        return 1;
    }
    printf("Enter the key,wich you want to find\n");
    int n, b, rc;
    n=getInt(&b);
    while(n!=1){
        if(n==-1){
            return 0;
        }
        printf("Pls, try again\n");
        n=getInt(&b);
    }
    rc=D_Findmi(table, b);
	if(rc>-1){
		printf("key: %d par: %d info: %d \n", b, table->ks[rc].par, table->ks[rc].info);
	}
	else{
		printf("Not found\n");
	}
//    printf("%s: %d\n:", errmsgs[rc], b);
    return 1;
}
int D_Indtask(Table* table){
    if(table==NULL){
        return 0;
    }
    if(table->ks==NULL){
        printf("Table is empty\n");
        return 1;
    }
    printf("Enter the statr of seacrh\n");
    int b;
    int a;
    int n=getInt(&b);
    while(n!=1){
        if(n==-1){
            return 0;
        }
        printf("Pls, try again\n");
        n=getInt(&b);
    }
    printf("Enter the end of seacrh\n");
    n=getInt(&a);
    while(n!=1){
        if(n==-1){
            return 0;
        }
        printf("Pls, try again\n");
        n=getInt(&a);
    }
    int start=b;
    int end =a;
    if((start>end) || (start<0) || (end<0)){
        printf("Uncorrect try again latter");
        return 1;
    }
    Table* newt=malloc(sizeof(Table));
    newt->csize=0;
    newt->maxsize=table->maxsize;
    newt->ks=malloc(table->maxsize*sizeof(KeySpace));
    int k=0;
    for(int i=0; i<table->csize; i++){
        if((table->ks[i].par>=start) && (table->ks[i].par<=end)){
            newt->ks[k].key=table->ks[i].key;
            newt->ks[k].par=table->ks[i].par;
            newt->ks[k].info=table->ks[i].info;
            k++;
            newt->csize=k;
        }
    }
    if(newt->csize==0){
        free(newt->ks);
        newt->ks=NULL;
    }
    D_Show(newt);
    if(newt->ks!=NULL){
        free(newt->ks);
    }
    free(newt);
    return 1;
}
int D_Findmi(Table* table, unsigned int key){
    if(table->ks==NULL){
        return 2;
    }
    int flag=0;
    for(int i=0; i<table->csize; i++){
        if(table->ks[i].key==key){
//            printf("key: %d par: %d info: %d \n", key, table->ks[i].par, table->ks[i].info);
//		flag=1;
		return i;
        }
    }
//    if (flag==1){
//        return 1;
//    }
//    else{
        return -1;
//    }
}
int D_Findpar(Table* table, int par){
    if(table==NULL){
        return 0;
    }
    if (par==0){
                return 1;
        }
    for(int i=0; i<table->csize; i++){
        if(table->ks[i].key==par){
            return 1;
        }
    }
    return 0;
}
int insert(Table* table, unsigned int k, unsigned int par, unsigned int info){
    if(table == NULL){
        return 2;
    }
    if(k==0){
		printf("Main key cannot be 0\n");
		return 1;
	}
    if(table->ks==NULL){
        if(table->maxsize<1){
                return 2;
        }
        table->csize=1;
        if(par!=0){
        printf("Becouse its 1 element you can add par kay only 0, your par key change to 0\n");
        }
        table->ks=malloc(sizeof(KeySpace));
        table->ks->key=k;
        table->ks->info=info;
        table->ks->par=0;
        return 0;
    }
    if (k==par){
        printf("Key!=parKey\n");
        return 1;
    }
    if((D_Findmi(table, k)==0) && (D_Findpar(table, par)==1)){
        table->csize++;
        if(table->csize>table->maxsize){
            table->csize--;
            return 2;
        }
        table->ks=realloc(table->ks, (table->csize)*sizeof(KeySpace));
//        printf("%d", k);
        table->ks[table->csize-1].key=k;
//        printf("tb= %d", table->ks[table->csize-1].key);
        table->ks[table->csize-1].par=par;
        table->ks[table->csize-1].info=info;
        return 0;
    }

    else {
        return 1;
    }

}
int D_Add(Table *ptab){
    int rc, n, p, t;
    unsigned int info, par, k;
    printf("Enter Key:-->\n");
    n=getInt(&k);
    while(n!=1){
        if(n==-1){
            return 0;
        }
        printf("Error Key, try again\n");
        n=getInt(&k);
    }
    printf("Enter par Key:-->\n");
    p=getInt(&par);

    while(p!=1){
        if(p==-1){
            return 0;
        }
        printf("Error par, try again\n");
        p=getInt(&par);
    }
    printf("Enter the info:\n");
    t=getInt(&info);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error info, try again\n");
        t=getInt(&info);
    }
    rc=insert(ptab, k, par, info);
    printf("%s: %d\n:", errmsgs[rc], k);
    return 1;
}
int deleteTable(Table* table){
    if(table->ks!=NULL){
        free(table->ks);
    }
    free(table);
}
static int (*fptr[])(Table*)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Indtask};
int dialog(const char * msgs[], int N){
    char *errmsg="";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg="You are wrong.Repeat please!";
        for(i =0; i<N; i++){
            puts(msgs[i]);
        }
        puts("Make your choise: -->");
        n=getInt(&rc);
        if(n==-1){
            rc=0;
        }
        if(n==0){
            rc=-1;
        }
    }while(rc<0 || rc >=N);
    return rc;
}
Table* init(){
    Table* table=malloc(sizeof(Table));
    table->ks=NULL;
    table->csize=0;
    int rc;
    printf("Enter maxsize\n");
    int t= getInt(&rc);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error maxsize, try again\n");
        t=getInt(&rc);
    }
    table->maxsize=rc;
    return table;
}

