#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int val;
    struct node* next;
}Node;

void create(Node** head,int val){
    Node* tmp = malloc(sizeof(Node));;
    tmp->val = val;
    tmp->next = NULL;
    if(*head == NULL){
        *head = tmp;
    }
    else{
        Node *node = *head;
        while(node->next!=NULL){
            node = node->next;
        }
        node->next = tmp;
    }
}

void removeTarget(Node**head,int target){
    Node *node = *head;
    Node *dummy = (Node*) malloc(sizeof(Node));
    dummy->next = *head;
    Node *last = dummy;
    while(node!=NULL){
        if(node->val == target){
            last->next = node->next;
            break;
        }
        last = node;
        node = node->next;
    }
    *head = dummy->next;
}


void print(Node* node){
    while(node != NULL){
        printf("%d ",node->val);
        node = node->next;
    }
    printf("\n");
}

int getCenterNodeValue(Node* node){
    Node *fast = node;
    Node *slow = node;
    while(fast->next!=NULL && fast->next->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow->val;
}

int getLength(Node** node){
    Node *fast = *node;
    int len = 0;
    while(fast!=NULL){
        len++;
        fast = fast->next;
    }
    return len;
}

void rotateList(Node** node,int step){
    Node *fast = *node;
    Node *slow = *node;
    Node *dummy = (Node*) malloc(sizeof(Node));
    dummy->next = *node;
    int len = getLength(node);
    for(int i=0;i<(step%len);i++){
        fast = fast->next;
    }
    while(fast->next!=NULL){
        fast = fast->next;
        slow = slow->next;
    }
    fast->next = dummy->next;
    dummy->next = slow->next;
    slow->next = NULL;
    *node = dummy->next;
}

void reverseList(Node** head){
    Node* node = *head;
    Node* new_head = NULL;
    while(node != NULL){
        Node* pre_node = node->next;
        // 斷掉next的連結
        node->next = new_head;
        // 下一輪
        new_head = node;
        node = pre_node;
    }
    *head = new_head;
}

 Node* mergeTwoList(Node* l1,Node* l2){
     if(l1 == NULL) return l2;
     if(l2 == NULL) return l1;
     if(l1->val <= l2->val){
         l1->next = mergeTwoList(l1->next,l2);
         return l1;
     }
     else{
         l2->next = mergeTwoList(l2->next,l1);
         return l
     }
}

void splitList(Node *node,Node **a,Node **b){
    Node *fast = node;
    Node *slow = node;
    while(fast->next!=NULL && fast->next->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    *a = node;
    *b = slow->next;
    slow->next = NULL;
}

void mergeSort(Node **node){
    Node *a;
    Node *b;
    Node *head = *node;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    splitList(head,&a,&b);
    mergeSort(&a);
    mergeSort(&b);
    *node = mergeTwoList(a,b);
}


int main(void){
    Node* head = NULL;
    int size = 10;
    for(int i=0;i<size;i++){
        create(&head,size-i);
    }
    print(head);
    mergeSort(&head);
    print(head);
    
    rotateList(&head,7);
    print(head);
    
    removeTarget(&head,4);
    print(head);
    
    printf("center is %d\n",getCenterNodeValue(head));
    printf("length is %d\n",getLength(&head));
    
    reverseList(&head);
    print(head);
    free(head);
    head = NULL;
}
