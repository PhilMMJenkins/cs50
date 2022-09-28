import sys  # Access to Reader and DictReader
import csv  # access to ArgV


def get_repeats(STR, sequence):
    STRlen = len(STR)
    seqlen = len(sequence)
    count_array = [0] * seqlen
    for i in range(seqlen):  # iterate over the whole sequence
        loop = 0  # this counter will reset at the end of each STR
        counter = 0  # This counts repeats
        for j in range(seqlen - i):  # The -1 accounts for the nth item being empty
            if sequence[i + j] == STR[loop]:  # add j to i to start counting from i
                loop += 1
                if loop == STRlen - 1:  # if the nucleotides match across the repeat, increment the counter
                    counter += 1
                if loop == STRlen:  # if the loop reaches the end of the STR, and the nucleotides match, reset the counter for the next repeat
                    loop = 0
                count_array[i] = counter
            else:
                break
    return max(count_array)  # return the greatest value from the array of counts
        
        
def get_sample_dict(STRs):
    with open(sys.argv[2]) as sequence:
        sqreader = sequence.read()
        sample = {  # make an empty dictionary to store the counts of the different STRs
        
        }
        for i in range(1, len(STRs)):
            sample[f"{STRs[i]}"] = get_repeats(STRs[i], sqreader)  # populate the dict
    return(sample)
    

# Open CSV file and DNA sequence and read the contents into memory
with open(sys.argv[1]) as database:
    dbreader = csv.DictReader(database)
    STRs = dbreader.fieldnames
    sample = get_sample_dict(STRs)  # read sequence into memory here
    tmp = {  # make empty dictionary to populate and compare to sample
        
    }
    match = False
    for row in dbreader:  # iterate through the dictionaries in dbreader
        for i in range(1, len(STRs)):
            tmp[f"{STRs[i]}"] = int(row[f"{STRs[i]}"])  # populate tmp by iteration
            if tmp == sample and match == False:  # compare and ensure one output
                print(row["name"])
                match = True
    if not match:
        print("No match")