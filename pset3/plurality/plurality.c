#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {

        //Compares the i'th candidate name to the string name, gotten from the voter
        if (strcmp(candidates[i].name, name) == false)
        {
            //If the name is present in the cadidates list, add a vote to it
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Bubble sort
    //Creates a placeholder array for swaping while sorting
    candidate hold[candidate_count];


    //Iterates trough the candidates (candidate_count) times, and sorts from least voted to most voted
    for (int i = 0; i < candidate_count; i++)
    {
        //Compares the first candidate's votes ('j') with the next candidate's('j+1')
        for (int j = 0; j < candidate_count - 1; j++)
        {
            //Swaps out of order candidate pairs
            if (candidates[j].votes > candidates[j + 1].votes)
            {
                //assigns the higher vote-count candidate of the pair to a placeholder
                hold[0] = candidates[j];

                //assigns the lower vote-count candidate of the pair to the first position
                candidates[j] = candidates[j + 1];

                //assigns the higher vote-count candidate to the seccond position
                candidates[j + 1] = hold[0];
            }
        }
    }

    //Checks for winner and ties
    for (int i = 0; i < candidate_count; i++)
    {
        //Prints i'th candidate's name if it's vote count is equal to the most voted candidate's vote count
        if (candidates[candidate_count - 1].votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

