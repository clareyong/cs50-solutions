#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void) {
    int result = 0;

    int number = get_int("Enter a positive integer: ");
    printf("%i\n", number);
    //scanf("%d", &number);

    result = collatz(number);

    printf("Collatz = %i\n", result);
    return 0;
}

int collatz(int n) {
    if (n == 1)
    {
        return 0;
    }
    else if ((n%2) == 0)
    {
        return 1+collatz(n/2);;
    }
    else
    {
        return 1+collatz(3*n+1);
    }
}

// int collatz(int n) {
//     if (n/2 != 0 && n != 1)
//     {
//         // sum() function calls itself
//         printf("%i", collatz(3*n+1));
//         return collatz(3*n+1);
//     }
//     else if (n/2 == 0 && n != 1)
//     {
//         printf("%i", collatz(n/2));
//         return collatz(n/2);
//     }
//     else
//         return n;
// }