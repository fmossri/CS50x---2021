import csv
import sys

people = []
str_list = []
sequence = ""
counts = []


def main():

    # Checks for the correct usage:
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    load()
    count_str()
    check_dna()


# Loads files into memory
def load():

    # Assigns files to file objects
    csv_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # Opens csv file and coppies it as dictionaries into a list
    with open(csv_file) as file:
        csv_reader = csv.DictReader(file)

        for line in csv_reader:
            people.append(line)

        # Stores the STRs into a list from the csv header
        global str_list
        str_list = list(csv_reader.fieldnames)
        del str_list[0]

    for i in range(len(str_list)):
        counts.append(0)

    # Opens txt file and coppies it into a string
    with open(sequence_file) as file:
        global sequence
        sequence = file.read()


# Counts STRs repetition
def count_str():

    # For each STR in str_list, looks for the STR in the given sequence
    for i in range(len(str_list)):
        str_sample = str_list[i]

        # For each of the sequence's nucleotides, checks if its the start of str_sample
        for j in range(len(sequence)):
            repetition_count = 0

            # If given STR is identified, checks for its repetition
            if sequence[j: (j + len(str_sample))] == str_sample:
                k = 0

                while sequence[j + k: (j + k + len(str_sample))] == str_sample:
                    repetition_count += 1
                    k += len(str_sample)

                # If a given number of repeatitions is bigger than the original biggest, assign it as the biggest
                if repetition_count > counts[i]:
                    counts[i] = repetition_count


# Checks if the sequence's STR counts matches anyone in the "people" list
def check_dna():

    # For each person in "people" dictionaries' list
    for i in range(len(people)):
        present_counts = 0

        # For each STR in str_list, checks if its repetition count matches given person's STR count
        for j in range(len(str_list)):
            if int(counts[j]) == int(people[i][str_list[j]]):
                present_counts += 1
        # If all STR counts matches given person's, print it's name and exit
        if present_counts == len(str_list):
            print(people[i]["name"])
            sys.exit(0)

    # If no matching person is found, say it and exit
    print("No match")
    sys.exit(0)


main()