/* Program ASCENDING RADIX SORT can..
1. Random raw data into 1 dimension Array
2. Sorting and display detail of each step result
3. Display final result
*/
#include <stdio.h>  // use printf
#include <stdlib.h> // use random
#include <time.h>   // use time

#define MaxData 100 // Define Max Data
#define MaxRow 10   // 0..9 in Decimal base
#define MaxCol 20   // 0..19

int Data[MaxData];
int Radix[MaxRow][MaxCol];
int N, N1;

void ClearStackPT(void)
{
    int i;
    for (i = 0; i < MaxRow; i++)   // FIXED: was "i <= MaxRow" (out-of-bounds write)
        Radix[i][0] = 0;
}

void PrepareRawData(int N2)
{
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < N2; i++)
        Data[i] = (rand() % 899) + 100;
}

void DispData(int N2)
{
    int i;
    for (i = 0; i < N2; i++)
        printf("%3d ", Data[i]);
    printf("\n");
}

void Push(int Rad, int Dat)
{
    int SP;
    SP = Radix[Rad][0] + 1;
    Radix[Rad][0] = SP;
    Radix[Rad][SP] = Dat;
}

void ReadStack(void)
{
    int i, j, k, SP;
    k = 0;
    for (i = 0; i < MaxRow; i++)
    {
        SP = Radix[i][0];
        for (j = 1; j <= SP; j++)
        {
            Data[k] = Radix[i][j];
            k++;
        }
    }
}

void RadixSort(int N2)
{
    int Digit, i, RadixNo, divisor;

    for (Digit = 0; Digit < 3; Digit++)
    {
        printf("[Digit : %d] ==>\n", Digit);
        ClearStackPT();

        for (i = 0; i < N2; i++)
        {
            divisor = 1;
            for (int d = 0; d < Digit; d++)
                divisor *= 10;
            RadixNo = (Data[i] / divisor) % 10;
            Push(RadixNo, Data[i]);
        }

        ReadStack();
        DispData(N2);
    }
}

int main(void)
{
    printf("ASCENDING RADIX SORT\n");
    printf("=====================================================================\n");

    N = 16;
    N1 = N;
    PrepareRawData(N);

    printf("Raw Data...\n");
    DispData(N);
    printf("---------------------------------------------------------------------\n");
    printf("Processing Data...\n");
    RadixSort(N);
    printf("---------------------------------------------------------------------\n");
    printf("Sorted Data : \n");
    DispData(N1);

    printf("\nPress ENTER to exit...");
    getchar(); //replaces conio.h's getch() - works on Mac/Linux

    return 0;
}