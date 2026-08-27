/* Program สร้างโครงสร้าง Tree ด้วยวิธี "Node Sequence"
   แสดงผลการท่องต้นไม้ (Traversal) แบบ
   1. Pre Order
   2. In Order
   3. Post Order
   รองรับต้นไม้สูงสุด 5 ระดับ (N = 31 โหนด)

   ฉบับแก้ไข: ใช้ได้กับ gcc มาตรฐาน (Linux/Mac/Windows-MinGW)
   ไม่พึ่งพา conio.h / getch() ของ Turbo C อีกต่อไป

   ** จุดที่เปลี่ยนจากเดิม **
   แทนที่จะเอาตัวอักษรจาก infix1 ยัดใส่ array เรียงตามลำดับตรง ๆ (ซึ่งไม่ใช่
   Expression Tree ที่ถูกต้องตามหลักคณิตศาสตร์) เวอร์ชันนี้จะ:
     1. แปลง Infix -> Postfix ด้วยอัลกอริทึม Shunting-Yard (จัดลำดับ operator/วงเล็บถูกต้อง)
     2. สร้าง Expression Tree ชั่วคราวแบบ Linked (pointer) จาก Postfix
     3. เดินต้นไม้ชั่วคราวนั้นแล้ว "จับใส่" ลง array data[] ตามตำแหน่งจริงของมันในต้นไม้
        (ราก=1, ลูกซ้าย=2*i, ลูกขวา=2*i+1) แล้วเลิกใช้ต้นไม้ชั่วคราว (free)
   ส่วน ShowArray, ShowTree, PreOrder/InOrder/PostOrder แบบ array ยังเป็นแนวคิด
   Node Sequence เดิม (ปรับ ShowArray เล็กน้อยเพื่อรองรับช่องว่างระหว่างโหนด)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxNode 100     // จำนวนช่องสูงสุดของอาเรย์
#define MAX_LEVEL 5     // จำนวนระดับสูงสุดของต้นไม้
#define MAXLEN 100

char infix1[80];        // ข้อมูลต้นฉบับ (นิพจน์ infix) ที่ผู้ใช้ป้อนเข้ามา

int N;
char data[MaxNode];     // เก็บค่าของแต่ละโหนดตามตำแหน่ง Node Sequence, '\0' = ไม่มีโหนด
char ch;

/* ---------- ต้นไม้ชั่วคราวแบบ Linked ใช้แค่ตอนสร้างข้อมูล ---------- */
typedef struct TNode {
    char data;
    struct TNode *left, *right;
} TNode;

int precedence(char op)
{
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isRightAssociative(char op)
{
    return (op == '^');   // ^ เป็น right-associative, ตัวอื่น left-associative
}

void infixToPostfix(char infix[], char postfix[])
{
    char stack[MAXLEN];
    int top = -1;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];
        if (isspace((unsigned char)c)) continue;

        if (isalnum((unsigned char)c))              // ตัวถูกดำเนินการ (operand)
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            stack[++top] = c;
        }
        else if (c == ')')
        {
            while (top >= 0 && stack[top] != '(')
                postfix[j++] = stack[top--];
            top--;                                    // pop '(' ทิ้ง
        }
        else                                           // operator: + - * / ^
        {
            while (top >= 0 && stack[top] != '(' &&
                   (precedence(stack[top]) > precedence(c) ||
                    (precedence(stack[top]) == precedence(c) && !isRightAssociative(c))))
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }
    while (top >= 0)
        postfix[j++] = stack[top--];

    postfix[j] = '\0';
}

TNode* newTNode(char d)
{
    TNode *n = (TNode*)malloc(sizeof(TNode));
    n->data = d;
    n->left = n->right = NULL;
    return n;
}

TNode* buildExpressionTree(char postfix[])
{
    TNode *stack[MAXLEN];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];
        if (isalnum((unsigned char)c))               // operand -> สร้างใบ (leaf)
        {
            stack[++top] = newTNode(c);
        }
        else                                           // operator -> ดึงลูก 2 ตัวมาผูก
        {
            TNode *n = newTNode(c);
            n->right = stack[top--];
            n->left  = stack[top--];
            stack[++top] = n;
        }
    }
    return stack[top];                                 // โหนดสุดท้ายที่เหลือคือราก
}

/* จับต้นไม้ชั่วคราว (pointer) ใส่ลง array Node Sequence ตามตำแหน่งจริง
   index = 1 คือราก, ลูกซ้าย = 2*index, ลูกขวา = 2*index+1               */
void StoreInArray(TNode *t, int index)
{
    if (t == NULL) return;
    if (index >= MaxNode)
    {
        printf("!! คำเตือน: ต้นไม้ลึกเกินขอบเขตอาเรย์ที่ index %d (ข้อมูลตกหล่น)\n", index);
        return;
    }
    data[index] = t->data;
    StoreInArray(t->left,  2 * index);
    StoreInArray(t->right, 2 * index + 1);
}

void freeTNode(TNode *t)
{
    if (t == NULL) return;
    freeTNode(t->left);
    freeTNode(t->right);
    free(t);
}

void ShowArray(void)
{
    /* ไล่ดูทั้งอาเรย์ (ไม่หยุดที่ช่องว่างแรก) เพราะ Expression Tree จริง
       มักมีช่องว่างคั่นระหว่างโหนด เช่น โหนดใบที่ไม่มีลูก */
    int i;
    for (i = 1; i < MaxNode; i++)
    {
        if (data[i] != '\0')
            printf("[%d]%c ", i, data[i]);
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
    char postfix[MAXLEN];

    printf("Enter infix = :  ");
    scanf("%s", infix1);

    infixToPostfix(infix1, postfix);
    printf("\nPostfix Expression : %s\n", postfix);

    TNode *root = buildExpressionTree(postfix);
    StoreInArray(root, 1);              // จับใส่ array Node Sequence ตามตำแหน่งจริง
    freeTNode(root);                    // เลิกใช้ต้นไม้ชั่วคราวแล้ว

    N = (int)strlen(postfix);           // เก็บไว้เผื่ออ้างอิง (จำนวนโหนดทั้งหมด)

    printf("\nTREE (NODE SEQUENCE)\n");
        printf("==================================\n");
        ShowArray();
        ShowTree();
        
        printf("\nPreOrder = ");
        PreOrder(1);
        printf("\nInOrder = ");
        InOrder(1);
        printf("\nPostOrder = ");
        PostOrder(1);
        printf("\n.....End_Program\n");

    return 0;
}