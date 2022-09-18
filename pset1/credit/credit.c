#include <cs50.h>
#include <stdio.h>

void check_valid();
void card_type();
long get_card_number();
long cartao_input;

//Main function
int main(void)
{
    get_card_number();
    check_valid();
}

//Prompts the user to type a card number.
long get_card_number(void)
{
    do
    {
        cartao_input = get_long("Card number: ");
    }
    while (cartao_input < 1);
    return cartao_input;
}
//checks if the provided number is valid according to the Luhn's Algorithm; if so, calls card_type() function
void check_valid(void)
{
    long sample = cartao_input;
    if (cartao_input > 1000000000000000 && cartao_input < 10000000000000000)
    {
        //The sum of every other number's product digits
        int p1 = ((sample % 100 / 10 * 2) / 10 + (sample % 100 / 10 * 2) % 10);
        int p2 = ((sample % 10000 / 1000 * 2) / 10 + (sample % 10000 / 1000 * 2) % 10);
        int p3 = ((sample % 1000000 / 100000 * 2) / 10 + (sample % 1000000 / 100000 * 2) % 10);
        int p4 = ((sample % 100000000 / 10000000 * 2) / 10 + (sample % 100000000 / 10000000 * 2) % 10);
        int p5 = ((sample % 10000000000 / 1000000000 * 2) / 10 + (sample % 10000000000 / 1000000000 * 2) % 10);
        int p6 = ((sample % 1000000000000 / 100000000000 * 2) / 10 + (sample % 1000000000000 / 100000000000 * 2) % 10);
        int p7 = ((sample % 100000000000000 / 10000000000000 * 2) / 10 + (sample % 100000000000000 / 10000000000000 * 2) % 10);
        int p8 = ((sample % 10000000000000000 / 1000000000000000 * 2) / 10 + (sample % 10000000000000000 / 1000000000000000 * 2) % 10);

        //Luhn's Algorithm - I couldn`t figure it out how to solve style50's issues about this part
        int final_num = p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + sample % 10 + (sample / 100 % 10) + (sample / 10000 % 10)
        + (sample / 1000000 % 10) + (sample / 100000000 % 10) + (sample / 10000000000 % 10)
        + (sample / 1000000000000 % 10) + (sample / 100000000000000 % 10);

        //Final checksum - if equivalent to 0, calls card_type()
        int checksum = final_num % 10;
        if (checksum != 0)
        {
            printf("INVALID\n");
        }
        else
        {
            card_type();
        }
    }
    else if (cartao_input > 100000000000000 && cartao_input < 1000000000000000)
    {
        //The sum of every other number's product digits
        int p1 = ((sample % 100 / 10 * 2) / 10 + (sample % 100 / 10 * 2) % 10);
        int p2 = ((sample % 10000 / 1000 * 2) / 10 + (sample % 10000 / 1000 * 2) % 10);
        int p3 = ((sample % 1000000 / 100000 * 2) / 10 + (sample % 1000000 / 100000 * 2) % 10);
        int p4 = ((sample % 100000000 / 10000000 * 2) / 10 + (sample % 100000000 / 10000000 * 2) % 10);
        int p5 = ((sample % 10000000000 / 1000000000 * 2) / 10 + (sample % 10000000000 / 1000000000 * 2) % 10);
        int p6 = ((sample % 1000000000000 / 100000000000 * 2) / 10 + (sample % 1000000000000 / 100000000000 * 2) % 10);
        int p7 = ((sample % 100000000000000 / 10000000000000 * 2) / 10 + (sample % 100000000000000 / 10000000000000 * 2) % 10);

        //Luhn's Algorithm - I couldn`t figure it out how to solve style50's issues about this part
        int final_num = p1 + p2 + p3 + p4 + p5 + p6 + p7 +  + sample % 10 + (sample / 100 % 10) + (sample / 10000 % 10)
        + (sample / 1000000 % 10) + (sample / 100000000 % 10) + (sample / 10000000000 % 10)
        + (sample / 1000000000000 % 10) + (sample / 100000000000000 % 10);

        //Final checksum - if equivalent to 0, calls card_type()
        int checksum = final_num % 10;
        if (checksum != 0)
        {
            printf("INVALID\n");
        }
        else
        {
            card_type();
        }
    }
    else if (cartao_input > 1000000000000 && cartao_input < 10000000000000)
    {
        //The sum of every other number's product digits
        int p1 = ((sample % 100 / 10 * 2) / 10 + (sample % 100 / 10 * 2) % 10);
        int p2 = ((sample % 10000 / 1000 * 2) / 10 + (sample % 10000 / 1000 * 2) % 10);
        int p3 = ((sample % 1000000 / 100000 * 2) / 10 + (sample % 1000000 / 100000 * 2) % 10);
        int p4 = ((sample % 100000000 / 10000000 * 2) / 10 + (sample % 100000000 / 10000000 * 2) % 10);
        int p5 = ((sample % 10000000000 / 1000000000 * 2) / 10 + (sample % 10000000000 / 1000000000 * 2) % 10);
        int p6 = ((sample % 1000000000000 / 100000000000 * 2) / 10 + (sample % 1000000000000 / 100000000000 * 2) % 10);
        int p7 = ((sample % 100000000000000 / 10000000000000 * 2) / 10 + (sample % 100000000000000 / 10000000000000 * 2) % 10);

        //Luhn's Algorithm - I couldn`t figure it out how to solve style50's issues about this part
        int final_num = p1 + p2 + p3 + p4 + p5 + p6 + p7 +  + sample % 10 + (sample / 100 % 10) + (sample / 10 % 10) +
        (sample / 1000000 % 10) + (sample / 100000000 % 10) + (sample / 10000000000 % 10)
        + (sample / 1000000000000 % 10) + (sample / 100000000000000 % 10);

        //Final checksum - if equivalent to 0, calls card_type()
        int checksum = final_num % 10;
        if (checksum != 0)
        {
            printf("INVALID\n");
        }
        else
        {
            card_type();
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
//Identifies the card flag by its number of digits and first pair.
void card_type(void)
{
    if (cartao_input > 1000000000000 && cartao_input < 100000000000000)
    {
        int first_pair = cartao_input / 100000000000;
        if (first_pair > 39 && first_pair < 50)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (cartao_input > 100000000000000 && cartao_input < 1000000000000000)
    {
        int first_pair = cartao_input / 10000000000000;
        if (first_pair == 34 || first_pair == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (cartao_input > 1000000000000000 && cartao_input < 10000000000000000)
    {
        int first_pair = cartao_input / 100000000000000;
        if (first_pair > 39 && first_pair < 50)
        {
            printf("VISA\n");
        }
        else if (first_pair > 50 && first_pair < 56)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

