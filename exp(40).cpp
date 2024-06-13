
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>



#define ALPHABET_SIZE 26



// Function to calculate letter frequencies in a string

void calculate_letter_frequency(const char *text, int *frequency) {

    for (int i = 0; text[i] != '\0'; i++) {

        if (isalpha(text[i])) {

            int index = tolower(text[i]) - 'a';

            frequency[index]++;

        }

    }

}



// Function to decrypt a ciphertext using a given key

void decrypt_with_key(const char *ciphertext, const int *key, char *plaintext) {

    for (int i = 0; ciphertext[i] != '\0'; i++) {

        if (isalpha(ciphertext[i])) {

            char base_char = islower(ciphertext[i]) ? 'a' : 'A';

            int index = tolower(ciphertext[i]) - 'a';

            plaintext[i] = key[index] + base_char;

        } else {

            plaintext[i] = ciphertext[i];

        }

    }

    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the string

}



// Function to find the index of the most frequent letter in the frequency array

int find_most_frequent_letter(const int *frequency) {

    int max_freq = 0;

    int max_index = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {

        if (frequency[i] > max_freq) {

            max_freq = frequency[i];

            max_index = i;

        }

    }

    return max_index;

}



// Function to decrypt ciphertext using a simple letter frequency attack

void letter_frequency_attack(const char *ciphertext, char *plaintext) {

    int frequency[ALPHABET_SIZE] = {0};

    calculate_letter_frequency(ciphertext, frequency);



    // Find the most frequent letter in the ciphertext

    int most_frequent_index = find_most_frequent_letter(frequency);



    // Calculate the key based on the shift required to convert the most frequent letter to 'e' (assuming English plaintext)

    int key[ALPHABET_SIZE];

    int shift = (most_frequent_index + ALPHABET_SIZE - ('e' - 'a')) % ALPHABET_SIZE;

    for (int i = 0; i < ALPHABET_SIZE; i++) {

        key[i] = (i - shift + ALPHABET_SIZE) % ALPHABET_SIZE;

    }



    // Decrypt ciphertext using the calculated key

    decrypt_with_key(ciphertext, key, plaintext);

}



int main() {

    const char *ciphertext = "Gwc uivioml bw nqvl bpm zqopb apqnb"; // Example ciphertext

    char plaintext[100]; // Make sure it's large enough to hold the decrypted text



    // Perform letter frequency attack

    letter_frequency_attack(ciphertext, plaintext);



    // Output the decrypted text

    printf("Decrypted plaintext: %s\n", plaintext);

    

    return 0;

}
