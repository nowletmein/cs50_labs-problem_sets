#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


string encoder(string key, string text);
bool check_char(string text);


string UPPERLETTERS[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};


int main(int argc, string argv[])
{

//checking for to mutch arguments error
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

//error check
    if (check_char(argv[1]) == false)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


//geting the text
    string text = get_string("plaintext: ");

//encodeing the text

    string answer = encoder(argv[1], text);

    printf("ciphertext: %s\n", answer);

    return 0;
}

bool check_char(string text)
{
//checking for lenght errors
    int len = strlen(text);

    if (len != 26)
    {
        return false;
    }

//checking for type errors

    for (int i = 0; i < len; i++)
    {
        if (!isalpha(text[i]))
        {
            return false;
        }


//checking for duplicates
        for (int y = i + 1; y < len; y++)
        {
            if (text[i] == text[y])
            {
                return false;
            }
        }
    }


    return true;
}

string encoder(string key, string text)
{

//convertink key to uppercase

    for (int j = 0; j < strlen(key); j++)
    {
        key[j] = toupper(key[j]);
    }
//encodeing
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            text[i] = key[text[i] - 65];
            text[i] = toupper(text[i]);
        }

        if (islower(text[i]))
        {
            text[i] = key[text[i] - 97];
            text[i] = tolower(text[i]);
        }
    }

    return text;
}