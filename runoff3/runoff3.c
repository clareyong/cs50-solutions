#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
}
candidate;

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


void use_prepared_votes() {
    string candidate_names[4] = {"Alice", "Bob", "Charlie", "Delta"};
    candidate_count = 4;
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = candidate_names[i];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
    voter_count = 4;

    vote(0, 0, "Alice");
    vote(0, 1, "Bob");
    vote(0, 2, "Charlie");
    vote(0, 3, "Delta");

    vote(1, 0, "Charlie");
    vote(1, 1, "Bob");
    vote(1, 2, "Alice");
    vote(1, 3, "Delta");

    vote(2, 0, "Bob");
    vote(2, 1, "Charlie");
    vote(2, 2, "Alice");
    vote(2, 3, "Delta");

    vote(3, 0, "Alice");
    vote(3, 1, "Charlie");
    vote(3, 2, "Delta");
    vote(3, 3, "Bob");

    // vote(4, 0, "Bob");
    // vote(4, 1, "Alice");
    // vote(4, 2, "Charlie");

    // vote(5, 0, "Charlie");
    // vote(5, 1, "Alice");
    // vote(5, 2, "Bob");

    // vote(6, 0, "Bob");
    // vote(6, 1, "Alice");
    // vote(6, 2, "Charlie");

}

int get_votes(int argc, string argv[]){
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

    return 0;
}

int main(int argc, string argv[])
{
    use_prepared_votes();

    // int err_code = get_votes(argc, argv);
    // if (err_code != 0) {
    //     return err_code;
    // }

     // DEBUG function to show preferences array after voting

    printf("=============DEBUG\n");
    printf("voter count: %i\n", voter_count);
    for (int voter = 0; voter < voter_count; voter++){
        printf("Voter %i: ", voter+1);
        for(int rank = 0; rank < candidate_count; rank++){
            int voted_cdt_idx = preferences[voter][rank]; // check from array
            printf("(%i) %s, ", rank+1, candidates[voted_cdt_idx].name);
        }
        printf("\n");
    }
    printf("=============\n");

    // Keep holding runoffs until winner exists
    while (true)
    {
        // printf("GOING\n");
        // Calculate votes given remaining candidates
        tabulate(); //function
        //printf("tabulate");

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            //printf("print_winner");
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        //printf("find_min");
        bool tie = is_tie(min);
        //printf("is tie");

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
        //printf("eliminate");

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    //printf("end");
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[j].eliminated == false)
            {
                int voted = preferences[i][j];
                candidates[voted].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count/2 && candidates[i].eliminated == false)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int candidate_min_votes = 999;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < candidate_min_votes && candidates[i].eliminated == false)
        {
            candidate_min_votes = candidates[i].votes;
            //printf("%i %s\n", candidate_min_votes, candidates[i].name);
        }
    }
    return candidate_min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min && candidates[i].eliminated == false)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            printf("%s is eliminated\n", candidates[i].name);
        }
    }
    return;
}