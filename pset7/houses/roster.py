from sys import argv, exit
from cs50 import SQL

if len(argv) != 2:
    print("Correct usage: python roster.py [house]")

db = SQL("sqlite:///students.db")

# retrieve the necessary information as a list of dictionaries
query = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

for i in range(len(query)):
    # check for a middle name
    if query[i]['middle'] == None:

        print(f"{query[i]['first']} {query[i]['last']}, born {query[i]['birth']}")

    else:
        print(f"{query[i]['first']} {query[i]['middle']} {query[i]['last']}, born {query[i]['birth']}")
