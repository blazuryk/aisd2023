#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include"func1.h"
static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import", "6.Indtask"};
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file"};
//int getInt(int *b);
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
Table* init(){
        Table* table=malloc(sizeof(Table));
        table->maxsize=0;
        table->csize=0;
        table->ks=NULL;
        table->fd=NULL;
}
int create(Table* table, char* fname, int maxsize){
        table->maxsize=maxsize;
//      printf("maxsiz = %d\n", table->maxsize);
        table->csize=0;
        table->fd=fopen(fname, "w+b");
//      if(fopen_s(&(table->fd), fname, "w+b")!=0){
        if(table->fd==NULL){
                table->ks=NULL;
                return 0;
        }
//      table->fd=fname;
//      printf("name= %s\n", table->fd);
        table->ks=(Item*)calloc(table->maxsize, sizeof(Item));
        fwrite(&table->maxsize, sizeof(int), 1, table->fd);
        fwrite(&table->csize, sizeof(int), 1, table->fd);
        fwrite(table->ks, sizeof(Item), table->maxsize, table->fd);
        return 1;
}
int save(Table *table){
        fseek(table->fd, sizeof(int), SEEK_SET);
        fwrite(&table->csize, sizeof(int), 1, table->fd);
        fwrite(table->ks, sizeof(Item), table->csize, table->fd);
        fclose(table->fd);
        table->fd=NULL;
        return 1;
}
int D_Show(Table* table){
        if(table==NULL){
                return 0;
        }
        if(table->csize==0){
                printf("Empty table\n");
                return 1;
        }
        int info;
        fseek(table->fd, 0, SEEK_SET);
        for(int i=0; i<table->csize; i++){
                fseek(table->fd, table->ks[i].offset, SEEK_SET);
                fread(&info, sizeof(int), 1, table->fd);
                printf("key= %d par =%d info=%d \n", table->ks[i].key, table->ks[i].par, info);
        }
        return 1;
}
int load(Table* table, char* fname){
        table->fd=fopen(fname, "r+b");
        if(table->fd==NULL){
                return 0;
        }
        fread(&table->maxsize, sizeof(int), 1, table->fd);
        table->ks=(Item*)calloc(table->maxsize, sizeof(Item));
        fread(&table->csize, sizeof(int), 1, table->fd);
        fread(table->ks, sizeof(Item), table->csize, table->fd);
        return 1;
}
int D_Load(Table* table){
        int maxsize;
        char* fname=NULL;
        int n;
        fname=readline("Enter the name of the file\n");
        if(fname==NULL){
                return 0;
        }
        if(load(table,fname)==0){
                printf("Enter possible vector size: -->");
                n=getInt(&maxsize);
                while(n!=1){
                        if(n==-1){
                        return 0;
                        }
                        printf("Error\n");
                        n=getInt(&maxsize);
                }
                printf("maxsize = %d\n", maxsize);
                create(table,fname,maxsize);
        }
        free(fname);
        return 1;
}
int find(Table* table, int k){
        int i=0;
        for(;i<table->csize; i++){
                if(table->ks[i].key==k){
                        return i;
                }
        }
        return -1;
}
int findInfo(Table*table, int k){
        unsigned int info;
        int i=find(table,k);
        if(i>=0){
                fseek(table->fd, table->ks[i].offset, SEEK_SET);
                fread(&info, sizeof(int), 1,table->fd);
        }
        return info;
}
int D_Find(Table* table){
        unsigned int info;
        unsigned int k, n, par;
        int i,j;
        puts("Enter key:-->");
        n=getInt(&k);
        while(n!=1){
                if(n==-1){
                return 0;
                }
                printf("Error\n");
                n=getInt(&k);
        }
        info= findInfo(table,k);
        if(info>0){
                j=find(table,k);
                printf("key = %d, par= %d, info =%d \n", k, table->ks[j].par, info);
        }
        else{
                printf("Item %d was not found\n", k);
        }
        return 1;
}
int findpar(Table* table, int par){
        for(int i=0; i<table->csize; i++){
                if(table->ks[i].key==par){
                        return 1;
                }
        }
        return 0;
}
int findpar1(Table* table, int k){
        for(int i=0; i<table->csize; i++){
                if(table->ks[i].par==k){
                        return 1;
                }
        }
        return 0;
}
int insert(Table* table, int k, int par, int info){
        if(find(table, k)>=0){
                return 1;
        }
        if((findpar(table, par)==0) && (par!=0)){
                printf("Invalid par key\n");
                return 1;
        }

        if(table->csize>=table->maxsize){
                return 2;
        }
        table->ks[table->csize].key=k;
        table->ks[table->csize].par=par;
        fseek(table->fd, 0, SEEK_END);
        table->ks[table->csize].offset=ftell(table->fd);
        fwrite(&info , sizeof(int), 1, table->fd);
        table->csize++;
        return 0;
}
int D_Add(Table* table){
        unsigned int k, par, info;
        int rc, n;
        printf("Enter key:-->\n");
        n=getInt(&k);
        while(n!=1){
                if(n==-1){
                return 0;
                }
                printf("Error\n");
                n=getInt(&k);
        }
        printf("Enter par:-->\n");
        n=getInt(&par);
        while(n!=1){
                if(n==-1){
                return 0;
                }
                printf("Error\n");
                n=getInt(&par);
        }
        printf("Enter info:-->\n");
        n=getInt(&info);
        while(n!=1){
                if(n==-1){
                        return 0;
                }
                printf("Error\n");
                n=getInt(&info);
        }
        rc=insert(table, k, par, info);
        printf("%s:  %d\n", errmsgs[rc], k);
        return 1;
}
int deleteTable(Table* table){
        if(table->ks!=NULL){
        free(table->ks);
        }
        free(table);
}
int impttb(Table* table, char* name){
        FILE *file;
        unsigned int key;
        unsigned int par;
        int records=0;
        int info;
        int rc;
        int k=table->csize;
        file=fopen(name, "r");
        free(name);
        if(file==NULL){
                return 4;
        }
        int read=0;
        while(read=fscanf(file, "%d%*c%d%*c%d%*c", &key, &par,&info)!=EOF){
                if(read!=1 && feof(file)){
                        return 4;
                }
        table->csize++;
        if(table->csize>table->maxsize){
                table->csize=k;
                fclose(file);
                return 2;
        }
        table->csize--;
        printf("key = %d, par= %d, info= %d\n", key, par, info);
        rc=insert(table, key, par, info);
        k++;
        printf("%s:  %d\n", errmsgs[rc], k);
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
int D_Indtask(Table* table){
    if(table==NULL){
        return 0;
    }
    if(table->csize==0){
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
    newt->ks=malloc(table->maxsize*sizeof(Item));
    int k=0;
    for(int i=0; i<table->csize; i++){
        if((table->ks[i].par>=start) && (table->ks[i].par<=end)){
            newt->ks[k].key=table->ks[i].key;
            newt->ks[k].par=table->ks[i].par;
            newt->ks[k].offset=table->ks[i].offset;
            k++;
            newt->csize=k;
        }

}
        if(newt->csize==0){
                free(newt->ks);
                free(newt);
                printf("Empty table\n");
                return 1;
        }
        newt->fd=table->fd;
        D_Show(newt);
        free(newt->ks);
        free(newt);
        return 1;
}
int D_Delete(Table* table){
        int k, n,i,rc;
        printf("Enter the key, wich you want to delete\n");
        n=getInt(&k);
        while(n!=1){
                if(n==-1){
                return 0;
                }
                printf("Error\n");
                n=getInt(&k);
        }
        i=find(table,k);
        if(i<0){
                printf("Not found\n");
                return 1;
        }
        rc=findpar1(table,table->ks[i].key);
        if(rc==1){
                printf("You cant kill him, he have a child\n");
                return 1;
        }
	int info;
        /*int corpos1=table->ks[i].offset;
        int size1=corpos1+1;
        int info1;
        int info2;
*/	if(table->csize>0){
/*        int corpos2=table->ks[table->csize-1].offset;
        int size2=corpos2+1;
        fseek(table->fd, corpos2, SEEK_SET);
        fread(&info2, sizeof(int),1, table->fd);
        fseek(table->fd,corpos1,SEEK_SET);
	printf("info= %d\n", info2);
        fwrite(&info2, sizeof(int), 1, table->fd);
        table->ks[i].key=table->ks[table->csize-1].key;
        table->ks[i].par=table->ks[table->csize-1].par;*/
	//if(i+1!=table->csize){
	for(; i<table->csize-1; i++){
		fseek(table->fd, table->ks[i+1].offset, SEEK_SET);
		fread(&info,sizeof(int),1,table->fd);
		fseek(table->fd, table->ks[i].offset,SEEK_SET);
		fwrite(&info, sizeof(int),1, table->fd);
		table->ks[i].key=table->ks[i+1].key;
		table->ks[i].par=table->ks[i+1].par;
	}
        int success = ftruncate(fileno(table->fd), ftell(table->fd) - sizeof(int));

    if (success != 0) {
        printf("Error for cutting\n");
        return 1;
    }
        table->csize--;
        return 1;
    }
    else
	{
		printf("Empty Table\n");
		return 1;
	}
	}
static int (*fptr[])(Table*)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Indtask};
