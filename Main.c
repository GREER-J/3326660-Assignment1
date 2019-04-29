
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Caesar Prototypes
char caesar_do_translation(char letter, char key);
void caesar_encode(char *message, int msg_size, char key, char *translated);
void caesar_decode(char *message, int msg_size, char key, char *translated);
void do_caesar_cipher(char *message, int msg_size, char key, char mode);
void do_casesar_brute_force(void);
int caesar_get_key(char *message, int msg_size);


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


/*-------------Main-----------*/
/*  This funciton is the start point for the whole progarm.
INPUTS: This funciton does not take any inputs.
CALCULATION: 
               1) Create a message that is 1000 characters long. This is the limit for message.
               2) Creates the variable msg_size which is used throughout the program.
               3) Creates the code and order flags used throuhout the program.
               4) Runs the menu program that executes all the functions.
OUTPUT: This code does not return anything.
*/

//Main
int main(void) {
    char message[1000],key[27], order, code = 0;
    int msg_size = get_input(message, &code, &order);
    menu(message, code, order, msg_size);
    return 0;

    
    
}

/********************************   CAESAR CIPHER *******************************/

/========================          Encode / Decode     ========================*/
    
/*-------------caesar_do_translation-----------*/
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
 
char caesar_do_translation(char letter, char key){
    char translated = ((((letter - 65) +260) + (key % 26)) % 26) + 65;
    return translated;
}

/*-------------caesar_encode-----------*/
/* This function utilises the previous function to encode a given letter with a given key
INPUT: A message to encrypt (given as an array of type char), a key (given as an intiger) - the number of letter to shift by,
        another array called translated, which the same length as the original message. The purpose of this is to keep track,
        of the translated characters.
CALCULATION:
                1) Loop through the message.
                2) Gives each letter and the key to the caesar_do_translation function in turn with the flag set to encode
                3) It then puts this new value in the same place in the "translated" list.
OUTPUT: There is no return from this function but it does populate the "tranlated" array with the encoded message
*/

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

/*-------------caesar_decode-----------*/
/* This function utilises the previous function to decode a given letter with a given key
INPUT: A message to encrypt (given as an array of type char), a key (given as an intiger) - the number of letter to shift by,
        another array called translated, which the same length as the encoded message. The purpose of this is to keep track,
        of the translated characters.
CALCULATION:
                1) Loop through the message.
                2) Gives each letter and the key to the caesar_do_translation function in turn with the flag set to decode
                3) It then puts this new value in the same place in the "translated" list.
OUTPUT: There is no return from this function but it does populate the "tranlated" array with the decoded message
*/

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

/*  This function uses the previously seen encoded and decoded funcitons to actually perform the caesar cipher.
INPUT: This funciton takes a message (as an array of type char), the size of the message (as an intiger),
       a key (given as an intiger) to shift by, and a flag called mode (an intiger).
       This mode flag is used to tell the program whether to encode or decode.
CALCULATION:
            1) Create an array called translated that is the same size as the original message (given by the intiger msg_size).
            2) check whether the flag is set to 1 or 0 and call the coresponding funciton (encode or decode) respectively.
            3) run the correct function and pass in everything it needs (the message, it's size, the key as well as the,
               "translated" array ready to be populated

OUTPUT: This function prints the translated message to the screen.
*/
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

/*-------------do_caesar_brute_force-----------*/
/*  This function is a basic attempt to brute force a message encrypted with a caesar cipher without the key.
INPUT: 
       This funciton does not take any arguments.

CALCULATION:
            1) Print the word "Brute Force" to the console so we know what it's doing. 
            2) Create an array called cipher. This is the word test hard coded with a key of 16.
            3) As there are only 25 possible combinations we loop through all the posibilities and output them to the screen.
            4) The user can then look at the output and see the key (as it will be the only one that they can read!)
*/
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

/*-------------substitution_encode-----------*/
/*  This function encodes a message with a caesar cipher, when given a key and a message.
INPUT: 
       This funciton takes a message (as an array of chars), the size of the array (as an intiger), a key (as another array of chars),
       and another array called tranlated of the same lengh as the message. This function ignores punctuation.

CALCULATION:
            1) This function loops through each letter, which will be equal to a number between 97 and 120.
            2) We want the distance from 'a' of the letter so we can take away 65 (the number for a) 
            3) We then jump forward that many steps in the key and put whatever value is there into the translated array.

OUTPUT: This funciton has no output but does populate the array translated with the encoded letters.
*/
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

