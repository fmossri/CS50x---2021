#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int pop_inicial;
    do
    {
        pop_inicial = get_int("Start size: ");
    }
    while (pop_inicial < 9);

    // TODO: Prompt for end size
    int pop_desej;
    do
    {
        pop_desej = get_int("End size: ");
    }
    while (pop_inicial > pop_desej);

    // TODO: Calculate number of years until we reach threshold
    int anos = 0;
    int n = pop_inicial;
    while (n < pop_desej)
    {
        n = n + (n / 3) - (n / 4);
        anos++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", anos);
}