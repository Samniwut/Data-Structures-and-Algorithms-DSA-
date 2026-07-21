#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

typedef struct {
    int data[MAX_SIZE];
    int front, rear;
} Queue;

typedef struct {
    int top;
    int front;
    int rear;
    int type; // 0 = Stack, 1 = Queue
} State;

Stack stack;
Queue queue;
State beforeState, afterState;

// ========== Shared Functions (ฟังก์ชันที่ใช้ร่วมกัน) ==========
void showProgramHeader(const char title[]) {
    printf("\n");
    for (int i = 0; i < 40; i++) printf("=");
    printf("\n %s\n", title);
    for (int i = 0; i < 40; i++) printf("=");
    printf("\n");
}

void showSeparator() {
    for (int i = 0; i < 40; i++) printf("-");
    printf("\n");
}

void showOperationResult(const char operation[], int value, int success) {
    printf("\nOperation : %s\n", operation);
    if (value != -9999) {
        printf("Value : %d\n", value);
    }

    printf("Before : ");
    if (beforeState.type == 0) { // Stack
        int count = (beforeState.top >= 0) ? (beforeState.top + 1) : 0;
        printf("Top = %d, Data = %d\n", beforeState.top, count);
    } else { // Queue
        int count = (beforeState.rear >= beforeState.front) ? (beforeState.rear - beforeState.front + 1) : 0;
        printf("Front = %d, Rear = %d, Data = %d\n", beforeState.front, beforeState.rear, count);
    }

    printf("After : ");
    if (afterState.type == 0) { // Stack
        int count = (afterState.top >= 0) ? (afterState.top + 1) : 0;
        printf("Top = %d, Data = %d\n", afterState.top, count);
    } else { // Queue
        int count = (afterState.rear >= afterState.front) ? (afterState.rear - afterState.front + 1) : 0;
        printf("Front = %d, Rear = %d, Data = %d\n", afterState.front, afterState.rear, count);
    }

    printf("Result : %s\n", success ? "SUCCESS" : "FAILED");
}

int getStackInput() {
    int value;
    printf("Enter value: ");
    if (scanf("%d", &value) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return -9999;
    }
    return value;
}

int getQueueInput() {
    int value;
    printf("Enter value: ");
    if (scanf("%d", &value) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return -9999;
    }
    return value;
}

// ========== Stack Functions ==========
void initStack() {
    stack.top = -1;
}

int isStackFull() {
    return stack.top >= MAX_SIZE - 1;
}

int isStackEmpty() {
    return stack.top < 0;
}

void push(int value) {
    beforeState.top = stack.top;
    beforeState.type = 0;

    if (isStackFull()) {
        printf("\nPush failed: Stack Overflow\n");
        afterState.top = stack.top;
        afterState.type = 0;
        showOperationResult("PUSH", value, 0);
        return;
    }

    stack.data[++stack.top] = value;
    afterState.top = stack.top;
    afterState.type = 0;
    showOperationResult("PUSH", value, 1);
}

int pop() {
    beforeState.top = stack.top;
    beforeState.type = 0;

    if (isStackEmpty()) {
        printf("\nPop failed: Stack Underflow\n");
        afterState.top = stack.top;
        afterState.type = 0;
        showOperationResult("POP", -9999, 0);
        return -1;
    }

    int value = stack.data[stack.top--];
    afterState.top = stack.top;
    afterState.type = 0;
    showOperationResult("POP", value, 1);
    return value;
}

void showStack() {
    showProgramHeader("STACK STATUS");
    printf("Capacity : %d\n", MAX_SIZE);
    printf("Data : %d\n", stack.top + 1);
    printf("Top : %d\n", stack.top);
    printf("Status : %s\n", isStackEmpty() ? "EMPTY" : "NORMAL");
    showSeparator();

    if (isStackEmpty()) {
        printf("Stack is empty.\n");
    } else {
        printf("TOP -> ");
        for (int i = stack.top; i >= 0; i--) {
            printf("[%d] index %d\n       ", stack.data[i], i);
        }
        printf("\n");
    }
    showSeparator();
}

void clearStack() {
    initStack();
    printf("\nStack cleared!\n");
}

// ========== Queue Functions ==========
void initQueue() {
    queue.front = 0;
    queue.rear = -1;
}

int isQueueFull() {
    return queue.rear >= MAX_SIZE - 1;
}

int isQueueEmpty() {
    return queue.rear < queue.front;
}

