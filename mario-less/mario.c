
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height>8 || height<=0);

    //to print #s
    for (int i = 1; i <= height; i++)
    {
        //for column
        for (int j = 1; j <= (height-i); j++)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");

        for (int m = 1; m <= i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}