/*-------------substitution_decode-----------*/
/*  This function encodes a message with a caesar cipher, when given a key and a message.
INPUT: 
       This funciton takes a message (as an array of chars), the size of the array (as an intiger), a key (as another array of chars),
       and another array called tranlated of the same lengh as the message.

CALCULATION:
            1) This function loops through each letter, and finds the distance from the first letter ('a').
            2) We an actual letter so we can take that position and add 65 to it. This gets us the original letter.

OUTPUT: This funciton has no output but does populate the array translated with the decoded letters.
*/
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

/*-------------do_substitution_cipher-----------*/
/*  This function uses the previously seen encoded and decoded funcitons to actually perform the substitution cipher.
INPUT: This funciton takes a message (as an array of type char), the size of the message (as an intiger),
       a key (given as an another array) to substitute, and a flag called mode (an intiger).
       This mode flag is used to tell the program whether to encode or decode.
CALCULATION:
            1) Create an array called translated that is the same size as the original message (given by the intiger msg_size).
            2) check whether the flag is set to 1 or 0 and call the coresponding funciton (encode or decode) respectively.
            3) run the correct function and pass in everything it needs (the message, it's size, the key as well as the,
               "translated" array ready to be populated

OUTPUT: This function prints the translated message to the screen.
*/
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

/*-------------dget_input-----------*/
/*  This function is used to read data from a text document and return give the data to other programs.
INPUT: This function takes an array of type char called message, this is used to save the message as we cannot easily return arrays.
       It also takes two pointers to flags in another part of the program. These will be populated later.
CALCULATION:
            1) Open the file "input.txt".
            2) Scan everything in "input.txt" into the message array.
            3) Calculate the length of the array that we put everything into. However the problem here is that this will also,
               include the orders to the program as well as any keys. As we don't want these translated we need to find out,
               where to stop. To do this we call another function called get_orders and we give it the message (in it's entirity),
               the message size, and pointers to the two flags for it to populate.
            4) Once it hears back from the other function it gives the actaul message size to the main function.

OUTPUT: This funciton returns the message length - the extra stuff.
*/

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

/*-------------output-----------*/
/*  This function is used to print stuff to the screen.
INPUT: This function takes an array of type char called message and the length of the message (as an intiger).
CALCULATION:
            1) Loop through each letter in the message and print it to the screen.
           
OUTPUT: This funciton doesn't return anything but does print whatever it's given to the screen.
*/
void output(char *message, int msg_size){
    int i;
    for(i = 0; i < msg_size; i++){
        printf("%c", message[i]);
    }
}


/*-------------sanitize-----------*/
/*  This function is used to make sure whatever is given to our program is always in a format that we like. I.E. upper case.
INPUT: This function takes an array of type char called message and the length of the message (as an intiger).
CALCULATION:
            1) Loop through each letter in the message and check if it is an upper case or lower case letter.
            2) If it is an upper case letter leave it.
            3) If it is a lower case letter then convert it to an upper case by taking away 32.
           
OUTPUT: This funciton doesn't return anything but does change all characters in the message to be upper case.
*/

void sanitize(char *message, int msg_size){
    int i;
    for (i = 0; i < msg_size; i++){
        if (message[i] >=97 && message[i] <=122){
            message[i] -= 32;
        }
    }
}


/*-------------get_orders-----------*/
/*  This function is used to get the orders from the input.txt file.
INPUT: This function takes an array of type char called message, the length of the message (as an intiger) and two pointers to,
        flags contained in other functions.
CALCULATION:
            1) Loop through each letter in the message and look for the separator being ":".
            2) Note the position of this and look ahead a set number of places to check the order.
            3) Because we set the format of input.txt the program knows exactly where to look.
            4) Set the value of order and code to whatever is in those positions
            5) Return the point where the marker is ":" for other programs.
           
OUTPUT: This funciton returns the position of the offset marker and populates the code and orders flags.
*/
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

