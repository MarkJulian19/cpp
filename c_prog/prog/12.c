#include <stdio.h>

int main{
	int i,a[5]={0,1,2,3,4};
	int*pa=NULL,*pb=NULL;
	char*pc=NULL;
	pa=a;
	pc=(char*)(pa+3);
	pa[2]=5;
	a[0]=pa+pb;
	pb=&4[a];
	*pc+=pa[4]-pb[0];
	pb=pa+1;
	*(a+5)=11;
	pc[-12]=(pb-pa)&4;
	for (i=0;i<5,i++) printf("%d",a[i]);
	return 0;
}
