#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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

int partition(int *nums,int left,int right){
    int pivot = nums[right];
    int l = left-1;
    for(int r=left;r<right;r++){
        if(nums[r] < pivot){
            l++;
            swap(&nums[l],&nums[r]);
        }
    }
    swap(&nums[l+1],&nums[right]);
    return (l+1);
}

void quick(int* nums,int left,int right){
    if(left<right){
        int index = partition(nums,left,right);
        quick(nums,left,index-1);
        quick(nums,index+1,right);
    }
}

int binary_search(int* nums,int size,int target){
    int l = 0, r = size-1;
    while(l<r){
        int mid = (l+r)/2;
        if(target == nums[mid]) return mid;
        if(nums[mid]<target){
            l = mid;
        }
        else{
            r = mid-1;
        }
    }
    return -1;
}


int main(void) {
    // srand(time(NULL));
    int size = 100;
    int *nums = (int*) malloc(sizeof(int)*size);
    getRandArray(nums,size);
    quick(nums,0,size-1);
    print(nums,0,size-1);
    int n = 51;
    printf("%d is at %d\n",n,binary_search(nums,size,n));
    free(nums);
    return 0;
}
