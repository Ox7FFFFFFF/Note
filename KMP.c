#include<stdio.h>

int main(void) {
    char str[16] = "ababcabcabababd";
    char pattern[5] = "ababd";
    int failure[5] = {-1};
    
    int l = -1;
    for(int r=1;r<5;r++){
        while(l != -1 && pattern[r] != pattern[l+1])
            l = failure[l];
        if(pattern[r] == pattern[l+1])
            failure[r] = ++l;
    }
    for(int i=0;i<5;i++)
        printf("%d ",failure[i]);
    printf("\n");
    
    int tail = -1;
    for(int i=0;i<16;i++){
        while(tail != -1 && str[i] != pattern[tail+1]){
            tail = failure[tail];
        }
        if(str[i] == pattern[tail+1]){
            tail++;
        }
        if(tail == 4) {
            printf("%d",i-tail);
            break;
        }
    }
}
