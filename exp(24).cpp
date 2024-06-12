#include <stdio.h>
int gcd(int a, int b) {
 if (b == 0)
 return a;
 return gcd(b, a % b);
}
int extendedGCD(int a, int b, int *x, int *y) {
 if (b == 0) {
 *x = 1;
 *y = 0;
 return a;
 }
 int x1, y1;
 int gcd = extendedGCD(b, a % b, &x1, &y1);
 *x = y1;
 *y = x1 - (a / b) * y1;
 return gcd;
}
int modInverse(int a, int m) {
 int x, y;
 int gcd = extendedGCD(a, m, &x, &y);
 if (gcd != 1) {
 printf("Inverse do#include <stdio.h>
#include <stdlib.h>

// Function to compute gcd
unsigned long gcd(unsigned long a, unsigned long b) {
    while (b != 0) {
        unsigned long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute modular inverse using Extended Euclidean Algorithm
unsigned long mod_inverse(unsigned long e, unsigned long phi) {
    long t = 0, newt = 1;
    long r = phi, newr = e;
    while (newr != 0) {
        long quotient = r / newr;
        long temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    if (r > 1) return -1;  // e is not invertible
    if (t < 0) t += phi;
    return t;
}

int main() {
    unsigned long n, e, known_plaintext, p, q, phi, d;

    // Assuming these values are given
    printf("Enter value of n (product of two primes p and q): ");
    scanf("%lu", &n);
    printf("Enter value of e (public exponent): ");
    scanf("%lu", &e);
    printf("Enter known plaintext block that has a common factor with n: ");
    scanf("%lu", &known_plaintext);

    // Compute gcd of the known plaintext and n
    unsigned long gcd_result = gcd(known_plaintext, n);
    if (gcd_result == 1) {
        printf("No common factor found with n.\n");
        return 1;
    }

    // gcd_result should be either p or q
    p = gcd_result;
    q = n / p;
    printf("Found prime factors p: %lu and q: %lu\n", p, q);

    // Compute phi(n)
    phi = (p - 1) * (q - 1);

    // Compute private key d
    d = mod_inverse(e, phi);
    if (d == (unsigned long)-1) {
        printf("Error computing modular inverse. e may not be invertible.\n");
        return 1;
    }

    printf("The private key d is: %lu\n", d);
    return 0;
}es not exist.\n");
 return -1;
 }
 int result = (x % m + m) % m;
 return result;
}
int main() {
 int e = 31;
 int n = 3599;
 int p, q;
 for (p = 2; p <= n; p++) {
 if (n % p == 0) {
 q = n / p;
 break;
 }
 }
 int phi_n = (p - 1) * (q - 1);
 int d = modInverse(e, phi_n);
 printf("Private key d: %d\n", d);
 return 0;
}
