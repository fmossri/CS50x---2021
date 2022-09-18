
#include <stdio.h>

int main(void)
{
    int hash = (('b' - 97) * 26) + ('a' - 97);
    int a = ('a' - 97) * 26;
    int b = ('z' - 97);
    int c = 'z';
    printf("%i - %i - %i - %i\n", hash, a, b, c);

    hash = (('z' - 97) * 676) + (('z' - 97) * 26) + ('z' - 97);

    printf("%i\n", hash);
}

