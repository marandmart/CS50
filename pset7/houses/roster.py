from sys import argv
from cs50 import SQL

# checks for the correct input of the command line argument
if len(argv) != 2:
    print("Usage: python roster.py housename")
    exit()

# gives us access to the students.db database
db = SQL("sqlite:///students.db")

# reads from the database the data of a particular house and returs that as a dictionary
rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

# for each row in the dictionary
for row in rows:
    # Checks if the table has a middle name
    if row["middle"] == None:
        # print the formated values
        print(row["first"], row["last"] + ",", "born", row["birth"])
    # Everyone else that doesn't have a middle name
    else:
        # print the formated values
        print(row["first"], row["middle"], row["last"] + ",", "born", row["birth"])