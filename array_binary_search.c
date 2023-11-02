/* 
 *    Program:      Searching an int in a sorted integer array with Binary Search Algorithm
 *    Made by:      Ransomware3301 (https://github.com/ransomware3301)
 *    Date:         01-11-2023
 */


#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define DEBUG 1

typedef int BOOL;

typedef struct result {
    int index;
    BOOL found;    
} result_t;


void array_input(int*, int);
void insertion_sort(int*, int);
void print_array(int*, int);
result_t binary_search(int*, int, int);


int main(int argc, char *argv[])
{
    int dim;
    int elem;
    int *arr;
    result_t res;

    /* Array size input */
    do{
        printf("Insert array size: ");
        scanf("%d", &dim);
    }while(dim < 1);


    if(( arr = (int*)malloc(sizeof(int) * dim) ))
    {
        array_input(arr, dim);      /* Array input */        
        insertion_sort(arr, dim);   /* Sorting the array */

        if(DEBUG){
            printf("---------------\n(DEBUG)");
            print_array(arr, dim);
            printf("---------------\n\n");
        }
            
        printf("Insert element to search in array: ");
        scanf("%d", &elem);

        res = binary_search(arr, dim, elem);

        if(res.found == TRUE){
            printf("\nValue %d was found at index %d\n\n", elem, res.index);
        }
        else{
            printf("\n=> Value %d was not found\n\n", elem);
        }
    }
    else{
        printf("[in \"main()\"] - Memory allocation error\n");
    }

    return 0;
}


/*
 *  Takes a declared array reference as input and fills it 
 *  with input values from user
 */
void array_input(int *arr, int dim)
{
    int i;

    for(i = 0; i < dim; i++)
    {
        printf("Insert value at index %d: ", i);
        scanf("%d", (arr + i));
    }
    printf("\n");
}


/*
 *  Sorts the passed array with the Insertion Sort Algorithm 
 *  in the ascending order
 */
void insertion_sort(int *arr, int dim)
{
    int i, j;
    int temp;

    for(i = 0; i < dim - 1; i++)
    {
        for(j = i + 1; j < dim; j++)
        {
            if(arr[j] < arr[i])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


/* 
 *  Prints the passed array to terminal
 */
void print_array(int *arr, int dim)
{
    int i;

    printf("\nArray Contents:\n");

    for(i = 0; i < dim; i++){
        printf("%d ", *(arr + i));
    }
    
    printf("\n");
}


/* 
 *  Performs a binary search of elem in array and returns a struct containing 
 *  the index and wether the element was found or not 
 */
result_t binary_search(int *arr, int dim, int elem)
{
    int l, r;
    int center;
    result_t res;


    if(dim < 2){
        /* Handling case where array dim == 1 */
        if( *(arr) == elem )
        {    
            res.index = 0;
            res.found = TRUE;   
        }
        else
        {
            res.index = -1;
            res.found = FALSE;
        }
    }
    else
    {
        /* Border flags, one at start and one at end of array */
        l = 0;
        r = dim - 1;

        /* Default vaules in case element isn't found */
        res.index = -1;
        res.found = FALSE;

        while( !res.found && l < r)
        {
            /* Calculating the center of the current array partition */
            center = (l + r)/2;

            if(DEBUG){
                printf("\n---------------\n(DEBUG) ");
                printf("\nCENTER: %d\n", center);
                printf("L: %d | R: %d\n", l, r);
                printf("---------------\n");
            }
            
            if( *(arr + center) == elem ){
                res.index = center;
                res.found = TRUE;
            }
            else if( *(arr + l) == elem){
                res.index = l;
                res.found = TRUE;
            }
            else if( *(arr + r) == elem){
                res.index = r;
                res.found = TRUE;
            }
            else if( elem > *(arr + center) ){
                l = center + 1;
            }  
            else{
                r = center - 1;
            }
        }
    }

    return res;
}
