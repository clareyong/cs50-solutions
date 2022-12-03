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

   // printf("======= |");
   for(int i = 0; i < candidate_count; i++){
       // printf(" %7s |", candidates[i]);
   }
   // printf("\n");
   for(int i = 0; i < candidate_count; i++){
       // printf("%7s |", candidates[i]);
       for (int j = 0; j < candidate_count; j++) {
           if (i != j)
           {
               // printf(" %7d |", preferences[i][j]);
           }
           else
           {
               // printf(" ******* |");
           }
       }
       // printf("\n");
   }

    add_pairs();
    sort_pairs();
    for (int i = 0; i < pair_count; i++)
    {
        // printf("winner is %s, loser is %s, difference is %d\n", candidates[pairs[i].winner], candidates[pairs[i].loser], (preferences[pairs[i].winner][pairs[i].loser]-preferences[pairs[i].loser][pairs[i].winner]));
    }
    lock_pairs();

    // printf("LOCK=== |");
    for(int i = 0; i < candidate_count; i++){
       // printf(" %7s |", candidates[i]);
    }
    // printf("\n");
    for(int i = 0; i < candidate_count; i++){
        // printf("%7s |", candidates[i]);
        for (int j = 0; j < candidate_count; j++) {
            // if (i != j) // printf(" %7d |", locked[i][j]);
            // else // printf(" ******* |");
        }
        // printf("\n");
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO

    for (int cdt = 0; cdt < candidate_count; cdt++)
    {
        if (strcmp(name, candidates[cdt]) == 0)
        {
            ranks[rank] = cdt;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = i+1; j < candidate_count; j++) {
            int more_preferred = ranks[i];
            int less_preferred = ranks[j];
            preferences[more_preferred][less_preferred]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    //pair_count = (candidate_count*(candidate_count-1))/2;
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j){
                continue;
            }

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // printf("winner is %s, loser is %s\n", candidates[i], candidates[j]);
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int step = 0; step < pair_count-1; step++)
    {
        for (int i = 0; i < pair_count-1; i++)
        {
            int differences_i = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            int differences_i_1 = preferences[pairs[i+1].winner][pairs[i+1].loser] - preferences[pairs[i+1].loser][pairs[i+1].winner];
            if (differences_i < differences_i_1){
                //swapping occurs if elements are not in the intended order
                pair temp = pairs[i];
                pairs[i] = pairs[i+1];
                pairs[i+1] = temp;
            }
        }

    }
    // pair to_swap = pairs[2];
    // pair swap_from = pairs[1];
    // to_swap = pairs[1];
    // swap_from = pairs[2];
    return;
}

bool has_cycle(void)
{
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++) {
        visited[i] = false;
    }
    bool on_stack[candidate_count];
    for (int i = 0; i < candidate_count; i++) {
        on_stack[i] = false;
    }

    int stack[pair_count];
    int stack_ptr = 0;

    for (int i = 0; i < candidate_count; i++) {
        // printf("Expoloring %s\n", candidates[i]);
        if (visited[i])
            continue;

        stack[stack_ptr++] = i;

        while (stack_ptr > 0) {
            int curr = stack[stack_ptr-1];
            // printf("stack:");
            for (int j = 0; j < stack_ptr; j++) {
                // printf(" %s", candidates[stack[j]]);
            }
            // printf("\n");

            if (!visited[curr]) {
                visited[curr] = true;
                on_stack[curr] = true;
            } else {
                on_stack[curr] = false;
                stack_ptr--;
            }

            for (int loser = 0; loser < candidate_count; loser++) {
                if (!locked[curr][loser]) {
                    continue;
                }

                if (!visited[loser]) {
                    // printf("adding loser %s\n", candidates[loser]);
                    stack[stack_ptr++] = loser;
                }
                if (visited[loser] && on_stack[loser]) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        pair strongest_pair = pairs[i];
        locked[strongest_pair.winner][strongest_pair.loser] = true;
        // printf("trying to lock %s %s\n", candidates[strongest_pair.winner], candidates[strongest_pair.loser]);
        if (has_cycle()) {
            // printf("pair %i has cycle\n", i+1);
            locked[strongest_pair.winner][strongest_pair.loser] = false;
            // break;
        }
        // printf("pair %i is safe\n", i+1);
    }
    return;
}


// // Print the winner of the election
// void print_winner(void)
// {
//     bool has_referred[candidate_count];
//     for (int i = 0; i < candidate_count; i++) {
//         has_referred[i] = false;
//     }

//     for (int i = 0; i < pair_count; i++) {
//         if (locked[pairs[i].winner][pairs[i].loser]) {
//             has_referred[pairs[i].loser] = true;
//         }
//     }

//     for (int i = 0; i < candidate_count; i++) {
//         if (!has_referred[i]) {
//             printf("\n%s", candidates[i]);
//             return;
//         }
//     }
//     printf("Kevin\n");
//     return;
// }

// Print the winner of the election
void print_winner(void)
{
    // Winner is the candidate with no arrows pointing to them
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}