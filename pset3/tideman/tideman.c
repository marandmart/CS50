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

// Update ranks given a new vote.
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        //If the name of the candidate is in the string array candidates, it gives ranks the position of the candidate in the candidates array.
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
    //Compares the prefered choise against the other other to. Since it's comparing, one to another, it does one less loop than the total candidate count.
    for (int i = 0; i < candidate_count; i++)
    {
        //Compares the choice at hand against the remaing options. Adds + 1 vote everytime it beats another option.
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                //Checks the values in the preferences array with the larger value and then assings it to winner or loser struct.
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count += 1;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count += 1;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Creates a array to measure how large the victory of the pair in question.
    int strength_of_victory[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strength_of_victory[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    // Creates a variable called change to start the while loop.
    int change = 1;

    //Creates a while loop to sort the pairs array in descending order.
    while (change != 0)
    {
        //Creates a replacement pair.
        pair replace;
        //Sets the change variable to zero in the beggining of every loop.
        change = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            //If there's a variable to the right larger than the one on the left, it swaps them.
            if (strength_of_victory[i + 1] > strength_of_victory[i])
            {
                int subst = strength_of_victory[i];
                strength_of_victory[i] = strength_of_victory[i + 1];
                strength_of_victory[i + 1] = subst;
                //Adds +1 to the change variable everytime there's a change of position in the strength array.
                change += 1;
                //Uses swaps that happen on the strength of victory array as reference to make the changes on the pairs array.
                replace.winner = pairs[i].winner;
                replace.loser = pairs[i].loser;
                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;
                pairs[i + 1].winner = replace.winner;
                pairs[i + 1].loser = replace.loser;
            }
        }

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //Locks the pairs accoring to the pairs struct array.
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        locked[pairs[i].loser][pairs[i].winner] = false;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //returns the winner when all the values in a line are true.
    for (int i = 0, all_true = (candidate_count - 1); i < candidate_count; i++)
    {
        int counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && locked[i][j] == true)
            {
                counter += 1;
            }
        }
        if (counter == all_true)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}