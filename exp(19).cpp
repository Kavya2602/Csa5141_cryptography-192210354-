#include <stdio.h>
#include <string.h>


void handleErrors(void) {
  
 
int main()  
     
    // Key and IV setup
    DES_cblock key1, key2, key3;
    DES_key_schedule ks1, ks2, ks3;
    DES_cblock ivec;
    unsigned char indata[8], outdata[8], cbc_in[8], cbc_out[8];
    int n;

    // Sample key data
    DES_string_to_key("key1", &key1);
    DES_string_to_key("key2", &key2);
    DES_string_to_key("key3", &key3);
    
    // Initialize keys
    DES_set_key_checked(&key1, &ks1);
    DES_set_key_checked(&key2, &ks2);
    DES_set_key_checked(&key3, &ks3);

    // Initialization Vector (IV)
    memset(ivec, 0, sizeof(ivec));

    // Sample plaintext
    unsigned char plaintext[] = "This is a test message.";

    // Pad plaintext to be a multiple of 8 bytes
    int len = strlen((const char*)plaintext);
    int padded_len = ((len / 8) + 1) * 8;
    unsigned char padded_plaintext[padded_len];
    memset(padded_plaintext, 0, padded_len);
    memcpy(padded_plaintext, plaintext, len);

    // Encrypt
    printf("Plaintext: %s\n", plaintext);
    for (int i = 0; i < padded_len; i += 8) {
        memcpy(indata, padded_plaintext + i, 8);
        DES_ede3_cbc_encrypt(indata, outdata, 8, &ks1, &ks2, &ks3, &ivec, DES_ENCRYPT);
        memcpy(padded_plaintext + i, outdata, 8);
    }

    printf("Ciphertext (in hex): ");
    for (int i = 0; i < padded_len; i++) {
        printf("%02x", padded_plaintext[i]);
    }
    printf("\n");

    // Reset IV for decryption
    memset(ivec, 0, sizeof(ivec));

    // Decrypt
    for (int i = 0; i < padded_len; i += 8) {
        memcpy(indata, padded_plaintext + i, 8);
        DES_ede3_cbc_encrypt(indata, outdata, 8, &ks1, &ks2, &ks3, &ivec, DES_DECRYPT);
        memcpy(padded_plaintext + i, outdata, 8);
    }

    printf("Decrypted text: %s\n", padded_plaintext);

    return 0;
}=

