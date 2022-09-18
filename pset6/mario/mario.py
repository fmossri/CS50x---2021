from cs50 import get_int

# Sets height variable for prompting the user
height = 0

# Keeps prompting the user for a correct height
while height < 1 or height > 8:
    height = get_int("Height: ")

# Draws collumns
for i in range(height):

    # Draws left-side spaces
    for j in range(height - 1, i, -1):
        print(" ", end="")
        j -= 1
    # Draws left-side blocks
    for k in range(i + 1):
        print("#", end="")
        k += 1
    # Draws middle spaces
    print("  ", end="")

    # Draws right-side blocks
    for l in range(i + 1):
        print("#", end="")
        l += 1

    # Prints a new line
    print("")
    i += 1