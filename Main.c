#include <stdio.h>

//Prototypes
char translate(char letter, char key);
char encode(char letter, char key);
char decode(char letter, char key);
char get_input(void);

//Main
int main(){
    /*
    char message, key, cipher, plaintext = 0;

    message = 65; // 65 = A, 90 = Z (for testing)
    key = 12;

    cipher = encode(message, key);
    plaintext = decode(cipher, key);

    printf("Message: %c\n", message);
    printf("Ciphertext: %c\n", cipher);
    printf("Plaintext: %c", plaintext);
    */

    get_input();

    return 0;
}
/******************************   Encode / Decode    ************************************/

char do_translation(char letter, char key){
    char translated = ((((letter - 65) +260) + (key % 26)) % 26) + 65;
    return translated;
}

char encode(char letter, char key){
    return do_translation(letter, key);
}


char decode(char letter, char key){
    return do_translation(letter, (-1 *key));
}

/********************************   Get input from user *******************************/

char get_input(void){
    char message[100];
    printf("Please enter your message: ");
    scanf("%s\ns", message);

    printf("%s", message); 
    return 0;
}
