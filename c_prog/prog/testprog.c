#include <stdio.h>

void plus(char* arr){
    arr++;
}

int main(){
    int arr[2];
    arr[0]=0;
    arr[1]=1;
    plus(arr);
    printf("%d", arr[0]);
}