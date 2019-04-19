/*
RUNNING WISH LIST:
    1. Edit do_caesar_cipher_test such that is passes encode and decode instead of hardcoding them in those functions
    2. Create size of function to make for loops neater / easier -- Use <type thingy>/
*/


#include <stdio.h>
#include <stdlib.h>

//Prototypes
char translate(char letter, char key);
char encode(char letter, char key);
char decode(char letter, char key);
char get_input(void);
int do_caesar_cipher_test(void);
int do_caesar_encode_test(void);
int do_caesar_decode_test(void);
char do_casesar_brute_force(void);
char encode_substitution(char *message, char *key);

//Main
int main(){

    
    char key[] = "phqgiumeaylnofdxjkrcvstzwb";
    char text[] = "TEST MESSAGE";

    encode_substitution(text, key);
    //Testing
    //do_caesar_cipher_test();
    //get_input();

    //do_casesar_brute_force();

    return 0;
}

/******************************   Encode / Decode    ************************************/

/*  This funciton implements the actual math of the cipher.
INPUTS: the letter to be encoded or decoded as a char (ascii number) ; key - number to be shifted by
CALCULATION: 
                1) takes the given letter and takes away 65. This translates the letter to it's position from a capital A (65 in ascii)
                2) Adds 260 to ensure that the total is alays positive, yet does not effect the % command later
                3) Takes the result of the key % 26 (to try account any number key) and adds this to the result from 2
                4) Takes this whole thing and % 26, this will gives an ajusted distance from A
                5) Add 65 to turn it back into ascii text
                6) Returns this value
OUTPUT: The letter shifted by the key value in ascii code
*/

char do_translation(char letter, char key){
    char translated = ((((letter - 65) +260) + (key % 26)) % 26) + 65;
    return translated;
}

/* This function utilises the previous function to encode a given letter with a given key
INPUT: A letter to encrypt (given in ascii code) ; a key - the number of letter to shift by
CALCULATION:
                1) Calls the do_translation() function and passes the given key and letter
                2) Returns the output of do_translation() to the program
OUTPUT: The letter shifted by the given key value in ascii code
*/
char encode(char letter, char key){
    return do_translation(letter, key);
}


/* This function utilises the do_translation function to decode a given letter with a given key
INPUT: A letter to decrypt (given in ascii code) ; a key - the number of letter to shift by
CALCULATION:
                1) The given key is * by -1 to put a negative sign in front of it
                2) Calls the do_translation() function and passes the given key and letter
                3) Returns the output of do_translation() to the program
OUTPUT: The letter shifted by the given key value in ascii code
*/
char decode(char letter, char key){
    return do_translation(letter, (-1 * key));
}

/********************************   Get input from user *******************************/

char get_input(void){
    char message[100];
    printf("Please enter your message: ");
    scanf("%s\ns", message);

    //For testing
    /*THIS CURRENTLY DOESN'T WORK AS IT STOPS PRINTING AT A SPACE*/
    //printf("%[^/n]s", message);

    int i;
    for(i=0; i<10; i++){
        printf("%c", message[i]);
    }
    return 0;
}

/********************************   Test Functions *******************************/
/*  This function gives the encode function a set input and tests the output against an expected output for testing purposes
INPUT: This funciton requires no input
CALCULATION:
*/
int do_caesar_cipher_test(void){
    char first = do_caesar_encode_test();
    char second = do_caesar_decode_test();

    if (first == 1 && second == 1){
        return 1;
        }
    else if (first != 1){
        printf("The encode function failed on %c", first);
    }
    else if (second != 1){
        printf("The decode function failed on %c", second);
    }

return 0;
}

int do_caesar_encode_test(void){
    char key, fail_char = 0;
    char plaintext[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char encoded[] = "LMNOPQRSTUVWXYZABCDEFGHIJK";
    key = 11;

    // While nothing fails the test
    fail_char = -1;
    //Flag set to 100 to indicate full test passed
    while((fail_char <0) && (fail_char != 100)){
    char i;
    
    for(i = 0; i < 26; i++){
        char output = encode(plaintext[i], key);
        
        if (output != encoded[i]){
            fail_char = plaintext[i];
            return fail_char;
        }
        }
        fail_char = 100;
        return 1;
    }

    //Return WTF thing This should never run but it shuts the compiler up.
    return 0;
}


int do_caesar_decode_test(void){
    char key, fail_char = 0;
    char plaintext[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char encoded[] = "LMNOPQRSTUVWXYZABCDEFGHIJK";
    key = 11;

    // While nothing fails the test
    fail_char = -1;
    //Flag set to 100 to indicate full test passed
    while((fail_char <0) && (fail_char != 100)){
    char i;
    
    for(i = 0; i < 26; i++){
        char output = decode(encoded[i], key);
        if (output != plaintext[i]){
            fail_char = plaintext[i];
            return fail_char;
        }
    }
    fail_char = 100;
    return 1;
    }
    return 0;
}

/********************************   Attack Caeser cipher *******************************/
/*
Attack plan for brute force

Setup: encrypt known value "test" with random key
CALCULATION:
            `1) Loop through numbers 1 - 25 with for Loop
                1.5) Decrypt the known cipher text with incremented key
            2) If the decrypt of the known cipher matches the known plaintext then return key
*/

char do_casesar_brute_force(void){
    //Setup

    char known_text[] = "test";
    char known_cipher[4];

    //Implement random key
    int key = 16;

    int i;
    for(i = 0; i < 4; i++){
        
        known_cipher[i] = encode(known_text[i], key);
        printf("%c", known_cipher[i]);
    }

    char k;

    for(k = 0; k < 4; k++){
        char i;
        for(i = 0; i < 26; i++){
            if(encode(known_text[k], i) == known_cipher[k]){
                printf("\nSuccess %d", i);
            }
        }
    }
    return 0;
}

/********************************   SUBSTITUTION CIPHER *******************************/


/********************************   Encode Substitution cipher *******************************/

char encode_substitution(char *message, char *key){
    //Substitution cipher
    char i;
    for(i = 0; i < 12; i++){
        char position = message[i];
        
        if(position > 64){
            position -= 65;
            printf("%c", key[position]);
        }

        else{
            printf("%c", position);
        }
        
    }

    return 0;
}
