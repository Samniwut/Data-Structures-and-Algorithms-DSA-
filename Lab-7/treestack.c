/* Program: Create a binary Expression Tree from a POSTFIX string and store it
   using the "NODE SEQUENCE Method" (array / heap representation, where for
   node at index i: left child = 2*i, right child = 2*i+1).

   Can show the result when traversed by:
   1. Pre Order
   2. In Order
   3. Post Order
   Can hold up to 5 levels of tree (N = 31 nodes max, MaxNode = 100 for safety).

   ---------------------------------------------------------------------------
   Fixes applied in this revision:
   1. CreateTreeNS() no longer just copies the postfix string character-by-
      character into the array (which produced garbage, off-by-one data, and
      was NOT an actual expression tree). It now genuinely PARSES the postfix
      expression with a stack (stack of pointer-based tree nodes), builds a
      real binary expression tree, and then maps that tree onto the
      node-sequence array using the standard heap index rule
      (root = 1, left = 2*i, right = 2*i + 1).
   2. Fixed the "%d" vs "%c" bug in ShowTree(): data[] holds characters, but
      every printf() in the switch-statement was printing the raw ASCII code
      instead of the character. All format specifiers changed to "%c".
   3. Removed the unused, stale "int N;" declaration.
   4. Removed the misleading comment claiming srand(time(NULL)) was added -
      the program builds a tree deterministically from a fixed postfix
      string, so there is nothing to randomize. (If you want a different
      expression each run, change 'postfix1' or feed input instead.)
   5. Replaced conio.h getch() with portable getchar() (works on
      Linux/Mac/Windows) - kept from the previous revision.
   6. Added bounds checking (index < MaxNode) when placing nodes into the
      array, and a clean error message if the postfix expression would
      require a tree deeper than the array can hold, or if the expression
      itself is malformed (stack has the wrong number of items at the end).
   7. Tree memory (pointer-based scratch tree) is freed after being copied
      into the array, avoiding a memory leak.
   ---------------------------------------------------------------------------
*/
#include <stdio.h>   // printf, getchar
#include <stdlib.h>  // malloc, free
#include <string.h>  // strlen
#include <ctype.h>   // isalnum

#define MaxNode 100  // Define Max Node of Tree array (node-sequence array)

char postfix1[80] = {"AB+C-D/"};

char ch, data[MaxNode];   // node-sequence array holding the tree ('\0' = empty slot)

/* ---- scratch pointer-based tree, used only to PARSE the postfix string ---- */
typedef struct TNode
{
    char symbol;
    struct TNode *left, *right;
} TNode;

typedef struct
{
    TNode *items[80];
    int top;
} Stack;

void StackInit(Stack *s)      { s->top = -1; }
int  StackIsEmpty(Stack *s)   { return s->top < 0; }
void StackPush(Stack *s, TNode *n) { s->items[++(s->top)] = n; }
TNode *StackPop(Stack *s)     { return s->items[(s->top)--]; }

TNode *NewTNode(char c)
{
    TNode *n = (TNode *)malloc(sizeof(TNode));
    n->symbol = c;
    n->left = n->right = NULL;
    return n;
}

void FreeTree(TNode *root)
{
    if (root == NULL) return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

/* Build a real binary expression tree from a postfix string using a stack.
   Operands (letters/digits) become leaves; any other symbol is treated as
   an operator that pops its right operand then its left operand. */
TNode *BuildExpressionTree(const char *postfix, int *ok)
{
    Stack s;
    StackInit(&s);
    *ok = 1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        if (isalnum((unsigned char)c))              // operand -> leaf node
        {
            StackPush(&s, NewTNode(c));
        }
        else                                         // operator -> internal node
        {
            if (s.top < 1)   // not enough operands on the stack -> malformed expr
            {
                *ok = 0;
                return NULL;
            }
            TNode *right = StackPop(&s);
            TNode *left  = StackPop(&s);
            TNode *node  = NewTNode(c);
            node->left  = left;
            node->right = right;
            StackPush(&s, node);
        }
    }

    if (s.top != 0)   // a valid postfix expression should leave exactly 1 node
    {
        *ok = 0;
        return NULL;
    }
    return StackPop(&s);
}

/* Copy the pointer-based tree into the node-sequence array using the
   standard heap indexing rule: root at index 1, left child = 2*i,
   right child = 2*i + 1. Returns 0 on success, -1 if the tree is too
   deep to fit in MaxNode. */
int AssignNodeSequence(TNode *node, int idx)
{
    if (node == NULL) return 0;
    if (idx >= MaxNode) return -1;   // tree too deep for the array

    data[idx] = node->symbol;

    if (AssignNodeSequence(node->left,  2 * idx)     != 0) return -1;
    if (AssignNodeSequence(node->right, 2 * idx + 1) != 0) return -1;

    return 0;
}

