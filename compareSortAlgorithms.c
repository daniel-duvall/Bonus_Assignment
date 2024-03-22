#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void *Alloc(size_t sz)
{
	extraMemoryAllocated += sz;
	size_t* ret = malloc(sizeof(size_t) + sz);
	*ret = sz;
	printf("Extra memory allocated, size: %ld\n", sz);
	return &ret[1];
}

void DeAlloc(void* ptr)
{
	size_t* pSz = (size_t*)ptr - 1;
	extraMemoryAllocated -= *pSz;
	printf("Extra memory deallocated, size: %ld\n", *pSz);
	free((size_t*)ptr - 1);
}

size_t Size(void* ptr)
{
	return ((size_t*)ptr)[-1];
}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

//*heapify function for heapSort*
void heapify(int arr[], int n, int i) 
{
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
    	largest = left;
  
    if (right < n && arr[right] > arr[largest])
    	largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) 
	{
    	//swap
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
    	heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int x, int n)
{
	// Build max heap
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// Heap sort
	for (int i = n - 1; i >= 0; i--) 
	{
		//swap
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
	// Heapify root element to get highest element at root again
		heapify(arr, i, 0);
	}
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	int mid = 0;
	
	if(l<r)
	{
		// get the mid point
		int mid = (l+r)/2;

		// Sort first and second halves
		mergeSort(pData, l, mid);
		mergeSort(pData, mid+1, r);
		
		int i, j, k;
		int n1 = mid - l + 1;
		int n2 = r - mid;

		// create temp arrays 
		int *L = (int*)Alloc(n1*sizeof(int));
		int *R = (int*)Alloc(n2*sizeof(int));

		// Copy data to temp arrays L[] and R[] 
		for (i = 0; i < n1; i++)
			L[i] = pData[l + i];
		for (j = 0; j < n2; j++)
			R[j] = pData[mid + 1+ j];

		// Merge the temp arrays back into arr[l..r]
		i = 0; // Initial index of first subarray
		j = 0; // Initial index of second subarray
		k = l; // Initial index of merged subarray
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				pData[k] = L[i];
				i++;
			}
			else
			{
				pData[k] = R[j];
				j++;
			}
			k++;
		}
		//Copy the remaining elements of L[], if there are any 
		while (i < n1)
		{
			pData[k] = L[i];
			i++;
			k++;
		}
		// Copy the remaining elements of R[], if there are any 
		while (j < n2)
		{
			pData[k] = R[j];
			j++;
			k++;
		}
		//free the arrays
		DeAlloc(L);
		DeAlloc(R);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, item, j;
	for (i = 1; i < n; i++)
	{
		item = pData[i];
		
		for(j=i-1; j>=0; j--)
		{
			if(pData[j]>item)
				pData[j+1] = pData[j];
			else
				break;
		}
		pData[j+1] = item;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (pData[j] > pData[j+1])//compares adjacent values, if the current element is greater than element to its right, then they are swaped 
            {
				int temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int m_index;//to keep track of the index of the smallest value in the array
    for(int i=0; i<n-1; i++)
    {
        m_index = i;//sets element i in array as the minimum 
        for(int j=i+1; j<n; j++)//loops through array again starting at i+1
        {
            if(pData[j]<pData[m_index])//if any value is less than element at i, or m_index, then the m_index becomes the index of that value 
                m_index = j;
        }
        //increment corresponding elements in counter array to keep track of swaps for that element 
        if(pData[i]!=pData[m_index])
        {
			int temp  = pData[i];
			pData[i] = pData[m_index];
			pData[m_index] = temp;
        }
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)Alloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (int i=0;i<dataSz;++i)
		{
			int n, *data;
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)Alloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

        printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		DeAlloc(pDataCopy);
		DeAlloc(pDataSrc);
	}
	
}
