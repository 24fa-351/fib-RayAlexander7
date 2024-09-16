#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the size of the memoization array (you can increase this based on need)
#define MAX_FIB 1000

// Memoization array for the recursive method
unsigned long long memo[MAX_FIB];

// Function to calculate Fibonacci number using iterative method
unsigned long long fib_iterative_wrapper(int n) {
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

// Function to calculate Fibonacci number using recursive method with memoization
unsigned long long fib_recursive_memo(int n) {
    if (memo[n] != 0)
        return memo[n];

    if (n <= 1)
        return n;

    memo[n] = fib_recursive_memo(n - 1) + fib_recursive_memo(n - 2);
    return memo[n];
}

// Wrapper for the recursive method
unsigned long long fib_recursive_wrapper(int n) {
    // Initialize memoization array with 0s
    for (int i = 0; i <= n; i++) {
        memo[i] = 0;
    }

    return fib_recursive_memo(n);
}

// Optional: Function pointer wrapper to call the appropriate Fibonacci function
unsigned long long fib_wrapper(unsigned long long (*fib_func)(int), int n) {
    return fib_func(n);
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
        fibonacci_number = fib_wrapper(fib_recursive_wrapper, N);
    } else if (argv[2][0] == 'i') {
        fibonacci_number = fib_wrapper(fib_iterative_wrapper, N);
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


