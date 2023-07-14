#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include<string.h>
#include<math.h>

int letters(string text);
int sentence(string text);
int wcount(string text);

int main(void)
{
//geting the input
    string Text = get_string("Text: ");
//counting sentences
    int numsentence = sentence(Text);

//counting words
    int wordc = wcount(Text);

    //counting letters

    int letterc = letters(Text);

//Coleman-Liau index  formula:
//index = 0.0588 * L - 0.296 * S - 15.8

    double L = (double)letterc / (double)wordc * 100;

    double S = (double)numsentence / (double)wordc * 100;

    double answer = (0.0588 * L) - (0.296 * S) - 15.8;


    int finalanswer = round(answer);

//printing the readability of the sentence   
    if(finalanswer > 16){
        printf("Grade 16+\n");
    }else if(finalanswer < 1){
        printf("Before Grade 1\n" );
    }
    else
    {
    printf("Grade %i\n" , finalanswer );
    }
}


int letters(string text)
{
    int count = 0;
    for(int i= 0; i < strlen(text); i++)
    {
        if(isalpha(text[i])){
            count++;
        }
    }
    return count;
}

int wcount(string text)
{
    int count = 0;
    for(int i= 0; i < strlen(text); i++)
    {
        if(isspace(text[i])){
            count++;
        }
    }
    count++;
    return count;
}
//63 33 46

int sentence(string text){
    int count = 0;

    for(int i= 0; i < strlen(text); i++)
    {
        //63 and 33 and 46 are the ASCII numbers of the  ! . ? symbols
        if(((text[i] == 63) || (text[i] == 33) || (text[i] == 46))){
            count++;
        }
    }
    return count;
}