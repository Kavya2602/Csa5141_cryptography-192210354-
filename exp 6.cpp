#include <stdio.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void decryptAffineCipher(int a, int b, char ciphertext[]) {
    int m = 26; // Modulus for the alphabet
    int a_inv = modInverse(a, m);
    
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int c = ciphertext[i] - 'A';
            int plain = (a_inv * (c - b + m)) % m;
            printf("%c", plain + 'A');
        } else {
            printf("%c", ciphertext[i]);
        }
    }
}

int main() {
    char ciphertext[] = "YOUR_CIPHERTEXT_HERE"; // Replace with your actual ciphertext
    int a = 5; // Assuming 'B' corresponds to 'E' implies a = 5
    int b = 4; // Assuming 'B' corresponds to 'E' implies b = 4

    decryptAffineCipher(a, b, ciphertext);

    return 0;
}


