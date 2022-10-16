import csv
from sys import argv, exit


# checks for proper input
if len(argv) != 3:
    print("Correct usage: dna.py [csv] [txt]")
    exit(1)

# read the csv file into dictionaries
database = csv.DictReader(open(argv[1]))

# read the txt file into a string
with open(argv[2]) as f:
    sequence = f.read()

# inefficient way to retrieve the keys lmao
STR = {}
x = 0
for row in database:
    STR[x] = row
    x += 1

# create list to contain highest consecutive count of each STR
highestCount = []

for i in STR[0].keys():
    if i == 'name':
        continue
    
    # check if STR is even in the sequence
    if sequence.find(i) == -1:
        highestCount.append(0)
        continue
    
    # create list to contain count
    count = [0] * len(sequence)
    start = 0
    
    while sequence[start:].find(i) != -1:
        # get the "lowest index" of the chain of consecutive repeats
        # need to add "start" to find() because find() only returns index of SUBSTRING, not the entire string itself
        lowestIndex = sequence[start:].find(i) + start
        count[lowestIndex] += 1
        # bump the start variable to the next STR for checking
        start = lowestIndex + len(i)
        
        while True:
            # check if the substring is equal to the STR
            if sequence[start:start + len(i)].find(i) == -1:
                break
            else:
                count[lowestIndex] += 1
                start += len(i)

    highestCount.append(max(count))
 

for row in STR:
    x = 0
    dictionary = STR[row]
    for i in dictionary.keys():
        if i == 'name':
            continue
        
        # check to see if it is checking the last entries, if last entry matches then print out name
        elif highestCount[x] == int(dictionary[i]) and x == len(dictionary.keys()) - 2:
            print(dictionary['name'])
            exit(0)
        
        # iterating through to check if the amount of consecutive repeats match
        elif highestCount[x] == int(dictionary[i]):
            x += 1
            
        else:
            break

print("No match.")
exit(0)