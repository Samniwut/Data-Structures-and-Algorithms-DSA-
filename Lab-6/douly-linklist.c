/*
Doubly Linked List Program
1. Can Create N Node with random data
2. Can Insert node before/after data as defined
3. Can Delete node before/itself/after data as defined
4. Show address of Node
*/
#include <stdio.h>   // use printf, getchar
#include <stdlib.h>  // use malloc, exit
#include <time.h>    // use time() for srand seed

struct Node //Declare structure of node
{
    int info;
    struct Node *llink;
    struct Node *rlink;
};
typedef struct Node Node;

Node *H, *H1, *p, *q; // Declare pointer node
int i, j, k, n, data;
char ch;

Node *Allocate() //Allocate 1 node from storage pool
{
    Node *temp;
    temp = (Node*)malloc(sizeof(Node)); //Allocate node by size declare
    if (temp == NULL) //Check if allocation failed
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    return temp;
}

void CreateNNode(int n) //Create N Node put data and link it
{
    int i, temp;
    H = NULL; H1 = NULL;
    for (i = 1; i <= n; i++) //Count N Node
    {
        p = Allocate(); //Allocate Node
        printf("Enter data node %d : ", i);
        scanf("%d", &temp);
        p->info = temp; //Put random data in to node
        if (i == 1)
            H = p; //Set H point to first node
        else
            H1->rlink = p; //Link first node to second node
        p->llink = H1;
        H1 = p; //Let H1 point to last node
        H1->rlink = NULL; //Set rlink of H1 to NULL
    }
}

void ShowAllNode()
{
    printf("H = %p\n", (void*)H); //Display address of pointer H
    p = H; //Set start point of p pointer
    i = 1; //set start value of counter
    while (p != NULL) //While if NOT NULL
    {
        printf("%d) : %p\t", i, (void*)p);       //Show COUNTER and POINTER
        printf("LLINK : %p\t", (void*)p->llink);  //Show LLINK
        printf("INFO : %d\t", p->info);           //Show INFO
        printf("RLINK : %p\n", (void*)p->rlink);  //Show RLINK
        p = p->rlink; //Skip to next node
        i++; //Skip Counter
    } //End While
} //End Fn.

void InsertAfter(int data1)
{
    int temp; //Temporary variable
    if (H == NULL)
        printf("Linked List have no node!!..\n");
    else
    {
        H1 = H; //Let H1 point at start node
        while (H1 != NULL) // Search for the data while H1<>NULL
        {
            if (H1->info == data1) //if Found
            {
                p = Allocate(); //Allocate one node from storage pool
                printf("\nInsert data : ");
                scanf("%d", &temp); //Read from KBD
                p->info = temp; // Entry temporary data into INFO of node
                if (H1->rlink == NULL)
                {
                    p->rlink = NULL;
                }
                else
                {
                    p->rlink = H1->rlink; //Change pointer 1st for insert node (FAR to NEAR)
                    H1->rlink->llink = p; //LLINK(RLINK(H1))=p
                }
                p->llink = H1; //LLINK(P)=H1
                H1->rlink = p; //RLINK(H1)=p
                break; //Stop after inserting once (avoid multiple inserts on duplicate data)
            } //End if
            H1 = H1->rlink; //Skip H1 to next node
        } //End while
    } //End IF
} //End Fn.

void InsertBefore(int data1)
{
    int temp; //Temporary variable
    if (H == NULL)
        printf("Linked List have no node!!..\n");
    else
    {
        H1 = H; //Let H1 point at start node
        while (H1 != NULL) // Search for the data while H1<>NULL
        {
            if (H1->info == data1) //if Found
            {
                p = Allocate(); //Allocate one node from storage pool
                printf("\nInsert data : ");
                scanf("%d", &temp); //Read from KBD
                p->info = temp; // Entry temporary data into INFO of node
                if (H1->llink == NULL)
                {
                    p->llink = NULL;
                    H = p;
                }
                else
                {
                    H1->llink->rlink = p; //RLINK(LLINK(H1))=p
                    p->llink = H1->llink; //LLINK(p)=LLINK(H1)
                }
                H1->llink = p; //LLINK(H1)=p
                p->rlink = H1; //RLINK(P)=H1
                break; //Stop after inserting once (avoid multiple inserts on duplicate data)
            } //End if
            H1 = H1->rlink; //Skip H1 to next node
        } //End while
    } //End IF
} //End Fn.

void DeleteBefore(int data1)
{
    if (H == NULL)
        printf("Linked List have NO NODE!!..\n");
    else
    {
        H1 = H; //Let H1 point at start node
        while (H1 != NULL) // Search for the data while H1<>NULL
        {
            if (H1->info == data1) //if Found
            {
                if (H1->llink == NULL) //If no more node
                    printf("No more node from here,Can't delete it!!!\n");
                else
                {
                    p = H1->llink; //Mark at node for Delete
                    if (p->llink == NULL) //If p is first node
                    {
                        H1->llink = NULL; //Set link of H1 to NULL
                        H = H1; //Set H to first NODE
                    }
                    else
                    {
                        H1->llink = p->llink; //If not set link of H1 point same address of p
                        p->llink->rlink = H1;
                    }
                    free(p); //Free node to storage pool
                } //End if2
                break; //Stop after deleting once
            } //End if1
            H1 = H1->rlink; //Skip H1 to next node
        } //End while
    } //End IF
} //End Fn.

