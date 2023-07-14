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
int pairpower(int index);

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
    //chacking if the candidate on the vote is an option
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int y = i + 1; y < candidate_count; y++)
        {
            preferences[ranks[i]][ranks[y]] += 1;
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int y = i + 1; y < candidate_count; y++)
        {
            if (preferences[i][y] > preferences[y][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = y;
                pair_count += 1;
            }
            else if (preferences[i][y] < preferences[y][i])
            {
                pairs[pair_count].winner = y;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    // TODO
    return;

}
int pairpower(int index)
{
    //calculateing the power of the win
    int winner = pairs[index].winner;
    int loser = pairs[index].loser;
    return preferences[winner][loser];

}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair swap;
    int i;

    for (i = 0; i < pair_count - 1; i++)
    {

        for (int y = 0; y < pair_count - i - 1; y++)
        {
            int v1 = pairpower(y);
            int v2 = pairpower(y + 1);
            if (v1 < v2)
            {
                swap = pairs[y];
                pairs[y] = pairs[y + 1];
                pairs[y + 1] = swap;
            }
        }
    }



    // TODO
    return;
}



// Lock pairs into the candidate graph in order, without creating cycles
bool cycle(int winner, int loser)
{
 //useing recursive function to determen if the lock woud create a cycle   
    if (winner == loser)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (cycle(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}

void lock_pairs(void)
{
    
    for (int i = 0; i < pair_count; i++)
    {

        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (!cycle(winner, loser))
        {

            locked[winner][loser] = true;
        }
    }
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int i;

    for (i = 0; i < candidate_count; i++)
    {
        bool check = true;
        for (int y = 0; y < candidate_count; y++)
        {
            if (locked[y][i])
            {
                check = false;
                break;
            }

        }
        if (check)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }

    // TODO
    return;
}