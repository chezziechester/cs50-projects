import csv
from cs50 import SQL
from sys import argv, exit

if len(argv) != 2:
    print("Correct usage: python import.py [csv file]")

# open database
db = SQL("sqlite:///students.db")

with open(argv[1], "r") as titles:

    # read the csv file
    reader = csv.DictReader(titles)

    for row in reader:

        # parse the names into first, middle, last
        names = row['name'].split()

        # checking for middle name
        if len(names) == 3:

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       names[0], names[1], names[2], row['house'], row['birth'])

        else:

            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)",
                       names[0], names[1], row['house'], row['birth'])
