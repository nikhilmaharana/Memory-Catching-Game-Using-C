#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>  // For Windows sleep function
#else
#include <unistd.h>   // For UNIX sleep function
#endif

#define MAX_STACK_SIZE 10 // Define maximum size of the stack

// Stack structure
typedef struct {
    int arr[MAX_STACK_SIZE];
    int top;
} Stack;

// Function to initialize the stack
void initStack(Stack *stack) {
    stack->top = -1;  // Stack is initially empty
}

// Function to check if the stack is full
int isFull(Stack *stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

// Function to check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;  // Return -1 if stack is empty
    }
    return stack->arr[stack->top--];
}

// Function to generate a random number between 1 and 9
int generateRandomNumber() {
    return rand() % 9 + 1;
}

// Function to pause execution for a specified number of seconds (cross-platform)
void pauseForSeconds(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);  // Windows Sleep works in milliseconds
#else
    sleep(seconds);         // UNIX sleep works in seconds
#endif
}

// Function to play the memory-catching game
void playGame() {
    Stack stack;
    initStack(&stack);

    int sequenceLength = 5; // Length of the sequence to memorize
    int score = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Step 1: Generate a random sequence and push it onto the stack
    printf("Generating sequence...\n");
    int i;
    for (i = 0; i < sequenceLength; i++) {
        int num = generateRandomNumber();
        push(&stack, num);
    }

    // Step 2: Display the sequence to the user
    printf("\nMemorize this sequence:\n");
    for (i = sequenceLength - 1; i >= 0; i--) {
        printf("%d ", stack.arr[i]);  // Print numbers from the stack (in the correct order)
    }
    printf("\n");

    // Give the user a few seconds to memorize the sequence
    printf("Memorize the sequence! (pause for 3 seconds)\n");
    pauseForSeconds(3);  // Wait for 3 seconds

    // Clear the screen (optional, to hide the sequence after the pause)
    printf("\033[H\033[J"); // This works in UNIX/Linux/macOS terminals
    // On Windows, use: system("cls");

    // Step 3: Ask the player to recall the sequence
    printf("\nRecall the sequence by entering the numbers in the correct order:\n");

    // Step 4: Player inputs numbers to pop from the stack
    for (i = 0; i < sequenceLength; i++) {
        int guess;
        printf("Enter your guess: ");
        scanf("%d", &guess);

        int correctValue = pop(&stack);
        if (guess == correctValue) {
            score++;
            printf("Correct! Score: %d\n", score);
        } else {
            printf("Incorrect! Game Over. Final Score: %d\n", score);
            return; // Game over on incorrect guess
        }
    }

    printf("Congratulations! You completed the sequence correctly with a final score of: %d\n", score);
}

int main() {
    printf("Welcome to the Memory Catching Game!\n");
    playGame();
    getch();
    return 0;
}