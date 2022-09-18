#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void declare_winner(int primeiro, int segundo);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    declare_winner(score1, score2);
}
//Computes the each of the word's character points value and sums it
int compute_score(string word)
{
    // TODO: Compute and return score for string
    int points_sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        //Separates the valid characters from the invalid ones
        if ((word[i] >= 65 && word[i] < 91) || (word[i] >= 97 && word[i] < 123))
        {
            //Checks if lowercase or uppercase, subtracts its ascii value so a = 0 and sums its points value from POINTS array
            char j = word[i];
            if (islower(word[i]))
            {
                points_sum += POINTS[j - 97];
            }
            else
            {
                points_sum += POINTS[j - 65];
            }
        }
    }
    return points_sum;
}
//Compares the scores and declares the winner
void declare_winner(int primeiro, int segundo)
{
    if (primeiro > segundo)
    {
        printf("Player 1 wins!\n");
    }
    else if (primeiro < segundo)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!");
    }
}