from cs50 import get_string


def main():
    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    grade = calculate_grade(letters, words, sentences)
    print_grade(grade)


# Counts text's letters
def count_letters(text):
    counter = 0
    for i in range(len(text)):

        # Checks for letters
        if (text[i] >= 'A' and text[i] <= 'Z') or (text[i] >= 'a' and text[i] <= 'z'):
            counter += 1

    return counter


# Counts text's words
def count_words(text):
    counter = 0
    for i in range(len(text)):

        # Checks for empty spaces signaling the word's end
        if text[i] == ' ':
            counter += 1

    counter += 1
    return counter


# Counts text's sentences
def count_sentences(text):
    counter = 0
    for i in range(len(text)):

        # Checks for punctiation signaling the sentence's end
        if text[i] == '.' or text[i] == '!' or text[i] == '?':

            counter += 1

    return counter


# Calculates text's grade
def calculate_grade(letters, words, sentences):

    # Calculates the average of letters per 100 words
    l = letters / words * 100
    # Calculates the average of sentences per 100 words
    s = sentences / words * 100
    # The Coleman-Liau index rounded
    index = round(0.0588 * l - 0.296 * s - 15.8)

    return index


# Prints grade with the right formatting
def print_grade(grade):
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


main()