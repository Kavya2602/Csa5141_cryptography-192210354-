#include <stdio.h>

// Function to calculate Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to check if a number is co-prime with 26
int isCoPrime(int num) {
    return gcd(num, 26) == 1;
}

// Function to determine allowed values of 'a'
void findAllowedA() {
    printf("Allowed values of 'a': ");
    for (int a = 1; a < 26; a++) {
        if (isCoPrime(a)) {
            printf("%d ", a);
        }
    }
    printf("\n");
}

int main() {
    printf("Limitations on the affine Caesar cipher:\n");

    printf("a. Limitations on the value of 'b':\n");
    printf("   'b' must be co-prime with 26 (no common factors other than 1).\n");
    printf("   Values of 'b' not divisible by 2 or 13 are allowed.\n");

    printf("\nb. Determine which values of 'a' are not allowed:\n");
    printf("   'a' must be co-prime with 26 (no common factors other than 1).\n");
    printf("   Allowed values of 'a': 1 3 5 7 9 11 15 17 19 21 23 25\n");

    return 0;
}

