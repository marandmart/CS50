from sys import argv
from csv import reader

def main():
    # checks if the parameters were given correctly
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit()

    # opens the sequence file as a string
    dna = (open(argv[2], "r")).readline()

    # open the csv file
    input_file = reader(open(argv[1]))

    # nests lists within the data list for each row using list comprehension to extract the csv data
    data = [row for row in input_file]

    # removes the first list from within data and saves it to a header variable, then slices it to remove the name header
    header = data.pop(0)[1::]

    # uses list comprehension to extract the names from the data list
    names = [element.pop(0) for element in data]

    # call the check pattern funtion through list comprehension and return a list of string numbers with the results
    pattern = [str(check_pattern(dna, str_head)) for str_head in header]

    # prints the result for the query
    print_result(data, names, pattern)

# function used to check a pattern in a dna sequence
def check_pattern(dna_seq, str_seq):
    # set the repetition number to 1
    repetition = 1
    # uses the find function to the check if the pattern exists in the dna sequence
    test = dna_seq.find(str_seq * repetition)
    # if test returns -1, then the repetition doesn't exist and returns 0
    if test == -1:
        return 0
    else:
        while test != -1:
            # keeps growing the repetition variable by 1
            repetition += 1
            # keeps trying to find larger repetitions of the dna sequence. If it doesn't find it, test will be equal to -1
            test = dna_seq.find(str_seq * repetition)
        # substracts the addition from the last loop and returns the number of repetitions
        return repetition - 1

# looks for the winner in the data list
def print_result(data_seqs, ppl_names, pattern_seq):
    # set an index variable
    idx = 0
    # a for loop to compare each of the lists within the data list
    for i in data_seqs:
        # if the list is equal to the pattern sequence found in the last function
        if i == pattern_seq:
            # it prints the name of the person on the names list through the index variable
            print(ppl_names[idx])
            # finishes the function's work
            break
        idx += 1
    # if the idx variable is equal to the ammount of lists within the data sequence, it means that that are no matches
    if idx == len(data_seqs):
        print("No match")

main()
