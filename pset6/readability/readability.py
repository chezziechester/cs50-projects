from cs50 import get_string

# use the coleman formula to calculate the grade


def coleman(letters, words, sentences): 
    per100 = words/100
    grade = 0.0588 * (letters/per100) - 0.296 * (sentences/per100) - 15.8
    return round(grade)


wordCount = 1
letterCount = 0
sentenceCount = 0

s = get_string("Text: ")

# iterates through the characters in the string, checks them against the strings
for c in s:
    if " " == c:
        wordCount += 1
    if "?" == c or "." == c or "!" == c:
        sentenceCount += 1
    if c.isalpha():
        letterCount += 1

grade = coleman(letterCount, wordCount, sentenceCount)
if grade <= 1:
    string = "Before Grade 1"
elif grade >= 16:
    string = "Grade 16+"
else:
    string = f"Grade { grade }"
    
print(f"{ string }")