/*-------------get_key-----------*/
/*  This function is used to get the orders from the input.txt file.
INPUT: This function takes an array of type char called message, the length of the message (as an intiger).
CALCULATION:
            1) Loop through each letter in the message starting from the offset (msg_size).
            2) Each number has a value in ascii with 0 being 48.
            3) We take the value that's in the position and take away 48, we have then converted it to decimal.
            4) We then take the one in the 10's position and * it by ten to get the actual value.
            5) We then add this to the running total. We do the same to the 1st collumn and return the result.
           
OUTPUT: This funciton returns key for the caesar cipher for other programs.
*/

int caesar_get_key(char *message, int msg_size){
    int sum, key = 0;
    int offset = msg_size + 5;
    int i;
    for(i = 0; i < 2; i++){
        key = message[i + offset] - 48;
        if(i == 0){
            sum += (key * 10);
        }
        else{
            sum += key;
        }
    }
    return sum;
}


/*-------------Menu-----------*/
/*  This function is used to execute the program.
INPUT: This function takes an array of type char called message, the length of the message (as an intiger) and the orders and code flags.
CALCULATION:
            1) Checks the value of code. If it is a capital or lower case "C" it checks the order flag. If that Code is a C and the order,
               is a D it runs the do_caesar_cipher in decode mode and hands over the required variables. If the order is an E it runs in encode mode.
            2) If the code is a S it runs the substituion code in the same fassion.
           
OUTPUT: This funciton does not return things as it runs other functions.
*/
void menu(char *message, char code, char order, int msg_size){
    if (code == 99 || code == 67){
        int key = caesar_get_key(message, msg_size);
        if(order == 101 || order == 69){
            //do caessar cipher
            printf("Caesar Encode, key = %d\n\n", key);
            do_caesar_cipher(message, msg_size, key, 1);
        }
        else if(order == 68 || order == 100){
            printf("Caesar Decode, key = %d\n\n", key);
            do_caesar_cipher(message, msg_size, key, 2);
        }
        else{
            printf("\n\nSomething went wrong!");
        }
    }
    else if (code == 83 || code == 115){
        char key[27];

        int i;
        for(i = msg_size + 5; i < msg_size + 31; i++){
            key[i - (msg_size + 5)] = message[i];
        }
        sanitize(key, 26);

        //Substitution
        if(order == 101 || order == 69){
            //do sub cipher
            printf("\n\nSUB Encode, key: ");
            int x;
            for(x = 0; x < 27; x++){
                printf("%c", key[x]);
            }
            printf("\n\n");
            do_substitution_cipher(message, msg_size, key, 1);
        }
        else if(order == 68 || order == 100){
            printf("\n\nSUB Decode, key: ");
            int x;
            for(x = 0; x < 27; x++){
                printf("%c", key[x]);
            }
            printf("\n\n\n");
            do_substitution_cipher(message, msg_size, key, 2);
            
        }
        else{
        printf("\n\nSomething went wrong!");
    }
    }
    else{
        printf("\n\nSomething went wrong!");
    }
}

/*
//Sorting
int l;
int tmp = 51;
for(l = 1; l < 51; l +=2){
    char letter = frequency_count[l -1];
    char amount = frequency_count[l];
    if(amount < frequency_count[tmp]){
        tmp = l;
        printf("LOWER");
    }
}

printf("TMP = %d, %c: %d",tmp, frequency_count[tmp-1], frequency_count[tmp]);

}

void substitution_get_count(char *message, char *frequency_count, int msg_size){
    char c;
    for(c = 0; c < 52; c+=2){
        int sum = 0;
        char i;
        for(i = 0; i < msg_size; i++){
            if(message[i] == frequency_count[c]){
                sum += 1;
            }
        }
        frequency_count[c + 1] = sum;
    }
}

void substitution_show_frequency(char *frequency_count){
    int x;
    for(x = 0; x < 52; x+=2){
    printf("%c: %d\n", frequency_count[x], frequency_count[x +1]);
    }

    char tmp = 52;
    char y;
    for(y = 1; y < 52; y +=2){
    if(frequency_count[y] > frequency_count[tmp]){
        tmp = y;
    }
    }
}
*/
