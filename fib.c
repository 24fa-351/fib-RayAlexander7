#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to calculate Fibonacci number using iterative method
unsigned long long fib_iterative(int n) {
    unsigned long long a = 0, b = 1, next;

    if (n == 0)
        return a;
    for (int i = 2; i <= n; i++) {
        next = a + b;
        a = b;
        b = next;
    }
    return b;
}

// Function to calculate Fibonacci number using recursive method
unsigned long long fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main(int argc, char *argv[]) {
    // Ensure correct number of arguments
    if (argc != 4) {
        printf("Usage: %s <integer> <r/i> <filename>\n", argv[0]);
        return 1;
    }

    // Parse first argument as an integer
    int first_number = atoi(argv[1]);

    // Open the file to read the second number
    FILE *file = fopen(argv[3], "r");  
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the integer from the file
    int second_number;
    fscanf(file, "%d", &second_number);
    fclose(file);

    // Calculate the sum of the two numbers
    int N = first_number + second_number;

    // Record the start time
    clock_t start_time = clock();

    // Determine the method: recursive or iterative
    unsigned long long fibonacci_number;
    if (argv[2][0] == 'r') {
        fibonacci_number = fib_recursive(N);
    } else if (argv[2][0] == 'i') {
        fibonacci_number = fib_iterative(N);
    } else {
        printf("Invalid option for Fibonacci calculation method. Use 'r' for recursive or 'i' for iterative.\n");
        return 1;
    }

    // Record the end time
    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Output the result
    printf("The %dth Fibonacci number is: %llu\n", N, fibonacci_number);
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}