void insertQueue(int value) {
    beforeState.front = queue.front;
    beforeState.rear = queue.rear;
    beforeState.type = 1;

    if (isQueueFull()) {
        printf("\nInsert failed: Queue Overflow\n");
        afterState.front = queue.front;
        afterState.rear = queue.rear;
        afterState.type = 1;
        showOperationResult("INSERT QUEUE", value, 0);
        return;
    }

    queue.data[++queue.rear] = value;
    afterState.front = queue.front;
    afterState.rear = queue.rear;
    afterState.type = 1;
    showOperationResult("INSERT QUEUE", value, 1);
}

int deleteQueue() {
    beforeState.front = queue.front;
    beforeState.rear = queue.rear;
    beforeState.type = 1;

    if (isQueueEmpty()) {
        printf("\nDelete failed: Queue Underflow\n");
        afterState.front = queue.front;
        afterState.rear = queue.rear;
        afterState.type = 1;
        showOperationResult("DELETE QUEUE", -9999, 0);
        return -1;
    }

    int value = queue.data[queue.front++];
    afterState.front = queue.front;
    afterState.rear = queue.rear;
    afterState.type = 1;
    showOperationResult("DELETE QUEUE", value, 1);
    return value;
}

void showQueue() {
    showProgramHeader("QUEUE STATUS");
    int count = isQueueEmpty() ? 0 : (queue.rear - queue.front + 1);

    printf("Capacity : %d\n", MAX_SIZE);
    printf("Data : %d\n", count);
    printf("Front : %d\n", queue.front);
    printf("Rear : %d\n", queue.rear);
    printf("Status : %s\n", isQueueEmpty() ? "EMPTY" : "NORMAL");
    showSeparator();

    if (isQueueEmpty()) {
        printf("Queue is empty.\n");
    } else {
        printf("Index : ");
        for (int i = 0; i < MAX_SIZE; i++) {
            printf("%d ", i);
        }
        printf("\nData  : ");
        for (int i = 0; i < MAX_SIZE; i++) {
            if (i >= queue.front && i <= queue.rear) {
                printf("[%d] ", queue.data[i]);
            } else {
                printf("[ ] ");
            }
        }
        printf("\n       ");
        for (int i = 0; i < MAX_SIZE; i++) {
            if (i == queue.front) printf("F ");
            else if (i == queue.rear) printf("R ");
            else printf("  ");
        }
        printf("\n");
        showSeparator();

        printf("Order : ");
        for (int i = queue.front; i <= queue.rear; i++) {
            printf("%d", queue.data[i]);
            if (i < queue.rear) printf(" -> ");
        }
        printf("\n");
    }
    showSeparator();
}

void clearQueue() {
    initQueue();
    printf("\nQueue cleared!\n");
}

// ========== Stack Menu ==========
void stackMenu() {
    int choice = 0;

    while (1) {
        showProgramHeader("STACK MENU");
        printf("1. Push\n2. Pop\n3. Show Stack\n4. Clear Stack\n0. Back to Main Menu\n");
        showSeparator();
        printf("Select menu: ");

        if (scanf("%d", &choice) != 1) {
            printf("Please input number!!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                int value = getStackInput();
                if (value != -9999) {
                    push(value);
                }
                break;
            }
            case 2:
                pop();
                break;
            case 3:
                showStack();
                break;
            case 4:
                clearStack();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

// ========== Queue Menu ==========
void queueMenu() {
    int choice = 0;

    while (1) {
        showProgramHeader("QUEUE MENU");
        printf("1. Insert\n2. Delete\n3. Show Queue\n4. Clear Queue\n0. Back to Main Menu\n");
        showSeparator();
        printf("Select menu: ");

        if (scanf("%d", &choice) != 1) {
            printf("Please input number!!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                int value = getQueueInput();
                if (value != -9999) {
                    insertQueue(value);
                }
                break;
            }
            case 2:
                deleteQueue();
                break;
            case 3:
                showQueue();
                break;
            case 4:
                clearQueue();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

// ========== Main ==========
int main() {
    int choose = 0;

    initStack();
    initQueue();

    while (1) {
        showProgramHeader("STACK AND QUEUE PROGRAM");
        printf("1. Stack\n2. Queue\n0. Exit\n");
        showSeparator();
        printf("Select menu: ");

        if (scanf("%d", &choose) != 1) {
            printf("Please input number!!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choose) {
            case 1:
                stackMenu();
                break;
            case 2:
                queueMenu();
                break;
            case 0:
                printf("\nExit program\n");
                return 0;
            default:
                printf("Choose -> %d Not in range (0-2)\n", choose);
        }
    }

    return 0;
}
