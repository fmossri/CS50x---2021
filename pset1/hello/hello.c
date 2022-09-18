#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Hello, World! Welcome;\n");
    //Gets username and greets
    string nome_usuario = get_string("Please, type your name: ");
    printf("Good day to you, %s!\n", nome_usuario);
}