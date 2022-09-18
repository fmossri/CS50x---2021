#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt the user for the piramids height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    //prints collumns
    for (int i = 0; i < height; i++)
    {
        //prints piramid rows - left piramid
        for (int j = height - 1; j > i ; j--)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        //prints the interval between piramids
        printf("  ");
        //prints right piramid
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}