#include <cs50.h>
#include <stdio.h>

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
bool cycle_detected(int a, bool b[]);
bool detect_source(int a);

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
        int j = 0;
        while (name[j] != '\0' && (char) name[j] == (char) candidates[i][j])
        {
            j++;
        }
        if (name[j] == '\0' && candidates[i][j] == '\0')
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
    //ranks[0] preferred over all other ranks up to candidate_count
    //therefore iterate over ranks[rank]
    for (int i = 0; i < candidate_count; i++)
    {
        //preferences[ranks[i]] will be the column for the candidate ranked i
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] != 0)
            {
                if (preferences[i][j] > preferences [j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //sort the pairs
    int s = -1;
    do
    {
        s = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                pair a = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = a;
                s++;
            }
        }
    }
    while (s != 0);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        bool nodes[candidate_count]; //nodes will be true if the candidate has been 'visited' before
        for (int z = 0; z < candidate_count; z++)
        {
            nodes[z] = false;//clear the array of nodes
        }
        if (cycle_detected(pairs[i].winner, nodes) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    //iterate over all candidates and see if they are in locked pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true &&  detect_source(i) == true)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
}

bool cycle_detected(int a, bool b[])
{
    if (b[a] == true)
    {
        return true; //the node has been visited previously and turned true
    }
    b[a] = true; //otherwise the node is being visited now and so will be turned true
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[a][i] == true && cycle_detected(i, b) == true)
        {
            return true;
        }
    }
    return false;
}

bool detect_source(int a)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[a].winner] == true) //if the winner of the indexed pair is the loser in another pair
        {
            return false;
        }
    }
    return true;
}