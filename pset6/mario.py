from cs50 import get_int

def get_height():
    h = get_int("Height: ")
    return h

def block(a, n):
    for i in range(n):
        print(f"{a}", end = "")

def make(h, s):
    block(" ", s - h)
    block("#", h)
    print("  ", end = "")
    block("#", h)
    print()

def draw(h, s):
    if h is 1:
        make(h, s)

    else:
        draw(h - 1, s)
        make(h, s)

def main():
    height = get_height()
    if height > 8 or height < 1:
        main()
    else:
        draw(height, height)

main()