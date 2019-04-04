#include <stdio.h>

//Prototype
char translate(char *alphabet, char letter);
char encode(char *alphabet, char letter, char key);

//Main
int main(){

char alphabet[26] = "abcdefghijklmnopqrstuvwxys";

char letter = 97; //97 = a, 122 = z (for testing)
char * pAlphabet = &alphabet;
char key = 5;

char test = encode(pAlphabet, letter, key);

printf("%c", alphabet[test]);

return 0;
}


//************************************************
char translate(char *alphabet, char letter){
/*
AIM: to translate a given letter from ascii into an internal alphabet from which all calculations will be made. This will make the flow easier.

Arguments:
    -This function accepts a pointer to a list of type char, which contains the alphabet that the program will use.
    -It also accepts a letter of type char, which it will match inside the alphabet.
*/
    //Will infinite loop if passed value outide of a:z
    
    //To ensure the while loop always fires
    char position = -1;
    

    while(position < 0){//While a match has not been found
        char x; //Loop counter
        for(x = 0; x < 26; x++){
            if(letter == alphabet[x]){
                position = x;
            }
        }
    }
    return(position);
}

//************************************************
char encode(char *alphabet, char letter, char key){
    char position = translate(alphabet, letter);
    char encoded_position = (position + key)%26;
    return encoded_position;
}



/*

//THIS WORKS!

//(m - 65 + 260) - k)%26 + 65

There is really interesting possibilities in this. Future investigaiton required -- too tired now!
*/
