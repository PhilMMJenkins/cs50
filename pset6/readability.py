import cs50


# get letters iterates over the string returning a value for characters using isalpha()
def get_letters(text):
    letters = ""
    for i in range(len(text)):
        if text[i].isalpha():
            letters += text[i]
    return len(letters)
    

# if by iterating over a atring you find a non space character immediately following a space
# increment a counter
def get_words(text):
    words = 1  # assume one word as input
    for i in range(len(text)):
        if not text[i].isspace() and text[i-1].isspace():
            words += 1
    return words


# counts ., !, ?
def get_sentences(text):
    sentences = 0
    for i in range(len(text)):
        if text[i] in [".", "!", "?"]:
            sentences += 1
    return sentences


# coleman liau formula returning a rounded value
def coleman_liau(letters, words, sentences):
    L = letters / words * 100
    S = sentences / words * 100
    cl = 0.0588 * L - 0.296 * S - 15.8
    return round(cl)
       
        
text = cs50.get_string("Text: ")
cl = coleman_liau(get_letters(text), get_words(text), get_sentences(text))

if cl < 1:
    print("Before Grade 1")
elif cl >= 16:
    print("Grade 16+")
else:
    print(f"Grade {cl}")