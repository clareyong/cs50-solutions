#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char substitute(char c, string mapping);
int char_index(char c);

int main(int argc, string argv[])
{
    //printf("%c\n",substitute('z', "YTNSHKVEFXRBAUQZCLWDMIPGJO"));

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
            return 1;
    }
    bool is_letter_used[26] = {false};
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        //argv[1][i] = argv[1][i];
        //if (is_letter_used[char_index(i)] == argv) {
        // printf("putting %c into ", argv[1][i]);
        // for (int j = 0; j < 26; j++) {
        //     printf("%c: %c, ", j+'a', is_letter_used[j]?'#':' ');
        // }
        // printf("\n");
        if (is_letter_used[char_index(argv[1][i])]) { // if this char_idx has been used before
            return 1;
        }
        is_letter_used[char_index(argv[1][i])] = true;
    }

    printf("%d\n", is_letter_used[25]);

    string message = get_string("plaintext: ");
    for (int i = 0; i < strlen(message); i++)
    {
        if (message[i] >='A' && message[i] <= 'Z')
            message[i] = toupper(substitute(message[i], argv[1]));
        else if (message[i] >= 'a' && message[i] <= 'z')
            message[i] = tolower(substitute(message[i], argv[1]));
//        printf("%d %d\n", i, message[i]);
    }
    printf("ciphertext: %s\n", message);


        // if (message[i] >= 'a' && message[i] <= 'z')
        // {
        //     printf("%c", (message[i], atoi(argv[1])));
        // }
        // else if (message[i] >= 'A' && message[i] <= 'Z')
        // {
        //     printf("%c", offsetCaps(message[i], atoi(argv[1])));
        // }
        // else
        // {
        //     printf("%c", message[i]);
        // }
    //printf("\n");

}

// substitute substitues the character with those from user

char substitute(char c, string mapping)
{
    if (c >= 'a' && c <= 'z')
        return mapping[c - 'a'];
    else if (c >= 'A' && c <= 'Z')
        return mapping[c - 'A'];
    else
        return 1;
}

int char_index(char c)
{
    if (c >='a' && c <= 'z')
        return (c - 'a');
    else if (c >= 'A' && c <= 'Z')
        return (c - 'A');
    else
        return -1;
}