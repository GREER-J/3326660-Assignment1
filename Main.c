#include <stdio.h>
#include <stdlib.h>


//Caesar Prototypes
char caesar_do_translation(char letter, char key);
void caesar_encode(char *message, int msg_size, char key, char *translated);
void caesar_decode(char *message, int msg_size, char key, char *translated);
void do_caesar_cipher(char *message, int msg_size, char key, char mode);
void do_casesar_brute_force(void);


//Substitution Prototypes
void substitution_encode(char *message, int msg_size, char *key, char *translated);
void substitution_decode(char *message, int msg_size, char *key, char *translated);
void do_substitution_cipher(char *message, int msg_size, char *key, char mode);

//Menu Prototypes
char get_input(void);
void output(char *message, int msg_size);
void menu(void);


//Main
int main(){
    menu();
/*
    //Substitution
char key[] = "PHQGIUMEAYLNOFDXJKRCVSTZWB";
char message[] = "TEST MESSAGE";
//char message[] = "CIRC OIRRPMI";
int msg_size = sizeof(message) / sizeof(message[0]) -1;
char translated[msg_size];

do_substitution_cipher(message, msg_size, key, 1);

    //do_casesar_brute_force();
    //do_caesar_cipher(message, msg_size, key, 1);

    //get_input();
    */
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

void menu(void){
    int flag = -1;
    while(flag == -1){
        printf("Press one (1) to encode with the caesar cipher\n");
        printf("Press two (2) to decode with the caesar cipher\n");
        printf("Press three (3) to encode with the substituion cipher\n");
        printf("Press three (4) to decode with the substituion cipher\n");
        printf("Your answer: ");
        scanf("%d", &flag);

        switch(flag){
            case 1:;
            printf("\n");
            char message[] = "TEST";
            char msg_size = sizeof(message) / sizeof(message[0]) -1;
            char key = 11;
            do_caesar_cipher(message, msg_size, key, 1);
            break;

            case 2:;
            printf("\n");
            char message_a[] = "EPDE";
            char msg_size_a = sizeof(message_a) / sizeof(message_a[0]) -1;
            char key_a = 11;
            do_caesar_cipher(message_a, msg_size_a, key_a, 2);
            break;

            case 3:;
            printf("\n");
            char message_b[] = "TEST";
            char msg_size_b = sizeof(message_a) / sizeof(message_a[0]) -1;
            char key_b[] = "PHQGIUMEAYLNOFDXJKRCVSTZWB";
            do_substitution_cipher(message_b, msg_size_b, key_b, 1);
            break;

            case 4:;
            printf("\n");
            char message_c[] = "CIRC";
            char msg_size_c = sizeof(message_a) / sizeof(message_a[0]) -1;
            char key_c[] = "PHQGIUMEAYLNOFDXJKRCVSTZWB";
            do_substitution_cipher(message_b, msg_size_b, key_b, 2);
            break;
        }
    }
}
