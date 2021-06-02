#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// InsertionSort: Worst,Average=O(n^2) Best=O(n)
void getRandArray(int *nums,int size){
    for(int i=0;i<size;i++){
        nums[i] = rand()%size+1;
    }
    print(nums,0,size-1);
}

void print(int *nums,int start,int end){
    for(int i=start;i<=end;i++){
        printf("%d ",nums[i]);
    }
    printf("\n\n");
}

void swap(int *a,int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion(int* nums,int size){
    int i,j,tmp;
    for(i=1;i<size;i++){
        tmp = nums[i];
        for(j=i;j>0 && tmp<nums[j-1];j--){
            nums[j] = nums[j-1]; 
        }
        nums[j] = tmp;
    }
}

int main(void) {
    // srand(time(NULL));
    int size = 100;
    int *nums = (int*) malloc(sizeof(int)*size);
    getRandArray(nums,size);
    insertion(nums,size);
    print(nums,0,size-1);
    free(nums);
    return 0;
}
