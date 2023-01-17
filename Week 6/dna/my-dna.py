import csv
import sys


def main():
    # Check for correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Wrong command-line input!")
        sys.exit(1)

    # Read CSV file and DNA sequence file
    str_database = read_str_database(sys.argv[1])
    dna_sequence = read_dna_sequence(sys.argv[2])

    # Find longest match of each STR in DNA sequence
    matches = {}
    for i in str_database[0]:
        matches[i] = longest_match(dna_sequence, i)

    # Check database for matching profiles
    suspect = find_suspect(str_database, matches)

    print(suspect)
    return


def read_str_database(filename):
    """Read CSV file containing STR information and return as list of dictionaries."""
    with open(filename, mode="r") as csv_file:
        csv_reader = csv.DictReader(csv_file)
        return list(csv_reader)


def read_dna_sequence(filename):
    """Read DNA sequence file and return as string."""
    with open(filename, mode="r") as dna_file:
        return dna_file.read()


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def find_suspect(str_database, matches):
    """Returns name of suspect if all values in "matches" match values in a row in "str_database", else "No Match"."""
    # In case it doesn't find matches
    suspect = 'No Match'
    # starts at 1, since its no name match
    suspect_counter = 1

    for i in range(len(str_database)):
        for j in matches:
            # Compare values in matches dictionary to values in CSV row
            if str(matches[j]) == str_database[i][j]:
                suspect_counter += 1
        # If all values in the matches dictionary match the values in the CSV row, set suspect to the name in the CSV row
        if suspect_counter == len(matches):
            suspect = str_database[i]['name']
            break
        else:
            suspect_counter = 1

    return suspect


main()
