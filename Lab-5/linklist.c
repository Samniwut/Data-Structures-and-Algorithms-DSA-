/* Program: Singly Linked List
   1. Create N Nodes (รับค่าจากผู้ใช้)
   2. Insert node after specified data
   3. Delete node with specified data (แก้ให้ลบตัวที่ตรง ไม่ใช่ตัวถัดไป)
   4. Show address of Node and LINK
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int info;
    struct Node *link;
} Node;

Node *H = NULL, *H1 = NULL;
int n;

/* Allocate 1 node from storage pool */
Node *Allocate()
{
    Node *temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    return temp;
}

/* Create N Node, put data (from user input) and link it */
void CreateNNode(int n)
{
    int i, tempData;
    Node *p;
    H = NULL;
    H1 = NULL;
    for (i = 1; i <= n; i++) {
        printf("Enter data node %d : ", i);
        scanf("%d", &tempData);

        p = Allocate();
        p->info = tempData;
        p->link = NULL;
        if (i == 1)
            H = p;
        else
            H1->link = p;
        H1 = p;
    }
}

void ShowAllNode()
{
    Node *p = H;
    int i = 1;
    printf("H = %p\n", (void*)H);
    while (p != NULL) {
        printf("%d) %p\tINFO : %d\tLINK : %p\n", i,
             (void*)p, p->info, (void*)p->link);
        p = p->link;
        i++;
    }
}

void InsertAfter(int data1)
{
    int tempData;
    Node *p;
    Node *cur;
    int found = 0;
    if (H == NULL) {
        printf("Linked List have no node!!..\n");
        return;
    }
    cur = H;
    while (cur != NULL) {
        if (cur->info == data1) {
            found = 1;
            p = Allocate();
            printf("\nInsert data : ");
            scanf("%d", &tempData);
            p->info = tempData;
            p->link = cur->link;  
            cur->link = p;        
            break;
        }
        cur = cur->link;
    }
    if (!found)
        printf("Not found data %d in the list! Insert failed.\n", data1);
}

void DeleteAfter(int data1)
{
    Node *cur;
    Node *prev;
    int found = 0;
    if (H == NULL) {
        printf("Linked List have no node!!..\n");
        return;
    }
    prev = NULL;
    cur = H;
    while (cur != NULL) {
        if (cur->info == data1) {
            found = 1;
            if (prev == NULL)
                H = cur->link;      /* ลบโหนดแรกสุด (Head) */
            else
                prev->link = cur->link;
            free(cur);
            break;   /* stop after deleting once 
            (avoid multiple deletes on duplicate data) */
        }
        prev = cur;
        cur = cur->link;
    }
    if (!found)
        printf("Not found data %d in the list! Delete failed.\n", data1);
}

/* Free every node before program ends (avoid memory leak) */
void FreeAllNode()
{
    Node *p = H;
    Node *next;
    while (p != NULL) {
        next = p->link;
        free(p);
        p = next;
    }
    H = NULL;
}

int main()
{
    char ch;
    int data;
     printf("Enter amount of node (N) : ");
    while (scanf("%d", &n) != 1 || n <= 0)
    {
       // เคลียร์ตัวอักษรค้างใน buffer ทิ้งให้หมด
        while (getchar() != '\n');
        printf("Please input Number : ");
    }
    CreateNNode(n);
    printf("PROGRAM SINGLY LINKED LIST \n");
    printf("================================== \n");
    printf("All Data in Linked List \n");
    ShowAllNode();

    ch = ' ';
    while (ch != 'E') {
        printf("\nMENU : [I:Insert D:Delete E:Exit] : ");
        scanf(" %c", &ch);

        switch (ch) {
            case 'i':
            case 'I':
                printf("\nInsert After data : ");
                scanf("%d", &data);
                InsertAfter(data);
                printf("\nAll Data in Linked List AFTER INSERTED\n");
                ShowAllNode();
                break;
            case 'd':
            case 'D':
                printf("\nDelete After data : ");
                scanf("%d", &data);
                DeleteAfter(data);
                printf("\nAll Data in Linked List AFTER DELETED\n");
                ShowAllNode();
                break;
            case 'e':
            case 'E':
               FreeAllNode();
               return 0;
                break;
            default:
                printf("Invalid choice!\n");
        }
    }

    FreeAllNode();
    return 0;
}