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
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

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
    voter_count = get_int("Number of voters: ");

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
        if (strcmp(name, candidates[i]) == 0)
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 1; j < candidate_count - i; j++)
        {
            preferences[ranks[i]][ranks[i + j]] += 1;
        }
    }L
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int victory[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        victory[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }
    //bubble sort
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (victory[j] < victory[j + 1])
            {
                //update margin of victory array
                int tempVictory[j];
                tempVictory[0] = victory[j + 1];
                victory[j + 1] = victory[j];
                victory[j] = tempVictory[0];
                //update pairs array
                pair tempPair[1];
                tempPair[0] = pairs[j + 1];
                pairs[j + 1] = pairs[j];
                pairs[j] = tempPair[0];
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }
    return;
}

bool cycle(int winner, int loser)
{
    /*If edge already exists, return false: if this parameter returns true,
    this indicates that the remaining edge creates a cycle. Returning false
    would result in the rest of the recursive stack returning false, therefore
    returning false overall.*/
    if (locked[loser][winner] == 1)
    {
        return 0;
    }
    /*Iterates through candidates to check for other edges where the winning
    candidate is the losing candidate.*/
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner] == 1)
        {
            /*checks to see if the previous edge makes a cycle with the given
            losing candidate, if so, the base case will return as false; otherwise,
            the conditional won't detect any previous edges, meaning it returns
            true, resulting in all of the function returning true.*/
            if (cycle(i, loser))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;

}

// Print the winner of the election
void print_winner(void)
{
    int counter;
    for (int i = 0; i < candidate_count; i++)
    {
        counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (counter == candidate_count - 1 && locked[j][i] == 0)
            {
                printf("%s\n", candidates[i]);
            }
            counter++;
        }
    }
    return;
}