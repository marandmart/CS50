from sys import argv
from cs50 import SQL
import csv

# checks for the correct input of the command line argument
if len(argv) != 2:
    print("Usage: python import.py file.csv")
    exit()

# gives us access to the students.db database
db = SQL("sqlite:///students.db")

# starts reading the data
with open(argv[1], 'r') as file:
    # creates a variable to the data into
    reader = csv.DictReader(file)
    # uses a for loop to parse through the data
    for row in reader:
        # gives us a temporary variable called to receive the name data
        tmp = row["name"]
        # save the name data as a split list
        name = tmp.split()
        # receives the house data
        house = row["house"]
        # receives the birth data
        birth = row["birth"]
        # checks if the length of the name constains only first and last
        if len(name) == 2:
            # save the data into the students.db database
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[0], None, name[1], house, birth)
        # checks if the length of the name constains first, middle and last
        elif len(name) == 3:
            # save the data into the students.db database
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[0], name[1], name[2], house, birth)