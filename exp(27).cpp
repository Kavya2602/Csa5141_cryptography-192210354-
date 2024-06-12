#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to compute the modular exponentiation (base^exp % mod)
unsigned long mod_exp(unsigned long base, unsigned long exp, unsigned long mod) {
    unsigned long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to encrypt a single character
unsigned long encrypt_char(char c, unsigned long e, unsigned long n) {
    unsigned long m = (unsigned long)(toupper(c) - 'A');
    return mod_exp(m, e, n);
}

// Function to decrypt a single character using brute-force attack
char decrypt_char(unsigned long ciphertext, unsigned long e, unsigned long n) {
    for (unsigned long m = 0; m < 26; m++) {
        if (mod_exp(m, e, n) == ciphertext) {
            return (char)(m + 'A');
        }
    }
    return '?';  // Should never reach here if ciphertext is valid
}

int main() {
    unsigned long n, e;
    char message[100], encrypted_message[100];
    unsigned long ciphertexts[100];
    int i;

    // Example values for public key (n, e)
    n = 3233;  // A large prime product for demonstration
    e = 17;    // Public exponent

    // Input the message to encrypt
    printf("Enter a message to encrypt (only alphabetic characters): ");
    scanf("%s", message);

    // Encrypt each character in the message
    for (i = 0; message[i] != '\0'; i++) {
        ciphertexts[i] = encrypt_char(message[i], e, n);
        encrypted_message[i] = (char)ciphertexts[i];
    }
    encrypted_message[i] = '\0';

    // Display the encrypted message
    printf("Encrypted message: ");
    for (i = 0; encrypted_message[i] != '\0'; i++) {
        printf("%lu ", ciphertexts[i]);
    }
    printf("\n");

    // Decrypt the message using brute-force attack
    printf("Decrypted message: ");
    for (i = 0; encrypted_message[i] != '\0'; i++) {
        printf("%c", decrypt_char(ciphertexts[i], e, n));
    }
    printf("\n");

    return 0;
}
