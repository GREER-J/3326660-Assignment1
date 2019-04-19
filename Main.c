
#include <stdio.h>
#include <stdlib.h>


//Caesar Prototypes


char caesar_do_translation(char letter, char key);
void caesar_encode(char *message, int msg_size, char key, char *translated);
void caesar_decode(char *message, int msg_size, char key, char *translated);
void do_caesar_cipher(char *message, int msg_size, char key, char mode);

//Substitution Prototypes
char encode_substitution(char letter, char *key);
char * do_encode_substitution(char *message, char * key, int size);

//Menu Prototypes
char get_input(void);
void output(char *message, int msg_size);


//Main
int main(){
    char message[] = "TEST";
    int msg_size = sizeof(message) / sizeof(message[0]) - 1;
    int key = 11;
    char translated[msg_size];

    do_caesar_cipher(message, msg_size, key, 1);

    //get_input();
    return 0;
}

/********************************   CAESAR CIPHER *******************************/

/******************************   Encode / Decode    ************************************/


char caesar_do_translation(char letter, char key){
    char translated = ((((letter - 65) +260) + (key % 26)) % 26) + 65;
    return translated;
}

void caesar_encode(char *message, int msg_size, char key, char *translated){
    char i;
    for(i = 0; i < msg_size; i++){
        translated[i] =  caesar_do_translation(message[i], key);
    }
}

void caesar_decode(char *message, int msg_size, char key, char *translated){
    char i;
    for(i = 0; i < msg_size; i++){
        translated[i] =  caesar_do_translation(message[i], (-1 * key));
    }
}

void do_caesar_cipher(char *message, int msg_size, char key, char mode){
    char translated[msg_size];
    if(mode ==1){
        caesar_encode(message, msg_size, key, translated);
    }
    else if(mode == 2){
        caesar_decode(message, msg_size, key, translated);
    }
    output(translated, msg_size);
}



/********************************   Attack Caeser cipher *******************************/

/*
char do_casesar_brute_force(void){
    //Setup

    char known_text[] = "test";
    char known_cipher[4];

    //Implement random key
    int key = 16;
    int size = 4;

    int i;
    for(i = 0; i < size; i++){
        
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
*/


/********************************   SUBSTITUTION CIPHER *******************************/


/********************************   Encode Substitution cipher *******************************/

char encode_substitution(char letter, char *key){
    //Substitution cipher
    if (letter > 64){
        letter -= 65;
        char encoded = key[letter];
        return encoded;
    }
    else{
        return letter;
    }
}


/********************************   Do Encode Substitution cipher *******************************/

char * do_encode_substitution(char *message, char * key, int size){
    static char encoded[14];
    char i;
    for(i = 0; i < size; i++){
        encoded[i] = encode_substitution(message[i], key);
    }
    return encoded;
}




/********************************  MENU FUNCTIONS *******************************/

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


void output(char *message, int msg_size){
    char i;
    for(i = 0; i < msg_size; i++){
        printf("%c", message[i]);
    }
}
