#include <stdio.h> 
#include <vector>

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
    
    while(j <= end)  {
        temp[k++] = array[j++];
    }

    for(int x = 0; x < len; x++) {
        array[start + x] = temp[x];
    }
}

void mergeSort(int *array, int start, int end) {
    if(start < end) {
        int mid = (end + start) / 2;

        //split all
        mergeSort(array, start, mid); //left
        mergeSort(array, mid+1, end); //right

        //merge one by one
        merge(array, start, mid, end);
    }
}

int binarySearch(int *array, int left, int right, int target) {
    if(left <= right) {
        int mid = (right + left) / 2;

        if(target == array[mid]) {
            return mid;
        }

        if(target > array[mid]) {
            return binarySearch(array, mid+1, right, target);
        } else {
            return binarySearch(array, left, mid-1, target);
        }
    }
    return -1;
}

int main() {

    int array[] = {9,10,2,1,3,4,5,6,8,7};
    int size = sizeof(array) / sizeof(array[0]);
    mergeSort(array, 0, size - 1);
    
    for(int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("%d", binarySearch(array, 0, size - 1, 10));
    return 0;
}