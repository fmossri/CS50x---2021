#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int diferenca_votos(int par);
bool verifica_ciclos(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == false)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //From the preference ranks of each votter, updates the preference of a candidate over the next rank candidates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //For each pair of candidates, determines who is the winner by calculating which one is most preferred against the other, and updates pairs_count,
        //ignoring ties
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //sets a placeholder "pair matrix"
    pair hold[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            //for each pair against each pair, calculates which has the bigger margin of victory, and sorts them from bigger to smaller
            if (diferenca_votos(j) < diferenca_votos(j + 1))
            {
                hold[0] = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = hold[0];
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //For each pair of candidates, calls cycle checking
    for (int i = 0; i < pair_count; i++)
    {
        //If no cycle is found, lock the pair
        if (verifica_ciclos(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Prints the winner(s) of the election
void print_winner(void)
{
    int counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        //Looks for a candidate that has no edge ending on it.
        for (int j = 0; j < candidate_count; j++)
        {
            //If there's an edge pointing to the candidate i, he cannot be the winner, so add 1 counter
            if (locked[j][i] == true)
            {
                counter++;
            }
        }
        //If the candidate i has no counters, print it's name.
        if (counter == 0)
        {
            printf("%s\n", candidates[i]);
        }

        else
        {
            counter = 0;
        }
    }

    return;
}
//Calculates the modulus of the preference of i over j
int diferenca_votos(int par)
{
    return preferences[pairs[par].winner][pairs[par].loser] - preferences[pairs[par].loser][pairs[par].winner];
}

//Verifies if a cycle is created from the loser of a given pair
bool verifica_ciclos(int winner, int loser)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //If the loser of the given pair wins from anybody, checks if it belongs to a winning cycle to the winner of the pair
        if (locked[loser][i] == true)
        {
            //if the given recursive loser beats the given winner, there's a cycle
            if (i == winner)
            {
                return true;
            }

            //If the candidate beaten by the given recursive loser is not the given winner,
            //recursively calls the function to find out if anybody is; if somebody is, there's a cycle
            else if (verifica_ciclos(winner, i))
            {
                return true;
            }
        }
        //If the loser of the given pair doesn't beat anybody, or its beaten candidates doesn't beat anyone who beats the winner, there's no cycle
    }
    return false;
}