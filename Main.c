#include <stdio.h>

//Prototype
char translate(char *alphabet, char letter);

//Main
int main(){

char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char letter = 122; 
char * pAlphabet = &alphabet;

char position = translate(pAlphabet, letter);
printf("%d: %c", position, alphabet[position]);

return 0;
}


/*
AIM: to translate a given letter from ascii into an internal alphabet from which all calculations will be made. This will make the flow easier.

Arguments:
    -This function accepts a pointer to a list of type char, which contains the alphabet that the program will use.
    -It also accepts a letter of type char, which it will match inside the alphabet.
*/
char translate(char *alphabet, char letter){

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
