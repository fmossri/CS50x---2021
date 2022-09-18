from cs50 import get_string

# Sets an empty card_number string
card_number = ""

# Prompts user for card number, stored as a string
while len(card_number) < 1:
    card_number = get_string("Number: ")

# calculates card_number length
card = len(card_number)

luhn = 0

# Tests 13 digit cards
if card == 13:

    # Executes luhn algorithm iterating over every other card's digit, starting from seccond-to-last
    for i in rage(11, 0, -2):

        # from seccond-to-last, multiplies every other number by 2, turns it into a string for easier manipulation
        temp = str(2 * int(card_number[i]))

        # If the product is more than one digit long, adds each digit to luhn variable
        if len(temp) > 1:
            luhn += int(temp[0]) + int(temp[1])

        # If one digit long, adds it to luhn
        else:
            luhn += int(temp)

    # Finishes luhn's algorithm by adding the remaining digits to "luhn"
    for i in range(12, -1, -2):
        luhn += (card_number[i])

    # Checks for card validity
    if luhn % 10 != 0:
        print("INVALID")

    else:
        print("VISA")

# Tests 15 digit cards
elif card == 15:
    for i in range(13, 0, -2):
        temp = str(2 * int(card_number[i]))
        if len(temp) > 1:
            luhn += int(temp[0]) + int(temp[1])
        else:
            luhn += int(temp)

    for i in range(14, -1, -2):
        luhn += int(card_number[i])

    if luhn % 10 != 0:
        print("INVALID")

    else:
        # Checks for card flag
        if int(card_number[0]) == 3:
            if int(card_number[1]) in [4, 7]:
                print("AMEX")
            else:
                print("INVALID")

# Tests 16 digit cards
elif card == 16:

    for i in range(14, -1, -2):
        temp = str(2 * int(card_number[i]))
        if len(temp) > 1:
            luhn += int(temp[0]) + int(temp[1])

        else:
            luhn += int(temp)

    for i in range(15, 0, -2):
        luhn += int(card_number[i])

    if luhn % 10 != 0:
        print("INVALID")

    else:
        # Checks for card flag
        if int(card_number[0]) == 4:
            print("VISA")
        elif int(card_number[0]) == 5:
            if int(card_number[1]) in range(1, 6):
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
else:
    print("INVALID")