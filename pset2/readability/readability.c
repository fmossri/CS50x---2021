>#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_grade(int letters, int words, int sentences);
void print_grade(int grade);


//Main function. Prompts the user for a text, and returns its reading grade level in the north american standard
int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int grade = calculate_grade(letters, words, sentences);
    print_grade(grade);
}


//Diferentiates letters from other symbols and counts them
int count_letters(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            counter++;
        }
        else
        {

        }
    }
    return counter;
}


//Counts words by calculating the number of spaces
int count_words(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            counter++;
        }
    }
    counter++;
    return counter;
}


//Counts sentences by calculating the number of punctuation marks
int count_sentences(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}


//Calculates the grade trough the Coleman-Liau index and rounds it.
int calculate_grade(int letters, int words, int sentences)
{
    //Calculates the average of letters per 100 words
    float l = (float) letters / words * 100;
    //Calculates the average of sentences per 100 words
    float s = (float) sentences / words * 100;
    //The Coleman-Liau index rounded
    float index = round(0.0588 * l - 0.296 * s - 15.8);

    return index;
}


//Correctly prints the grades, from Before grade 1 to Grade 16+
void print_grade(int grade)
{
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}