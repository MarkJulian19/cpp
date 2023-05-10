#include <stdio.h>

int main(){
    FILE *test_file_1, *test_file_2;
    test_file_1 = fopen("test_file_1.txt","w");
    test_file_2 = fopen("test_file_2.txt","w");
    int i;
    for (i=0; i<10;i++){
        fprintf(test_file_1, "%d ", i);
    }
    for (i=8; i<15;i++){
        fprintf(test_file_2, "%d ", i);
    }
    fclose(test_file_1);
    fclose(test_file_2);
    return 0;
}