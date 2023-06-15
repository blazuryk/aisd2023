#include<stdio.h>
#include<stdlib.h>
#include"main.h"
int main(){
	Matrix m;
//	int a;
//	printf("Enter the height\n");
//	scanf("%d", &a);
//	m->size=a;
//	m->data=malloc(a*sizeof(Line));	
	int r=input(&m);
	if(r==0){
		return 0;
	}
	indtask(&m);
	printmtr(&m);
	deletemtr(&m);
}


