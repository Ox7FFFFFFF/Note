#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// Selection sort : best,worst,average=O(n^2)
// Bubble sort : best=O(n), worst,average=O(n^2)
typedef bool  (*CMP)(int,int);
typedef void (*SORT)(int*,int,CMP);

bool ascending(int a,int b){
    return a>b;
}
bool descending(int a,int b){
    return b>a;
}

void getRandArray(int *nums,int size){
    for(int i=0;i<size;i++){
        nums[i] = rand()%size+1;
    }
    print(nums,size);
}

void print(int *nums,int size){
    for(int i=0;i<size;i++){
        printf("%d ",nums[i]);
    }
    printf("\n");
    printf("\n");
}

void swap(int *a,int *b){
    // int tmp = *a;
    // *a = *b;
    // *b = tmp;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void selection(int *nums, int size,CMP cmp){
    for(int i=0;i<size-1;i++){
        int index = i;
        int tmp = nums[i];
        for(int j=i+1;j<size;j++){
            if(cmp(tmp,nums[j])){
                tmp = nums[j];
                index = j;
            }
        }
        if(index != i)  swap(&nums[i],&nums[index]);
    }
    print(nums,size);
}

void bubble(int *nums,int size,CMP cmp){
    bool exchange = true;
    for(int i=0;exchange&&i<size-1;i++){
        exchange = false;
        for(int j=0;j<size-1;j++){
            if(cmp(nums[j],nums[j+1])){
                swap(&nums[j],&nums[j+1]);
                exchange = true;
            }
        }
    }
    print(nums,size);
}

int main(void) {
    // srand(time(NULL));
    int size = 100;
    int *nums = (int*) malloc(sizeof(int)*size);
    SORT sort;
    
    getRandArray(nums,size);
    sort = selection;
    sort(nums,size,descending);
    sort(nums,size,ascending);
    
    getRandArray(nums,size);
    sort = bubble;
    sort(nums,size,descending);
    sort(nums,size,ascending);
    
    free(nums);
    return 0;
}
