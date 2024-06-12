#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 16  // Block size in bytes (128 bits)

// Mock block cipher function (for illustration purposes)
void mock_block_cipher_encrypt(uint8_t *block, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

void mock_block_cipher_decrypt(uint8_t *block, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];  // Since it's XOR, encrypt and decrypt are the same
    }
}

// ECB Mode
void ecb_mode(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
        mock_block_cipher_encrypt(ciphertext + i, key);
    }
}

// CBC Mode
void cbc_mode(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, int length) {
    uint8_t buffer[BLOCK_SIZE];
    memcpy(buffer, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            buffer[j] ^= plaintext[i + j];
        }
        mock_block_cipher_encrypt(buffer, key);
        memcpy(ciphertext + i, buffer, BLOCK_SIZE);
    }
}

// CFB Mode
void cfb_mode(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, int length) {
    uint8_t buffer[BLOCK_SIZE];
    memcpy(buffer, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        mock_block_cipher_encrypt(buffer, key);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ buffer[j];
            buffer[j] = ciphertext[i + j];  // Feedback for next block
        }
    }
}

// Padding function
void pad_plaintext(uint8_t *plaintext, int *length) {
    int pad_length = BLOCK_SIZE - (*length % BLOCK_SIZE);
    for (int i = 0; i < pad_length; i++) {
        plaintext[*length + i] = (i == 0) ? 0x80 : 0x00;  // 1 bit followed by 0 bits
    }
    *length += pad_length;
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x00};  // Simple key for demonstration
    uint8_t iv[BLOCK_SIZE] = {0x00};   // Initialization Vector for CBC and CFB
    uint8_t plaintext[64] = "This is a secret message. It needs to be encrypted.";  // Example plaintext
    int length = strlen((char *)plaintext);

    // Pad the plaintext to be a multiple of the block size
    pad_plaintext(plaintext, &length);

    uint8_t ciphertext_ecb[64] = {0};
    uint8_t ciphertext_cbc[64] = {0};
    uint8_t ciphertext_cfb[64] = {0};

    // ECB Mode
    ecb_mode(plaintext, key, ciphertext_ecb, length);
    // CBC Mode
    cbc_mode(plaintext, key, iv, ciphertext_cbc, length);
    // CFB Mode
    cfb_mode(plaintext, key, iv, ciphertext_cfb, length);

    printf("ECB Ciphertext: ");
    for (int i = 0; i < length; i++) printf("%02x ", ciphertext_ecb[i]);
    printf("\n");

    printf("CBC Ciphertext: ");
    for (int i = 0; i < length; i++) printf("%02x ", ciphertext_cbc[i]);
    printf("\n");

    printf("CFB Ciphertext: ");
    for (int i = 0; i < length; i++) printf("%02x ", ciphertext_cfb[i]);
    printf("\n");

    return 0;
}
