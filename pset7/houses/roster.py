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
        open("students.db")
    except FileNotFoundError:
        print("File not Found")
        return False
    return True


def main():
    if not checkinput():
        sys.exit()
    
    roster = db.execute(
        f"SELECT DISTINCT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", sys.argv[1])
            
    for i in roster:    
        if i['middle'] == None:
            print(f"{i['first']} {i['last']}, born {i['birth']}")
        else:
            print(f"{i['first']} {i['middle']} {i['last']}, born {i['birth']}")


main()