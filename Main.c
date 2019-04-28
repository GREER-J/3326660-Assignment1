
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
int get_input(char *message, char *code, char *order);
void output(char *message, int msg_size);
void sanitize(char *message, int msg_size);
int get_orders(char *message, int msg_size, char *code, char *order);
void menu(char *message, char code, char order, int msg_size);


//Main
int main(void) {
    char message[1000],key[27], order, code = 0;
    int msg_size = get_input(message, &code, &order);
    menu(message, code, order, msg_size);
    printf("\n\n");
    output(message, msg_size);
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
    printf("\nPlease enter a key: ");
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

int get_input(char *message, char *code, char *order){
    FILE *input;
    input = fopen("input.txt", "r");
    fscanf(input, "%[^\n]s", message);
    int msg_size = strlen(message);
    int offset = get_orders(message, msg_size, code, order);
    msg_size = offset;
    sanitize(message, msg_size);
    return msg_size;
}


void output(char *message, int msg_size){
    int i;
    for(i = 0; i < msg_size; i++){
        printf("%c", message[i]);
    }
}

void sanitize(char *message, int msg_size){
    int i;
    for (i = 0; i < msg_size; i++){
        if (message[i] >=97 && message[i] <=122){
            message[i] -= 32;
        }
    }
}

int get_orders(char *message, int msg_size, char *code, char *order){
    int i;
    int offset;
    for(i = 0; i < msg_size; i++){
        if(message[i] == 58){
            offset = i;
            *code = message[i + 1];
            *order = message[i + 3];
        }
    }
    return offset;
}

void menu(char *message, char code, char order, int msg_size){
    if (code == 99 || code == 67){
        int key = message[msg_size +5];
        if(order == 101 || order == 69){
            //do caessar cipher
            printf("Caesar Encode");
            //do_caesar_cipher..........
        }
        else if(order == 68 || order == 100){
            printf("Caesar Decode");
            //do_caesar_cipher..........
        }
        else{
            printf("\n\nSomething went wrong!");
        }
    }
    else if (code == 83 || code == 115){
        char key[27];

        int i;
        for(i = msg_size + 5; i < msg_size + 31; i++){
            printf("%c", message[i]);
        }
        //Substitution
        if(order == 101 || order == 69){
            //do sub cipher
            printf("\n\nSUB Encode");
        }
        else if(order == 68 || order == 100){
            printf("\n\nSUB Decode");
        }
        else{
        printf("\n\nSomething went wrong!");
    }
    }
    else{
        printf("\n\nSomething went wrong!");
    }
}
