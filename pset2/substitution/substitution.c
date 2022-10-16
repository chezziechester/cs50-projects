#include <cs50.h>
#include <stdio.h>
#include <string.h>

//checks every following letter against previous letters
bool checkForUnique(string key) 
{
    for (int i = 1; i < 25; i++) 
    {
        for (int j = 1; j <= i; j++) 
        {
            if (key[i] == key[i - j]) 
            {
                return 1;
            }
        }
    }
    return 0;
}

//checks if every character is a letter
bool checkForNonAlphabet(string key) 
{
    for (int i = 0; i < 26; i++) 
    {
        if (!((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122))) 
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, string argv[]) 
{

    //copies key into another string
    string key = argv[1];

    //checks to see if two arguments were entered
    if (argc != 2) 
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    //checks to see if the second argument is 26 letters long
    else if (strlen(argv[1]) != 26) 
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    else if (checkForUnique(key)) 
    {
        printf("Key must contain unique characters.\n");
        return 1;
    }
    
    else if (checkForNonAlphabet(key)) 
    {
        printf("Key must contain only alphabetical letters.\n");
        return 1;
    }
    
    //gets string from user
    string plainText = get_string("plaintext: ");
    //create integer array to refer to index within key
    int numberText[strlen(plainText)];

    //iterates through all characters of the string
    for (int i = 0, n = strlen(plainText); i < n; i++) 
    {
        //iterates through the letters of the alphabet until it matches, then corresponds to letter of alphabet (starting with 0)
        for (int j = 0; j < 26; j++) 
        {
            if (plainText[i] == j + 65 || plainText[i] == j + 97) 
            {
                numberText[i] = j;
                break;
            }
            //was used for something before but now irrelevant, keeping it just in case
            else 
            {
                numberText[i] = 27;
            }
        }
    }

    printf("ciphertext: ");
    
    //iterates through the printing
    for (int i = 0, n = strlen(plainText); i < n; i++) 
    {
        //checks to see if the character within key is UPPERCASE
        if (key[numberText[i]] >= 65 && key[numberText[i]] <= 90) 
        {
            //checks to see if character within entered string is UPPERCASE
            if (plainText[i] >= 65 && plainText[i] <= 90) 
            {
                printf("%c", key[numberText[i]]);
            }
            //checks to see if character within entered string is LOWERCASE
            else if (plainText[i] >= 97 && plainText[i] <= 122) 
            {
                printf("%c", key[numberText[i]] + 32);
            }
            //leaves other characters alone
            else 
            {
                printf("%c", plainText[i]);
            }
        }
        //checks to see if the character within key is LOWERCASE
        else if (key[numberText[i]] >= 97 && key[numberText[i]] <= 122) 
        {
            if (plainText[i] >= 65 && plainText[i] <= 90) 
            {
                printf("%c", key[numberText[i]] - 32);
            }
            else if (plainText[i] >= 97 && plainText[i] <= 122) 
            {
                printf("%c", key[numberText[i]]);
            }
            else 
            {
                printf("%c", plainText[i]);
            }
        }
    }
    printf("\n");

}