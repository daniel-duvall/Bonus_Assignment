/*
lab assignment 7 - cs1 
 
Daniel DuVall 03/07/2024
*/
#include <stdio.h>

//swap function
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
//bubble sort function 
void bubbleSort(int arr[], int c[], int n)
{
    int total = 0;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])//compares adjacent values, if the current element is greater than element to its right, then they are swaped 
            {
                c[j]++; //increment corresponding elements in counter array to keep track of swaps for that element 
                c[j+1]++;
                swap(&c[j], &c[j+1]);//swap those elements accordingly so it matches up with the main array
                swap(&arr[j], &arr[j+1]);//swaps main array elements 
                total++; //increments total swaps by 1 because only one swap was made
            }
        }
    }
    //prints sorted array, # of swaps for each element, and total # of swaps made
    for(int i=0; i<n; i++)
        printf("%d: %d\n", arr[i], c[i]);
    printf("%d\n", total);
}
//selection sort function
void selectionSort(int arr[], int c[], int n)
{
    int total = 0;
    int m_index;//to keep track of the index of the smallest value in the array
    for(int i=0; i<n-1; i++)
    {
        m_index = i;//sets element i in array as the minimum 
        for(int j=i+1; j<n; j++)//loops through array again starting at i+1
        {
            if(arr[j]<arr[m_index])//if any value is less than element at i, or m_index, then the m_index becomes the index of that value 
                m_index = j;
        }
        //increment corresponding elements in counter array to keep track of swaps for that element 
        if(arr[i]!=arr[m_index])
        {
            c[i]++;
            c[m_index]++;
            swap(&c[i], &c[m_index]);//swap those elements accordingly so it matches up with the main array
            swap(&arr[i], &arr[m_index]);//swap main array elements 
            total++;//increments total swaps by 1 because only one swap was made
        }
    }
    //prints sorted array, # of swaps for each element, and total # of swaps made
    for(int i=0; i<n; i++)
        printf("%d: %d\n", arr[i], c[i]);
    printf("%d\n", total);
}

//resets the counter array to all 0s 
void reset(int c[], int n)
{
    for(int i=0; i<n; i++)
        c[i] = 0;
}

int main()
{
    int a1[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int a2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int len = 9;//length of the two arrays
    int n1 = sizeof(a1)/sizeof(a1[0]);
    int n2 = sizeof(a2)/sizeof(a2[0]);
    //declare and initialize duplicate arrays so it's easy to reset after bubble sort 
    int dup1[len], dup2[len];
    for(int i= 0; i<len; i++)
    {
        dup1[i] = a1[i];
        dup2[i] = a2[i];
    }
    int counter[9] = {0};//counter arry (i would've done "int counter[len] = {0}" but that caused an error and it counter wasn't declared yet) 

    printf("\nUsing bubble sort:\n");
    
    printf("Array 1:\n");
    bubbleSort(dup1, counter, n1);
    
    reset(counter, len);//reset counter for array 2

    printf("Array 2:\n");
    bubbleSort(dup2, counter, n2);
    
    //reset duplicate arrays back to original arrays so im not passing in already sorted arrays into selection sort 
    for(int i= 0; i<len; i++)
    {
        dup1[i] = a1[i];
        dup2[i] = a2[i];
    }
    reset(counter, len);//reset counter

    printf("\nUsing selection sort:\n");
    printf("Array 1\n");
    selectionSort(dup1, counter, n1);
    
    reset(counter, len);//reset counter for array 2

    printf("Array 2:\n");
    selectionSort(dup2, counter, n2);
    
    return 0;
}