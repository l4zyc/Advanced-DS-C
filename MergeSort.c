#include <stdio.h>

void merge(int *array, int start, int mid, int end) {
    int len = (end - start) + 1;
    int temp[len];

    int i = start, j = mid + 1, k = 0;

    while(i <= mid && j <= end) {
        if(array[i] < array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    while(i <= mid) {
        temp[k++] = array[i++];
    }

    while(j <= end) {
        temp[k++] = array[j++];
    }

    for(int x = 0; x < len; x++) {
        array[start + x] = temp[x];
    }
}

void mergeSort(int *array, int start, int end) {
    if(start < end) {
        int mid = (end + start) / 2;

        mergeSort(array, start, mid); //left
        mergeSort(array, mid+1, end); //right

        merge(array, start, mid, end);
    }
}

int main() {

    int arr[] = {2,5,3,4,1};
    int size = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, size - 1);

    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}