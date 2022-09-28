import cs50

cc = cs50.get_string("Number: ")

# Return True if luhn algorithm correct


def luhn(cc):
    n = "\0"
    t = 0
    for i in range(len(cc) - 2, -1, -2):  # Range enables backward iteration by defining (start, end, increment)
        
        n += str(int(cc[i])*2)

    for i in range(len(cc) - 1, -1, -2):
        n += str(int(cc[i]))
    
    for i in range(1, len(n)):  # Start at 1 because n[0] is not populated
        t += int(n[i])
    
    if t % 10 == 0:  # Modulus returns remainder
        return True
    return False
    
# Check the length and first Digits of a credit card 


def check(cc):
    if len(cc) == 15 and cc[0] == "3" and cc[1] in str(range(4, 7, 3)):
        return "AMEX"
    
    elif len(cc) == 13 or len(cc) == 16:
        if cc[0] == "5" and cc[1] in ("1", "2", "3", "4", "5"):  # possibly could have used str(range(cc))
            return "MASTERCARD"
        elif cc[0] == "4":
            return "VISA"
        
    return "INVALID"


# Main goes here


if luhn(cc):
    print(f"{check(cc)}")
else:
    print("INVALID")