#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int check_arguments(int array_length, string key);
int check_symbols(string key);
int check_repeated_chars(string key);
string substitute_chars(string text, string key);


int main(int argc, string argv[])
{
    //number of given arguments
    int array_length = argc;

    //Locates valid key in the command line
    string key = argv[argc - 1];

    //Checks for all key conditions: 26 non-repeated alphabetical characters
    if (check_arguments(array_length, key) == false)
    {
        //Gets the original text from the user
        string plain_text = get_string("Plain text: ");

        //Calls for the substitution function and stores it in a string
        string cipher_text = substitute_chars(plain_text, key);

        //Prints the resulting ciphertext
        printf("ciphertext: %s\n", cipher_text);
    }
    else
    {
        return 1;
    }
}

//Checks if a key is provided, it's length and calls for character verification functions
int check_arguments(int array_length, string key)
{
    if (array_length != 2)  //Checks the number of arguments provided (argc) and accepts if and only if two are given
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    else if (strlen(key) != 26)                     //Checks the key length and accepts only 26 characters keys
    {
        printf("Key must contain 26 alphabetical characters\n");
        return 1;
    }
    else if (check_symbols(key) == true)            //Checks for symbols and rejects symbol filled keys
    {
        printf("Key must contain only alphabetical characters\n");
        return 1;
    }
    else if (check_repeated_chars(key) == true)     //Checks for repeated characters and rejects keys that contains it
    {
        printf("Key must not contain repeated characters\n");
        return 1;
    }
    return 0;
}
//Checks if the key contains non-alphabetical characters
int check_symbols(string key)
{
    int counter = 0;
    for (int i = 0, n = strlen(key); i < n; i++)                            //Iterates trough the key's characters
    {
        if (key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122)    //Checks for non-alphabetical characters
        {
            return 1;
        }
    }
    return 0;
}
//Checks if the key contains repeated characters
int check_repeated_chars(string key)
{
    int counter = 0;    //Counts repeated letters
    for (int i = 0, n = strlen(key); i < n; i++)              //iterates trough the key's characters
    {
        for (int j = 0; j < n; j++)                           //For each character, iterates trough the key's characters
        {
            if (toupper(key[i]) == toupper(key[j]) && i != j) //Checks if a key's character is repeated, excluding itself.
            {
                counter++;                                    //If a letter is repeated, adds to the counter
            }
        }
    }
    if (counter > 1)                                         //If repetition is found, rejects the key
    {
        return 1;
    }
    return 0;
}

//Substitutes each text's character by the corresponding key's character
string substitute_chars(string text, string key)
{
    for (int i = 0, n = strlen(text); i < n; i++)           //iterates trough the text
    {
        if (isalpha(text[i]) == false)                      //Checks for non-alphabetical characters and keep them as they are
        {
            text[i] = text[i];
        }
        else if (isupper(text[i]) == false)                 //Checks for lowercase letters
        {
            int j = text[i] - 97;                           //Finds lowercase letters' alphabetical position
            text[i] = tolower(key[j]);                      //Substitutes each lowercase character for its corresponding key character
        }
        else
        {
            int k = text[i] - 65;                           //Finds uppercase letters' alphabetical position
            text[i] = toupper(key[k]);                      //Substitutes each uppercase letter by it's corresponding key character
        }
    }
    return text;
}