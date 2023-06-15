#include<stdio.h>
#include<stdlib.h>
#include"main.h"
int getInt(int* a){
	int b=*a;
	int c=scanf("%d", &b);
	if(c==1){
		if(b>0){
			*a=b;
			 scanf("%*[^\n]");
			return 1;
		}
		else if(b<=0){
			*a=b;
			 scanf("%*[^\n]");
			return 2;
		}
	}
	else if(c==0)
	{
		scanf("%*[^\n]");
//		printf("%d\n", b);	
		return 0;
	}
	else{
               scanf("%*[^\n]");
		return 5;
	}
}
int getDouble(double* a){
        double b=*a;
	int c=scanf("%lf", &b);
        if(c==1){
                if(b>0){
                        *a=b;
			scanf("%*[^\n]");
                        return 1;
                }
                else if(b<=0){
                        *a=b;
			scanf("%*[^\n]");
                        return 2;
                }
        }
        else if(c==0){
                scanf("%*[^\n]");
                return 0;
        }
	else{
		scanf("%*[^\n]");
		return 5;
	}
}

int input(Matrix *rm){
	int a;
	double p;
	int c;
	printf("Enter the size of matrix\n");
	c=getInt(&a);
	while(c!=1){
		printf("Please try again\n");
		if(c==5){
			return 0;
		}
		c=getInt(&a);
		
	}
	rm->size=a;
	rm->data=(Line*)malloc(a*sizeof(Line));
	int sz;
	int temp;
	int ci;
	for(int i=0; i<a; i++){
		printf("Enter the size of new line\n");
		ci=getInt(&sz);
		while(ci!=1){
                	printf("Please try again\n");
			if(ci==5){
				rm->size=i;
				deletemtr(rm);
				return 0;
			}
			ci=getInt(&sz);

	        }
		rm->data[i].size=sz;
		//p=(int*)malloc(sizeof(int)*sz);
		rm->data[i].data=(double*)malloc(sizeof(double)*sz);
		printf("Enter the elements for yout matrix line\n");
		for(int j=0; j<sz; j++)
		{
			temp=getDouble(&p);
			while(temp<1)
			{
                        	printf("Please try again\n");
				if(temp==-1){
					rm->size=i;
					deletemtr(rm);
					return 0;
				}
				temp=getDouble(&p);
                	}
			rm->data[i].data[j]=p;
		}
	}
	return 1;
}
	
/*	do {
		printf("%s\n", pr);
		printf("Enter number of lines: --> ");
		pr = "You are wrong; repeat, please!";
		if(getInt(&a) == 0)
			return 0;
	} while (a < 1);
*/
void deletemtr(Matrix *m){
	for(int i=0; i<m->size; i++){
		free(m->data[i].data);
	}
	free(m->data);
}
void printmtr(Matrix* m){
	printf("Matrix\n");
        for(int i=0; i<m->size; i++){
                for(int j=0; j<m->data[i].size; j++){
                        printf("%10.3lf ", m->data[i].data[j]);
                }
                printf("\n");
        }
}
int countK(Matrix* m,int i){
	int k=0;
	int max=m->data[i].data[0];
	for(int j=0; j<m->data[i].size; j++){
		if(m->data[i].data[j]>max){
			k=j;
			max=m->data[i].data[j];
		}
	}
	return k;
	
}
int countL(Matrix* m, int i, int k){
	int l=0;
	int minstr=m->data[i].size;
	int minstlb=0;
	for(int j=0; j<m->size; j++){
		if(m->data[j].size>k){
			minstlb++;
		}
	}
	if(minstr>minstlb){
		return minstlb;
	}
	else if(minstlb>minstr){
		return minstr;
	}
}
void indtask(Matrix* m){
	double* b=(double*)malloc((m->size)*sizeof(double));
	int k;
	int l;
	b[0]=0;
	for(int i=0; i<m->size; i++){
		k=countK(&(*m), i);
//		printf("k= %d\n",k);
                l=countL(&(*m), i, k);
//		printf("l=%d\n ", l);
		b[i]=0;
		for(int j=0; j<l; j++){
			if(m->data[j].size>k){
				b[i]=b[i]+m->data[i].data[j]*m->data[j].data[k];
//				printf("b[i]= %d\n", b[i]);
			}
		}
	} 
	printf("Array\n");
	for(int i=0; i<m->size; i++){
		printf("%10.3lf ", b[i]);
	}
	printf("\n-----------\n");
	free(b);
}