/* Build the whole node-sequence array from a postfix string. */
void CreateTreeNS(const char *infix)
{
    int ok;
    TNode *root = BuildExpressionTree(infix, &ok);

    for (int i = 0; i < MaxNode; i++)   // start with a clean, empty array
        data[i] = 0;

    if (!ok)
    {
        printf("ERROR: \"%s\" is not a valid postfix expression.\n", infix);
        return;
    }

    if (AssignNodeSequence(root, 1) != 0)
    {
        printf("ERROR: expression tree is too deep to fit in the array "
               "(MaxNode = %d).\n", MaxNode);
    }

    FreeTree(root);   // scratch tree no longer needed once copied into data[]
}

void ShowArray()
{
    int i = 1;
    while (i < MaxNode && data[i] != 0)
    {
        printf("[%d]%c ", i, data[i]);
        i++;
    }
    printf("\n===========================================================================\n");
}

void ShowTree()
{
    int j, level, start, ends;
    int anyLeft = 1;
    level = 1; // Start at Level 1
    printf("\n");
    while (anyLeft)
    {
        start = 1 << (level - 1);   // START Node of this level (2^(level-1))
        ends  = (1 << level) - 1;   // END Node of this level (2^level - 1)

        if (start >= MaxNode) break;   // safety: don't run past the array
        if (ends >= MaxNode) ends = MaxNode - 1;

        anyLeft = 0;
        for (j = start; j <= ends; j++)
        {
            if (data[j] != 0)
            {
                anyLeft = 1;   // found at least one live node at this level
                switch (level)
                {
                    case 1:
                        printf("%40c", data[j]);
                        break;
                    case 2:
                        if (j == 2)
                            printf("%20c", data[j]);
                        else
                            printf("%40c", data[j]);
                        break;
                    case 3:
                        if (j == 4)
                            printf("%10c", data[j]);
                        else
                            printf("%20c", data[j]);
                        break;
                    case 4:
                        if (j == 8)
                            printf("%5c", data[j]);
                        else
                            printf("%10c", data[j]);
                        break;
                    case 5:
                        if (j == 16)
                            printf("%c", data[j]);
                        else
                            printf("%5c", data[j]);
                        break;
                    default:
                        printf("%5c", data[j]);
                        break;
                }
            }
            else
            {
                switch (level)
                {
                    case 1: printf("%40c", ' '); break;
                    case 2: printf("%s", j == 2 ? "                    " : "                                        "); break;
                    default: break; // keep deeper empty slots compact
                }
            }
        }
        printf("\n\n"); // Line feed
        level++;
    }
}

void PreOrder(int i)
{
    int lson, rson;
    if (i < MaxNode && data[i] != 0) // if INFO NOT NULL/0
    {
        printf(" %c", data[i]);      // Display INFO
        lson = 2 * i;                // Calculate LSON
        rson = 2 * i + 1;            // Calculate RSON
        PreOrder(lson);              // Call left Son by PreOrder
        PreOrder(rson);              // Call Right Son by PreOrder
    }
}

void InOrder(int i)
{
    int lson, rson;
    if (i < MaxNode && data[i] != 0)
    {
        lson = 2 * i;
        rson = 2 * i + 1;
        InOrder(lson);                // Call left Son by InOrder
        printf(" %c", data[i]);       // Display INFO
        InOrder(rson);                // Call Right Son by InOrder
    }
}

void PostOrder(int i)
{
    int lson, rson;
    if (i < MaxNode && data[i] != 0)
    {
        lson = 2 * i;
        rson = 2 * i + 1;
        PostOrder(lson);              // Call left Son by PostOrder
        PostOrder(rson);              // Call Right Son by PostOrder
        printf(" %c", data[i]);       // Display INFO
    }
}

int main()
{
    CreateTreeNS(postfix1); // Create the node-sequence tree from the postfix string

    while (ch != 'E')
    {
        printf("\nTREE (NODE SEQUENCE)\n");
        printf("==================================\n");
        ShowArray();
        ShowTree();
        printf("\nMENU => P:PreOrder I:InOrder O:PostOrder E:Exit");
        printf("\n---------------------------------------------------------------------------\n");

        ch = getchar();
        // consume leftover newline character left in input buffer by getchar()
        if (ch == '\n')
            ch = getchar();

        switch (ch)
        {
            case 'P':
                printf("PRE ORDER TRAVERSAL : ");
                PreOrder(1);
                printf("\n");
                break;
            case 'I':
                printf("IN ORDER TRAVERSAL : ");
                InOrder(1);
                printf("\n");
                break;
            case 'O':
                printf("POST ORDER TRAVERSAL : ");
                PostOrder(1);
                printf("\n");
                break;
        } // End Switch...case
    } // End While

    return 0;
} // End Main