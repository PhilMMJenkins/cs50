import csv  # Access DictReader
import sys  # Access Argv
from cs50 import SQL  # Access SQL

# Initialise a database in SQL

db = SQL("sqlite:///students.db")

# Check Command Line Arguments


def checkinput():
    try:
        if len(sys.argv) != 2:
            print("Usage: python import.py FILENAME")
            return False
        open(sys.argv[1])
    except FileNotFoundError:
        print("File not Found")
        return False
    return True

# This function will parse the name for the student in row into first middle and last names


def parse_name(row):
    splitname = row["name"].split()
    if len(splitname) != 3:
        splitname.append(None)
        splitname[1], splitname[2] = splitname[2], splitname[1]
    return splitname

# Open a CSV file from the command line arguments and parse for each line


def readfile():
    with open(sys.argv[1]) as characters:
        characters_reader = csv.DictReader(characters)
        for row in characters_reader:
            
            # Separate names
            
            splitname = parse_name(row)
            
            # insert students into the SQL db
            
            db.execute(f"INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       splitname[0], splitname[1], splitname[2], row['house'], row['birth'])

        
def main():
    if not checkinput():
        sys.exit()

    readfile()


main()