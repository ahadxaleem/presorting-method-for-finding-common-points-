#define __STDC_WANT_LIB_EXT1__ 1
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//pointer to the input file
FILE* ptr;
//for storing beginning and ending time
clock_t begin, end;
//total execution time
int exectime = 0;

//structure of arrays of endpoints
struct endpoint {
    int *a;//starting point
    int *b;//ending point
};

//for calculating maximum common points
void maxCommonPnt(int min,int max, int a[], int b[],int size) {
    //to store frequency of every point
    int* freq;
    freq = calloc(max , sizeof(int));
    //to store maximum frequency and common point
    int maxfreq = 0, commonpnt = 0;
    int i;
    /*for (i = min; i < max; i++) {
        freq[i] = 0;
    }*/

    //calculating frequency of every point
    int temp = 0;
    while (temp!=size-1) {
        int j;
        for (j = a[temp] + 1; j < b[temp]; j++) {
            freq[j]++;
        }
        temp++;
    }
    //finding out the maximum frequency
    int k;
    for (k = min + 1; k < max-1; k++) {
        if (freq[k] > maxfreq) {
            maxfreq = freq[k];
            commonpnt = k;
        }
    }
    printf("The maximum number of intervals = %d\n", maxfreq);
    printf("The interval include point = %d\n", commonpnt);
    free(freq);
}

//merge sort algorithm to sort array
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // create temp arrays 
    int* L, * R;
    L = calloc(n1 , sizeof(int));
    R = calloc(n2 , sizeof(int));

    // Copy data to temp arrays L and R 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //Copy the remaining elements of L
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

//driver program to call above functions
void main() {
    //object of struct
    struct endpoint arr;
    //to store input file name
    char filename[20];
    int size=0;
    printf("Enter file name : ");
    fgets(filename, sizeof(filename), stdin);
    int i = 0;
    //caculating file size
    while (filename[i] != '\n') {
        i++;
    }
    //getting filename to a proper format
    filename[i] = '.';
    strcat_s(filename, sizeof(filename), "txt");
    errno_t err = fopen_s(&ptr, filename, "r");
    
    if (err)
        printf_s("The file %s was not opened\n", filename);
    else
    {
        int temp;
        //calculating lengh of column of data to declare arrays
        while (!feof(ptr)) {
            fscanf_s(ptr, "%d", &temp);
            fscanf_s(ptr, "%d", &temp);
            size++;
        }
    }
    //dynamically allocating 
    arr.a = malloc(size * sizeof(int));
    arr.b = malloc(size * sizeof(int));
    if (err)
        printf_s("The file %s was not opened\n", filename);
    else
    {
        //seeking file pointer to the top
        fseek(ptr, 0, SEEK_SET);
        int j = 0;
        //storing each colum of data from file to saparate arrays
        while (!feof(ptr)) {
            fscanf_s(ptr, "%d", &(arr.a[j]));
            fscanf_s(ptr, "%d", &(arr.b[j]));
            j++;
        }
        fclose(ptr);
    }
    begin = clock();
    mergeSort(arr.a, 0, size - 1);//sorting array a
    mergeSort(arr.b, 0, size - 1);//sorting array b
    printf("presorting program for finding max number of interval\n");
    maxCommonPnt(arr.a[1], arr.b[size-1],arr.a,arr.b,size);//function call
    end = clock();
    exectime += end - begin;
    //printing execution time
    printf("Time for finding the maximum number : %d ms", exectime);
    free(arr.a);
    free(arr.b);
    /*for (i = 0; i < size-1 ; i++) {
        printf("%d\t%d\n", arr.a[i], arr.b[i]);
    }*/
}