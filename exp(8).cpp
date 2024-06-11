#include <stdio.h>
#include <string.h>

int main() {
    char plain[] = "abcdefghijklmnopqrstuvwxyz";
    char cipher[] = "CIPHERABDFGJKLMNOQSTUVWXYZ";
    char text[] = "hello";
    for (int i = 0; i < strlen(text); i++)
        for (int j = 0; j < 26; j++)
            if (text[i] == plain[j]) {
                text[i] = cipher[j];
                break;
            }
    printf("Ciphered text: %s\n", text);
    return 0;
}