void DeleteSelf(int data1)
{
    if (H == NULL)
        printf("Linked List have NO NODE!!..\n");
    else
    {
        H1 = H; //Let H1 point at start node
        while (H1 != NULL) // Search for the data while H1<>NULL
        {
            if (H1->info == data1) //if Found
            {
                Node *next = H1->rlink; //Remember next node BEFORE freeing
                p = H1; //Mark at node for Delete
                if (p->llink == NULL && p->rlink == NULL) //If only one node
                    H = NULL;
                else
                {
                    if (p->llink == NULL) //Check if first NODE
                    {
                        H = p->rlink; //Let H point to RLINK(P)
                        H->llink = NULL; //Assign LLINK(H)=NULL
                    }
                    else
                    {
                        if (p->rlink == NULL) //Check if Last NODE
                            p->llink->rlink = NULL;
                        else //NORMAL
                        {
                            p->llink->rlink = p->rlink;
                            p->rlink->llink = p->llink;
                        }
                    }
                }
                free(p); //Free node to storage pool
                H1 = next; //Continue from the node after the deleted one
                continue;
            } //End if1
            H1 = H1->rlink; //Skip H1 to next node
        } //End while
    } //End IF
} //End Fn.

void DeleteAfter(int data1)
{
    if (H == NULL)
        printf("Linked List have NO NODE!!..\n");
    else
    {
        H1 = H; //Let H1 point at start node
        while (H1 != NULL) // Search for the data while H1<>NULL
        {
            if (H1->info == data1) //if Found
            {
                if (H1->rlink == NULL) //If no more node
                    printf("No more node from here,Can't delete it!!!\n");
                else
                {
                    p = H1->rlink; //Mark at node for Delete
                    if (p->rlink == NULL) //If p is last node
                        H1->rlink = NULL; //Set link of H1 to NULL
                    else
                    {
                        H1->rlink = p->rlink; //If not set link of H1 point same address of p
                        p->rlink->llink = H1;
                    }
                    free(p); //Free node to storage pool
                } //End if2
                break; //Stop after deleting once
            } //End if1
            H1 = H1->rlink; //Skip H1 to next node
        } //End while
    } //End IF
} //End Fn.

int GetValidInt(const char *prompt) //Read integer safely, re-ask if invalid
{
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1)
    {
        while (getchar() != '\n'); //Clear invalid input from buffer
        printf("Please enter a valid number: ");
    }
    return value;
}

int main() //MAIN Fn.
{
    srand((unsigned int)time(NULL)); //Seed random number generator

    printf("Enter amount of node (N) : ");
    while (scanf("%d", &n) != 1 || n <= 0)
    {
       // เคลียร์ตัวอักษรค้างใน buffer ทิ้งให้หมด
        while (getchar() != '\n');
        printf("Please input Number : ");
    }

    CreateNNode(n); //Call Fn. Create N nodes
    printf("PROGRAM DOUBLY LINKED LIST \n");
    printf("================================== \n");
    printf("All Data in Linked List \n");
    ShowAllNode(); //Call Fn. Show all node

    ch = ' ';
    while (ch != 'E' && ch != 'e')
    {
        printf("\nMENU>> [B:InsertBefore A:InsertAfter\n");
        printf("          O:DeleteBefore X:Delete itself\n");
        printf("          D:DeleteAfter  E:Exit] : ");

        while (getchar() != '\n'); //Clear leftover newline from previous scanf
        scanf("%c", &ch);

        switch (ch)
        {
            case 'B':
                data = GetValidInt("\nInsert Before data : ");
                InsertBefore(data); //Call Fn. Insert before data
                printf("\nAll Data in Linked List AFTER INSERTED\n");
                ShowAllNode(); //Call Fn. Show all node
                break;

            case 'A':
                data = GetValidInt("\nInsert After data : ");
                InsertAfter(data); //Call Fn. Insert after data
                printf("\nAll Data in Linked List AFTER INSERTED\n");
                ShowAllNode(); //Call Fn. Show all node
                break;

            case 'O':
                data = GetValidInt("\nDelete Before data : ");
                DeleteBefore(data); //Call Fn. Delete before data
                printf("\nAll Data in Linked List AFTER DELETED\n");
                ShowAllNode(); //Call Fn. Show all node
                break;

            case 'X':
                data = GetValidInt("\nDelete ItSelf data : ");
                DeleteSelf(data); //Call Fn. Delete data itself
                printf("\nAll Data in Linked List ITSELF DELETED\n");
                ShowAllNode(); //Call Fn. Show all node
                break;

            case 'D':
                data = GetValidInt("\nDelete After data : ");
                DeleteAfter(data); //Call Fn. Delete after data
                printf("\nAll Data in Linked List AFTER DELETED\n");
                ShowAllNode(); //Call Fn. Show all node
                break;

            case 'E':
            case 'e':
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid menu choice, please try again.\n");
                break;
        } // End Switch...case
    } //End While

    return 0;
} //End MAIN