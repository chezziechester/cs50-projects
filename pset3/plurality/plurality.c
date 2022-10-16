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
        vote(name);

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
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //bubble sort
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count - i - 1; j++)
        {
            if (candidates[j].votes > candidates[j + 1].votes)
            {
                candidate temp[1];
                temp[0] = candidates[j + 1];
                candidates[j + 1] = candidates[j];
                candidates[j] = temp[0];
            }
        }
    }
    int numberOfWinners = 1;
    string tempWinners[candidate_count];
    tempWinners[0] = candidates[candidate_count - 1].name;
    for (int i = candidate_count - 1; i > 0; i--)
    {
        if (candidates[i].votes == candidates[i - 1].votes)
        {
            numberOfWinners += 1;
            tempWinners[candidate_count - i] = candidates[i - 1].name;
        }
        else 
        {
            break;
        }
    }
    string winners[numberOfWinners];
    for (int i = 0; i < numberOfWinners; i++)
    {
        winners[i] = tempWinners[i];
        printf("%s\n", winners[i]);
    }
    return;
}
