/* Program สร้างโครงสร้าง Tree ด้วยวิธี "Node Sequence"
   แสดงผลการท่องต้นไม้ (Traversal) แบบ
   1. Pre Order
   2. In Order
   3. Post Order
   รองรับต้นไม้สูงสุด 5 ระดับ (N = 31 โหนด)

   ฉบับแก้ไข: ใช้ได้กับ gcc มาตรฐาน (Linux/Mac/Windows-MinGW)
   ไม่พึ่งพา conio.h / getch() ของ Turbo C อีกต่อไป
   และเปลี่ยนจากการสุ่มตัวเลข เป็นการนำตัวอักษรจากสตริง infix1
   มาบรรจุลงในแต่ละโหนดตามลำดับแทน
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxNode 100     // จำนวนช่องสูงสุดของอาเรย์
#define MAX_LEVEL 5     // จำนวนระดับสูงสุดของต้นไม้

char infix1[80] = {"A+B*(C^D*E/F)-G"};   // ข้อมูลต้นฉบับที่จะนำมาใส่ในต้นไม้

int N;
char data[MaxNode];     // เก็บค่าของแต่ละโหนด, '\0' หมายถึง "ไม่มีโหนด"
char ch;

void CreateTreeNS(int n)
{
    int i;
    for (i = 1; i <= n; i++)
        data[i] = infix1[i - 1];     // นำตัวอักษรจาก infix1 ใส่ทีละตัวตามลำดับ
}

void ShowArray(void)
{
    int i = 1;
    while (i < MaxNode && data[i] != '\0')
    {
        printf("[%d]%c ", i, data[i]);
        i++;
    }
    printf("\n================================================================================\n");
}

void ShowTree(void)
{
    int j, level, start, ends;
    printf("\n");
    for (level = 1; level <= MAX_LEVEL; level++)
    {
        start = 1 << (level - 1);      // เทียบเท่า pow(2, level-1) แต่แม่นยำกว่า
        ends  = (1 << level) - 1;      // เทียบเท่า pow(2, level) - 1
        if (start >= MaxNode) break;

        for (j = start; j <= ends && j < MaxNode; j++)
        {
            if (data[j] != '\0')
            {
                switch (level)
                {
                    case 1: printf("%40c", data[j]); break;
                    case 2: printf(j == 2  ? "%20c" : "%40c", data[j]); break;
                    case 3: printf(j == 4  ? "%10c" : "%20c", data[j]); break;
                    case 4: printf(j == 8  ? "%5c"  : "%10c", data[j]); break;
                    case 5: printf(j == 16 ? "%c"   : "%5c",  data[j]); break;
                }
            }
            else
            {
                /* โหนดว่าง: เว้นช่องว่างขนาดเท่ากันไว้ เพื่อให้ตำแหน่งคอลัมน์ตรงกัน */
                switch (level)
                {
                    case 1: printf("%40s", ""); break;
                    case 2: printf(j == 2  ? "%20s" : "%40s", ""); break;
                    case 3: printf(j == 4  ? "%10s" : "%20s", ""); break;
                    case 4: printf(j == 8  ? "%5s"  : "%10s", ""); break;
                    case 5: printf(j == 16 ? "%s"   : "%5s",  ""); break;
                }
            }
        }
        printf("\n\n");
    }
}

void PreOrder(int i)
{
    if (i >= MaxNode) return;          // กัน index เกินขอบเขตอาเรย์
    if (data[i] != '\0')
    {
        printf(" %c", data[i]);
        PreOrder(2 * i);
        PreOrder(2 * i + 1);
    }
}

void InOrder(int i)
{
    if (i >= MaxNode) return;
    if (data[i] != '\0')
    {
        InOrder(2 * i);
        printf(" %c", data[i]);
        InOrder(2 * i + 1);
    }
}

void PostOrder(int i)
{
    if (i >= MaxNode) return;
    if (data[i] != '\0')
    {
        PostOrder(2 * i);
        PostOrder(2 * i + 1);
        printf(" %c", data[i]);
    }
}

int main(void)
{
    N = (int)strlen(infix1);           // จำนวนโหนด = จำนวนตัวอักษรใน infix1
    if (N > MaxNode - 1) N = MaxNode - 1;   // กันล้นอาเรย์ถ้าสตริงยาวเกินไป
    CreateTreeNS(N);

    ch = ' ';
    while (ch != 'E' && ch != 'e')
    {
        printf("\nTREE (NODE SEQUENCE)\n");
        printf("==================================\n");
        ShowArray();
        ShowTree();

        printf("\nMENU => P:PreOrder I:InOrder O:PostOrder E:Exit");
        printf("\n----------------------------------------------------------------------------\n");

        ch = getchar();
        while (getchar() != '\n');     // เคลียร์บัฟเฟอร์ (getchar อ่านทีละตัวอักษร)

        switch (ch)
        {
            case 'P': case 'p':
                printf("PRE ORDER TRAVERSAL : ");
                PreOrder(1);
                printf("\n");
                break;
            case 'I': case 'i':
                printf("IN ORDER TRAVERSAL : ");
                InOrder(1);
                printf("\n");
                break;
            case 'O': case 'o':
                printf("POST ORDER TRAVERSAL : ");
                PostOrder(1);
                printf("\n");
                break;
        }
    }
    return 0;
}