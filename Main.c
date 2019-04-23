
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Caesar Prototypes
char caesar_do_translation(char letter, char key);
void caesar_encode(char *message, int msg_size, char key, char *translated);
void caesar_decode(char *message, int msg_size, char key, char *translated);
void do_caesar_cipher(char *message, int msg_size, char key, char mode);
void do_casesar_brute_force(void);
int caesar_get_key(void);


//Substitution Prototypes
void substitution_encode(char *message, int msg_size, char *key, char *translated);
void substitution_decode(char *message, int msg_size, char *key, char *translated);
void do_substitution_cipher(char *message, int msg_size, char *key, char mode);

//Menu Prototypes
int get_input(char *message);
void output(char *message, int msg_size);
void sanitize(char *message, int msg_size);
void menu(void);


//Main
int main(){
    menu();

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

        if(message[i] >= 65 && message[i] <= 90){
            translated[i] =  caesar_do_translation(message[i], key);
        }
        else{
            translated[i] = message[i];
        }
        
    }
}

void caesar_decode(char *message, int msg_size, char key, char *translated){
    char i;
    for(i = 0; i < msg_size; i++){

                if(message[i] >= 65 && message[i] <= 90){
            translated[i] =  caesar_do_translation(message[i], (-1 * key));
        }
        else{
            translated[i] = message[i];
        }
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

int caesar_get_key(void){
    int key;
    printf("\n\nPlease enter a key: ");
    scanf("%d", &key);
    return key;
}

/********************************   Attack Caeser cipher *******************************/

void do_casesar_brute_force(void){
    printf("Brute Force\n\n");
    char cipher[] = "EPDE";
    char msg_size = 4;
    char translated[msg_size];

    char k;
    for(k = 1; k < 26; k++){
        printf("%d: ", k);
        caesar_decode(cipher, msg_size, k, translated);
        output(translated, 4);
        printf("\n");
    }
}


/********************************   SUBSTITUTION CIPHER *******************************/


void substitution_encode(char *message, int msg_size, char *key, char *translated){

    char i;
    for(i = 0; i < msg_size; i++){
        char position = message[i];
        if(position > 65){
            position -= 65;
            translated[i] =  key[position];
        }
        else{
            translated[i] = position;
        }
    
    }
}

void substitution_decode(char *message, int msg_size, char *key, char *translated){
    char i;
    for(i = 0; i < msg_size; i++){
        char letter = message[i];
        if(letter > 64){
            char p;
            for(p = 0; p < 26; p++){
                if(letter == key[p]){
                    translated[i] = p + 65;
                }
            }
        }
        else{
            translated[i] = letter;
        }
    }
    }

void do_substitution_cipher(char *message, int msg_size, char *key, char mode){
    char translated[msg_size];
    if(mode ==1){
        substitution_encode(message, msg_size, key, translated);
    }
    else if(mode == 2){
        substitution_decode(message, msg_size, key, translated);
    }
    output(translated, msg_size);
}




/********************************  MENU FUNCTIONS *******************************/

/********************************   Get input from user *******************************/

int get_input(char *message){
    printf("Please enter your message: ");
    scanf(" %[^\n]s", message);
    int msg_size = strlen(message);
    sanitize(message, msg_size);
    return msg_size;
}


void output(char *message, int msg_size){
    char i;
    for(i = 0; i < msg_size; i++){
        printf("%c", message[i]);
    }
}

void sanitize(char *message, int msg_size){
    char i;
    for(i = 0; i < msg_size; i++){
        if(message[i] >= 97 && message[i] <= 122){
            message[i] -= 32;
        }
    }
}

void menu(void){
        int flag = -1;
        char message[100], key, key_sub[30];
        int msg_size;
        printf("Press one (1) to encode with the caesar cipher\n");
        printf("Press two (2) to decode with the caesar cipher\n");
        printf("Press three (3) to encode with the substituion cipher\n");
        printf("Press three (4) to decode with the substituion cipher\n");
        printf("Your answer: ");
        scanf(" %d", &flag);

        switch(flag){
            case 1:;
            printf("\n");
            msg_size = get_input(message);
            key = caesar_get_key();
            do_caesar_cipher(message, msg_size, key, 1);
            break;

            case 2:;
            printf("\n");
            msg_size = get_input(message);
            key = caesar_get_key();
            do_caesar_cipher(message, msg_size, key, 2);
            break;

            case 3:;
            printf("\n");
            msg_size =  get_input(message);
            //key_sub = "PHQGIUMEAYLNOFDXJKRCVSTZWB";
            do_substitution_cipher(message, msg_size, key_sub, 1);
            break;

            case 4:;
            printf("\n");
            msg_size  = get_input(message);
            //key_sub = "PHQGIUMEAYLNOFDXJKRCVSTZWB";
            do_substitution_cipher(message, msg_size, key_sub, 2);
            break;

            default:
            printf("\n\n");
            printf("Invalid entry: Please try again.");
            printf("\n\n");
            menu();
        }
}
