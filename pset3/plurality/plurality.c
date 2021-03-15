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
    //Checks all candidates in the array.
    for (int i = 0; i < candidate_count; i++)
    {
        //If the name given exist in the array, that candidate gets +1 vote
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
    //Assumes the first candidate has the most votes.
    int most = 0;
    //Checks all candidates.
    for (int i = 0; i < candidate_count; i++)
    {
        //If a candidate has more votes than the assumed "most", that candidate becomes new "most"
        if (candidates[most].votes < candidates[i].votes)
        {
            most = i;
        }
    }
    printf("%s\n", candidates[most].name);
    //Checks all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // For a condidate with a different name than the assumed most
        if (strcmp(candidates[most].name, candidates[i].name) != 0)
        {
            // If another candidate has the same ammount of votes as the one considered the most, they also get their name printed.
            if (candidates[most].votes == candidates[i].votes)
            {
                printf("%s\n", candidates[i].name);
            }
        }
    }
}

