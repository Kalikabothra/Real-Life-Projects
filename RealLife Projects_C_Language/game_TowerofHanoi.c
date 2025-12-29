#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure
typedef struct {
    int items[MAX];
    int top;
} Stack;

// Function prototypes
void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);
int peek(Stack *s);
void displayTowers(Stack towers[], int n);
int isValidMove(Stack *from, Stack *to);
void moveDisk(Stack *from, Stack *to, char fromName, char toName, int *moves);
void solveHanoi(int n, Stack *source, Stack *auxiliary, Stack *destination, 
                char s, char a, char d, int *moves);
void playManual(Stack towers[], int n);
void playAutomatic(Stack towers[], int n);

int main() {
    int choice, n;
    Stack towers[3];
    
    printf("\n========================================\n");
    printf("    TOWER OF HANOI GAME\n");
    printf("========================================\n");
    
    // Get number of disks
    printf("\nEnter number of disks (1-8): ");
    scanf("%d", &n);
    
    if (n < 1 || n > 8) {
        printf("Invalid number! Using 3 disks.\n");
        n = 3;
    }
    
    // Initialize all three towers (stacks)
    for (int i = 0; i < 3; i++) {
        initStack(&towers[i]);
    }
    
    // Place all disks on Tower A (largest at bottom)
    for (int i = n; i >= 1; i--) {
        push(&towers[0], i);
    }
    
    printf("\n========================================\n");
    printf("GAME RULES:\n");
    printf("1. Move all disks from Tower A to Tower C\n");
    printf("2. Only one disk can be moved at a time\n");
    printf("3. Larger disk cannot be placed on smaller disk\n");
    printf("4. You can use Tower B as auxiliary\n");
    printf("========================================\n");
    
    printf("\nChoose mode:\n");
    printf("1. Manual Mode (You play)\n");
    printf("2. Automatic Mode (Computer solves)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    printf("\nInitial State:\n");
    displayTowers(towers, n);
    
    if (choice == 1) {
        playManual(towers, n);
    } else {
        playAutomatic(towers, n);
    }
    
    return 0;
}

// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Push element onto stack
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->items[++(s->top)] = value;
}

// Pop element from stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->items[(s->top)--];
}

// Peek top element of stack
int peek(Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->items[s->top];
}

// Display all three towers
void displayTowers(Stack towers[], int n) {
    printf("\n");
    
    // Display from top to bottom
    for (int level = n - 1; level >= 0; level--) {
        for (int tower = 0; tower < 3; tower++) {
            if (level <= towers[tower].top) {
                int disk = towers[tower].items[level];
                printf("   ");
                for (int i = 0; i < disk; i++) printf("*");
                printf("%d", disk);
                for (int i = 0; i < disk; i++) printf("*");
                printf("   ");
            } else {
                printf("     |     ");
            }
            printf("    ");
        }
        printf("\n");
    }
    
    // Base
    printf("  =========    =========    =========\n");
    printf("   Tower A      Tower B      Tower C\n\n");
}

// Check if move is valid
int isValidMove(Stack *from, Stack *to) {
    if (isEmpty(from)) {
        return 0; // Cannot move from empty tower
    }
    
    if (isEmpty(to)) {
        return 1; // Can move to empty tower
    }
    
    // Check if top disk of 'from' is smaller than top disk of 'to'
    return peek(from) < peek(to);
}

// Move disk from one tower to another
void moveDisk(Stack *from, Stack *to, char fromName, char toName, int *moves) {
    int disk = pop(from);
    push(to, disk);
    (*moves)++;
    printf("Move %d: Disk %d from Tower %c to Tower %c\n", *moves, disk, fromName, toName);
}

// Recursive function to solve Tower of Hanoi
void solveHanoi(int n, Stack *source, Stack *auxiliary, Stack *destination,
                char s, char a, char d, int *moves) {
    if (n == 1) {
        moveDisk(source, destination, s, d, moves);
        return;
    }
    
    // Move n-1 disks from source to auxiliary using destination
    solveHanoi(n - 1, source, destination, auxiliary, s, d, a, moves);
    
    // Move the largest disk from source to destination
    moveDisk(source, destination, s, d, moves);
    
    // Move n-1 disks from auxiliary to destination using source
    solveHanoi(n - 1, auxiliary, source, destination, a, s, d, moves);
}

// Manual play mode
void playManual(Stack towers[], int n) {
    int moves = 0;
    int from, to;
    int minMoves = (1 << n) - 1; // 2^n - 1
    
    printf("\nMinimum moves required: %d\n", minMoves);
    printf("\nTower numbers: A=1, B=2, C=3\n");
    
    while (towers[2].top != n - 1) { // While Tower C doesn't have all disks
        printf("\nEnter move (from to) [e.g., 1 3]: ");
        scanf("%d %d", &from, &to);
        
        from--; to--; // Convert to 0-indexed
        
        if (from < 0 || from > 2 || to < 0 || to > 2) {
            printf("Invalid tower number! Use 1, 2, or 3.\n");
            continue;
        }
        
        if (from == to) {
            printf("Source and destination cannot be same!\n");
            continue;
        }
        
        if (!isValidMove(&towers[from], &towers[to])) {
            printf("Invalid move! ");
            if (isEmpty(&towers[from])) {
                printf("Source tower is empty.\n");
            } else {
                printf("Cannot place larger disk on smaller disk.\n");
            }
            continue;
        }
        
        moveDisk(&towers[from], &towers[to], 'A' + from, 'A' + to, &moves);
        displayTowers(towers, n);
    }
    
    printf("\n========================================\n");
    printf("🎉 CONGRATULATIONS! YOU WON! 🎉\n");
    printf("========================================\n");
    printf("Your moves: %d\n", moves);
    printf("Minimum moves: %d\n", minMoves);
    
    if (moves == minMoves) {
        printf("PERFECT! You solved it optimally! ⭐\n");
    } else {
        printf("You took %d extra moves.\n", moves - minMoves);
    }
}

// Automatic solve mode
void playAutomatic(Stack towers[], int n) {
    int moves = 0;
    
    printf("\nSolving automatically...\n");
    printf("Press Enter to see each move...\n");
    getchar(); // Clear buffer
    
    solveHanoi(n, &towers[0], &towers[1], &towers[2], 'A', 'B', 'C', &moves);
    
    printf("\nFinal State:\n");
    displayTowers(towers, n);
    
    printf("\n========================================\n");
    printf("✅ SOLVED!\n");
    printf("========================================\n");
    printf("Total moves: %d\n", moves);
    printf("This is the optimal solution!\n");
}