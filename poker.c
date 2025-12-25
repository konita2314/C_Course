#include <stdio.h>
void reverseArray(int arr[], int size) {
    int i,temp;
    for (i = 0; i < size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}
void handleArray(int arr[], int size) {
    //模拟进队列，出队列的操作
    int i,j,temp;
    for (i = 0; i < size; i++) {
            //printf("%d ", arr[i]);
        temp = arr[0];
        for(j = 0; j < i; j++) {
            arr[j]=arr[j+1];       //逐个前移
        }    
        arr[i]=temp;
    }    
}
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main() {
    int n,i;
    printf("请输入扑克牌的张数:\n");
    scanf("%d",&n);
    int arr[n];
    for(i=0;i<n;i++){
    arr[i] = i + 1;
    }
    int size = sizeof(arr) / sizeof(arr[0]);
    reverseArray(arr, size);
    handleArray(arr,size);
    reverseArray(arr, size);
    printArray(arr,size);
    return 0;
}
