#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Check all candidates.
    for (int i = 0; i < candidate_count; i++)
    {
        // If valid:
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Record by filling preferences array with ranks (i = candidate):
            preferences[voter][rank] = i;

            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // The function should update the number of votes each candidate has at this stage in the runoff.
    // Scan through votes
    for (int i = 0; i < voter_count; i++)
    {
        // Scan through candidates
        for (int j = 0; j < candidate_count; j++)
        {
            // Make a new int, which holds the most preferred candidate not eliminated.
            int preferred_candidate = preferences[i][j];

            if (candidates[preferred_candidate].eliminated == false)
            {
                // add vote to the preferred candidate.
                candidates[preferred_candidate].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Making an int declaring what would be a majority
    int majority = round(voter_count / 2);
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if anybody has more votes than majority
        if (candidates[i].votes > majority)
        {
            // if they do, declare them the winner by printf + true
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // if no majority
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Assign minimum to whatever votes the first candidate has
    int min_votes = candidates[0].votes;
    // Scan through to check if anybody has less
    for (int i = 0; i < candidate_count; i++)
    {
        // change them to minimum if they do
        if (candidates[i].votes <= min_votes && candidates[i].eliminated == false)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Scan through all candidates.
    for (int i = 0; i < candidate_count; i++)
    {
        // check if they got the least amount of votes
        if (candidates[i].votes == min)
        {
            // eliminate if they do
            candidates[i].eliminated = true;
        }
    }
}