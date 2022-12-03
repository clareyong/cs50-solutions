#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char offset(char c, int k);
char offsetCaps(char c, int k);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error!!\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Error!\n");
            return 1;
        }

    string message = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(message); i++)
        if (message[i] >= 'a' && message[i] <= 'z')
        {
            printf("%c", offset(message[i], atoi(argv[1])));
        }
        else if (message[i] >= 'A' && message[i] <= 'Z')
        {
            printf("%c", offsetCaps(message[i], atoi(argv[1])));
        }
        else
        {
            printf("%c", message[i]);
        }
    printf("\n");
}

// offset offsets lowercase letters by k
char offset(char c, int k)
{
    return (c - 'a' + k) % 26 + 'a';
}

// offsetCaps offsets uppercase letters by k
char offsetCaps(char c, int k)
{
    return (c - 'A' + k) % 26 + 'A';
}