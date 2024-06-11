#include <stdio.h>
#include <string.h>

char decode_char(char a, char b) {
    char key[5][5] = { {'P', 'L', 'A', 'Y', 'F'}, {'I', 'R', 'E', 'X', 'M'},
                       {'B', 'C', 'D', 'G', 'H'}, {'K', 'N', 'O', 'Q', 'S'},
                       {'T', 'U', 'V', 'W', 'Z'} };
    int r1, c1, r2, c2, i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++) {
            if (key[i][j] == a) { r1 = i; c1 = j; }
            if (key[i][j] == b) { r2 = i; c2 = j; }
        }
    if (r1 == r2) return key[r1][(c1 + 4) % 5] + key[r2][(c2 + 4) % 5];
    if (c1 == c2) return key[(r1 + 4) % 5][c1] + key[(r2 + 4) % 5][c2];
    return key[r1][c2] + key[r2][c1];
}

int main() {
    char message[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPO???????NTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char decoded[100];
    int len = strlen(message), i;

    for (i = 0; i < len; i += 2)
        strcat(decoded, decode_char(message[i], message[i + 1]));

    printf("Decoded message: %s\n", decoded);
    return 0;
}
