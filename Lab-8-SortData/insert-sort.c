/* Program ASCENDING INSERTION SORT can..
1. Random raw data into 1 dimension Array
2. Sorting and display detail of each result
3. Display final result
*/
#include <stdio.h>   // use printf
#include <stdlib.h>  // use random
#include <time.h>    // use time

#define MaxData 100  // Define Max Data

int Data[MaxData];
int N;

void PrepareRawData(int N)
{
    int i;
    srand((unsigned int)time(NULL));
    for (i = 1; i <= N; i++)
        Data[i] = 1 + rand() % 99;
}

void DispData(int N)
{
    int i;
    for (i = 1; i <= N; i++)
        printf("%2d ", Data[i]);
    printf("\n");
}

void InsertionSort(int N)
{
    int i, j, temp;

    printf("------------------------------------------------------------\n");
    printf(" i ");
    for (i = 1; i <= N; i++)
        printf(" (%2d)", i);
    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("%2d. ", 0);
    DispData(N);

    for (i = 2; i <= N; i++)
    {
        temp = Data[i];
        j = i - 1;

        while (j >= 1 && Data[j] > temp)
        {
            Data[j + 1] = Data[j];
            j--;
        }

        Data[j + 1] = temp;
        printf("%2d. ", i);
        DispData(N);
    }
}

int main(void)
{
    printf("ASCENDING INSERTION SORT\n");
    printf("==============================\n");

    N = 12;
    PrepareRawData(N);
    printf("Raw Data... ");
    DispData(N);
    printf("Processing Data...\n");
    InsertionSort(N);
    printf("------------------------------------------------------------\n");
    printf("Sorted Data : ");
    DispData(N);

    printf("\nPress ENTER to exit...");
    getchar(); //replaces conio.h's getch() - works on Mac/Linux

    return 0;
}